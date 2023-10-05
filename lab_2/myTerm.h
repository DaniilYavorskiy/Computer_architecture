#pragma once
#include <stdio.h>
#include <sys/ioctl.h>

enum colors
{
  RED = 196,
  GREEN = 10,
  BLUE = 20,
  BLACK = 16,
  WHITE = 15
};

int mt_clrscr ();
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
int set_default_color ();