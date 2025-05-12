#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  

struct Stack{
    char medicines[MAX][50]; 
    int top;                
};

void initStack(struct Stack *s){
    s->top = -1;
}

int isFull(struct Stack *s){
    return s->top == MAX - 1;
}

int isEmpty(struct Stack *s){
    return s->top == -1;
}

void push(struct Stack *s, char *medicine){
    if(isFull(s)){
        printf("Stack penuh,Maaf Tidak bisa menambahkan lebih banyak obat.\n");
        return;
    }
    strcpy(s->medicines[++(s->top)], medicine);
}

void pop(struct Stack *s){
    if(isEmpty(s)){
        printf("Tidak ada obat dalam resep\n");
        return;
    }
    printf("Take Medicine #%d: %s\n", s->top + 1, s->medicines[s->top--]);
}

int main() 
{
    struct Stack prescription;
    char medicine[50];
    char choice[5];    
    do{
        initStack(&prescription);
        printf("Sunib Hospital\n");
        printf("===============\n");
        printf("Enter the medicine name [minimum 5 medicines] ('done' to finish):\n");
        int count = 0;
        while(1){
            printf("Medicine %d: ", count + 1);
            scanf("%s", medicine);
            if(strcmp(medicine, "done") == 0 && count >= 5){
                break;
            }else if(strcmp(medicine, "done") == 0){
                printf("Minimal 5 obat harus dimasukkan!\n");
                continue;
            }
            push(&prescription, medicine);
            count++;
        }
        printf("\nMedicine Prescription:\n");
        while(!isEmpty(&prescription)){
            pop(&prescription);
        }
        printf("Do you want to continue? (yes/no): ");
        scanf(" %4s", choice);
    }while(strcasecmp(choice, "yes") == 0);
    printf("Program terminated.\n");
    return 0;
}

