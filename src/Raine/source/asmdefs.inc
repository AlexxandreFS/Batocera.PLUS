#ifdef RAINE_DOS

#define CODE_SEG				\
.text					;	\

#define FUNC(name)				\
.p2align 2				;	\
.globl _##name				;	\
_##name:				;	\

#define GLOBL(name)		_##name		\

#endif


#if defined(RAINE_WIN32) || defined(DARWIN)

#define CODE_SEG				\
.data					;	\

#define FUNC(name)				\
.p2align 2				;	\
.globl _##name				;	\
_##name:				;	\

#define GLOBL(name)		_##name		\

#endif

#if defined(RAINE_UNIX) && !defined(DARWIN)

#define CODE_SEG				\
.data					;	\

#define FUNC(name)				\
.p2align 2				;	\
.globl name				;	\
##name:					;	\

#define GLOBL(name)		name		\

#endif

