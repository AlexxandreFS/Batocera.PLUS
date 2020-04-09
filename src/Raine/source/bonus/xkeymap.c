/* xkeymap.c --- create mapping from X keycodes to Allegro scancodes
 *
 * Compile with : gcc -o keymap xkeymap.c -lalleg -lalleg_unsharable
 * it needs at least allegro-3.9.34 (in cvs at this time)
 *
 * This file is gift-ware.  This file is given to you freely
 * as a gift.  You may use, modify, redistribute, and generally hack
 * it about in any way you like, and you do not have to give anyone
 * anything in return.
 *
 * I do not accept any responsibility for any effects, adverse or
 * otherwise, that this code may have on just about anything that
 * you can think of.  Use it at your own risk.
 *
 * Copyright (C) 2000  Michael Bukin
 */

#include <stdio.h>

#include <allegro.h>
#include <xalleg.h>

static struct
{
  int key;
  char *string;
  int scancode;
} keymap[] =
{
  { KEY_ESC, "KEY_ESC", 0x01 },
  { KEY_F1, "KEY_F1", 0x3B },
  { KEY_F2, "KEY_F2", 0x3C },
  { KEY_F3, "KEY_F3", 0x3D },
  { KEY_F4, "KEY_F4", 0x3E },
  { KEY_F5, "KEY_F5", 0x3F },
  { KEY_F6, "KEY_F6", 0x40 },
  { KEY_F7, "KEY_F7", 0x41 },
  { KEY_F8, "KEY_F8", 0x42 },
  { KEY_F9, "KEY_F9", 0x43 },
  { KEY_F10, "KEY_F10", 0x44 },
  { KEY_F11, "KEY_F11", 0x57 },
  { KEY_F12, "KEY_F12", 0x58 },
  { KEY_PRTSCR, "KET_PRTSCR", 0x54 | 0x80 },
  { KEY_SCRLOCK, "KET_SCRLOCK", 0x46 },
  { KEY_PAUSE, "KEY_PAUSE", 0x00 | 0x100 },

  { KEY_TILDE, "KEY_TILDE", 0x29 },
  { KEY_1, "KEY_1", 0x02 },
  { KEY_2, "KEY_2", 0x03 },
  { KEY_3, "KEY_3", 0x04 },
  { KEY_4, "KEY_4", 0x05 },
  { KEY_5, "KEY_5", 0x06 },
  { KEY_6, "KEY_6", 0x07 },
  { KEY_7, "KEY_7", 0x08 },
  { KEY_8, "KEY_8", 0x09 },
  { KEY_9, "KEY_9", 0x0A },
  { KEY_0, "KEY_0", 0x0B },
  { KEY_MINUS, "KEY_MINUS", 0x0C },
  { KEY_EQUALS, "KEY_EQUALS", 0x0D },
  { KEY_BACKSLASH, "KEY_BACKSLASH", 0x2B },
  { KEY_BACKSPACE, "KEY_BACKSPACE", 0x0E },

  { KEY_TAB, "KEY_TAB", 0x0F },
  { KEY_Q, "KEY_Q", 0x10 },
  { KEY_W, "KEY_W", 0x11 },
  { KEY_E, "KEY_E", 0x12 },
  { KEY_R, "KEY_R", 0x13 },
  { KEY_T, "KEY_T", 0x14 },
  { KEY_Y, "KEY_Y", 0x15 },
  { KEY_U, "KEY_U", 0x16 },
  { KEY_I, "KEY_I", 0x17 },
  { KEY_O, "KEY_O", 0x18 },
  { KEY_P, "KEY_P", 0x19 },
  { KEY_OPENBRACE, "KEY_OPENBRACE", 0x1A },
  { KEY_CLOSEBRACE, "KEY_CLOSEBRACE", 0x1B },
  { KEY_ENTER, "KEY_ENTER", 0x1C },

  { KEY_CAPSLOCK, "KEY_CAPSLOCK", 0x3A },
  { KEY_A, "KEY_A", 0x1E },
  { KEY_S, "KEY_S", 0x1F },
  { KEY_D, "KEY_D", 0x20 },
  { KEY_F, "KEY_F", 0x21 },
  { KEY_G, "KEY_G", 0x22 },
  { KEY_H, "KEY_H", 0x23 },
  { KEY_J, "KEY_J", 0x24 },
  { KEY_K, "KEY_K", 0x25 },
  { KEY_L, "KEY_L", 0x26 },
  { KEY_COLON, "KEY_COLON", 0x27 },
  { KEY_QUOTE, "KEY_QUOTE", 0x28 },

  { KEY_LSHIFT, "KEY_LSHIFT", 0x2A },
  { KEY_Z, "KEY_Z", 0x2C },
  { KEY_X, "KEY_X", 0x2D },
  { KEY_C, "KEY_C", 0x2E },
  { KEY_V, "KEY_V", 0x2F },
  { KEY_B, "KEY_B", 0x30 },
  { KEY_N, "KEY_N", 0x31 },
  { KEY_M, "KEY_M", 0x32 },
  { KEY_COMMA, "KEY_COMMA", 0x33 },
  { KEY_STOP, "KEY_STOP", 0x34 },
  { KEY_SLASH, "KEY_SLASH", 0x35 },
  { KEY_RSHIFT, "KEY_RSHIFT", 0x36 },

  { KEY_LCONTROL, "KEY_LCONTROL", 0x1D },
  { KEY_LWIN, "KEY_LWIN", 0x5B | 0x80 },
  { KEY_ALT, "KEY_ALT", 0x38 },
  { KEY_SPACE, "KEY_SPACE", 0x39 },
  { KEY_ALTGR, "KEY_ALRGR", 0x38 | 0x80 },
  { KEY_RWIN, "KEY_RWIN", 0x5C | 0x80 },
  { KEY_MENU, "KEY_MENU", 0x5D | 0x80 },
  { KEY_RCONTROL, "KEY_RCONTROL", 0x1D | 0x80 },

  { KEY_INSERT, "KEY_INSERT", 0x52 | 0x80 },
  { KEY_HOME, "KEY_HOME", 0x47 | 0x80 },
  { KEY_PGUP, "KEY_PGUP", 0x49 | 0x80 },

  { KEY_DEL, "KEY_DEL", 0x53 | 0x80 },
  { KEY_END, "KEY_END", 0x4F | 0x80 },
  { KEY_PGDN, "KEY_PGDN", 0x51 | 0x80 },

  { KEY_UP, "KEY_UP", 0x48 | 0x80 },
  { KEY_LEFT, "KEY_LEFT", 0x4B | 0x80 },
  { KEY_DOWN, "KEY_DOWN", 0x50 | 0x80 },
  { KEY_RIGHT, "KEY_RIGHT", 0x4D | 0x80 },

  { KEY_NUMLOCK, "KEY_NUMLOCK", 0x45 },
  { KEY_SLASH_PAD, "KEY_SLASH_PAD", 0x35 | 0x80 },
  { KEY_ASTERISK, "KEY_ASTERISK", 0x37 },
  { KEY_MINUS_PAD, "KEY_MINUS_PAD", 0x4A | 0x80 },
  { KEY_7_PAD, "KEY_7_PAD", 0x47 },
  { KEY_8_PAD, "KEY_8_PAD", 0x48 },
  { KEY_9_PAD, "KEY_9_PAD", 0x49 },
  { KEY_PLUS_PAD, "KEY_PLUS_PAD", 0x4E },
  { KEY_4_PAD, "KEY_4_PAD", 0x4B },
  { KEY_5_PAD, "KEY_5_PAD", 0x4C },
  { KEY_6_PAD, "KEY_6_PAD", 0x4D },
  { KEY_1_PAD, "KEY_1_PAD", 0x4F },
  { KEY_2_PAD, "KEY_2_PAD", 0x50 },
  { KEY_3_PAD, "KEY_3_PAD", 0x51 },
  { KEY_ENTER_PAD, "KEY_ENTER_PAD", 0x1C | 0x80 },
  { KEY_0_PAD, "KEY_0_PAD", 0x52 },
  { KEY_DEL_PAD, "KEY_DEL_PAD", 0x53 },

  { KEY_BACKSLASH2, "KEY_BACKSLASH2", 0x56 | 0x80 },

  { KEY_YEN, "KEY_YEN", 0x73 },
  { KEY_YEN2, "KEY_YEN2", 0x7D },
  { KEY_KANA, "KEY_KANA", 0x70 },
  { KEY_HENKAN, "KEY_HENKAN", 0x79 },
  { KEY_MUHENKAN, "KEY_MUHENKAN", 0x7B },

  { 0, 0 }
};

static int black = 0;
static int white = 1;
static int red = 2;
static int yellow = 3;

static volatile int waiting_for_key = 0;
static volatile int new_keycode = 0;
static int keycode_to_scancode[256];

static void
get_raw_keycode (int pressed, int keycode)
{
  if (pressed && waiting_for_key)
    {
      new_keycode = keycode;
      waiting_for_key = 0;
    }
}

static void
setup_all_keys (void)
{
  int i, y, ymin, ymax;
  static char *welcome[] =
  {
    "Press a key to map to this scancode",
    "Press mouse button for next scancode",
    0
  };

  text_mode (-1);

  /* Clear screen and output prompt.  */
  clear_to_color (screen, white);
  for (i = 0; welcome[i] != 0; i++)
    textout (screen, font, welcome[i], 8, i * 8 + 8, black);

  ymin = i * 8 + 16;
  ymax = ymin + 8 * 8;
  y = ymin - 8;

  for (i = 0; keymap[i].string != 0; i++)
    {
      y += 8;
      if (y >= ymax)
	{
	  blit (screen, screen, 8, ymin + 8, 8, ymin, 200, ymax - ymin);
	  y -= 8;
	}

      textprintf (screen, font, 8, y, red, "scancode: %s", keymap[i].string);

      /* Wait while any mouse button is pressed.  */
      do
	{
	  poll_mouse ();
	}
      while (mouse_b);

      /* Wait for new key press.  */
      new_keycode = -1;
      waiting_for_key = 1;

      do
	{
	  poll_keyboard ();
	  poll_mouse ();

	  if (mouse_b)
	    waiting_for_key = 0;
	}
      while (waiting_for_key);

      /* Save keycode to scancode mapping.  */
      if ((new_keycode >= 0) && (new_keycode < 256))
	{
	  _xwin.keycode_to_scancode[new_keycode] = keymap[i].scancode;
	  keycode_to_scancode[new_keycode] = keymap[i].scancode;
	}
    }

  do
    {
      poll_keyboard ();
      poll_mouse ();
    }
  while ((key[KEY_MUHENKAN]) || (mouse_b));

  clear_keybuf ();
}

static void
test_key_map (void)
{
  int i;
  static int key_was_pressed[KEY_MAX + 1];
  static int key_is_pressed[KEY_MAX + 1];
  static char *welcome[] =
  {
    "Key that is pressed now is marked with red",
    "Key that was pressed is marked with yellow",
    "Press mouse button or Escape to exit test",
    0
  };

  text_mode (-1);

  /* Clear screen and output prompt.  */
  clear_to_color (screen, white);
  for (i = 0; welcome[i] != 0; i++)
    textout (screen, font, welcome[i], 8, i * 8 + 8, black);

  clear_to_color (screen, white);
  for (i = 0; keymap[i].string != 0; i++)
    textout (screen, font, keymap[i].string, 32 + (i % 4) * 160, 40 + (i / 4) * 14, black);

  do
    {
      poll_keyboard ();
      poll_mouse ();
    }
  while ((key[KEY_ESC]) || (mouse_b));

  do
    {
      poll_keyboard ();
      poll_mouse ();

      for (i = 0; i < KEY_MAX; i++)
	{
	  if (key[i])
	    key_was_pressed[i] = key_is_pressed[i] = 1;
	  else
	    key_is_pressed[i] = 0;
	}

      for (i = 0; keymap[i].string != 0; i++)
	{
	  int x = 16 + (i % 4) * 160;
	  int y = 40 + (i / 4) * 14;
	  int k = keymap[i].key;

	  if (key_is_pressed[k])
	    rectfill (screen, x, y, x + 7, y + 7, red);
	  else if (key_was_pressed[k])
	    rectfill (screen, x, y, x + 7, y + 7, yellow);
	  else
	    rectfill (screen, x, y, x + 7, y + 7, white);
	}
    }
  while ((!key[KEY_ESC]) && (!mouse_b));

  do
    {
      poll_keyboard ();
      poll_mouse ();
    }
  while ((key[KEY_ESC]) || (mouse_b));

  clear_keybuf ();
}

static void
save_key_map (void)
{
  int i;
  char *section, *option_format, option[80], tmp1[80], tmp2[80];

  set_config_file ("allegro.cfg");
  section = uconvert_ascii ("xkeymap", tmp1);
  option_format = uconvert_ascii ("keycode%d", tmp2);

  for (i = 0; i < 256; i++)
    {
      if (keycode_to_scancode[i] > 0)
	{
	  usprintf (option, option_format, i);
	  set_config_int (section, option, keycode_to_scancode[i]);
	}
    }
}

static DIALOG main_dialog[] =
{
  { d_clear_proc,  0,  0,  250, 102, 0, 0,   0,   0,      0, 0, 0 },
  { d_button_proc, 10, 10, 230, 16,  0, 255, 'm', D_EXIT, 0, 0, "Setup key &mappings" },
  { d_button_proc, 10, 32, 230, 16,  0, 255, 't', D_EXIT, 0, 0, "&Test key mappings" },
  { d_button_proc, 10, 54, 230, 16,  0, 255, 's', D_EXIT, 0, 0, "&Save and exit" },
  { d_button_proc, 10, 76, 230, 16,  0, 255, 'x', D_EXIT, 0, 0, "E&xit" },
  { NULL,          0,  0,  0,   0,   0, 0,   0,   0,      0, 0, 0 },
};

static void
show_main_dialog (void)
{
  int focus = 1;

  /* Prepare dialog.  */
  set_dialog_color (main_dialog, black, white);
  centre_dialog (main_dialog);

  /* Parse input.  */
  while (1)
    {
      focus = do_dialog (main_dialog, focus);
      switch (focus)
	{
	case 1:
	  /* Setup all key mappings.  */
	  setup_all_keys ();
	  break;
	case 2:
	  /* Test key mappings.  */
	  test_key_map ();
	  break;
	case 3:
	  /* Save and quit.  */
	  save_key_map ();
	  return;
	case 4:
	  /* Just exit.  */
	  return;
	}
    }
}

int
main (void)
{
  int i;

  allegro_init ();
  install_keyboard ();
  install_mouse ();
  install_timer ();

  if (set_gfx_mode (GFX_XWINDOWS, 640, 480, 0, 0) < 0)
    {
      allegro_message ("Can not set graphics mode\n%s", allegro_error);
      return 0;
    }

  black = makecol (0, 0, 0);
  white = makecol (255, 255, 255);
  red = makecol (255, 0, 0);
  yellow = makecol (255, 255, 0);

  /* Clear key mappings.  */
  for (i = 0; i < 256; i++)
    keycode_to_scancode[i] = -1;

  /* Hook X-windows keyboard callback.  */
  _xwin_keyboard_callback = get_raw_keycode;

  show_main_dialog ();

  return 0;
}
END_OF_MAIN ();

/*
 * xkeymap.c ends here
 */
