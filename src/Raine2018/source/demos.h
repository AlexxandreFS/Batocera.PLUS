
#ifdef __cplusplus
extern "C" {
#endif

extern int recording_demo , reading_demo;
void GameSaveDemo(void);
void GameLoadDemo(void);

void save_demo_inputs(); // Must be called after inputs have been processed
// while recording a demo
void write_demo_inputs(); // The opposite : called instead of inputs processing
// while reading a demo
void stop_demo(); // Stop recording


#ifdef __cplusplus
}
#endif
