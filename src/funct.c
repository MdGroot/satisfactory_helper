#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funct.h"

typedef struct MyMaterial{
    char name [40];
    int amount;
}Material;

typedef struct MyMachine{
    char name [40];
    Material out;
    Material in1;
    Material in2;
}Machine;

void clear(){
    printf("\e[1;1H\e[2J");
}

Machine *machineInit(){
    Machine *machine = (Machine *) malloc(sizeof(*machine));
    return machine;
}

Machine *machineFill(Machine *machine, char *name, char *mat_out, int mat_out_amount, char *mat_in1, int mat_in1_amount, char *mat_in2, int mat_in2_amount){
    strncpy(machine->name, name, sizeof(machine->name));
    strncpy(machine->out.name, mat_out, sizeof(machine->out.name));
    strncpy(machine->in1.name, mat_in1, sizeof(machine->in1.name));
    strncpy(machine->in2.name, mat_in2, sizeof(machine->in2.name));
    machine->out.amount = mat_out_amount;
    machine->in1.amount = mat_in1_amount;
    machine->in2.amount = mat_in2_amount;
    return machine;
}

void machineDestroy(Machine *machine){
    free(machine);
    return;
}

Machine *machineArrayCreate(int size){
    Machine *machine_array = (Machine *) malloc(size * sizeof(* machine_array));
    return machine_array;
}

void machinePrint(Machine *machine){
        printf("Machine name:      %s\nMaterial output:   %s, %d\nMaterial 1 intput: %s, %d\nMaterial 2 intput: %s, %d\n\n", 
                machine->name, machine->out.name, machine->out.amount, machine->in1.name, 
                machine->in1.amount, machine->in2.name, machine->in2.amount);
}

Machine *machineRead(FILE *fp, Machine *machine){
        fread(machine, sizeof(Machine), 1, fp); 
        return machine;
}

void machineWrite(FILE *fp, Machine *machine){
    fwrite(machine, sizeof(Machine), 1, fp);
}

int fpCheck(FILE *fp){
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        getchar();
        clear();
        return 0;
    }
    return 1;
}

FILE *fpSetback(FILE *fp){
    int i = 0;
    i = fseek(fp, (long)sizeof(Machine), SEEK_CUR);
    if(i!=0){
        printf("ERROR IN SETBACK\n");
    }
    return fp;
}
