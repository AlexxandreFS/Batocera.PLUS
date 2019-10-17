/******************************************************************************/
/*									      */
/*			    CONFIG FILE ROUTINES			      */
/*									      */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "deftypes.h"
#include <sys/stat.h>
#include "debug.h"
#include "files.h"
#if !defined(RAINE_WIN32) && !defined(stricmp)
#define stricmp strcasecmp
#endif
/*

Taken from allegro 3.11, I had to do it, because the allegro ones are too slow
with large files (eg. cheat files of 200kb). The allegro ones check the whole
file, these ones try not to check beyond the end of a [section]. Also the last
[section] pointer is cached. Also removed hook support, packfile support,
datafile support etc...
Hopefully this file is portable without major problems.

*/

typedef struct CONFIG_ENTRY
{
   char *name;			    /* variable name (NULL if comment) */
   char *data;			    /* variable value */
   struct CONFIG_ENTRY *next;	    /* linked list */
} CONFIG_ENTRY;

typedef struct CONFIG
{
   CONFIG_ENTRY *head;		    /* linked list of config entries */
   char *filename;		    /* where were we loaded from? */
   int dirty;			    /* has our data changed? */
   CONFIG_ENTRY *section_cache;     /* cache last section position */
   char *data_buf;
   UINT32 data_size;	// size allocated
   UINT32 current_size; // size actually used so far
} CONFIG;

#define MAX_CONFIGS	4

static CONFIG *config[MAX_CONFIGS] = { NULL, NULL, NULL, NULL };
static CONFIG *config_language = NULL;
static CONFIG *system_config = NULL;

static int config_installed = FALSE;

/* Functions for the data/value pairs */
/* These are to ease the work of electric fence and allocate less buffers */
/* With all the buffers allocated before for cheats.cfg, I made a segfault
   with default parameters of electric fence !!! */

#define DATA_BLOCK 4096

char *get_data_ptr(CONFIG *cfg,UINT32 size) {
  char *new_ptr;
  CONFIG_ENTRY *pos, *prev;
  UINT32 offset;

  if (size == 0){
    fprintf(stderr,"get_data_ptr: Allocation of 0 byte !!!\n");
    exit(1);
  }
  if (!cfg->data_buf) { // No buffer allocated yet...
    cfg->data_size = size + DATA_BLOCK;
    cfg->current_size = size;
    cfg->data_buf = malloc( cfg->data_size );
    return cfg->data_buf;
  }
  if (cfg->current_size + size < cfg->data_size) { // Still some room
    cfg->current_size += size;
    return cfg->data_buf + cfg->current_size-size;
  }

  // Else we need to reallocate the buffer...
  new_ptr = realloc(cfg->data_buf,cfg->current_size + size + DATA_BLOCK);
  if (!new_ptr) {
    print_debug("confile: realloc failed for %d %s\n",cfg->data_size,cfg->filename);
    return NULL;
  }
  cfg->data_size = cfg->current_size + size + DATA_BLOCK;

  pos = cfg->head;

  while (pos) {
    prev = pos;
    pos = pos->next;
    if (prev->name){
      offset = prev->name - cfg->data_buf;
      if (offset > cfg->current_size || offset < 0) {
	fprintf(stderr,"get_data_ptr: Allocation problem !!!\n");
	exit(1);
      }
      prev->name = new_ptr + offset;
    }
    if (prev->data){
      offset = prev->data - cfg->data_buf;
      if (offset > cfg->current_size || offset < 0) {
	fprintf(stderr,"get_data_ptr: Allocation problem !!!\n");
	exit(1);
      }
      prev->data = new_ptr + offset;
    }
  }
  cfg->data_buf = new_ptr;
  return get_data_ptr(cfg,size);
}

void free_data_buff(CONFIG *cfg) {
  if (cfg->data_size) {
    free(cfg->data_buf);
    cfg->data_buf = NULL;
    cfg->data_size = cfg->current_size = 0;
  }
}

/* destroy_config:
 *  Destroys a config structure, writing it out to disk if the contents
 *  have changed.
 */
static void destroy_config(CONFIG *cfg)
{
   CONFIG_ENTRY *pos, *prev;

   if (cfg) {
      if (cfg->filename) {
	 if (cfg->dirty) {
	    /* write changed data to disk */
	    FILE *f = fopen(cfg->filename, "w");

	    if (f) {
	       pos = cfg->head;

	       while (pos) {
		  if (pos->name) {
		     fputs(pos->name, f);
		     if (pos->name[0] != '[')
			fputs(" = ", f);
		  }
		  if (pos->data)
		     fputs(pos->data, f);

		  fputs("\n", f);
		  pos = pos->next;
	       }

	       fclose(f);
	    }
	 }

	 free(cfg->filename);
      }

      /* destroy the variable list */
      pos = cfg->head;

      while (pos) {
	 prev = pos;
	 pos = pos->next;

#if 0
	 if (prev->name)
	    free(prev->name);

	 if (prev->data)
	    free(prev->data);
#endif

	 free(prev);
      }

      free_data_buff(cfg);
      free(cfg);
   }
}



/* config_cleanup:
 *  Called at shutdown time to free memory being used by the config routines,
 *  and write any changed data out to disk.
 */
void raine_config_cleanup()
{
   int i;

   for (i=0; i<MAX_CONFIGS; i++) {
      if (config[i]) {
	 destroy_config(config[i]);
	 config[i] = NULL;
      }
   }

   if (config_language) {
      destroy_config(config_language);
      config_language = NULL;
   }

   if (system_config) {
      destroy_config(system_config);
      system_config = NULL;
   }

   config_installed = FALSE;
}



/* init_config:
 *  Sets up the configuration routines ready for use, also loading the
 *  default config file if the loaddata flag is set and no other config
 *  file is in memory.
 */
static void init_config(int loaddata)
{
   if (!config_installed) {
      config_installed = TRUE;
   }

   if (!system_config) {
      system_config = malloc(sizeof(CONFIG));
      if (system_config) {
	 system_config->head = NULL;
	 system_config->filename = NULL;
	 system_config->dirty = FALSE;
	 system_config->section_cache = NULL;
	 system_config->data_buf = NULL;
	 system_config->current_size = system_config->data_size = 0;
      }
   }
}


static int cfg_isspace(char i)
{
   if((i == ' ')||(i == '\t')||(i == '\n')||(i == '\r'))
      return 1;
   else
      return 0;
}

/* get_line:
 *  Helper for splitting files up into individual lines.
 */
static int get_line(char *data, int length, char *name, char *val)
{
   char buf[256], buf2[256];
   int pos, i, j;

   for (pos=0; (pos<length) && (pos<255); pos++) {
      if ((data[pos] == '\r') || (data[pos] == '\n')) {
	 buf[pos] = 0;
	 if ((pos < length-1) &&
	     (((data[pos] == '\r') && (data[pos+1] == '\n')) ||
	      ((data[pos] == '\n') && (data[pos+1] == '\r')))) {
	    pos++;
	 }
	 pos++;
	 break;
      }

      buf[pos] = data[pos];
   }
   if (pos > 255) {
     printf("overflow buffer %d\n",pos);
     exit(1);
   }

   buf[MIN(pos,255)] = 0;

   /* skip leading spaces */
   i = 0;
   while ((buf[i]) && (cfg_isspace(buf[i])))
      i++;

   /* read name string */
   j = 0;
   while ((buf[i]) && (!cfg_isspace(buf[i])) && (buf[i] != '=') && (buf[i] != '#'))
      buf2[j++] = buf[i++];

   if (j) {
      /* got a variable */
      buf2[j] = 0;
      strcpy(name, buf2);

      while ((buf[i]) && ((cfg_isspace(buf[i])) || (buf[i] == '=')))
	 i++;

      strcpy(val, buf+i);

      /* strip trailing spaces */
      i = strlen(val) - 1;
      while ((i >= 0) && (cfg_isspace(val[i])))
	 val[i--] = 0;
   }
   else {
      /* blank line or comment */
      name[0] = 0;
      strcpy(val, buf);
   }

   return pos;
}



/* set_config:
 *  Does the work of setting up a config structure.
 */
static void set_config(CONFIG **config, char *data, int length, char *filename)
{
   char name[256];
   char val[256];
   CONFIG_ENTRY **prev, *p;
   int pos;

   init_config(FALSE);

   if (*config) {
      destroy_config(*config);
      *config = NULL;
   }

   *config = malloc(sizeof(CONFIG));
   if (!(*config))
      return;

   (*config)->head = NULL;
   (*config)->dirty = FALSE;
   (*config)->section_cache = NULL;
   (*config)->data_buf = NULL;
   (*config)->data_size = (*config)->current_size = 0;

   if (filename) {
      (*config)->filename = strdup(filename);
   }
   else
      (*config)->filename = NULL;

   prev = &(*config)->head;
   pos = 0;

   while ((pos < length) && (data[pos])){
     int size = sizeof(CONFIG_ENTRY);
#ifndef RAINE_DOS
     if (size < 16) size = 16; // alignement, especially for efence
#endif
      pos += get_line(data+pos, length-pos, name, val);

      *prev = p = malloc(size);
      if (!p)
	 return;
      p->next = NULL;
      p->name = p->data = NULL;

      if (name[0]) {
	 p->name = get_data_ptr(*config,(strlen(name)+1));
	 if (p->name)
	    strcpy(p->name, name);
      }

      p->data = get_data_ptr(*config,strlen(val)+1);
      if (p->data)
	 strcpy(p->data, val);

      prev = &p->next;
   }
}

/* load_config_file:
 *  Does the work of loading a config file.
 */
static void load_config_file(CONFIG **config, char *filename, char *savefile)
{
   int length;

   if (*config) {
      destroy_config(*config);
      *config = NULL;
   }

   length = size_file(filename);

   if (length > 0) {
     FILE *f = fopen(filename, "rb");
      if (f) {
	 char *tmp = malloc(length);
	 if (tmp) {
	    fread(tmp, 1, length, f);
	    set_config(config, tmp, length, savefile);
	    free(tmp);
	 }
	 else
	    set_config(config, NULL, 0, savefile);
	 fclose(f);
      }
      else
	 set_config(config, NULL, 0, savefile);
   }
   else
      set_config(config, NULL, 0, savefile);
}



/* set_config_file:
 *  Sets the file to be used for all future configuration operations.
 */
void raine_set_config_file(char *filename)
{
   load_config_file(&config[0], filename, filename);
}



/* set_config_data:
 *  Sets the block of data to be used for all future configuration
 *  operations.
 */
void raine_set_config_data(char *data, int length)
{
   set_config(&config[0], data, length, NULL);
}



/* push_config_state:
 *  Pushes the current config state onto the stack.
 */
void raine_push_config_state(void)
{
   int i;

   if (config[MAX_CONFIGS-1])
      destroy_config(config[MAX_CONFIGS-1]);

   for (i=MAX_CONFIGS-1; i>0; i--)
      config[i] = config[i-1];

   config[0] = NULL;
}



/* pop_config_state:
 *  Pops the current config state off the stack.
 */
void raine_pop_config_state(void)
{
   int i;

   if (config[0])
      destroy_config(config[0]);

   for (i=0; i<MAX_CONFIGS-1; i++)
      config[i] = config[i+1];

   config[MAX_CONFIGS-1] = NULL;
}



/* prettify_section_name:
 *  Helper for ensuring that a section name is enclosed by [ ] braces.
 */
static void prettify_section_name(const char *in, char *out)
{
   if (in) {
      if (in[0] != '[')
	 strcpy(out, "[");
      else
	 out[0] = 0;

      strcat(out, in);

      if (out[strlen(out)-1] != ']')
	 strcat(out, "]");
   }
   else
      out[0] = 0;
}



/* find_config_string:
 *  Helper for finding an entry in the configuration file.
 */
static CONFIG_ENTRY *find_config_string(CONFIG *config, char *section, const char *name, CONFIG_ENTRY **prev)
{
   CONFIG_ENTRY *p;
   int in_section = 0;

   if (config) {
      p = config->head;

      if(config->section_cache){
	 if (section) {
	    p = config->section_cache;
	    /* change section */
	    in_section = (stricmp(section, p->name) == 0);
	    if( !in_section )
	       p = config->head;
	 }
      }

      if (prev)
	 *prev = NULL;

      in_section = 0;

      if (section){

      while (p) {
	 if (p->name) {
	   if (p->name[0] == '[') {
	       /* change section */
	       if (in_section){
		  return NULL;
	       }
	       in_section = (stricmp(section, p->name) == 0);
	       if (in_section){
		  config->section_cache = p;
	       }
	    }
	    if (in_section) {
	       /* is this the one? */
	       if (stricmp(p->name, name) == 0)
		  return p;
	    }
	 }

	 if (prev)
	    *prev = p;

	 p = p->next;
      }

      }
      else{

      while (p) {
	 if (p->name) {
	    /* is this the one? */
	    if (stricmp(p->name, name) == 0)
	       return p;
	 }

	 if (prev)
	    *prev = p;

	 p = p->next;
      }

      }

   }

   return NULL;
}



/* get_config_string:
 *  Reads a string from the configuration file.
 */
char *raine_get_config_string(const char *section, const char *name, char *def)
{
   char section_name[256];
   CONFIG_ENTRY *p;

   init_config(TRUE);

   prettify_section_name(section, section_name);

   /* find the string */

   p = find_config_string(config[0], section_name, name, NULL);

   if (p)
      return (p->data ? p->data : "");
   else
      return def;
}



/* get_config_int:
 *  Reads an integer from the configuration file.
 */
int raine_get_config_int(const char *section, const char *name, int def)
{
   char *s;

   /* read normal data */
   s = raine_get_config_string(section, name, NULL);

   if ((s) && (*s))
      return strtol(s, NULL, 0);

   return def;
}



/* get_config_hex:
 *  Reads a hexadecimal _unsigned_ integer from the configuration file.
 */
UINT32 raine_get_config_hex(char *section, char *name, UINT32 def)
{
   char *s = raine_get_config_string(section, name, NULL);
   UINT32 i;

   if ((s) && (*s)) {
      i = strtoul(s, NULL, 16);
      return i;
   }

   return def;
}


#ifdef __MINGW32__
#undef toupper
#undef isspace
#endif

/* get_config_id:
 *  Reads a driver ID number from the configuration file.
 */
int raine_get_config_id(char *section, char *name, int def)
{
   char *s = raine_get_config_string(section, name, NULL);
   char tmp[4];
   char *endp;
   int val, i;

   if ((s) && (*s)) {
      val = strtol(s, &endp, 0);
      if (!*endp)
	 return val;

      tmp[0] = tmp[1] = tmp[2] = tmp[3] = ' ';

      for (i=0; i<4; i++) {
	 if (s[i])
	    tmp[i] = toupper(s[i]);
	 else
	    break;
      }

      return ASCII_ID(tmp[0], tmp[1], tmp[2], tmp[3]);
   }

   return def;
}



/* insert_variable:
 *  Helper for inserting a new variable into a configuration file.
 */
static CONFIG_ENTRY *insert_variable(CONFIG *the_config, CONFIG_ENTRY *p, const char *name, char *data)
{
   CONFIG_ENTRY *n = malloc(sizeof(CONFIG_ENTRY));

   if (!n)
      return NULL;

   if (p) {
      n->next = p->next;
      p->next = n;
   }
   else {
      n->next = NULL;
      the_config->head = n;
   }

   n->name = n->data = NULL;

   if (name) {
      n->name = get_data_ptr(the_config,strlen(name)+1);
      if (n->name)
	 strcpy(n->name, name);
   }

   if (data) {
      n->data = get_data_ptr(the_config,strlen(data)+1);
      if (n->data)
	 strcpy(n->data, data);
   }

   return n;
}



/* set_config_string:
 *  Writes a string to the configuration file.
 */
void raine_set_config_string(const char *section, const char *name, char *val)
{
   CONFIG *the_config;
   CONFIG_ENTRY *p, *prev;
   char section_name[256];

   init_config(TRUE);

   prettify_section_name(section, section_name);

   the_config = config[0];

   if (the_config) {
      p = find_config_string(the_config, section_name, name, &prev);

      if (p) {
	 if (val ) {
	    /* modify existing variable */
	   // Well you loose a few bytes by doing so
	   // but you win so many with one big buff instead of lots of little
#if 0
	   if (p->data)
	       free(p->data);
#endif

	    p->data = get_data_ptr(the_config,strlen(val)+1);
	    if (p->data)
	       strcpy(p->data, val);
	 }
	 else {
	    /* delete variable */
#if 0
	   if (p->name)
	       free(p->name);
	    if (p->data)
	       free(p->data);
#endif

	    if (prev)
	       prev->next = p->next;
	    else
	       the_config->head = p->next;

	    free(p);
	 }
      }
      else {
	 if (val) {
	    /* add a new variable */
	    if (section_name[0]) {
	       p = find_config_string(the_config, NULL, section_name, &prev);

	       if (!p) {
		  /* create a new section */
		  p = the_config->head;
		  while ((p) && (p->next))
		     p = p->next;

		  if ((p) && (p->data) && (*p->data))
		     p = insert_variable(the_config, p, NULL, NULL);

		  p = insert_variable(the_config, p, section_name, NULL);
	       }

	       /* append to the end of the section */
	       while ((p) && (p->next) &&
		      (((p->next->name) && (*p->next->name)) ||
		       ((p->next->data) && (*p->next->data))))
		  p = p->next;

	       p = insert_variable(the_config, p, name, val);
	    }
	    else {
	       /* global variable */
	       p = the_config->head;
	       insert_variable(the_config, NULL, name, val);
	       the_config->head->next = p;
	    }
	 }
      }

      the_config->dirty = TRUE;
   }
}



/* set_config_int:
 *  Writes an integer to the configuration file.
 */
void raine_set_config_int(const char *section, const char *name, int val)
{
   char buf[32];
   sprintf(buf, "%d", val);
   raine_set_config_string(section, name, buf);
}



/* set_config_hex:
 *  Writes a hexadecimal integer to the configuration file.
 */
void raine_set_config_hex(char *section, char *name, int val)
{
   if (val >= 0) {
      char buf[32];
      sprintf(buf, "%X", val);
      raine_set_config_string(section, name, buf);
   }
   else
      raine_set_config_string(section, name, "-1");
}

void raine_set_config_8bit_hex(char *section, char *name, UINT32 val)
{
   char buf[32];
   sprintf(buf, "%02X", val);
   raine_set_config_string(section, name, buf);
}

void raine_set_config_16bit_hex(char *section, char *name, UINT32 val)
{
   char buf[32];
   sprintf(buf, "%04X", val);
   raine_set_config_string(section, name, buf);
}

void raine_set_config_24bit_hex(char *section, char *name, UINT32 val)
{
   char buf[32];
   sprintf(buf, "%06X", val);
   raine_set_config_string(section, name, buf);
}

void raine_set_config_32bit_hex(char *section, char *name, UINT32 val)
{
   char buf[32];
   sprintf(buf, "%08X", val);
   raine_set_config_string(section, name, buf);
}

/* set_config_float:
 *  Writes a float to the configuration file.
 */
void raine_set_config_float(char *section, char *name, float val)
{
   char buf[32];
   sprintf(buf, "%f", val);
   raine_set_config_string(section, name, buf);
}



/* set_config_id:
 *  Writes a driver ID to the configuration file.
 */
void raine_set_config_id(char *section, char *name, int val)
{
   char buf[32];
   int i;

   if (val < 256) {
      sprintf(buf, "%d", val);
   }
   else {
      buf[0] = (val>>24)&0xFF;
      buf[1] = (val>>16)&0xFF;
      buf[2] = (val>>8)&0xFF;
      buf[3] = val&0xFF;
      buf[4] = 0;

      for (i=0; buf[i]; i++) {
	 if (buf[i] == ' ') {
	    buf[i] = 0;
	    break;
	 }
      }
   }

   raine_set_config_string(section, name, buf);
}

/* get_config_text:
 *  Looks up a translated version of the specified English string,
 *  returning a suitable message in the current language if one is
 *  available, or a copy of the parameter if no translation can be found.
 */
char *raine_get_config_text(char *msg)
{
   static char section[] = "[language]";
   char name[256];
   CONFIG_ENTRY *p;
   int i;

   init_config(TRUE);

   for (i=0; msg[i]; i++) {
      if ((isspace(msg[i])) || (msg[i] == '=') || (msg[i] == '#'))
	 name[i] = '_';
      else
	 name[i] = msg[i];
   }

   name[i] = 0;

   /* find the string */

   p = find_config_string(config[0], section, name, NULL);

   if (p)
      return (p->data ? p->data : "");
   else
      return msg;
}

/* raine_clear_config_section:
 *  Useful! :)
 */
void raine_clear_config_section(const char *section)
{

   CONFIG *the_config;
   CONFIG_ENTRY *p,*prev,*next;
   int in_section = 0;
   char section_name[256];

   init_config(TRUE);

   prettify_section_name(section, section_name);

   the_config = config[0];

   if ((the_config) && (section)) {
      p = the_config->head;

      if(the_config->section_cache){
	    p = the_config->section_cache;
	    /* change section */
	    in_section = (stricmp(section_name, p->name) == 0);
	    if( !in_section )
	       p = the_config->head;
      }

      prev = NULL;

      in_section = 0;

      while (p) {

	 next = p->next;

	 if (p->name) {
	    if (p->name[0] == '[') {
	       /* change section */
	       if (in_section){
		  return;
	       }
	       in_section = (stricmp(section_name, p->name) == 0);
	       if (in_section){
		  the_config->section_cache = p;
	       }
	    }

	    if (in_section) {
	       /* is this the one? */
	       if ((p->name[0] != '#') && (p->name[0] != '[')){

	    /* delete variable */
#if 0
		 if (p->name)
	       free(p->name);

	    if (p->data)
	       free(p->data);
#endif

	    if (prev)
	       prev->next = next;
	    else
	       the_config->head = next;

	    free(p);

	    if (prev)
	       p = prev;
	    else
	       p = the_config->head;

	       }
	    }
	 }

	 prev = p;

	 p = next;
      }

   }

}
