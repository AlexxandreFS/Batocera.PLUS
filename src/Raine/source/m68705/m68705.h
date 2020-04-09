
#ifdef __cplusplus
extern "C" {
#endif
/* MCU (M68705) header file.
 *
 * This is for the statically-recompiled code.
 */

typedef struct {
   UINT8 x, a, flag_n, flag_h, flag_z, flag_c, flag_i;
   UINT16 sp, pc;
} M68705;

typedef struct {
   UINT16 addr;
   void *code;
} M68705_JumpTable;

extern M68705 m68705;
extern void *m68705_jump_table[];

void M68705_Unpack(const M68705_JumpTable *table, void *invalid);

/* CPU opcode functions */

#define SET_NZ(val) flag_n = (val); \
                    flag_z = (val)

#define INC(o,a)    (o) = (a)+1; \
                    flag_n = (o); \
                    flag_z = (o)

#define DEC(o,a)    (o) = (a)-1; \
                    flag_n = (o); \
                    flag_z = (o)

#define AND(o, a,b) (o) = (a) & (b);
#define  OR(o, a,b) (o) = (a) | (b);
#define EOR(o, a,b) (o) = (a) ^ (b);

#define NEG(o, a) flag_c = (a) != 0; \
                  (o) = -(a);

#define ASL(o, a) flag_c = (a) & 0x80; \
                  (o) = (a) << 1;

#define ROL(o, a) dummy = (a) & 0x80; \
                  (o) = ((a) << 1) | (flag_c ? 1 : 0); \
                  flag_c = dummy;
#define ROR(o, a) dummy = (a) & 0x01; \
                  (o) = ((a) >> 1) | (flag_c ? 0x80 : 0); \
                  flag_c = dummy;

#define COM(o, a) flag_c = 1; \
                  (o) = ~(a);

#define ADD(o, a,b) flag_c = ((a) + (b)) >> 8; \
                    (o) = (a) + (b); \
                    flag_h = (a) ^ (b) ^ (o); \
                    flag_n = (o); \
                    flag_z = (o)

#define SUB(o, a,b) flag_c = (b) > (a) ? 1 : 0; \
                    (o) = (a) - (b); \
                    flag_n = (o); \
                    flag_z = (o)

#define ADC(o, a,b) dummy = flag_c ? 1 : 0; \
                    flag_c = ((a) + (b) + dummy) >> 8; \
                    (o) = (a) + (b) + dummy; \
                    flag_h = (a) ^ (b) ^ (o); \
                    flag_n = (o); \
                    flag_z = (o)

#define SBC(o, a,b) dummy = flag_c ? 1 : 0; \
                    flag_c = ((b) + dummy) > (a) ? 1 : 0; \
                    (o) = (a) - ((b) + dummy); \
                    flag_n = (o); \
                    flag_z = (o)

#define PUSHWORD(val) MCU_WRMEM(sp-1, (val) >> 8); \
                      MCU_WRMEM(sp,   (val) & 0xff); \
                      sp -= 2

#define PULLWORD(val) sp += 2; \
                      val = (MCU_RDMEM(sp-1) << 8) | MCU_RDMEM(sp)

#define IF_CC_C() if (flag_c)
#define IF_CC_N() if (flag_n & 0x80)
#define IF_CC_Z() if (!flag_z)
#define IF_CC_H() if (flag_h & 0x10)
#define IF_CC_LS() if (flag_c && !flag_z)
#define IF_CC_int() if (m68705.flag_i)
#define IF_CC_NC() if (!flag_c)
#define IF_CC_NN() if (!(flag_n & 0x80))
#define IF_CC_NZ() if (flag_z)
#define IF_CC_NH() if (!(flag_h & 0x10))
#define IF_CC_HI() if (!flag_c && flag_z)
#define IF_CC_Nint() if (!m68705.flag_i)

#define BSET(addr, bit) MCU_WRMEM(addr, MCU_RDMEM(addr) | (1 << (bit)))
#define BCLR(addr, bit) MCU_WRMEM(addr, MCU_RDMEM(addr) & ~(1 << (bit)))
#define BRCLR(addr, bit) if (!(MCU_RDMEM(addr) & (1 << (bit))))
#define BRSET(addr, bit) if (MCU_RDMEM(addr) & (1 << (bit)))

#define JUMP(addr) goto *m68705_jump_table[addr];
#define JUMP_IMM(addr) do { m68705.pc = addr; goto L##addr; } while(0)

#ifdef __cplusplus
}
#endif
