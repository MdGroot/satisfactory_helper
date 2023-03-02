#include <stdio.h>
#include <stdlib.h>
#include "funct.h"

void makeMachinefile(){
    FILE *fp = fopen("machines.dat", "rb");
    if(fp){
        fclose(fp);
        return;
    }
    printf("can't open file to read\n");
    fp = fopen("machines.dat", "wb");
    int begin = 0;
    fwrite(&begin, sizeof(int), 1, fp);
    printf("Made new file\n\n");
    getchar();
    fclose(fp); 
    return;
};

void readMachines(){
    FILE *fp = fopen("machines.dat", "rb");
    if(fpCheck(fp) == 0){
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(int), 1, fp);
    Machine *machine = machineInit();
    for(int i = 0; i < maximum; ++i){
        machine = machineRead(fp, machine); 
        machinePrint(machine);
    }
    machineDestroy(machine);
    fclose(fp);
    return;
};

void addMachines(){
    char proceed = ('n');
    FILE *fp = fopen("machines.dat", "rb+");
    if(fpCheck(fp) == 0){
        return;
    }
    int counter = 0;
    fread(&counter, sizeof(int), 1, fp);
    fpMoveToEnd(fp, counter);
    Machine *machine = machineInit();
    char new_name[40];
    char new_out_name[40];
    char new_in1_name[40];
    char new_in2_name[40];
    int new_out_amount;
    int new_in1_amount;
    int new_in2_amount;
    while(proceed == ('n')) {
        clear();
        printf("New machine name: ");
        scanf(" %39[^\n]", new_name);
        printf("Material out name: ");
        scanf(" %39[^\n]", new_out_name);
        printf("Material out amount: ");
        scanf(" %d", &new_out_amount);
        printf("Material in1 name: ");
        scanf(" %39[^\n]", new_in1_name);
        printf("Material in1 amount: ");
        scanf(" %d", &new_in1_amount);
        printf("Material in2 name: ");
        scanf(" %39[^\n]", new_in2_name);
        printf("Material in2 amount: ");
        scanf(" %d", &new_in2_amount);
        machine = machineFill(machine, new_name, new_out_name, new_out_amount, new_in1_name, new_in1_amount, new_in2_name, new_in2_amount);
        clear();
        machinePrint(machine);
        printf("Proceed(y/n)?\n");
        scanf(" %c", &proceed);
    }

    machineWrite(fp, machine);
    machineDestroy(machine);
    fclose(fp); 

    fp = fopen("machines.dat", "rb+");
    int amount = 0;
    fread(&amount, sizeof(int), 1, fp);
    ++amount;
    rewind(fp);
    fwrite(&amount, sizeof(int), 1, fp);
    fclose(fp); 
    return;
};

void removeMachines(){
    // TODO : make function to remove machine from file
    readMachines();
    char name[40];
    printf("Enter name of machine to be removed: ");
    scanf(" %39[^\n]", name);
    FILE *fp = fopen("machines.dat", "rb");
    FILE *fpw = fopen("machines.dat", "rb+");
    if(fpCheck(fp) == 0){
        return;
    }
    if(fpCheck(fpw) == 0){
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(int), 1, fp);
    Machine *machine = machineInit();
    int equal = 1;
    int found = 0;
    for(int i = 0; i < maximum; ++i){
        machine = machineRead(fp, machine); 
        if(found > 0){
            machineWrite(fpw, machine);
        }
        equal = machineCompare(machine, name);
        if(equal == 0){
            fpw = fpMove(fp, fpw);
            ++found;
        }
    }
    maximum -= found;
    fclose(fp);
    FILE *fpi = fopen("machines.dat", "rb+");
    rewind(fpi);
    fwrite(&maximum, sizeof(int), 1, fpi);
    fclose(fpi); 
    machineDestroy(machine);
    fclose(fpw);
};

void makeCalculation(){
    // TODO : make function to calculate necessary materials based on end result
};

int main(){//int arc, char** argv){
    clear();
    makeMachinefile();
    
    int choice;
    while(1){
        clear();
        printf("1. Read Machines\n");
        printf("2. Add Machines\n");
        printf("3. Remove Machines\n");
        printf("4. Make Calculation\n");
        printf("9. quit\n");
        printf("Enter your choice: ");
    
        scanf("%1d", &choice);
        clear();    
        switch (choice)
        {
            case 1:
                readMachines();
                getchar();
                getchar();
                break;
            case 2:
                addMachines();
                break;
            case 3:
                removeMachines();
                break;
            case 4:
                makeCalculation();
                break;
            case 9:
                return 0;
                break;
            default:
                printf("invalid\n");
                break;
        }
    }
    return 0;
}

