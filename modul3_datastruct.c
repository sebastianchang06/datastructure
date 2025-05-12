#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient{
    char name[26];         
    int age;               
    char description[256]; 
    char code[7];          
    int priority;          
    struct Patient *next;
    struct Patient *prev;
};

struct Patient *head = NULL; 

int getPriority(const char *code){
    if(strcmp(code, "Red") == 0)
        return 3;
    else if(strcmp(code, "Yellow") == 0)
        return 2;
    else if(strcmp(code, "Green") == 0)
        return 1;
    else
        return 0; 
}

void insertPatient(){
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    if(!newPatient){
        printf("Memory allocation error!\n");
        return;
    }

    do{
        printf("Enter name (4-25 characters): ");
        fgets(newPatient->name, 26, stdin);
        newPatient->name[strcspn(newPatient->name, "\n")] = 0; 
        if (strlen(newPatient->name) < 4 || strlen(newPatient->name) > 25)
            printf("Invalid name length. Please try again.\n");
    }while(strlen(newPatient->name) < 4 || strlen(newPatient->name) > 25);
    
    do{
        printf("Enter age (>=0): ");
        scanf("%d", &newPatient->age);
        if(newPatient->age < 0)
            printf("Invalid age. Please try again.\n");
    }while(newPatient->age < 0);
    while(getchar() != '\n'); 
    
    do{
        printf("Enter description/symptoms (at least 6 characters): ");
        fgets(newPatient->description, 256, stdin);
        newPatient->description[strcspn(newPatient->description, "\n")] = 0;
        if(strlen(newPatient->description) < 6)
            printf("Description too short. Please try again.\n");
    }while(strlen(newPatient->description) < 6);
    
    do{
        printf("Enter code (Red, Yellow, or Green): ");
        fgets(newPatient->code, 7, stdin);
        newPatient->code[strcspn(newPatient->code, "\n")] = 0;
        if(strcmp(newPatient->code, "Red") != 0 && strcmp(newPatient->code, "Yellow") != 0 && strcmp(newPatient->code, "Green") != 0)
            printf("Invalid code. Please try again.\n");
    }while(strcmp(newPatient->code, "Red") != 0 && strcmp(newPatient->code, "Yellow") != 0 && strcmp(newPatient->code, "Green") != 0);
    
    newPatient->priority = getPriority(newPatient->code);
    newPatient->next = NULL;
    newPatient->prev = NULL;

    if(head == NULL){
        head = newPatient;
    }else{
        if(newPatient->priority > head->priority){
            newPatient->next = head;
            head->prev = newPatient;
            head = newPatient;
         }else{
            struct Patient *current = head;
            while(current->next != NULL && current->next->priority >= newPatient->priority){
                current = current->next;
            }
            newPatient->next = current->next;
            if(current->next != NULL){
                current->next->prev = newPatient;
            }
            current->next = newPatient;
            newPatient->prev = current;
        }
    }
    printf("Patient added successfully!\n");
}

void viewQueue(){
    if(head == NULL){
        printf("There is no queue yet!\n");
        return;
    }
    struct Patient *current = head;
    int count = 1;
    while(current != NULL){
        printf("Patient %d:\n", count);
        printf("Name: %s\n", current->name);
        printf("Age: %d\n", current->age);
        printf("Description: %s\n", current->description);
        printf("Code: %s (Priority: %d)\n", current->code, current->priority);
        printf("---------------------\n");
        current = current->next;
        count++;
    }
}

void nextQueue(){
    if(head == NULL){
        printf("There is no queue yet!\n");
        return;
    }
    struct Patient *temp = head;
    printf("Next patient:\n");
    printf("Name: %s\n", temp->name);
    printf("Age: %d\n", temp->age);
    printf("Description: %s\n", temp->description);
    printf("Code: %s (Priority: %d)\n", temp->code, temp->priority);

    head = head->next;
    if(head != NULL)
        head->prev = NULL;
    free(temp);
}

void freeQueue(){
    while(head != NULL){
        struct Patient *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() 
{
    int pilih;
    do{
        printf("Bluejack Hospital\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Next Queue\n");
        printf("4. Exit\n");
        printf("pilihan: ");
        scanf("%d", &pilih);
        while(getchar() != '\n'); 
    
        switch(pilih){
            case 1:
                insertPatient();
                break;
            case 2:
                viewQueue();
                break;
            case 3:
                nextQueue();
                break;
            case 4:
                printf("Exiting the program.\n");
                freeQueue();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while(pilih != 4);    
}

