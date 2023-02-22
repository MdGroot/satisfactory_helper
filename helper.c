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
    
    printf("Error: can't open file to read\n");
    fp = fopen("machines.dat", "wb");
    int begin = 0;
    fwrite(&begin, sizeof(&begin), 1, fp);
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
    fread(&maximum, sizeof(&maximum), 1, fp);
    printf("maximum = %d\n", maximum);
    Machine *machines = malloc(maximum * sizeof(&machines));
    for(int i = 0; i <= maximum; ++i){
        fread(&machines[i], sizeof(&machines[i]), 1, fp); 
        printf("machine name: %s\tmaterial output: %s, %d\tmaterial intput: %s, %d %s, %d\n", 
                machines[i].name, machines[i].out.name, machines[i].out.amount, machines[i].in1.name, 
                machines[i].in1.amount, machines[i].in2.name, machines[i].in2.amount);
    }
    fclose(fp); 
    free(machines);
    return;
};

void addmachines(){
    // TODO : make funciton to add machine to machines array and file
};

void removemachines(){
    // TODO : make function to remove machine from machines array and file
};

void makecalculation(){
    // TODO : make function to calculate necessary materials based on end result
};

int main(int arc, char* argv[])
{
    makeMachinefile();
    readMachines();
    int choice;

    printf("1. Read Machines\n");
    printf("2. Add Machines\n");
    printf("3. Remove Machines\n");
    printf("4. Make Calculation\n");
    printf("Enter your choice: ");

    // Read the user's choice
    scanf("%1d", &choice);

    // Switch statement to handle the user's choice
    switch (choice)
    {
        case 1:
            readMachines();
            break;
        case 2:
            addmachines();
            break;
        case 3:
            removemachines();
            break;
        case 4:
            makecalculation();
            break;
        default:
            printf("menu error\n");
            break;
    }
    return 0;
}

