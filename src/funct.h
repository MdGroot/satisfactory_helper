#ifndef HEADER
#define HEADER
#include <stdio.h>

typedef struct MyMaterial Material;

typedef struct MyMachine Machine;

void clear();

Machine *machineInit();

Machine *machineArrayCreate(int size);

Machine *machineFill(Machine *machine, char *name, char *mat_out, int mat_out_amount, char *mat_in1, int mat_in1_amount, char *mat_in2, int mat_in2_amount);

void machineDestroy(Machine *machine);

void machinePrint(Machine *machine);

Machine *machineRead(FILE *fp, Machine *machine);

void machineWrite(FILE *fp, Machine *machine);

#endif
