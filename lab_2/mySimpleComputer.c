#include "mySimpleComputer.h"
unsigned short int memory_arr[N];
char flag = 0;

void
sc_memoryInit ()
{
  for (int i = 0; i < N; i++)
    memory_arr[i] = 0;
}

void
sc_memorySet (int address, int value)
{
  if (0 > address || address > 99)
    {
      flag = 1;
      return;
    }
  memory_arr[address] = value;
}

void
sc_memoryGet (int address, int *value)
{
  if (0 > address || address > 99)
    {
      flag = 1;
      return;
    }
  *value = memory_arr[address];
}

void
sc_memorySave (char *filename)
{
  FILE *out = fopen (filename, "wb");
  if (out == NULL)
    return;
  fwrite (memory_arr, sizeof (memory_arr), 1, out);
  fclose (out);
}

void
memory_load (char *filename)
{
  FILE *in = fopen (filename, "rb");
  if (in == NULL)
    return;
  fread (memory_arr, sizeof (memory_arr), 1, in);
  fclose (in);
}

void
regInit ()
{
  flag = 0;
}

void
sc_regSet (int _register, int value)
{
  if (_register < 0 || _register > 4)
    {
      printf ("Error. Wrong _register\n");
      return;
    }
  if (value < 0 || value > 1)
    {
      printf ("Error. Wrong Value\n");
      return;
    }

  if (value == 1)
    {
      flag = flag | (1 << _register);
    }
  else
    {
      flag = flag & ~(1 << _register);
    }
}

void
sc_regGet (int _register, int *value)
{
  if (_register < 0 || _register > 4)
    {
      printf ("Error. Wrong _register\n");
      return;
    }
  if (flag & (1 << _register))
    {
      *value = 1;
    }
  else
    {
      *value = 0;
    }
}

void
sc_commandEncode (int command, int operand, int *value)
{

  if (!((command >= 0x10 && command <= 0x11)
        || (command >= 0x20 && command <= 0x21)
        || (command >= 0x30 && command <= 0x33)
        || (command >= 0x40 && command <= 0x43)
        || (command >= 0x51 && command <= 0x76)))
    {
      printf ("Error\n");
      return;
    }
  if (operand < 0 || operand > 127)
    {
      printf ("Error\n");
      return;
    }

  *value = 0;
  *value = *value | operand;
  *value = *value | (command << 7);
}

void
sc_commandDecode (int value, int *command, int *operand)
{
  *operand = 0;
  *command = 0;

  *command = (value & 0x3F80) >> 7; // 16256
  *operand = (value & 0x7F);        // 127

  if (!(*command > 0x9 && *command < 0xC)
      && !(*command > 0x13 && *command < 0x16)
      && (*command > 0x1D && *command < 0x22)
      && !(*command > 0x27 && *command < 0x4D))
    {
      printf ("ERROR! INVALID COMMAND\n");
    }

  if (!(*operand > 0 && *operand < 0x80))
    {
      printf ("ERROR! INVALID OPERAND\n");
    }
}