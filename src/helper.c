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
    clear();
    FILE *fp = fopen("machines.dat", "rb");
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        getchar();
        clear();
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(int), 1, fp);
    Machine *machine;
    for(int i = 0; i < maximum; ++i){
        machine = machineRead(fp); 
        machinePrint(machine);
    }
    fclose(fp);
    getchar();
    getchar();
    return;
};

void addMachines(){
    char proceed = ('n');
    FILE *fp = fopen("machines.dat", "ab");
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        getchar();
        clear();
        return;
    }
    Machine *machine;
    char *new_name;
    char *new_out_name;
    char *new_in1_name;
    char *new_in2_name;
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
        machine = machineCreate(new_name, new_out_name, new_out_amount, new_in1_name, new_in1_amount, new_in2_name, new_in2_amount);
        clear();
        machinePrint(machine);
        printf("Proceed(y/n)?\n");
        scanf(" %c", &proceed);
        clear();
    }

    machineWrite(fp, machine);
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
    // TODO : make function to remove machine from machines array and file
};

void makeCalculation(){
    // TODO : make function to calculate necessary materials based on end result
};

int main(int arc, char** argv)
{
    clear();
    makeMachinefile();
    readMachines();
    
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
    
        switch (choice)
        {
            case 1:
                readMachines();
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

