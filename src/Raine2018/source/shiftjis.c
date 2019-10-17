#define U_SJIS          AL_ID('S','J','I','S')

/* sjis_getc:
 *  Reads a character from a shift-jis string.
 */
#if 0
static int sjis_getc(AL_CONST char *s)
{
   int c = *((unsigned char *)(s++));
   int t;

   if (c & 0x80) {

      t = *((unsigned char *)(s++));

      c = (c<<8) | (t);

   }

   return c;
}

/* sjis_getx:
 *  Reads a character from a shift-jis string, advancing the pointer position.
 */
static int sjis_getx(char **s)
{
   int c = *((unsigned char *)((*s)++));
   int t;

   if (c & 0x80) {

      t = *((unsigned char *)((*s)++));

      c = (c<<8) | (t);

   }

   return c;
}

/* sjis_setc:
 *  Sets a character in a shift-jis string.
 */
static int sjis_setc(char *s, int c)
{
   if (c < 128) {
      *s = c;
      return 1;
   }

   s[0] = c >> 8;
   s[1] = c;

   return 2;
}

/* sjis_width:
 *  Returns the width of a shift-jis character.
 */
static int sjis_width(AL_CONST char *s)
{
   int c = *((unsigned char *)s);

   if(c & 0x80)
      return 2;
   else
      return 1;

}

/* sjis_cwidth:
 *  Returns the width of a shift-jis character.
 */
static int sjis_cwidth(int c)
{
   if (c < 128)
      return 1;
   else
      return 2;
}

/* utf8_isok:
 *  Checks whether this character can be encoded in UTF-8 format.
 */
static int sjis_isok(int c)
{
	(void)(c);
   return TRUE;
}
#endif
