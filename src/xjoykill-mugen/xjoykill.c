/*
 * Batocera.PLUS
 * Alexandre Freire dos Santos.
 * alexxandre.freire@gmail.com
 */

int procargs(int argc, char *argv[]);
int output(int *buttons);

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <X11/Xlib.h>

/* Maximum Number of supported Buttons */
#define MAXBUTTONS 16

/* USB-Message Constants */
#define SRC 6
#define NUM 7
#define VAL 4

int id_buttons[MAXBUTTONS];

char *devicefilename = "/dev/input/js0";
char command_kill[1024];
char command_esc[1024];
int verbose          = 0;

char *displayname    = NULL;
Display *mydisp;

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    unsigned char msg[8];
    int           buttons[MAXBUTTONS];
    int           i        = 0;
    int           file;
    short         value;
    int           finished = 0;
    int           exit     = 0;

    /* Initialize Buttons */
    for (i = 0; i < MAXBUTTONS; i++)
    {
        buttons[i]    = 0;
        id_buttons[i] = 0;
    }

    /* Help Parameters */
    if (i = procargs(argc, argv))
    {
        if (i == 2)
        {
          fprintf(stderr, "usage: %s [-display display] [-device filename] [-verbose] [-hotkey keycode] [-start keycode] [-select keycode] [-kill program] [-esc program]\n", argv[0]);
        }
        return 1;
    }

    /* Open X Display */
    mydisp = XOpenDisplay(displayname);

    if (!mydisp)
    {
        fprintf(stderr, "%s: cannot open Display\n", argv[0]);
        return 2;
    }

    file = open(devicefilename, O_RDONLY);

    if (file == -1)
    {
        fprintf(stderr, "%s: cannot open Device\n", argv[0]);
        return 3;
    }

    while (!finished)
    {
        i = read(file, msg, sizeof(msg));

        if (i < 8)
        {
            finished = 1;
        }

        if (msg[SRC] == 1) /* Somente botões */
        {
            if (msg[NUM] < MAXBUTTONS)
            {
                if (buttons[msg[NUM]] != msg[VAL])
                {
                    if (msg[VAL])
                    {
                        if (msg[NUM] == id_buttons[0]) /* hotkey */
                        {
                            if (exit == 1)
                            {
                                system(command_kill);
                                return 0;
                            }
                            else
                            {
                                exit = 1;
                            }
                        }
                        else if (msg[NUM] == id_buttons[1]) /* start */
                        {
                            if (exit == 1)
                            {
                                system(command_kill);
                                return 0;
                            }
                            else
                            {
                                exit = 1;
                            }
                        }
                        else if (msg[NUM] == id_buttons[2]) /* select */
                        {
                            system(command_esc);
                        }
                        else
                        {
                            exit = 0;
                        }
                    }
                    else
                    {
                        exit = 0;
                    }
                    buttons[msg[NUM]] = msg[VAL];
                }
            }
        }

        if (verbose)
        {
            output(buttons);
        }
    }

    close(file);
    XCloseDisplay(mydisp);
}

/*----------------------------------------------------------------------------*/


int output(int *buttons)
{
    int i = 0;

    for (i = 0; i < MAXBUTTONS; i++)
    {
        if (buttons[i])
        {
            printf("B%i ", i);
        }
    }

    printf("\n");

    return 0;
}

/*----------------------------------------------------------------------------*/

int procargs(int argc, char *argv[])
{
    int i;
    int j;

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-device"))
        {
            i++;

            if (i < argc)
            {
                if (argv[i][0] == '/')
                {
		    devicefilename=argv[i];
                }
                else
                {
                    devicefilename=malloc(strlen(argv[i]) + 20);

                    if (devicefilename)
                    {
                        sprintf(devicefilename, "/dev/input/%s", argv[i]);
                    }
                    else
                    {
                        fprintf(stderr, "%s: malloc error\n", argv[0]);
                        return 1;
                    }
                }
            }
            else
            {
                fprintf(stderr, "%s: Devicefilename missing\n", argv[0]);
                return 2;
            }
        }
        else if (!strcmp(argv[i], "-display"))
        {
            i++;

            if (i < argc)
            {
                displayname = argv[i];
            }
            else
            {
                fprintf(stderr, "%s: Displayname missing\n", argv[0]);
                return 2;
            } 
        }
        else if (!strcmp(argv[i], "-hotkey"))
        {
            i++;

            if (atoi(argv[i]))
            {
                id_buttons[0] = atoi(argv[i]);
            }
        }
        else if (!strcmp(argv[i], "-start"))
        {
            i++;

            if (atoi(argv[i]))
            {
                id_buttons[1] = atoi(argv[i]);
            }
        }
        else if (!strcmp(argv[i], "-select"))
        {
            i++;

            if (atoi(argv[i]))
            {
                id_buttons[2] = atoi(argv[i]);
            }
        }
        else if (!strcmp(argv[i], "-kill"))
        {
            i++;
            if (!strcpy(command_kill, argv[i]))
            {
                printf("Program to kill missing");
            }
         }
        else if (!strcmp(argv[i], "-esc"))
        {
            i++;
            if (!strcpy(command_esc, argv[i]))
            {
                printf("Program to esc missing");
            }
         }
        else if (!strcmp(argv[i], "-verbose"))
        {
            verbose = 1;
        }
        else
        {
            fprintf(stderr, "%s: unknown option %s\n", argv[0], argv[i]);
            return 2;
        }
    }

    return 0;
}

