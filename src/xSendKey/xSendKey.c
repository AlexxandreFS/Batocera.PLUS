/* xSendKey
 * Autor: Alexandre Freire dos Santos
 * Email: alexxandre.freire@gmail.com
 * Version: 08/12/2018
 * Todos os direitos reservados 2018
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <sys/timeb.h>

int procargs(int argc, char *argv[]);
int sendKey(int keyCode);
int getKeyCode(char *key);
int sendEvent(int typ, int keycode);

Display *mydisp;

int main(int argc, char *argv[])
{
    if (procargs(argc, argv))
    {
        printf("xSendKey 1.0 - Batocera.Plus - alexxandre.freire@gmail.com\n");
        printf("usage: xSendKey up down left right enter esc space backspace alt\n");
        return 1;
    }

    mydisp = XOpenDisplay(NULL);

    if (!mydisp)
    {
        fprintf(stderr, "%s: cannot open Display\n", argv[0]);
        return 1;
    }

    //sleep(2);

    for (int i = 1; i < argc; i++)
    {
        sendKey(getKeyCode(argv[i]));
    }

    XCloseDisplay(mydisp);

    return 0;
}

/*
 * Retorna o código da tecla informada. 
 */
int getKeyCode(char *key)
{
    int up        = 111;
    int down      = 116;
    int left      = 113;
    int right     = 114;
    int enter     = 36;
    int esc       = 9;
    int space     = 65;
    int backspace = 22;
    int alt       = 64;

    if (!strcmp(key, "up"))
    {
        return up;
    }

    if (!strcmp(key, "down"))
    {
        return down;
    }

    if (!strcmp(key, "left"))
    {
        return left;
    }

    if (!strcmp(key, "right"))
    {
        return right;
    }

    if (!strcmp(key, "enter"))
    {
        return enter;
    }

    if (!strcmp(key, "esc"))
    {
        return esc;
    }

    if (!strcmp(key, "space"))
    {
        return space;
    }

    if (!strcmp(key, "backspace"))
    {
        return backspace;
    }
    if (!strcmp(key, "alt"))
    {
        return alt;
    }
    return 0;
}

/*
 * Verifica se os parâmetros de entrada são válidos.
 */
int procargs(int argc, char *argv[])
{
    int i = 0;

    if (argc < 2)
    {
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "up"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "down"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "left"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "right"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "enter"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "esc"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "space"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "backspace"))
        {
            continue;
        }
        else if (!strcmp(argv[i], "alt"))
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

/*
 * Simula o pressionar e soltar tecla
 */
int sendKey(int keycode)
{
    sendEvent(KeyPress, keycode);
    sendEvent(KeyRelease, keycode);

    return 0;
}

/*
 * Envia um comando para o servidor X.
 */
int sendEvent(int typ, int keycode)
{
	XEvent event;
	Window win;
	int    revert_to;
    struct timeb t;

    ftime(&t);
  
	XGetInputFocus(mydisp, &win, &revert_to);

	event.xkey.type        = typ;
	event.xkey.serial      = 0;
	event.xkey.send_event  = True;
	event.xkey.display     = mydisp;
	event.xkey.window      = win;
	event.xkey.root        = XDefaultRootWindow(mydisp);
	event.xkey.subwindow   = None;
	event.xkey.time        = t.time * 1000 + t.millitm;
	event.xkey.x           = 0;
	event.xkey.y           = 0;
	event.xkey.x_root      = 0;
	event.xkey.state       = 0;
	event.xkey.keycode     = keycode;
	event.xkey.same_screen = True;

	XSendEvent(mydisp, InputFocus, True, 3, &event);
    XFlush(mydisp);

	return 0;
}

