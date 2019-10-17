/* 7zMain.c - Test application for 7z Decoder
2010-10-28 : Igor Pavlov : Public domain */

#include <string.h>
#include <stdio.h>

#include "7z.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "7zFile.h"
#include "7zVersion.h"

#ifndef USE_WINDOWS_FILE
/* for mkdir */
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <errno.h>
#endif
#endif

#include "../loadroms.h"
#include "files.h"
#include "newmem.h"

#ifdef __GLIBC__
#if __GLIBC__ >= 2
#define stricmp strcasecmp
#define strnicmp strncasecmp
#endif
#elif defined(DARWIN) || defined(ANDROID)
#define stricmp strcasecmp
#define strnicmp strncasecmp
#endif

static ISzAlloc g_Alloc = { SzAlloc, SzFree };

static int Buf_EnsureSize(CBuf *dest, size_t size)
{
  if (dest->size >= size)
    return 1;
  Buf_Free(dest, &g_Alloc);
  return Buf_Create(dest, size, &g_Alloc);
}

#ifndef _WIN32

static Byte kUtf8Limits[5] = { 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

static Bool Utf16_To_Utf8(Byte *dest, size_t *destLen, const UInt16 *src, size_t srcLen)
{
  size_t destPos = 0, srcPos = 0;
  for (;;)
  {
    unsigned numAdds;
    UInt32 value;
    if (srcPos == srcLen)
    {
      *destLen = destPos;
      return True;
    }
    value = src[srcPos++];
    if (value < 0x80)
    {
      if (dest)
        dest[destPos] = (char)value;
      destPos++;
      continue;
    }
    if (value >= 0xD800 && value < 0xE000)
    {
      UInt32 c2;
      if (value >= 0xDC00 || srcPos == srcLen)
        break;
      c2 = src[srcPos++];
      if (c2 < 0xDC00 || c2 >= 0xE000)
        break;
      value = (((value - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
    }
    for (numAdds = 1; numAdds < 5; numAdds++)
      if (value < (((UInt32)1) << (numAdds * 5 + 6)))
        break;
    if (dest)
      dest[destPos] = (char)(kUtf8Limits[numAdds - 1] + (value >> (6 * numAdds)));
    destPos++;
    do
    {
      numAdds--;
      if (dest)
        dest[destPos] = (char)(0x80 + ((value >> (6 * numAdds)) & 0x3F));
      destPos++;
    }
    while (numAdds != 0);
  }
  *destLen = destPos;
  return False;
}

static SRes Utf16_To_Utf8Buf(CBuf *dest, const UInt16 *src, size_t srcLen)
{
  size_t destLen = 0;
  Bool res;
  Utf16_To_Utf8(NULL, &destLen, src, srcLen);
  destLen += 1;
  if (!Buf_EnsureSize(dest, destLen))
    return SZ_ERROR_MEM;
  res = Utf16_To_Utf8(dest->data, &destLen, src, srcLen);
  dest->data[destLen] = 0;
  return res ? SZ_OK : SZ_ERROR_FAIL;
}
#endif

static SRes Utf16_To_Char(CBuf *buf, const UInt16 *s, int fileMode)
{
  int len = 0;
  for (len = 0; s[len] != '\0'; len++);

  #ifdef _WIN32
  {
    int size = len * 3 + 100;
    if (!Buf_EnsureSize(buf, size))
      return SZ_ERROR_MEM;
    {
      char defaultChar = '_';
      BOOL defUsed;
      int numChars = WideCharToMultiByte(fileMode ?
          (
          #ifdef UNDER_CE
          CP_ACP
          #else
          AreFileApisANSI() ? CP_ACP : CP_OEMCP
          #endif
          ) : CP_OEMCP,
          0, s, len, (char *)buf->data, size, &defaultChar, &defUsed);
      if (numChars == 0 || numChars >= size)
        return SZ_ERROR_FAIL;
      buf->data[numChars] = 0;
      return SZ_OK;
    }
  }
  #else
  fileMode = fileMode;
  return Utf16_To_Utf8Buf(buf, s, len);
  #endif
}

void PrintError(char *sz)
{
    if (!strstr(load_debug,sz)) {
	strcat(load_debug,sz);
	strcat(load_debug,"\n");
    }
}

// Returns the size of the file in case of success, 0 if error
int load_7z(char *zipfile, char *name, unsigned int offs, unsigned int size, int crc32, unsigned char *dest, int actual_load)
{
  static CFileInStream archiveStream;
  static CLookToRead lookStream;
  static CSzArEx db;
  SRes res;
  static ISzAlloc allocImp;
  static ISzAlloc allocTempImp;
  static UInt16 *temp = NULL;
  static size_t tempSize = 0;
  static char oldfile[1024];
  static Byte *outBuffer = 0; /* it must be 0 before first call for each new archive. */
  static size_t outBufferSize = 0;  /* it can have any value before first call (if outBuffer = 0) */
  static UInt32 blockIndex = 0xFFFFFFFF; /* it can have any value before first call (if outBuffer = 0) */
  static size_t outSizeProcessed = 0;
  UInt32 i;
  size_t offset = 0;
  const CSzFileItem *f;

  if (!*oldfile) {
      allocImp.Alloc = SzAlloc;
      allocImp.Free = SzFree;

      allocTempImp.Alloc = SzAllocTemp;
      allocTempImp.Free = SzFreeTemp;
  }
  if (strcmp(oldfile,zipfile)) {
      CFileInStream newstream;
     if (InFile_Open(&newstream.file, zipfile))
     {
	 /*
	    char buf[1024];
	    sprintf(buf,"can not open %s",zipfile);
	    PrintError(buf); */
	 // We don't display the error here, raine has something specific
	 return 0;
     }
     if (*oldfile) { // had already something
	 // file just changed
	 IAlloc_Free(&allocImp, outBuffer);
	 SzArEx_Free(&db, &allocImp);
	 SzFree(NULL, temp);
	 temp = NULL;
	 outBuffer = 0;
	 outBufferSize = 0;
	 File_Close(&archiveStream.file);
	 blockIndex = 0xFFFFFFFF;
	 outSizeProcessed = 0;
	 tempSize = 0;
     }
     archiveStream = newstream;

     strncpy(oldfile,zipfile,1024);

     FileInStream_CreateVTable(&archiveStream);
     LookToRead_CreateVTable(&lookStream, False);

     lookStream.realStream = &archiveStream.s;
     LookToRead_Init(&lookStream);

     CrcGenerateTable();

     SzArEx_Init(&db);
     res = SzArEx_Open(&db, &lookStream.s, &allocImp, &allocTempImp);
  } else { // same file
      res = SZ_OK;
  }

  if (res == SZ_OK)
  {
      /*
      if you need cache, use these 3 variables.
      if you use external function, you can make these variable as static.
      */

      for (i = 0; i < db.db.NumFiles; i++)
      {
        f = db.db.Files + i;
        size_t len;
        if (f->IsDir)
	    continue;
        len = SzArEx_GetFileNameUtf16(&db, i, NULL);

        if (len > tempSize)
        {
          SzFree(NULL, temp);
          tempSize = len;
          temp = (UInt16 *)SzAlloc(NULL, tempSize * sizeof(temp[0]));
          if (temp == 0)
          {
            res = SZ_ERROR_MEM;
            break;
          }
        }
	SzArEx_GetFileNameUtf16(&db, i, temp);
	CBuf buf;
	Buf_Init(&buf);
	Utf16_To_Char(&buf,temp,0);

	if (f->Crc == crc32 || !stricmp(name,(char*)buf.data))
        {
	    if (actual_load) {
		res = SzArEx_Extract(&db, &lookStream.s, i,
			&blockIndex, &outBuffer, &outBufferSize,
			&offset, &outSizeProcessed,
			&allocImp, &allocTempImp);
		if (outSizeProcessed >= size) {
		    memcpy(dest,outBuffer+offset+offs,size);
		    if (outSizeProcessed > size) {
			if (remaining_b) {
			    FreeMem(remaining_b);
			    remaining_b = NULL;
			}
			remaining_size = outSizeProcessed - size;
			// Shouldn't happen, but it does, found out thanks to
			// efence. Apparently it's just the remaining_size
			// which is too big, the buffer is not overloaded at
			// this point
			if (remaining_size+offset+offs+size > outBufferSize)
			    remaining_size = outBufferSize-(offset+offs+size);
			remaining_b = AllocateMem(remaining_size);
			memcpy(remaining_b,outBuffer+offset+offs+size,remaining_size);
		    } else if (remaining_b) {
			FreeMem(remaining_b);
			remaining_size = 0;
			remaining_b = NULL;
		    }
		} else if (outSizeProcessed)
		    memcpy(dest,outBuffer+offset+offs,outSizeProcessed);
		if (res == SZ_ERROR_CRC) {
		    load_error |= LOAD_WARNING;

		    if (load_debug)
			sprintf(load_debug+strlen(load_debug),
				"Got a bad CRC for ROM %s (%x)\n",name,crc32);
		}
	    } else
		res = SZ_OK;
	    Buf_Free(&buf, &g_Alloc);
	    break;
        }
	Buf_Free(&buf, &g_Alloc);
      }
  }
  if (i == db.db.NumFiles)
      return 0; // not found
  if (res == SZ_OK)
  {
    // printf("\nEverything is Ok\n");
    return f->Size;
  }
  if (res == SZ_ERROR_UNSUPPORTED)
    PrintError("decoder doesn't support this archive");
  else if (res == SZ_ERROR_MEM)
    PrintError("can not allocate memory");
  else if (res == SZ_ERROR_CRC) {
      load_error |= LOAD_WARNING;

      if (load_debug)
	  sprintf(load_debug+strlen(load_debug),
		  "Bad rom size for %s: tried to read %xh bytes, got %xh\n",name,size,(UINT32)outSizeProcessed);
  }
  else {
      char buf[80];
      sprintf(buf,"7z ERROR #%d\n", res);
      PrintError(buf);
  }
  return 0;
}


