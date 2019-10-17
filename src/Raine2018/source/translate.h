#ifndef _
#ifndef RAINE_DOS
#include <libintl.h>
#include <locale.h>
#else
#define gettext(string) string
#endif

#if defined( __cplusplus) && !defined(RAINE_DOS)
#define _(string) gettext(string)
#else
// For C just map this to an empty macro to allow translation of static structs
#define _(string) string
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern char language[3]; // raine.c

#ifdef RAINE_WIN32

char *get_win_lang();

#endif

#ifdef __cplusplus
}
#endif

#endif
