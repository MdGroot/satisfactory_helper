#ifndef HEADER
#define HEADER
#include <stdio.h>

typedef struct MyMaterial Material;

typedef struct MyMachine Machine;

void clear();

Machine *machineArrayCreate(int size);

Machine *machineCreate(char *name, char *mat_out, int mat_out_amount, char *mat_in1, int mat_in1_amount, char *mat_in2, int mat_in2_amount);

void machinePrint(Machine *machine);

Machine *machineRead(FILE *fp);

void machineWrite(FILE *fp, Machine *machine);

#endif
