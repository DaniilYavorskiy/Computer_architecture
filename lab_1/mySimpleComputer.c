#include "mySimpleComputer.h"
int flag = 0;
unsigned char registers;
int accessMemory[memorySize];
void sc_memoryInit() {
  for (int i = 0; i < memorySize; i++) {
    accessMemory[i] = 0;
  }
}

int sc_regSet(int regIster, int value) {
  if ((regIster < 0 || regIster >= NUMBER_REGS) || (value != 0 && value != 1)) {
    flag = -1;
  } else {
    value == 1 ? (registers |= (1 << regIster))
               : (registers &= ~(1 << regIster));
  }
  return flag;
}

void sc_regInit() { registers = 0; }

int sc_regGet(int regIster, int *value) {
  if (regIster < 0 || regIster >= NUMBER_REGS) {
    flag = -1;
  }

  if (registers & (1 << regIster)) {
    *value = 1;
  } else {
    *value = 0;
  }

  return (flag == -1) ? flag : *value;
}

int sc_memorySet(int address, int value) {
  if (address > 0 && address <= memorySize) {
    accessMemory[address] = value;
  } else {
    sc_regSet(OUTMEMORY, 1);
    flag = -1;
  }
  return flag;
}

int sc_memoryGet(int address, int *value) {
  if (address >= 0 && address <= memorySize) {
    *value = accessMemory[address];
  } else {
    sc_regSet(OUTMEMORY, 1);
    flag = -1;
  }
  return (flag == -1) ? -1 : *value;
}

int sc_memorySave(char *filename) {
  FILE *file = NULL;
  int len = memorySize;

  file = fopen(filename, "wb");

  if (file == NULL) {
    return -1;
  }
  fwrite(&len, sizeof(int), 1, file);
  fwrite(accessMemory, sizeof(int), len, file);
  fclose(file);
  return 0;
}

int sc_memoryLoad(char *filename) {
  FILE *Read = fopen(filename, "rb");

  if (Read == NULL) {
    return -1;
  }
  int lenRead = 0;
  fread(&lenRead, sizeof(int), 1, Read);
  int *ArrIn = (int *)malloc(lenRead * sizeof(int));
  fread(ArrIn, sizeof(int), lenRead, Read);
  fclose(Read);

  for (int i = 0; i < lenRead; i++)
    printf("%d ", ArrIn[i]);

  free(ArrIn);
  return 0;
}

int sc_commandEncode(int command, int operand, int *value) {
  if (!(command > 0x9 && command < 0x12) &&
      !(command > 0x19 && command < 0x22) &&
      !(command > 0x29 && command < 0x34) &&
      !(command > 0x39 && command < 0x77))
    flag = -1;

  if ((operand < 0) || (operand >= 128))
    flag = -1;

  *value = 0;

  if (flag != -1) {
    /* Операнд */
    for (int i = 0; i < 7; i++) {
      int bit = (operand >> i) & 1;
      *value |= (bit << i);
    }

    /* Команда */
    for (int i = 0; i < 7; i++) {
      int8_t bit = (command >> i) & 1;
      *value |= (bit << (i + 7));
    }
  }
  return (flag == -1) ? -1 : *value;
}
int sc_commandDecode(int value, int *command, int *operand) {
  int tmpCom = 0, tmpOp = 0;
  if ((value >> 14) & 1)
    flag = -1;

  for (int i = 0; i < 7; i++) {
    int bit = (value >> i) & 1;
    tmpOp |= (bit << i);
  }

  for (int i = 0; i < 7; i++) {
    int bit = (value >> (i + 7)) & 1;
    tmpCom |= (bit << i);
  }

  if (!(tmpCom > 0x9 && tmpCom < 0x12) && !(tmpCom > 0x19 && tmpCom < 0x22) &&
      !(tmpCom > 0x29 && tmpCom < 0x34) && !(tmpCom > 0x39 && tmpCom < 0x77))
    flag = -1;
  if ((tmpOp < 0) || (tmpOp >= 128))
    flag = -1;

  *command = tmpCom;
  *operand = tmpOp;
  if (flag == -1)
    sc_regSet(INVALID_COMMAND, 1);
  return (flag == -1) ? -1 : 0;
}