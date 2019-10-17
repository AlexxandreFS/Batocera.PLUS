#ifndef __MESSAGEBOX_H
#define __MESSAGEBOX_H

#define ErrorMsg(msg) MessageBox("Error",msg,"OK")

#ifdef __cplusplus
extern "C" {

int MessageBox(char *title, char *content, char *buttons = NULL);

}
#else
int MessageBox(char *title, char *content, char *buttons);
#endif

#endif

