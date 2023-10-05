#include "myCU.h"

int
READ (int operand)
{
  char buff[32];
  mt_gotoXY (1, 24);
  sprintf (buff, "Input value: ");
  write (STDOUT_FILENO, buff, 14);
  rk_myTermRegime (0, 0, 1, 1, 1);
  char buffAf[32];
  fgets (buffAf, 32, stdin);
  sc_memorySet (operand, atoi (buffAf));

  return 0;
}

int
WRITE (int operand)
{
  int value;
  sc_memoryGet (operand, &value);
  char tmp[14];
  if (value > 0)
    {
      sprintf (tmp, "Value:> %.4X", value);
    }
  else
    {
      sprintf (tmp, "Value:> -%.4X", -1 * value);
    }
  return 0;
}

int
LOAD (int operand)
{
  int value = 0;
  sc_memoryGet (operand, &value);
  accumulator = value;
  return 0;
}

int
STORE (int operand)
{
  sc_memorySet (operand, accumulator);
  return 0;
}

int
JUMP (int operand)
{
  instruction_counter = operand;
  CU ();
  return 0;
}

int
JNEG (int operand)
{
  if (accumulator < 0)
    {
      instruction_counter = operand;
      CU ();
    }
  return 0;
}

int
JZ (int operand)
{
  if (accumulator == 0)
    {
      instruction_counter = operand;
      CU ();
    }
  return 0;
}

int
HALT ()
{
  sc_regSet (3, 1);
  instruction_counter = 0;

  return 0;
}

int
JNS (int operand)
{
  if (accumulator > 0)
    {
      instruction_counter = operand;
    }
  return 0;
}

int
CU ()
{
  int value = 0;
  sc_memoryGet (instruction_counter, &value);
  int command, operand;
  if (sc_commandDecode (value, &command, &operand) < 0)
    {
      sc_regSet (3, 1);
      return 1;
    }
  if (((command >= 0x30) && (command <= 0x33)) || (command == 0x52))
    {
      ALU (command, operand);
    }
  else
    {
      switch (command)
        {
        case 0x10:
          READ (operand);
          break;
        case 0x11:
          WRITE (operand);
          break;
        case 0x20:
          LOAD (operand);
          break;
        case 0x21:
          STORE (operand);
          break;
        case 0x40:
          JUMP (operand);
          break;
        case 0x41:
          JNEG (operand);
          break;
        case 0x42:
          JZ (operand);
          break;
        case 0x43:
          HALT ();
          break;
        case 0x55:
          JNS (operand);
          break;
        }
    }
  return 0;
}