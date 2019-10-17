#ifdef __cplusplus
extern "C" {
#endif

extern int goto_debuger;

void read_gui_config();
void write_gui_config();
void setup_font();
void load_progress(char *rom,int count);
void load_message(char *msg);
void StartGUI(void);
#ifdef __cplusplus
}
#endif
