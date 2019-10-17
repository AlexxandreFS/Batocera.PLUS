
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  UINT16 adr;
  UINT16 content;
} tclassic_break;

#define MAX_BREAK 10

extern tclassic_break classic_bl[MAX_BREAK];

int break_proc(int msg, DIALOG *d, int c);

#ifdef __cplusplus
}
#endif
