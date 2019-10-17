/***************************************************************************/
/*  xjoypad.c - USB-Joypad to X-Event Converter V0.02                      */
/***************************************************************************/
/* Copyright (C) 2002 Erich Kitzmüller  erich.kitzmueller@itek.at          */
/***************************************************************************/
/* This program is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation; either version 2 of the License, or       */
/* (at your option) any later version.                                     */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with tis program; if not, write to the Free Software              */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston MA  02111-1307 USA */
/***************************************************************************/
int sendevent(int typ, int keycode);
int procargs(int argc, char *argv[]);
int output (int up, int down, int left, int right, int *buttons, int throttle);

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/Xlib.h>

/* Maximum Number of supported Buttons */
#define MAXBUTTONS 32

/* Zero-Range for analog Joysticks */
/* not tested, I have no idea if these values are reasonable */
#define MINZERO -100
#define MAXZERO  100

/* USB-Message Constants */
#define SRC 6
#define NUM 7
#define VAL 4


int keycode_up    = 98;
int keycode_down  = 104;
int keycode_left  = 100;
int keycode_right = 102;

int keycode_button[MAXBUTTONS];

char *devicefilename = "/dev/input/js0";
int verbose=0;

char *displayname = NULL;
extern Display *mydisp;

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {

    unsigned char msg[8];

    int   left  = 0;
    int   right = 0;
    int   up    = 0;
    int   down  = 0;

    int   buttons[MAXBUTTONS];
    int   i        = 0;
    int   file;
    short value;
    short throttle = 0;  /* currently I have no use for throttle, but I want to keep the code */
    int   finished = 0;

    /* Initialize Buttons */
    for (i = 0; i < MAXBUTTONS; i++)
    {
        buttons[i] = 0;

        if (i < 10)
        {
            keycode_button[i] = 10 + i;
        }
        else
        {
            keycode_button[i] = 14 + i;
        }
    }


    /* Prozess Input Parameters */
    if (i = procargs(argc, argv))
    {
        if (i == 2)
        {
          fprintf(stderr, "usage: %s [-display display] [-devicefilename filename] [-verbose] [-up keycode] [-down keycode] [-left keycode] [-right keycode] [-buttons keycode keycode ...]\n", argv[0]);
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
        i = read (file, msg, 8);

        if (i < 8)
        {
            finished = 1;
        }
        else
        {
            if (msg[SRC] == 2) /* stick or pad */
            {
                value = msg[VAL] + 256 * msg[VAL + 1];

                if ((msg[NUM] == 1) || (msg[NUM] == 7)) /* Adicionei 7 para o controle PS4 */
                {
                    if (value > MAXZERO)
                    {
                        if (up)
                        {
                            sendevent(KeyRelease, keycode_up);
                        }

                        if (!down)
                        {
                            sendevent(KeyPress, keycode_down);
                        }

                        down = 1;
                        up   = 0;
                    }
                    else if (value < MINZERO)
                    {
                        if (down)
                        {
                            sendevent(KeyRelease, keycode_down);
                        }

                        if (!up)
                        {
                            sendevent(KeyPress, keycode_up);
                         }

                        down = 0;
                        up   = 1;
                    }
                    else
                    {
                        if (up)
                        {
                            sendevent(KeyRelease, keycode_up);
                        }

                        if (down)
                        {
                            sendevent(KeyRelease, keycode_down);
                        }

                        down = 0;
                        up   = 0;
                    }
                }

                if ((msg[NUM] == 0) || (msg[NUM] == 6)) /* Adicionei 6 para o controle PS4 */
                {
                    if (value > MAXZERO)
                    {
                        if (left)
                        {
                            sendevent(KeyRelease, keycode_left);
                        }

                        if (!right)
                        {
                            sendevent(KeyPress, keycode_right);
                        }

                        right = 1;
                        left  = 0;
                    }
                    else if (value < MINZERO)
                    {
                        if (right)
                        {
                            sendevent(KeyRelease, keycode_right);
                        }

                        if (!left)
                        {
                            sendevent(KeyPress, keycode_left);
                        }

                        right = 0;
                        left  = 1;
                    }
                    else
                    {
                        if (left)
                        {
                            sendevent(KeyRelease, keycode_left);
                        }

                        if (right)
                        {
                            sendevent(KeyRelease, keycode_right);
                        }

                        right = 0;
                        left  = 0;
                    }
                }

                if (msg[NUM] == 2)
                {
                    throttle = value;
                }
            }
  

            if (msg[SRC] == 1) /* Button */
            {
                if (msg[NUM] < MAXBUTTONS)
                {
                    if (buttons[msg[NUM]] != msg[VAL])
                    {
                        sendevent(msg[VAL] ? KeyPress : KeyRelease, keycode_button[msg[NUM]]);
                        buttons[msg[NUM]] = msg[VAL];
                    }
                }
            }
        }

        if (verbose)
        {
            output(up, down, left, right, buttons, throttle);
        }
    }

    close(file);
    XCloseDisplay(mydisp);
}


/*----------------------------------------------------------------------------*/


int output (int up, int down, int left, int right, int *buttons, int throttle)
{
    int i = 0;

    printf("%d ", throttle);

    if (up)
    {
        printf("%s", "UP ");
    }

    if (down)
    {
        printf("%s", "DOWN ");
    }

    if (left)
    {
        printf("%s", "LEFT ");
    }

    if (right)
    {
        printf("%s", "RIGHT ");
    }

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
        else if (!strcmp(argv[i], "-up"))
        {
            i++;

            if (i < argc)
            {
                keycode_up = atoi(argv[i]);

                if (!keycode_up)
                {
                    fprintf(stderr, "%s: Bad Keycode for -up\n", argv[0]);
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "%s: Keycode for -up missing\n", argv[0]);
                return 2;
            }
        }
        else if (!strcmp(argv[i], "-down"))
        {
            i++;

            if (i < argc)
            {
                keycode_down=atoi(argv[i]);

                if (!keycode_down)
                {
                    fprintf(stderr, "%s: Bad Keycode for -down\n", argv[0]);
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "%s: Keycode for -down missing\n", argv[0]);
                return 2;
            }
        }
        else if (!strcmp(argv[i], "-left"))
        {
            i++;

            if (i < argc)
            {
                keycode_left = atoi(argv[i]);

                if (!keycode_left)
                {
                    fprintf(stderr, "%s: Bad Keycode for -left\n", argv[0]);
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "%s: Keycode for -left missing\n", argv[0]);
                return 2;
            }
        }
        else if (!strcmp(argv[i], "-right"))
        {
            i++;

            if (i < argc)
            {
            keycode_right = atoi(argv[i]);

                if (!keycode_right)
                {
                    fprintf(stderr, "%s: Bad Keycode for -right\n", argv[0]);
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "%s: Keycode for -right missing\n", argv[0]);
                return 2;
            }
        }
        else if (!strcmp(argv[i], "-buttons"))
        {
            for (j = 0, i++; j < MAXBUTTONS && i < argc && argv[i][0] >= '0' && argv[i][0] <= '9'; i++, j++)
            {
                if (atoi(argv[i]))
                {
                    keycode_button[j] = atoi(argv[i]);
                }
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

