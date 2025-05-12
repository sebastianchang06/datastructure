#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1007
#define MAX_MEDICINES 1000

struct Medicine{
    char id[30];  
    char name[51]; 
    char manufacturer[26]; 
    char registration[11]; 
    char batch[17]; 
};

struct Medicine hashTable[TABLE_SIZE]; 
int medicineCount = 0; 
int hashFunction(char *medicineId){
    int sum = 0;
    for(int i = 0; medicineId[i] != '\0'; i++){
        sum += medicineId[i];
    }
    return sum % TABLE_SIZE;
}

void generateMedicineID(struct Medicine *medicine, int index){
    sprintf(medicine->id, "M%05d-%s-%c%c", index + 1, medicine->registration, toupper(medicine->manufacturer[0]), toupper(medicine->name[0]));
}

void insertMedicine(){
    if(medicineCount >= MAX_MEDICINES){
        printf("Medicine storage is full!\n");
        return;
    }
    struct Medicine newMedicine;
    printf("Enter Medicine Name (5-50 characters): ");
    scanf(" %[^\n]", newMedicine.name);
    if(strlen(newMedicine.name) < 5 || strlen(newMedicine.name) > 50){
        printf("Invalid Medicine Name Length!\n");
        return;
    }
    printf("Enter Manufacturer Name (must end with 'Ltd.', 3-25 characters): ");
    scanf(" %[^\n]", newMedicine.manufacturer);
    int len = strlen(newMedicine.manufacturer);
    if(len < 3 || len > 25 || strcmp(&newMedicine.manufacturer[len-4], "Ltd.") != 0){
        printf("Invalid Manufacturer Name Format!\n");
        return;
    }
    printf("Enter Registration Number (10 digits): ");
    scanf(" %s", newMedicine.registration);
    if(strlen(newMedicine.registration) != 10){
        printf("Invalid Registration Number!\n");
        return;
    }
    printf("Enter Batch Number (at least 16 characters): ");
    scanf(" %s", newMedicine.batch);
    if(strlen(newMedicine.batch) < 16){
        printf("Invalid Batch Number!\n");
        return;
    }
    generateMedicineID(&newMedicine, medicineCount);
    int index = hashFunction(newMedicine.id);
    hashTable[index] = newMedicine;
    medicineCount++;    
    printf("Medicine Added Successfully with ID: %s\n", newMedicine.id);
}

void viewMedicines(){
    if(medicineCount == 0){
        printf("There is no medicine(s)!\n");
        return;
    }
    for(int i = 0; i < TABLE_SIZE; i++){
        if(strlen(hashTable[i].id) > 0){
            printf("Medicine ID: %s\n", hashTable[i].id);
            printf("Name: %s\n", hashTable[i].name);
            printf("Manufacturer: %s\n", hashTable[i].manufacturer);
            printf("Registration: %s\n", hashTable[i].registration);
            printf("Batch: %s\n", hashTable[i].batch);
            printf("--------------------------------\n");
        }
    }
}

void removeMedicine(){
    if(medicineCount == 0){
        printf("There is no medicine(s) to remove!\n");
        return;
    }
    char medicineId[30];
    printf("Enter Medicine ID to Remove: ");
    scanf(" %s", medicineId);
    int index = hashFunction(medicineId);
    if(strcmp(hashTable[index].id, medicineId) == 0){
        printf("Medicine Found: %s\n", hashTable[index].name);
        printf("Confirm Delete? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if(confirm == 'y'){
            strcpy(hashTable[index].id, ""); 
            printf("Medicine Deleted Successfully!\n");
            medicineCount--;
        }else{
            printf("Deletion Cancelled.\n");
        }
    }else{
        printf("Medicine not found!\n");
    }
}

int main() 
{
    int choice;
    do{
        printf("\n=== Sunib Hospital Medicine Management ===\n");
        printf("1. View Medicine\n");
        printf("2. Insert Medicine\n");
        printf("3. Remove Medicine\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: viewMedicines(); break;
            case 2: insertMedicine(); break;
            case 3: removeMedicine(); break;
            case 4: printf("Exiting Program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    }while(choice != 4);

    return 0;
}

