#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funct.h"

typedef struct MyMaterial{
    char name [40];
    double amount;
}Material;

typedef struct MyMachine{
    char name [40];
    Material out;
    Material in1;
    Material in2;
}Machine;

typedef struct MyMachineList{
    char name [40];
    double amount;
    struct MyMachineList *next;
}MachineList;

void clear(){
    printf("\e[1;1H\e[2J");
}

Machine *machineInit(){
    Machine *machine = (Machine *) malloc(sizeof(*machine));
    return machine;
}

Machine *machineFill(Machine *machine, char *name, char *mat_out, double mat_out_amount, char *mat_in1, double mat_in1_amount, char *mat_in2, double mat_in2_amount){
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

void listUpdate(MachineList **head, char *name, double amount){
    int equal; 
    MachineList *tmp = *head;
    if(tmp == NULL){
        MachineList *new_entry = (MachineList *) malloc(sizeof(*new_entry));
        strncpy(new_entry->name, name, sizeof(new_entry->name));
        new_entry->amount = amount;
        new_entry->next = NULL;
        *head = new_entry;
        return;
    }
    equal = strcmp(tmp->name, name);
    while(equal != 0 && tmp->next != NULL){
        tmp = tmp->next;
        equal = strcmp(tmp->name, name);
    }
    if(equal == 0){
        tmp->amount += amount;
    }
    else if(tmp->next == NULL){
        MachineList *new_entry = (MachineList *) malloc(sizeof(*new_entry));
        strncpy(new_entry->name, name, sizeof(new_entry->name));
        new_entry->amount = amount;
        new_entry->next = NULL;
        tmp->next = new_entry;
    }
    return;
}

void machineListCreate(MachineList **head, char *cur_mat, double cur_amount){
    FILE *fp = fopen("machines.dat", "rb");
    if(fpCheck(fp) == 0){
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(int), 1, fp);
    Machine *machine = machineInit();
    double machinecount = 0;
    int equal = 1;

    rewind(fp);
    fp = fpSetforwardInt(fp);
    for(int i = 0; i < maximum; ++i){
        machine = machineRead(fp, machine); 
        equal = outputCompare(machine, cur_mat);
        if(equal == 0){
            if(cur_amount == 0){machinecount = 1;}
            else{
                machinecount = cur_amount/machine->out.amount;
                listUpdate(head, machine->name, machinecount);
            }

            //update list
            //update curr amount and material 1 and run again
            //update curr amount and material 2 and run again
        }
    }

    fclose(fp);
    machineDestroy(machine);
    return;
}



Machine *machineArrayCreate(int size){
    Machine *machine_array = (Machine *) malloc(size * sizeof(* machine_array));
    return machine_array;
}

void machinePrint(Machine *machine){
    printf("Machine name:      %s\nMaterial output:   %s, %lf\nMaterial 1 intput: %s, %lf\nMaterial 2 intput: %s, %lf\n\n", 
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

int machineCompare(Machine *machine, char *name){
    int equal = strcmp(machine->name, name);
    return equal;
}

int outputCompare(Machine *machine, char *out_name){
    int equal = strcmp(machine->out.name, out_name);
    return equal;
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
    int i;
    i = fseek(fp, (long)-sizeof(Machine), SEEK_CUR);
    if(i!=0){
        printf("ERROR IN SETBACK\n");
    }
    return fp;
}

FILE *fpSetforwardInt(FILE *fp){
    int i;
    i = fseek(fp, (long)sizeof(int), SEEK_CUR);
    if(i!=0){
        printf("ERROR IN SETBACK\n");
    }
    return fp;
}

FILE *fpSetforward(FILE *fp){
    int i;
    i = fseek(fp, (long)sizeof(Machine), SEEK_CUR);
    if(i!=0){
        printf("ERROR IN SETFORWARD\n");
    }
    return fp;
}

FILE *fpMove(FILE *fp, FILE *fpw){
    fp = fpSetback(fp);
    long curr = ftell(fp);
    int i;
    i = fseek(fpw, curr, SEEK_SET);
    fp = fpSetforward(fp);
    if(i!=0){
        printf("ERROR IN SET\n");
    }
    return fpw;
}

void fpMoveToEnd(FILE *fp, int amount){
    int i;
    i = fseek(fp, (long)(amount * sizeof(Machine)), SEEK_CUR);
    if(i!=0){
        printf("ERROR IN MOVE\n");
    }
    return;
}
