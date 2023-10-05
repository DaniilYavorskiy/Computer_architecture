#include "myInterface.h"

int instruction_counter;

int
print_symbol (char symbol)
{
  printf ("\033(0%c\033(B", symbol);

  return 0;
}

int
print_box (int x, int y, int width, int height)
{
  int count_rows, count_columns;

  mt_getscreensize (&count_rows, &count_columns);
  if (count_rows < 20 || count_columns < 20)
    return -1;
  /* ушко слева вверху */
  mt_gotoXY (x, y);
  print_symbol (UL_CORNER);

  /* ушко справа вверху */
  mt_gotoXY (x + width - 1, y);
  print_symbol (UR_CORNER);

  /* ушко справа внизу */
  mt_gotoXY (x + width - 1, y + height - 1);
  print_symbol (DR_CORNER);

  /* ушко слева внизу */
  mt_gotoXY (x, y + height - 1);
  print_symbol (DL_CORNER);

  /* линии вверх-низ */
  for (int i = 1; i < width - 1; ++i)
    {
      /* верхние линии */
      mt_gotoXY (x + i, y);
      print_symbol (H_LINE);

      /* нижние линии*/
      mt_gotoXY (x + i, y + height - 1);
      print_symbol (H_LINE);
    }

  /* боковые линии */
  for (int i = 1; i < height - 1; ++i)
    {
      /* лево */
      mt_gotoXY (x, y + i);
      print_symbol (V_LINE);

      /* право */
      mt_gotoXY (x + width - 1, y + i);
      print_symbol (V_LINE);
    }

  return 0;
}

int
drawing_boxes ()
{

  /* memory */
  if (print_box (1, 1, 61, 12))
    {
      printf ("no");
      return -1;
    }

  /*  accumulator */
  if (print_box (62, 1, 22, 3))
    {
      return -1;
    }

  /* instruction counter */
  if (print_box (62, 4, 22, 3))
    {
      return -1;
    }

  /*  operation*/
  if (print_box (62, 7, 22, 3))
    {
      return -1;
    }

  /* flags */
  if (print_box (62, 10, 22, 3))
    {
      return -1;
    }

  /*big chars */
  if (print_box (1, 13, 52, 10))
    {
      return -1;
    }

  /* keys */
  if (print_box (53, 13, 31, 10))
    {
      return -1;
    }

  return 0;
}

int
drawing_texts ()
{
  mt_gotoXY (30, 1);
  printf (" Memory ");

  mt_gotoXY (66, 1);
  printf (" accumulator ");

  mt_gotoXY (63, 4);
  printf (" instructionCounter ");

  mt_gotoXY (68, 7);
  printf (" Operation ");

  mt_gotoXY (68, 10);
  printf (" Flags ");

  mt_gotoXY (54, 13);
  printf (" Keys: ");

  /* HotKeys */
  char *hot_keys[7] = { (char *)"l  - load",
                        (char *)"s  - save",
                        (char *)"r  - run",
                        (char *)"t  - step",
                        (char *)"i  - reset",
                        (char *)"F5 - accumulator",
                        (char *)"F6 - instructionCounter" };

  for (int i = 0; i < 7; ++i)
    {
      mt_gotoXY (54, i + 14);
      printf ("%s", hot_keys[i]);
    }

  mt_gotoXY (1, 24);

  printf ("%s", "Input/Output: ");

  return 0;
}

int
drawing_memory ()
{
  for (int i = 0; i < 10; ++i)
    {
      for (int j = 0; j < 10; ++j)
        {
          mt_gotoXY (2 + (5 * j + j), 2 + i);

          int value;
          sc_memoryGet (i * 10 + j, &value);

          if ((i * 10 + j) == instruction_counter)
            {
              mt_setbgcolor (GREEN);
            }

          if ((value >> 14) & 1)
            {
              printf (" %04X", value & (~(1 << 14)));
            }
          else
            {
              printf ("+%04X", value);
            }

          set_default_color ();
        }
    }

  return 0;
}

int
drawing_flags ()
{
  char flags[] = { 'O', 'Z', 'M', 'P', 'C' };

  for (int i = 0; i < REGISTER_SIZE; ++i)
    {
      int value;

      sc_regGet (i, &value);

      mt_gotoXY (69 + (i * 2), 11);
      printf ("%c", flags[i]);
    }
  mt_gotoXY (69, 8);
  printf ("+00 : 00");
  mt_gotoXY (69, 5);
  printf ("+0000");
  mt_gotoXY (69, 2);
  printf ("+0001");

  return 0;
}

int
ui_initial ()
{
  instruction_counter = 0;

  mt_clrscr ();

  if (drawing_boxes ())
    {
      return -1;
    }

  if (drawing_texts ())
    {
      return -1;
    }
  if (drawing_memory ())
    {
      return -1;
    }

  if (drawing_flags ())
    {
      return -1;
    }

  mt_gotoXY (1, 24);

  return 0;
}
