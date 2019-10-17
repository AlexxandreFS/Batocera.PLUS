
#ifdef __cplusplus
extern "C" {
#endif

#if defined(RAINE_UNIX) && !defined(DARWIN)
#define hq2x_16 _hq2x_16
#define hq2x_32 _hq2x_32
#define hq3x_16 _hq3x_16
#define hq3x_32 _hq3x_32
#endif

void hq2x_16(BITMAP* src, BITMAP* dst, int x1, int y1, int x2, int y2, int w, int h);
void hq2x_32(BITMAP* src, BITMAP* dst, int x1, int y1, int x2, int y2, int w, int h);
void hq3x_16(BITMAP* src, BITMAP* dst, int x1, int y1, int x2, int y2, int w, int h);
void hq3x_32(BITMAP* src, BITMAP* dst, int x1, int y1, int x2, int y2, int w, int h);

#ifdef __cplusplus
}
#endif
