
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                              DEBUG FILE SUPPORT                            */
/*                                                                            */
/******************************************************************************/

#ifdef RAINE_DEBUG

extern int debug_mode;

void open_debug(void);

#ifdef RAINE_DOS
void print_debug(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
#else
void print_debug(const char *format, ...);
#endif

void close_debug(void);

#else

#define print_debug(format, ...) 
/* You can use this for a macro with variable number of arguments : */
/* fprintf (stderr, format, __VA_ARGS__) */
/* see http://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html */

#endif

#ifdef __cplusplus
}
#endif
