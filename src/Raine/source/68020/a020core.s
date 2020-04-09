	.file	"core.c"

#include "asmdefs.inc"

CODE_SEG

#ifdef RAINE_UNIX
	#include "68020/asm02x.s"
#endif
#ifdef __MINGW32__
	#include "68020/asm02x.s"
#endif
	#include "68020/asm020.s"
	#include "68020/asm021.s"
	#include "68020/asm022.s"
	#include "68020/asm023.s"
	#include "68020/asm024.s"
	#include "68020/asm025.s"
	#include "68020/asm026.s"
	#include "68020/asm027.s"
	#include "68020/asm028.s"
	#include "68020/asm029.s"
	#include "68020/asm02a.s"
	#include "68020/asm02b.s"
	#include "68020/asm02c.s"
	#include "68020/asm02d.s"
	#include "68020/asm02e.s"
	#include "68020/asm02f.s"
