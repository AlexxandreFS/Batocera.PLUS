#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "raine.h"
#include "loadroms.h" // load_error

static void *MemoryPool[256];	// Pointers to allocated memory areas
static UINT32 MemSize[256];     // Size of each segment
static int MemoryPoolCount;	// Number of items in memory pool
static int MemoryPoolSize;	// Size of all items in memory pool

/* The general idea of these functions is to be able to allocate a block of
 * ram without caring about freeing it later, it's freed automatically, while
 * hiding the complexity (AllocateMem always calls malloc). */

// AllocateMem():
// Allocates a space memory, size bytes long
// Returns a pointer on success, or NULL on failiure. Also generates
// a raine error message on failure...

void *AllocateMem(UINT32 size)
{
   void *memptr;

   if (size < 8) {
     printf("received size %d\n",size);
     size = 8;
   }

   memptr = malloc(size);

   if(memptr)
   {

      /*

      check memory pool is not full up (unlikely)

      */

      if(MemoryPoolCount == 256) {
         print_debug("alloc_mem(0x%08X) OVERFLOW [0x%02X blocks; 0x%08X total]\n", size, MemoryPoolCount, MemoryPoolSize);
	 exit(1);
      }

      /*

      add to memory pool list

      */

      MemSize[MemoryPoolCount] = size;
      MemoryPool[MemoryPoolCount++] = memptr;
      MemoryPoolSize += size;
      // print_debug("alloc_mem(0x%08X) [0x%02X blocks; 0x%08X total]\n", size, MemoryPoolCount, MemoryPoolSize);

      return memptr;

   }
   else
   {

      /*

      error (for gui)

      */

#ifndef STANDALONE
      sprintf(
         load_debug+strlen(load_debug),
         "ERROR: Unable to allocate memory\n"
         "\n"
         "Failed to obtain 0x%08X bytes\n"
         "\n"
         "To fix this, buy more ram, or increase the available dpmi memory to 65535kb. "
         "Read rainefaq.txt for help with this (don't email us about it, thanks).\n"
         "\n",
         size
      );

      load_error |= LOAD_FATAL_ERROR;
#endif

      // print_debug("alloc_mem(0x%08X) FAILED [0x%02X blocks; 0x%08X total]\n", size, MemoryPoolCount, MemoryPoolSize);

      return NULL;

   }

}

// FreeMem():
// Deallocates a specific memory resource, memptr

void FreeMem(void *memptr)
{
   int ta,found=0;

   if(memptr)
   {

      for(ta = 0; ta < MemoryPoolCount; ta ++)
      {
	if(MemoryPool[ta] == memptr) {
	  free(memptr);
	  MemoryPoolSize -= MemSize[ta];
	  found = 1;
	  if (MemoryPoolCount > ta+1) {
	    memmove(&MemoryPool[ta],&MemoryPool[ta+1],(MemoryPoolCount-(ta+1))*sizeof(UINT8*));
	    memmove(&MemSize[ta],&MemSize[ta+1],(MemoryPoolCount-(ta+1))*sizeof(UINT32));
	  }
	  MemoryPoolCount--;
	}
      }

      if (!found) {
	print_debug("FreeMem called with an unknown adr !!!\n");
      }
   }
}

// ResetMemoryPool():
// Call this to start/reset the ingame memory allocation list. Should
// be called only in one place, before loadgame.

void ResetMemoryPool(void)
{
   int ta;

   for(ta=0;ta<256;ta++){
      MemoryPool[ta]=NULL;
   }

   MemoryPoolCount=0;
   MemoryPoolSize=0;
}

int GetMemoryPoolSize() {
  return MemoryPoolSize;
}

void FreeMemoryPool(void)
{
   //print_debug("START: FreeMemoryPool();\n");
   //print_debug("Before memory free: 0x%08x\n", malloc(0));

   while (MemoryPoolCount){
      if(MemoryPool[0]!=NULL) {
	FreeMem(MemoryPool[0]);
      }
   }

   ResetMemoryPool();

   //print_debug("END: FreeMemoryPool();\n");
}

void ByteSwap(UINT8 *MEM, UINT32 size)
{
   UINT32 ta;
   for(ta=0;ta<size;ta+=2){
      WriteWord(&MEM[ta],ReadWord68k(&MEM[ta]));
   }
}

#ifdef MEMORY_DEBUG

#undef malloc
#undef realloc
#undef free

struct sMemEntry
{
   void * entry;
   char * filename;
   UINT32  line;

   struct sMemEntry * next;
};

static struct sMemEntry * list = NULL;

// Init the memory list

void mbInitPurify(void)
{
   if (list)
      DonePurify();

   list = NULL;
}

// Clear the list, reporting leaked memory

void mbDonePurify(void)
{
   struct sMemEntry * node = list;

   while (node)
   {
      struct sMemEntry * tempnode = node;

      print_debug("Memory Leak in <%s> at line %d  ->  %08xh\n", node->filename, node->line, node->entry);
      free(node->entry);	// Don't free, incase it is still in use

      node = node->next;
      free(tempnode);
   }

   list = NULL;
}

// malloc replacement

void *mymalloc(UINT32 size, char * fname, UINT32 fline)
{
   struct sMemEntry * node;

   if (!size){			// Malloc(0) is used to get actual Heap Pointer
      print_debug("mymalloc: malloc(0) in file <%s> at line %d.\n", fname, fline);
      return malloc(size); 		// thus is not a memory leak
   }

   node = malloc(sizeof(struct sMemEntry));

   node->next = list;
   node->filename = fname;
   node->line = fline;
   node->entry = malloc(size);

   list = node;

   return node->entry;
}

// realloc replacement

void *myrealloc(void *ptr, UINT32 size, char *fname, UINT32 fline)
{
   struct sMemEntry *node;
   struct sMemEntry *prev;
   struct sMemEntry *next;

   if(ptr!=NULL){

   prev = NULL;
   node = list;

   while(node){

      next = node->next;

      if(node->entry == ptr){
         if(prev != NULL){
            prev->next = next;
         }
         else{
            list = next;
         }
         free(node);
      }
      else{
         prev = node;
      }
      node = next;
   }

   }

   // -----

   node = malloc(sizeof(struct sMemEntry));

   node->next = list;
   node->filename = fname;
   node->line = fline;
   node->entry = realloc(ptr, size);

   list = node;

   return node->entry;
}

// free replacement

void myfree(void * ptr, char * fname, UINT32 fline)
{
   int found;
   struct sMemEntry *node;
   struct sMemEntry *prev;
   struct sMemEntry *next;

   found = 0;

   prev = NULL;
   node = list;

   while(node){

      next = node->next;

      if(node->entry == ptr){
         if(prev != NULL){
            prev->next = next;
         }
         else{
            list = next;
         }
         free(node->entry);
         free(node);
         found++;
      }
      else{
         prev = node;
      }
      node = next;
   }

#ifdef RAINE_DEBUG
   if(!found){
      print_debug("myfree: Trying to delete unexistant pointer $%08x in file <%s> at line %d.\n", ptr, fname, fline);
   }
   if(found > 1){
      print_debug("myfree: Pointer was found %d times $%08x in file <%s> at line %d.\n", found, ptr, fname, fline);
   }
#endif
}

#endif
