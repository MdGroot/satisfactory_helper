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
    FILE *fp = fopen("machines.dat", "r");
    if(fp){
        fclose(fp);
        return;
    }
    printf("can't open file to read\n");
    fp = fopen("machines.dat", "w");
    int begin = 0;
    fwrite(&begin, sizeof(begin), 1, fp);
    printf("Made new file\n");
    fclose(fp); 
    return;
};

void readMachines(){
    FILE *fp = fopen("machines.dat", "r");
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        return;
    }
    int maximum = 0;
    fread(&maximum, sizeof(maximum), 1, fp);
    printf("maximum = %d\n", maximum);
    Machine *machines = (Machine *) malloc(maximum * sizeof(* machines));
    for(int i = 0; i < maximum; ++i){
        fread(&machines[i], sizeof(Machine), 1, fp); 
        printf("Machine name: %s\nMaterial output: %s, %d\nMaterial 1 intput: %s, %d\nMaterial 2 intput: %s, %d\n", 
                machines[i].name, 
                machines[i].out.name, machines[i].out.amount, machines[i].in1.name, 
                machines[i].in1.amount, machines[i].in2.name, machines[i].in2.amount);
    }
    fclose(fp); 
    free(machines);
    return;
};

void addMachines(){
    // FIX : make funciton to add machine to machines array and file
    char proceed = ('n');
    FILE *fp = fopen("machines.dat", "a");
    if(!fp)
    {
        printf("Error: can't open file to read\n");
        return;
    }
    Machine *newmachine = (Machine *) malloc(sizeof(* newmachine));
    while(proceed == ('n')) {
        printf("New machine name: ");
        scanf(" %[^\n]", newmachine->name);
        printf("Material out name: ");
        scanf(" %[^\n]", newmachine->out.name);
        printf("Material out amount: ");
        scanf(" %d", &newmachine->out.amount);
        printf("Material in1 name: ");
        scanf(" %[^\n]", newmachine->in1.name);
        printf("Material in1 amount: ");
        scanf(" %d", &newmachine->in1.amount);
        printf("Material in2 name: ");
        scanf(" %[^\n]", newmachine->in2.name);
        printf("Material in2 amount: ");
        scanf(" %d", &newmachine->in2.amount);
        printf("\n\nMachine name: %s\n", newmachine->name);
        printf("Material out name: %s\n", newmachine->out.name);
        printf("Material out amount: %d\n", newmachine->out.amount);
        printf("Material in1 name: %s\n", newmachine->in1.name);
        printf("Material in1 amount: %d\n", newmachine->in1.amount);
        printf("Material in2 name: %s\n", newmachine->in2.name);
        printf("Material in2 amount: %d\n\n", newmachine->in2.amount);
        printf("Proceed(y/n)?\n");
        scanf(" %c", &proceed);
    }
    fwrite(&newmachine, sizeof(Machine), 1, fp);
    fclose(fp); 
    fp = fopen("machines.dat", "r");
    int amount = 0;
    fread(&amount, sizeof(amount), 1, fp);
    printf("amount = %d\n", amount);
    fclose(fp);
    fp = fopen("machines.dat", "w");
    ++amount;
    fwrite(&amount, sizeof(amount), 1, fp);
    printf("Wrote new amount\n");
    fclose(fp); 
    free(newmachine);
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

