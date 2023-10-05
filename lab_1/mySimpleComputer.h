#include <stdio.h>
#include <stdlib.h>
#ifndef MYSYMPLECOMPUTER_H
#define MYSYMPLECOMPUTER_H
#define memorySize 100
#define OWERFLOW 0
#define DIVIZION_NULL 1
#define OUTMEMORY 2
#define IGNORE_PULSE_TACT 3
#define INVALID_COMMAND 4
#define FILE_ERR 6
#define NUMBER_REGS 5
void sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memoryLoad(char *filename);
int sc_memorySave(char *filename);
void sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int regIster, int *value);
int sc_commandDecode(int value, int *command, int *operand);
int sc_commandEncode(int command, int operand, int *value);
#endif
