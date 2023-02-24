#include <stdio.h>
#include <stdlib.h>

typedef struct Material{
    char name [20];
    int amount;
}Material;

typedef struct Machine{
    char name [40];
    Material out;
    Material in1;
    Material in2;
}Machine;

void makeMachinefile(){
    FILE *fp = fopen("machines.dat", "rb");
    if(fp){
        fclose(fp);
        return;
    }
    printf("can't open file to read\n");
    fp = fopen("machines.dat", "wb");
    int begin = 0;
    fwrite(&begin, sizeof(begin), 1, fp);
    printf("Made new file\n");
    fclose(fp); 
    return;
};

void readMachines(){
    FILE *fp = fopen("machines.dat", "rb");
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(maximum), 1, fp);
    printf("maximum = %d\n", maximum);
    Machine *machines[maximum] = malloc(maximum * sizeof(* machines));
    for(int i = 0; i < maximum; ++i){
        fread(&machines[i], sizeof(Machine), 1, fp); 
        printf("machine name: %s\tmaterial output: %s, %d\tmaterial intput: %s, %d %s, %d\n", 
                machines[i].name, machines[i].out.name, machines[i].out.amount, machines[i].in1.name, 
                machines[i].in1.amount, machines[i].in2.name, machines[i].in2.amount);
    }
    fclose(fp); 
    free(machines);
    return;
};

void addMachines(){
    // TODO : make funciton to add machine to machines array and file
};

void removeMachines(){
    // TODO : make function to remove machine from machines array and file
};

void makeCalculation(){
    // TODO : make function to calculate necessary materials based on end result
};

int main(int arc, char** argv)
{
    makeMachinefile();
    readMachines();
    int choice;
    while(1){
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

