#include "z80/mz80help.h"
#include "68020/u020help.h"
#include <muParser.h>
#include <stdio.h>
#include "sdl/compat.h"
#include "sdl/dialogs/messagebox.h"
#include "parser.h"
#include "starhelp.h"
#include "console.h"
#include "raine.h" // ReadWord !
#include "cpumain.h"

/* muParser is specialised in double numbers, so it lacks some basic integer
 * operations, but can be easily extended, so let's go... */

using namespace mu;
value_type rol(value_type v1, value_type v2) { return int(rint(v1))<<int(rint(v2)); }
value_type ror(value_type v1, value_type v2) { return int(rint(v1))>>int(rint(v2)); }
value_type Or(value_type v1, value_type v2) { return int(v1) | int(v2); }
value_type And(value_type v1, value_type v2) { return int(v1) & int(v2); }
value_type Not(value_type v1) { return ~int(rint(v1)); }
value_type LogNot(value_type v1) { return !int(rint(v1)); }

double sr, pc, a[8], d[8],za,zb,zc,zd,ze,zf,zh,zl,iff;

value_type peek(value_type fadr) {
  UINT32 adr = fadr;
  UINT8 *ptr = get_ptr(adr);
  if (!ptr) throw "this adr isn't in ram !";

  if ((get_cpu_id()>>4) == 1)
      return ptr[adr ^ 1];
  else
      return ptr[adr];
}

value_type dpeek(value_type fadr) {
  UINT32 adr = fadr;
  UINT8 *ptr = get_ptr(adr);
  if (!ptr) throw "this adr isn't in ram !";

  return ReadWord(&ptr[adr]);
}

value_type lpeek(value_type fadr) {
  UINT32 adr = fadr;
  UINT8 *ptr = get_ptr(adr);
  if (!ptr) throw "this adr isn't in ram !";

  return ReadLongSc(&ptr[adr]);
}

void get_regs(int cpu) {
    int num;
    switch (cpu >> 4) {
    case 1: // 68k
	for (int n=0; n<8; n++) {
	    a[n] = (long)s68000context.areg[n];
	    d[n] = (long)s68000context.dreg[n];
	}
	sr = s68000context.sr;
	pc = s68000readPC();
	break;
    case 2:
	num = cpu & 0xf;
	switch_cpu(cpu+1);
	switch_cpu(cpu);
	za = (Z80_context[num].z80af>>8);
	zf = (Z80_context[num].z80af&0xff);
	zb = (Z80_context[num].z80bc>>8);
	zc = (Z80_context[num].z80bc&0xff);
	zd = (Z80_context[num].z80de>>8);
	ze = (Z80_context[num].z80de&0xff);
	zh = (Z80_context[num].z80hl>>8);
	zl = (Z80_context[num].z80hl&0xff);
	pc = Z80_context[num].z80pc;
	iff = Z80_context[num].z80iff;
	break;
#ifndef NO020
    case 3: // 68020
	for (int n=0; n<8; n++) {
	    a[n] = (long)regs.regs[n+8];
	    d[n] = (long)regs.regs[n];
	}
	sr = regs.sr;
	pc = regs.pc;
	break;
#endif
    }
}

void set_regs(int cpu) {
    int num = cpu & 0xf;
    switch (cpu >> 4) {
    case 1:
	for (int n=0; n<8; n++) {
	    M68000_context[num].areg[n] = s68000context.areg[n] = a[n];
	    M68000_context[num].dreg[n] = s68000context.dreg[n] = d[n];
	}
	M68000_context[num].sr = s68000context.sr = sr;
	M68000_context[num].pc = s68000context.pc = pc;
	break;
    case 2:
	Z80_context[num].z80af = (int(za)<<8)|int(zf);
	Z80_context[num].z80bc = (int(zb)<<8)|int(zc);
	Z80_context[num].z80de = (int(zd)<<8)|int(ze);
	Z80_context[num].z80hl = (int(zh)<<8)|int(zl);
	Z80_context[num].z80pc = pc;
	Z80_context[num].z80iff = iff;
	break;
#ifndef NO020
    case 3:
	for (int n=0; n<8; n++) {
	    regs.regs[n+8] = a[n];
	    regs.regs[n] = d[n];
	}
	regs.sr = sr;
	regs.pc = pc;
	break;
#endif
    }
}

static value_type alert(const char_type *msg_and_btns) {
  // muparser doesn't support more than 1 string for its arguments...
  // so we'll pass the message + the buttons in the same string, separated by
  // the char |
  string_type mystr = msg_and_btns;
  char *cmsg = (char*)mystr.c_str();
  char *btn = strchr(cmsg,'|');
  if (btn) {
    *btn++ = 0;
    return MessageBox("alert",cmsg,btn);
  }
  // otherwise it's just a message
  return MessageBox("alert",cmsg);
}

static int initialised = 0;
static mu::Parser p;
int parser_error;
static double afValBuf[100];
static int iVal = 0;

double* AddVariable(const char *a_szName, void *pUserData)
{

  afValBuf[iVal++] = 0;
  if (iVal>=99)
    throw mu::Parser::exception_type("Variable buffer overflow.");

  return &afValBuf[iVal-1];
}

int parse(char *orig)
{
//  using namespace mu;
  int res;
  char expr[1024];
  strcpy(expr,orig);
  parser_error = 0;

  /* Handling of bases is stupid in muparser, you can't make it to understand
   * hex numbers begining by 0x, so it's easier to convert everything before
   * calling it... */
  strlwr(expr);
  char *s = expr;
  while ((s = strstr(s,"0x"))) {
    s[1] = '$';
    strcpy(s,s+1);
  } // 0x -> $
  s = expr;
  while ((s = strchr(s,'$'))) {
    *s = 0;
    s++;
    int res = 0;
    while ((*s >= '0' && *s <= '9') || (*s >= 'a' && *s <= 'f')) {
      int digit;
      if (*s >= 'a') digit = *s - 'a' + 10;
      else
	digit = *s - '0';
      res = res*16 + digit;
      s++;
    }
    char buff2[1024];
    sprintf(buff2,"%s%d%s",expr,res,s);
    strcpy(expr,buff2); // obliged to use another string for the sprintf
  }

  try
  {
    if (!initialised) {
      p.DefineOprt( _T("<<"), rol, 0);
      p.DefineOprt( _T(">>"), ror, 0);
      p.DefineOprt( _T("|"), Or, 0);
      p.DefineOprt( _T("&"), And, 0);
      p.DefineInfixOprt( _T("~"), Not);
      p.DefineInfixOprt( _T("!"), LogNot);
      p.DefineFun( _T("alert"), alert, false);
      p.DefineFun( _T("dpeek"), dpeek, false);
      p.DefineFun( _T("peek"), peek, false);
      p.DefineFun( _T("lpeek"), lpeek, false);
      p.SetVarFactory(AddVariable,&p);
      // p.DefineFun( _T("r"), reg, false);
      for (int n=0; n<8; n++) {
	  char name[3];
	  sprintf(name,"d%d",n);
	  p.DefineVar(name,&d[n]);
	  sprintf(name,"a%d",n);
	  p.DefineVar(name,&a[n]);
      }
      p.DefineVar("sr",&sr);
      // z80
      p.DefineVar("a",&za);
      p.DefineVar("b",&zb);
      p.DefineVar("c",&zc);
      p.DefineVar("d",&zd);
      p.DefineVar("e",&ze);
      p.DefineVar("f",&zf);
      p.DefineVar("h",&zh);
      p.DefineVar("l",&zl);
      p.DefineVar("iff",&iff);
      p.DefineVar("pc",&pc);
      initialised = 1;
    }
//    p.DefineVar("a", &fVal);
//    p.DefineFun("MyFunc", MyFunction);
    p.SetExpr(expr);
    res = p.Eval();

    // STd::cout << p.Eval() << endl;
  }
  catch (mu::Parser::exception_type &e)
  {
    parser_error = 1;
    const char *msg = e.GetMsg().c_str();
    // apparently vsprintf needs a char* which can be writen to, so we convert
#ifdef RAINE_DEBUG
    printf("console: %s\n",msg);
#endif
    throw msg;
  }
  return res;
}

