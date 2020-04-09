#ifdef __cplusplus
extern "C" {
#endif

struct dxsmpinterface
{
  char *dx_name;
  int mixing_level;			/* master volume */
};

int dxsmp_sh_start(const struct dxsmpinterface *intf);
void dxsmp_sh_stop(void);
int is_dxsmp_playing(int sample);
void read_dx_file();

extern int raine_nb_samples; // number of samples loaded
void raine_play_sample(int sample, int volume);
void raine_loop_sample(int sample, int volume);
void raine_stop_sample(int sample);
void raine_stop_samples();

#ifdef __cplusplus
}
#endif
