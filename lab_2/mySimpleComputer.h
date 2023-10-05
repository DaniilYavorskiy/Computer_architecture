#pragma once
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#define N 100
#define REGISTER_SIZE 5
#define OVERFLOW 0               // переполнение
#define DIVISION_ERROR_BY_ZERO 1 // ошибка деления на 0
#define OUT_OF_MEMORY 2          // выход за границы памяти
#define IGNORING_CLOCK_PULSES 3 // игнорирование тактовых импульсов
#define INVALID_COMMAND 4 // неверная команда

void sc_memoryInit ();
void sc_memorySet (int address, int value);
void sc_memoryGet (int address, int *value);
void sc_memorySave (char *filename);
void memory_load (char *filename);
void regInit ();
void sc_regSet (int _register, int value);
void sc_regGet (int _register, int *value);
void sc_commandEncode (int command, int operand, int *value);
void sc_commandDecode (int value, int *command, int *operand);