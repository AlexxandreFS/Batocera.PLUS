/*
 *   A quick-hack 68(7)05 disassembler
 *   Written by Aaron Giles,
 *   converted to a command-line disassembler by Richard Mitton.
 *
 *   Note: this is not the good and proper way to disassemble anything, but it works
 *
 *   I'm afraid to put my name on it, but I feel obligated:
 *   This code written by Aaron Giles (agiles@sirius.com) for the MAME project
 *
 */

#include <string.h>
#include <stdio.h>

static char *opcode_strings[0x0100] =
{
	"brset0", 	"brclr0", 	"brset1", 	"brclr1", 	"brset2", 	"brclr2",	"brset3",	"brclr3",		/*00*/
	"brset4",	"brclr4",	"brset5",	"brclr5",	"brset6",	"brclr6",	"brset7",	"brclr7",
	"bset0",	"bclr0",	"bset1", 	"bclr1", 	"bset2", 	"bclr2", 	"bset3",	"bclr3",		/*10*/
	"bset4", 	"bclr4",	"bset5", 	"bclr5",	"bset6", 	"bclr6", 	"bset7", 	"bclr7",
	"bra",		"brn",		"bhi",		"bls",		"bcc",		"bcs",		"bne",		"beq",			/*20*/
	"bhcc",		"bhcs",		"bpl",		"bmi",		"bmc",		"bms",		"bil",		"bih",
	"neg_di",	"illegal", 	"illegal", 	"com_di",	"lsr_di",	"illegal", 	"ror_di",	"asr_di",		/*40*/
	"asl_di",	"rol_di",	"dec_di",	"illegal", 	"inc_di",	"tst_di",	"illegal", 	"clr_di",
	"nega",		"illegal", 	"illegal", 	"coma",		"lsra",		"illegal", 	"rora",		"asra",			/*40*/
	"asla",		"rola",		"deca",		"illegal", 	"inca",		"tsta",		"illegal", 	"clra",
	"negx",		"illegal", 	"illegal", 	"comx",		"lsrx",		"illegal", 	"rorx",		"asrx",			/*50*/
	"aslx",		"rolx",		"decx",		"illegal", 	"incx",		"tstx",		"illegal", 	"clrx",
	"neg_ix1",	"illegal", 	"illegal", 	"com_ix1",	"lsr_ix1",	"illegal", 	"ror_ix1",	"asr_ix1",		/*60*/
	"asl_ix1",	"rol_ix1",	"dec_ix1",	"illegal", 	"inc_ix1",	"tst_ix1",	"jmp_ix1",	"clr_ix1",
	"neg_ix",	"illegal", 	"illegal", 	"com_ix",	"lsr_ix",	"illegal", 	"ror_ix",	"asr_ix",		/*70*/
	"asl_ix",	"rol_ix",	"dec_ix",	"illegal", 	"inc_ix",	"tst_ix",	"jmp_ix",	"clr_ix",
	"rti",		"rts",		"illegal",	"swi",		"illegal",	"illegal",	"illegal",	"illegal",		/*80*/
	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",
	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"illegal",	"tax",			/*90*/
	"clc",		"sec",		"cli",		"sei",		"rsp",		"nop",		"illegal",	"txa",
	"suba_im",	"cmpa_im",	"sbca_im",	"cpx_im", 	"anda_im",	"bita_im",	"lda_im",	"illegal",		/*A0*/
	"eora_im",	"adca_im",	"ora_im",	"adda_im",	"illegal",	"bsr",		"ldx_im",	"illegal",
	"suba_di",	"cmpa_di",	"sbca_di",	"cpx_di", 	"anda_di",	"bita_di",	"lda_di",	"sta_di",		/*B0*/
	"eora_di",	"adca_di",	"ora_di",	"adda_di",	"jmp_di",	"jsr_di",	"ldx_di",	"stx_di",
	"suba_ex",	"cmpa_ex",	"sbca_ex",	"cpx_ex", 	"anda_ex",	"bita_ex",	"lda_ex",	"sta_ex",		/*C0*/
	"eora_ex",	"adca_ex",	"ora_ex",	"adda_ex",	"jmp_ex",	"jsr_ex",	"ldx_ex",	"stx_ex",
	"suba_ix2",	"cmpa_ix2",	"sbca_ix2",	"cpx_ix2", 	"anda_ix2",	"bita_ix2",	"lda_ix2",	"sta_ix2",		/*D0*/
	"eora_ix2",	"adca_ix2",	"ora_ix2",	"adda_ix2",	"jmp_ix2",	"jsr_ix2",	"ldx_ix2",	"stx_ix2",
	"suba_ix1",	"cmpa_ix1",	"sbca_ix1",	"cpx_ix1", 	"anda_ix1",	"bita_ix1",	"lda_ix1",	"sta_ix1",		/*E0*/
	"eora_ix1",	"adca_ix1",	"ora_ix1",	"adda_ix1",	"jmp_ix1",	"jsr_ix1",	"ldx_ix1",	"stx_ix1",
	"suba_ix",	"cmpa_ix",	"sbca_ix",	"cpx_ix", 	"anda_ix",	"bita_ix",	"lda_ix",	"sta_ix",		/*F0*/
	"eora_ix",	"adca_ix",	"ora_ix",	"adda_ix",	"jmp_ix",	"jsr_ix",	"ldx_ix",	"stx_ix"
};


int Dasm6805 (unsigned char *base, char *buf, int pc)
{
	int code = *base++;
	char *opptr = opcode_strings[code];
	char opstr[20];
	char *p;

	strcpy (opstr, opptr);
	p = opstr + 3;
	if (*p != '_')
	{
		if (*++p != '_')
		{
			if (code < 0x10)
			{
			    sprintf (buf, "%-7s$%02x, $%04x", opstr, *base, (pc + 3 + *(signed char *)&base[1]) & 0xffff);
				return 3;
			}
			if (code < 0x20)
			{
				sprintf (buf, "%-7s$%02x", opstr, *base);
				return 2;
			}
			if ((code < 0x30) || code == 0xad)
			{
				sprintf (buf, "%-7s$%04x", opstr, (pc + 2 + *(signed char *)base) & 0xffff);
				return 2;
			}
			else
			{
				strcpy (buf, opstr);
				return 1;
			}
		}
	}

	*p++ = 0;
	if (*p == 'i')
	{
		if (*++p == 'x')
		{
			++p;
			if (*p == '1')
			{
				sprintf (buf, "%-7s(x+$%02x)", opstr, *base);
				return 2;
			}
			else if (*p == '2')
			{
				sprintf (buf, "%-7s(x+$%04x)", opstr, (base[0] << 8) + base[1]);
				return 3;
			}
			else
			{
				sprintf (buf, "%-7s(x)", opstr);
				return 1;
			}
		}
		else
		{
			sprintf (buf, "%-7s#$%02x", opstr, *base);
			return 2;
		}
	}
	else if (*p == 'd')
	{
		sprintf (buf, "%-7s$%02x", opstr, *base);
		return 2;
	}
	else
	{
		sprintf (buf, "%-7s$%04x", opstr, (base[0] << 8) + base[1]);
		return 3;
	}
}

unsigned char rom[0x800];

int main(int argc, char *argv[])
{
   FILE *file;
   int pc, n;
   char buf[200];

   if (argc != 3)
   {
      printf("Usage: DASM romname.bin dasmname.asm\n");
      return 1;
   }

   file = fopen(argv[1], "rb");
   if (!file)
   {
      printf("%s not found.\n", argv[1]);
      return 1;
   }
   fread(&rom[0], 1, 0x800, file);
   fclose(file);

   file = fopen(argv[2], "w");
   pc = rom[0x7ff] | (rom[0x7fe] << 8);
   fprintf(file, "#PC 0x%x\n", pc);

   pc = 0x80;
   do {
      n = Dasm6805(&rom[pc], &buf[0], pc);
      fprintf(file, "0x%.3x %s\n", pc, buf);
      pc += n;
   } while(pc < 0x800);
   fclose(file);
   return 0;
}
