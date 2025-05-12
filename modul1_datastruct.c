#include <stdio.h>
#include <string.h>

#define MAX_CAKES 4

struct Cake{
    char no[10];
    char code[10];
    char name[100];
    int stock;
    int price;
};

struct Cake cakes[MAX_CAKES] = 
{
    {"1", "CK001", "Blueberry Cake", 13, 25000},
    {"2", "CK002", "Chocochip Cake", 5, 20000},
    {"3", "CK003", "Mayonaise Cake", 24, 30000},
    {"4", "CK004", "StrawberryCake", 7, 17500}
};

void displayCakes(){
    printf("BLUE CAKE SHOP CASHIER\n");
    printf("=======================\n");
    printf("-------------------------------------------------\n");
    printf("No | Code |  Name         |       Stock | Price\n");
    printf("-------------------------------------------------\n");
    for(int i = 0; i < MAX_CAKES; i++) {
        printf("%-3s %-6s %-20s %-5d Rp %d\n", cakes[i].no, cakes[i].code, cakes[i].name, cakes[i].stock, cakes[i].price);
    }
    printf("---------------------------------------------\n");
}

int findCake(char *code){
    for(int i = 0; i < MAX_CAKES; i++) {
        if(strcmp(cakes[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

void sellCake(){
    char code[10];
    int quantity;
    while(1){
        printf("\nMasukkan kode kue yang ingin dijual: ");
        scanf("%s", code);
        int index = findCake(code);
        if(index == -1){
            printf("--- The Cake Code doesn't exist ---\n");
        }else{
            while(1){
                printf("Masukkan jumlah yang ingin dijual: ");
                scanf("%d", &quantity);
                if(quantity <= 0 || quantity > cakes[index].stock) {
                    printf("...The quantity of cake is not enough...\n");
                }else{
                    int total = cakes[index].price * quantity;
                    printf("Total Harga: Rp %d x %d = Rp %d,-\n", cakes[index].price, quantity, total);
                    cakes[index].stock -= quantity;
                    return;
                }
            }
        }
    }
}

void addStock(){
    char code[10];
    int quantity;
    while(1){
        printf("Masukkan kode kue yang ingin ditambah stoknya:\n");
        scanf("%s", code);
        int index = findCake(code);
        if(index == -1){
            printf("--- The Cake Code doesn't exist ---\n");
        }else{
            while(1){
                printf("Masukkan jumlah stok yang ingin ditambah (1-10):");
                scanf("%d", &quantity);
                if(quantity < 1 || quantity > 10){
                    printf("Jumlah tidak valid, harus antara 1 dan 10\n");
                }else{
                    cakes[index].stock += quantity;
                    printf("Adding Stock Success\n");
                    return;
                }
            }
        }
    }
}

int main()
{
    int a;
    while(1){
        displayCakes();
        printf("Menu\n");
        printf("1.Sell\n");
        printf("2.Add Stock\n");
        printf("3.Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &a);
        switch(a){
            case 1:
                sellCake();
                break;
            case 2:
                addStock();
                break;
            case 3:
                printf("Terima kasih\n");
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

