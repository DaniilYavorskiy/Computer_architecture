#include "myBigChars.h"
#include "myInterface.h"
#include "myReadKey.h"
#include "mySignal.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>

#include <unistd.h>

bool on = 1;

int
main ()
{
  int valueR;
  rk_myTermSave ();
  sc_memoryInit ();
  int rows, cols;
  for (int i = 0; i < N; ++i)
    sc_memorySet (i, i + 1);
  // sc_memorySet (0, 5);
  mt_getscreensize (&rows, &cols);
  if (rows < 24 || cols < 24)
    return -1;
  ui_initial ();
  sc_regSet (3, 1);

  struct itimerval nval, oval;
  nval.it_interval.tv_sec = 1;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;
  ms_setSignals ();
  enum keys key;

  do
    {
      ui_update ();
      rk_readKey (&key);
      switch (key)
        {
        case UP_KEY:
          (currMemCell <= 9) ? (currMemCell = 90 + currMemCell)
                             : (currMemCell -= 10);
          break;
        case RIGHT_KEY:
          (!((currMemCell + 1) % 10)) ? (currMemCell -= 9)
                                      : (currMemCell += 1);
          break;
        case DOWN_KEY:
          (currMemCell >= 90) ? (currMemCell = currMemCell - 90)
                              : (currMemCell += 10);
          break;
        case LEFT_KEY:
          (!(currMemCell % 10)) ? (currMemCell += 9) : (currMemCell -= 1);
          break;

        case L_KEY:
          sc_memoryLoad ("savefile.bin");
          break;
        case S_KEY:
          sc_memorySave ("savefile.bin");
          break;

        case R_KEY:
          instruction_counter = 0;
          currMemCell = 0;
          sc_regGet (3, &valueR);
          if (valueR)
            {
              sc_regSet (3, 0);
              setitimer (ITIMER_REAL, &nval, &oval);
            }
          else
            {
              alarm (0);
              sc_regSet (3, 1);
            }
          drawing_IC ();
          break;
        case T_KEY:
          sc_regSet (3, 0);
          ms_timerHandler (SIGALRM);
          sc_regSet (3, 1);
          drawing_IC ();
          break;
        case I_KEY:
          raise (SIGUSR1);
          accumulator = 0;
          instruction_counter = 0;
          currMemCell = 0;
          drawing_IC ();
          sc_memoryInit ();
          sc_regSet (3, 1);
          ui_update ();
          break;

        case F5_KEY:
          ui_Accum ();
          break;

        case F6_KEY:
          ui_Counter ();
          break;

        case ENTER_KEY:
          ui_setValue ();
          ui_update ();
          break;
        case ESC_KEY:
          on = 0;
          break;
        }
    }
  while (on);
  mt_gotoXY (1, 24);
  return 0;
}
