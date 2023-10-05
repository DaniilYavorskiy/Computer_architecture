#include "mySignal.h"

void
ms_setSignals ()
{
  signal (SIGALRM, ms_timerHandler);
  signal (SIGUSR1, ms_userSignal);
}

void
ms_timerHandler (int sig)
{
  CU ();
  int value;
  sc_regGet (3, &value);
  if ((instruction_counter <= 99 && instruction_counter >= 0) && !value)
    {
      instruction_counter++;
      ui_update ();
    }
  else if (instruction_counter > 99)
    {
      instruction_counter = 0;
    }
  if (!value)
    {
      ualarm (100000, 0);
    }
  currMemCell = instruction_counter;
}

void
ms_userSignal (int sig)
{
  alarm (0);
  sc_regInit ();
  sc_regSet (3, 1);
  instruction_counter = 0;
  accumulator = 0;
  drawing_IC ();
}