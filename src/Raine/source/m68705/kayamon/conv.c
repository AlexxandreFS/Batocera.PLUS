/* This converts a M68705 disassembly to a .c file

   Don't talk to me about:
    * The state of this code
    * Text file parsing
    * Motorola
    * Good coding practice
    * GCC's optimisation
    * The state of this code
    * Good coding practice

  p.s. this doesn't support all instructions >:-)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PC 0x800
#define TRUE 1
#define FALSE 0

typedef unsigned char byte;

FILE *in, *out;
char param1[50], param2[50];
int pc_used[MAX_PC], next_pc[MAX_PC];
int init_pc;

void DoParam(char *str, int rdmem)
{
   char buf[50];
   unsigned int hex;
   char *p;
   int mem=1;

   p = &buf[0];
   fscanf(in, "%s", p);
   if (*p == ',') p++;
   if (*p == '#') { mem=0; p++; }
   if (*p == '$') p++;
   if (!rdmem) mem = 0;

   if (!strncmp(p, "(x+", 3))
   {
      p += 3;
      if (*p == '#') { mem=0; p++; }
      if (*p == '$') p++;
      hex = strtoul(p, NULL, 16);

#if 0
      if (mem)
      {
         fprintf(out, "\taddr = x + 0x%.3x;\n", hex);
         sprintf(str, "MCU_RDMEM(addr)");
      } else sprintf(str, "0x%.3x", hex);
#else
      fprintf(out, "\taddr = x + 0x%.3x;\n", hex);
      if (mem)
	  sprintf(str, "MCU_RDMEM(addr)");
      else
	  sprintf(str, "addr");
#endif
   } else if (!strncmp(p, "(x)", 3))
   {
      if (mem)
      {
         fprintf(out, "\taddr = x;\n");
         sprintf(str, "MCU_RDMEM(addr)");
      } else sprintf(str, "x");
   } else {
      hex = strtoul(p, NULL, 16);
      if (mem)
      {
         fprintf(out, "\taddr = 0x%.3x;\n", hex);
         sprintf(str, "MCU_RDMEM(0x%.3x)", hex);
      } else sprintf(str, "0x%.3x", hex);
   }
}

void GetParam1(int rdmem)
{
   DoParam(&param1[0], rdmem);
}

void GetParam2(int rdmem)
{
   DoParam(&param2[0], rdmem);
}

#define SET_NZ(x) fprintf(out, "\tSET_NZ(%s);\n", x)
#define INC(o,x) fprintf(out, "\tINC(%s, %s);\n", o, x)
#define DEC(o,x) fprintf(out, "\tDEC(%s, %s);\n", o, x)
#define  OR(o,x,y) fprintf(out, "\tOR(%s, %s, %s);\n", o, x, y)
#define EOR(o,x,y) fprintf(out, "\tEOR(%s, %s, %s);\n", o, x, y)
#define AND(o,x,y) fprintf(out, "\tAND(%s, %s, %s);\n", o, x, y)
#define ADD(o,x,y) fprintf(out, "\tADD(%s, %s, %s);\n", o, x, y)
#define SUB(o,x,y) fprintf(out, "\tSUB(%s, %s, %s);\n", o, x, y)
#define ADC(o,x,y) fprintf(out, "\tADC(%s, %s, %s);\n", o, x, y)
#define SBC(o,x,y) fprintf(out, "\tSBC(%s, %s, %s);\n", o, x, y)
#define COM(o,x) fprintf(out, "\tCOM(%s, %s);\n", o, x)
#define NEG(o,x) fprintf(out, "\tNEG(%s, %s);\n", o, x)
#define ASL(o,x) fprintf(out, "\tASL(%s, %s);\n", o, x)
#define ROL(o,x) fprintf(out, "\tROL(%s, %s);\n", o, x)
#define ROR(o,x) fprintf(out, "\tROR(%s, %s);\n", o, x)
#define PUSHWORD(x) fprintf(out, "\tPUSHWORD(%s);\n", x)
#define PULLWORD(x) fprintf(out, "\tPULLWORD(%s);\n", x)
#define MCU_WRMEM(addr, x) fprintf(out, "\tMCU_WRMEM(%s, %s);\n", addr, x)
#define BSET(addr, x) fprintf(out, "\tBSET(%s, %s);\n", addr, x)
#define BCLR(addr, x) fprintf(out, "\tBCLR(%s, %s);\n", addr, x)
#define BRCLR(addr, x) fprintf(out, "\tBRCLR(%s, %s)\n", addr, x)
#define BRSET(addr, x) fprintf(out, "\tBRSET(%s, %s)\n", addr, x)
#define IF_CC(x) fprintf(out, "\tIF_CC_" #x "()\n")
#define JUMP(addr) fprintf(out, "\tJUMP(%s);\n", addr)
#define JUMP_IMM(addr) \
   if (pc_used[((int)strtoul(addr, NULL, 16)) & (MAX_PC-1)]) \
      fprintf(out, "\tJUMP_IMM(0x%.3x);\n", ((int)strtoul(addr, NULL, 16)) & (MAX_PC-1)); \
   else fprintf(out, "\tgoto invalid_pc;\n");
#define PUSH_NEXT_PC() fprintf(out, "\tPUSHWORD(0x%.3x);\n", next_pc[((int)strtoul(pc, NULL, 16))])

void NextLine(FILE *file)
{
   int c;
   do {
      c = fgetc(file);
   } while(c != '\n' && c != EOF && c != 0);
}

FILE *MakeJumpTable(char *filename)
{
   FILE *f;
   char buf[10];
   int pc, last_actual;

   f = fopen(filename, "r");
   if (!f)
   {
      printf("%s not found\n", filename);
      exit(1);
   }
   if (fscanf(f, "%s %x", &buf[0], &init_pc) != 2) return NULL;

   fprintf(out, "\n\tstatic const M68705_JumpTable jump_table[] = {\n");

   for (pc=0;pc<MAX_PC;pc++) pc_used[pc] = FALSE;

   last_actual = -1;
   while(!feof(f))
   {
      if (fscanf(f, "%x", &pc) != 1) break;
      if (last_actual != -1) next_pc[last_actual] = pc;

      fprintf(out, "\t\t{ 0x%.3x, &&L0x%.3x },\n", pc, pc);
      pc_used[pc] = TRUE;
      last_actual = pc;
      NextLine(f);
   }

   fprintf(out, "\t\t{ 0, NULL }\n\t};\n\n"
                "\tif (!unpacked) { M68705_Unpack(&jump_table[0], &&invalid_pc); unpacked=1; }\n\n"
                "/* code starts here */\n");
   fseek(f, 0, SEEK_SET);
   if (fscanf(f, "%s %x", &buf[0], &init_pc) != 2) return NULL;
   return f;
}

int main(int argc, char *argv[])
{
   char pc[100], buf[100], tmp[10];
   char in_name[200], out_name[200], prefix[200];

   if (argc != 4)
   {
      printf("Usage: CONV prefix filename.asm emufile.c\n");
      return 1;
   }

   strcpy(&prefix[0], argv[1]);
   strcpy(&in_name[0], argv[2]);
   strcpy(&out_name[0], argv[3]);

   out = fopen(out_name, "w");
   if (!out)
   {
      perror(out_name);
      return 1;
   }

   fprintf(out, "/* Auto-generated from %s! Do not modify! */\n\n"
                "#include \"raine.h\"\n"
                "#include \"debug.h\"\n"
                "#include \"ingame.h\"\n\n", in_name);

   fprintf(out, "UINT8 %s_MCU_RDMEM(int a);\n"
                "void %s_MCU_WRMEM(int a, UINT8 v);\n"
                "#define MCU_RDMEM(a) %s_MCU_RDMEM(a)\n"
                "#define MCU_WRMEM(a,v) %s_MCU_WRMEM(a,v)\n\n",
                prefix, prefix, prefix, prefix);

   fprintf(out, "#include \"m68705.h\"\n\n");

   fprintf(out, "static int unpacked;\n\n");

   fprintf(out, "void %s_mcu_reset(void)\n{\n"
                "\tm68705.pc = MCU_RDMEM(0x7ff) | (MCU_RDMEM(0x7fe) << 8);\n"
                "\tm68705.sp = 0x7f;\n"
                "\tm68705.a = m68705.x = 0x00;\n"
                "\tm68705.flag_i = 0;\n"
                "\tm68705.flag_n = m68705.flag_h = m68705.flag_z = m68705.flag_c = 0;\n"
                "\tunpacked = 0;\n"
                "}\n\n", prefix);

   fprintf(out, "void %s_mcu(int bih_count)\n{\n"
                "\tUINT8 temp, dummy;\n"
                "\tUINT16 addr;\n"
                "\tUINT8 x = m68705.x;\n"
                "\tUINT8 a = m68705.a;\n"
                "\tUINT16 sp = m68705.sp;\n"
                "\tUINT8 flag_c = m68705.flag_c;\n"
                "\tUINT8 flag_h = m68705.flag_h;\n"
                "\tUINT8 flag_n = m68705.flag_n;\n"
                "\tUINT8 flag_z = m68705.flag_z;\n", prefix);

   in = MakeJumpTable(in_name);

   JUMP("m68705.pc");
   while(!feof(in))
   {
      if (fscanf(in, "%s %s", &pc[0], &buf[0]) != 2) break;

      fprintf(out, "\nL%s:\t/* %s */\n", pc, buf);
      if ((int)strtoul(pc, NULL, 16) == init_pc) fprintf(out, "//INIT_PC\n");

      if (!strcmp(buf, "nop"))
      {
      } else if (!strcmp(buf, "ldx"))
      {
         GetParam1(TRUE);
         fprintf(out, "\tx = %s;\n", param1);
         SET_NZ("x");
      } else if (!strcmp(buf, "stx"))
      {
         GetParam1(FALSE);
         SET_NZ("x");
         MCU_WRMEM(param1, "x");
      } else if (!strcmp(buf, "lda"))
      {
         GetParam1(TRUE);
         fprintf(out, "\ta = %s;\n", param1);
         SET_NZ("a");
      } else if (!strcmp(buf, "sta"))
      {
         GetParam1(FALSE);
         SET_NZ("a");
         MCU_WRMEM(param1, "a");
      } else if (!strcmp(buf, "clr"))
      {
         GetParam1(TRUE);
         fprintf(out, "\ttemp = 0;\n");
         SET_NZ("temp");
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "tax"))
      {
         fprintf(out, "\tx = a;\n");
      } else if (!strcmp(buf, "txa"))
      {
         fprintf(out, "\ta = x;\n");
      } else if (!strcmp(buf, "clra"))
      {
         fprintf(out, "\ta = 0;\n");
         SET_NZ("a");
      } else if (!strcmp(buf, "clrx"))
      {
         fprintf(out, "\tx = 0;\n");
         SET_NZ("x");
      } else if (!strcmp(buf, "inc"))
      {
         GetParam1(TRUE);
         INC("temp", param1);
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "inca"))
      {
         INC("a", "a");
      } else if (!strcmp(buf, "incx"))
      {
         INC("x", "x");
      } else if (!strcmp(buf, "dec"))
      {
         GetParam1(TRUE);
         DEC("temp", param1);
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "deca"))
      {
         DEC("a", "a");
      } else if (!strcmp(buf, "decx"))
      {
         DEC("x", "x");
      } else if (!strcmp(buf, "adda"))
      {
         GetParam1(TRUE);
         ADD("a", "a", param1);
      } else if (!strcmp(buf, "suba"))
      {
         GetParam1(TRUE);
         SUB("a", "a", param1);
      } else if (!strcmp(buf, "adca"))
      {
         GetParam1(TRUE);
         ADC("a", "a", param1);
      } else if (!strcmp(buf, "sbca"))
      {
         GetParam1(TRUE);
         SBC("a", "a", param1);
      } else if (!strcmp(buf, "cpx"))
      {
         GetParam1(TRUE);
         SUB("temp", "x", param1);
      } else if (!strcmp(buf, "neg"))
      {
         GetParam1(TRUE);
         NEG("temp", param1);
         SET_NZ("temp");
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "nega"))
      {
         NEG("a", "a");
         SET_NZ("a");
      } else if (!strcmp(buf, "negx"))
      {
         NEG("x", "x");
         SET_NZ("x");
      } else if (!strcmp(buf, "cmpa"))
      {
         GetParam1(TRUE);
         SUB("temp", "a", param1);
      } else if (!strcmp(buf, "coma"))
      {
         COM("a", "a");
         SET_NZ("a");
      } else if (!strcmp(buf, "comx"))
      {
         COM("x", "x");
         SET_NZ("x");
      } else if (!strcmp(buf, "asl"))
      {
         GetParam1(TRUE);
         ASL("temp", param1);
         SET_NZ("temp");
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "asla"))
      {
         ASL("a", "a");
         SET_NZ("a");
      } else if (!strcmp(buf, "aslx"))
      {
         ASL("x", "x");
         SET_NZ("x");
      } else if (!strcmp(buf, "rol"))
      {
         GetParam1(TRUE);
         ROL("temp", param1);
         SET_NZ("temp");
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "rola"))
      {
         ROL("a", "a");
         SET_NZ("a");
      } else if (!strcmp(buf, "rolx"))
      {
         ROL("x", "x");
         SET_NZ("x");
      } else if (!strcmp(buf, "ror"))
      {
         GetParam1(TRUE);
         ROR("temp", param1);
         SET_NZ("temp");
         MCU_WRMEM("addr", "temp");
      } else if (!strcmp(buf, "rora"))
      {
         ROR("a", "a");
         SET_NZ("a");
      } else if (!strcmp(buf, "rorx"))
      {
         ROR("x", "x");
         SET_NZ("x");
      } else if (!strcmp(buf, "tst"))
      {
         GetParam1(TRUE);
         SET_NZ(param1);
      } else if (!strcmp(buf, "tsta"))
      {
         SET_NZ("a");
      } else if (!strcmp(buf, "tstx"))
      {
         SET_NZ("x");
      } else if (!strcmp(buf, "anda"))
      {
         GetParam1(TRUE);
         AND("a", "a", param1);
         SET_NZ("a");
      } else if (!strcmp(buf, "ora"))
      {
         GetParam1(TRUE);
         OR("a", "a", param1);
         SET_NZ("a");
      } else if (!strcmp(buf, "eora"))
      {
         GetParam1(TRUE);
         EOR("a", "a", param1);
         SET_NZ("a");
      } else if (!strcmp(buf, "asrx"))
      {
         fprintf(out, "\tflag_c = x & 0x01;\n"
                      "\tx = ((UINT8)x) >> 1;\n");
         SET_NZ("x");
      } else if (!strcmp(buf, "lsra"))
      {
         fprintf(out, "\tflag_c = a & 0x01;\n"
                      "\ta >>= 1;\n");
         SET_NZ("a");
      } else if (!strcmp(buf, "lsrx"))
      {
         fprintf(out, "\tflag_c = x & 0x01;\n"
                      "\tx >>= 1;\n");
         SET_NZ("x");
      } else if (!strcmp(buf, "jmp"))
      {
         GetParam1(FALSE);
         JUMP_IMM(param1);
      } else if (!strcmp(buf, "jsr"))
      {
         GetParam1(FALSE);
         PUSH_NEXT_PC();
         JUMP_IMM(param1);
      } else if (!strcmp(buf, "bra"))
      {
         GetParam1(FALSE);
         JUMP_IMM(param1);
      } else if (!strcmp(buf, "bsr"))
      {
         GetParam1(FALSE);
         PUSH_NEXT_PC();
         JUMP_IMM(param1);
      } else if (!strcmp(buf, "beq"))
      {
         GetParam1(FALSE);
         IF_CC(Z); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bne"))
      {
         GetParam1(FALSE);
         IF_CC(NZ); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bcc"))
      {
         GetParam1(FALSE);
         IF_CC(NC); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bcs"))
      {
         GetParam1(FALSE);
         IF_CC(C); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bmi"))
      {
         GetParam1(FALSE);
         IF_CC(N); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bpl"))
      {
         GetParam1(FALSE);
         IF_CC(NN); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bhcs"))
      {
         GetParam1(FALSE);
         IF_CC(H); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bhcc"))
      {
         GetParam1(FALSE);
         IF_CC(NH); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bls"))
      {
         GetParam1(FALSE);
         IF_CC(LS); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bhi"))
      {
         GetParam1(FALSE);
         IF_CC(HI); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bms"))
      {
         GetParam1(FALSE);
         IF_CC(int); JUMP_IMM(param1);
      } else if (!strcmp(buf, "bmc"))
      {
         GetParam1(FALSE);
         IF_CC(Nint); JUMP_IMM(param1);
      } else if (!strcmp(buf, "rts"))
      {
         PULLWORD("m68705.pc");
         JUMP("m68705.pc");
      } else if (!strncmp(buf, "bset", 4))
      {
         GetParam1(FALSE);
         tmp[0] = buf[4];
         tmp[1] = 0;
         BSET(param1, tmp);
      } else if (!strncmp(buf, "bclr", 4))
      {
         GetParam1(FALSE);
         tmp[0] = buf[4];
         tmp[1] = 0;
         BCLR(param1, tmp);
      } else if (!strncmp(buf, "brclr", 5))
      {
         GetParam1(FALSE);
         GetParam2(FALSE);
         tmp[0] = buf[5];
         tmp[1] = 0;
         BRCLR(param1, tmp); JUMP_IMM(param2);
      } else if (!strncmp(buf, "brset", 5))
      {
         GetParam1(FALSE);
         GetParam2(FALSE);
         tmp[0] = buf[5];
         tmp[1] = 0;
         BRSET(param1, tmp); JUMP_IMM(param2);
      } else if (!strcmp(buf, "bih"))
      {
         fprintf(out, "//BIH 0x%.3x\n", next_pc[strtoul(pc, NULL, 16)]);
         fprintf(out, "\tif (--bih_count == 0) {\n"
                      "\tm68705.pc = 0x%.3x;\n"
                      "\tm68705.x = x;\n"
                      "\tm68705.a = a;\n"
                      "\tm68705.sp = sp;\n"
                      "\tm68705.flag_c = flag_c;\n"
                      "\tm68705.flag_h = flag_h;\n"
                      "\tm68705.flag_n = flag_n;\n"
                      "\tm68705.flag_z = flag_z;\n"
                      "\treturn;\n"
                      "\t}\n", next_pc[strtoul(pc, NULL, 16)]);

      } else if (!strcmp(buf, "bil"))
      {
      } else if (!strcmp(buf, "clc"))
      {
         fprintf(out, "\tflag_c = 0;\n");
      } else if (!strcmp(buf, "sec"))
      {
         fprintf(out, "\tflag_c = 1;\n");
      } else if (!strcmp(buf, "rsp"))
      {
         fprintf(out, "\tsp = 0x7f;\n");
      } else if (!strcmp(buf, "sei"))
      {
         fprintf(out, "\tm68705.flag_i = 1;\n");
      } else if (!strcmp(buf, "cli"))
      {
         fprintf(out, "\tm68705.flag_i = 0;\n");
      } else {
         fprintf(out, "//invalid instruction!\n"
                      "\tgoto invalid_pc;\n");
      }

      NextLine(in);
   }

   fprintf(out, "\ninvalid_pc:\n"
                "#ifdef HACKS\n"
                "\t\tprint_debug(\"M68705: Invalid jump address (0x%%x)\\n\", m68705.pc);\n"
                "\t\tprint_ingame(200, \"M68705: Invalid jump address (0x%%x)\\n\", m68705.pc);\n"
                "#endif\n"
                "\treturn;\n"
                "}\n");
   fclose(in);
   fclose(out);
   return 0;
}
