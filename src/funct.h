#ifndef HEADER
#define HEADER
#include <stdio.h>

typedef struct MyMaterial Material;

typedef struct MyMachine Machine;

typedef struct MyMachineList MachineList;

void clear();

Machine *machineInit();

Machine *machineArrayCreate(int size);

Machine *machineFill(Machine *machine, char *name, char *mat_out, double mat_out_amount, char *mat_in1, double mat_in1_amount, char *mat_in2, double mat_in2_amount);

void machineDestroy(Machine *machine);

void listUpdate(MachineList **head, char *name, double amount);

void machineListCreate(MachineList **head, char *cur_mat, double cur_amount);

void listPrint(MachineList *head);

void listDestroy(MachineList *head);

void machinePrint(Machine *machine);

Machine *machineRead(FILE *fp, Machine *machine);

void machineWrite(FILE *fp, Machine *machine);

int machineCompare(Machine *machine, char *name);

int fpCheck(FILE *fp);

FILE *fpSetback(FILE *fp);

FILE *fpSetforwardInt(FILE *fp);

FILE *fpSetforward(FILE *fp);

FILE *fpMove(FILE *fp, FILE *fpw);

void fpMoveToEnd(FILE *fp, int amount);

int outputCompare(Machine *machine, char *out_name);

#endif
