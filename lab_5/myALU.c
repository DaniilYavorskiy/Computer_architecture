#include "myALU.h"

int
ALU (int command, int operand)
{
  int tmp;
  sc_memoryGet (operand, &tmp);
  switch (command)
    {
    case 0x30: //сложение, результат в акк
      accumulator += tmp;
      break;
    case 0x31: //вычитание
      accumulator -= tmp;
      break;
    case 0x32: //деление
      if (tmp == 0)
        {
          sc_regSet (1, 1);
          return -1;
        }
      sc_regSet (1, 0);
      accumulator /= tmp;
      break;
    case 0x33: //произведение
      accumulator *= tmp;
      break;
    case 0x52: //логич и
      accumulator &= tmp;
      break;
    }
  if ((accumulator > 0x7FFF) || (accumulator < 0))
    {
      accumulator &= 0x7FFF;
      sc_regSet (0, 1); // overflow
    }
  else
    {
      sc_regSet (0, 0); // overflow
    }
  return 0;
}