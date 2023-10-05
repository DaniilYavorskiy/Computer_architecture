#include "mySimpleComputer.h"
int main() {
  int value;
  sc_memorySet(1, 5);
  sc_memorySet(2, 4);
  sc_memorySet(3, 3);
  sc_memorySet(4, 2);
  sc_memorySet(5, 1);
  for (int i = 0; i < memorySize; i++) {
    sc_memoryGet(i + 1, &value);
    printf("RAM[%d] = %d\n", i + 1, value);
  }

  sc_memorySave("test.bin");

  sc_memorySet(1, 99);
  sc_memoryGet(1, &value);
  printf("RAM[1] = %d\n", value);

  sc_memoryLoad("test.bin");

  printf("\n\n\n");
  sc_regInit();
  sc_regSet(IGNORE_PULSE_TACT, 1);
  sc_regSet(OWERFLOW, 1);

  printf("FLAGS OWERFLOW = [%d]\n", sc_regGet(OWERFLOW, &value));
  printf("FLAGS DIVIZION_NULL = [%d]\n", sc_regGet(DIVIZION_NULL, &value));
  printf("FLAGS OUTMEMORY = [%d]\n", sc_regGet(OUTMEMORY, &value));
  printf("FLAGS IGNORE_PULSE_TACT = [%d]\n",
         sc_regGet(IGNORE_PULSE_TACT, &value));
  printf("FLAGS INVALID_COMMAND = [%d]\n", sc_regGet(INVALID_COMMAND, &value));

  printf("\n\n\n");
  int f = 0, f_c = 0, f_o = 0;
  sc_commandEncode(0x33, 0x59, &f);
  printf("KODING COMMAND: %d\n", f);
  sc_commandDecode(f, &f_c, &f_o);
  printf("COMMAND: %x  OPERAND: %x\n", f_c, f_o);
  return 0;
}
