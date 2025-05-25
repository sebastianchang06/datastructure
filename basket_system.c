#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SIZE 101

typedef struct Player{
    char name[50];
    int height;
    int weight;
    char position[20];
    struct Player* next;
}Player;

Player* hashTable[SIZE];

int isValidName(char* name){
    if(strlen(name) < 3) 
	return 0;
    for(int i = 0; name[i]; i++){
        if(!(isalpha(name[i]) || name[i] == ' ')) 
		return 0;
    }
    return 1;
}

int isValidHeight(int height){
    return height >= 140 && height <= 250;
}

int isValidWeight(int weight){
    return weight >= 40 && weight <= 200;
}

int isValidPosition(char* pos){
    if(strlen(pos) < 2) return 0;
    for(int i = 0; pos[i]; i++){
        if(!(isalpha(pos[i]) || pos[i] == ' ')) 
		return 0;
    }
    return 1;
}

int hash(char* name){
    int sum = 0;
    for(int i = 0; name[i]; i++){
        sum += name[i] * (i + 1);
    }
    return sum % SIZE;
}

Player* createPlayer(char* name, int height, int weight, char* position){
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    strcpy(newPlayer->name, name);
    newPlayer->height = height;
    newPlayer->weight = weight;
    strcpy(newPlayer->position, position);
    newPlayer->next = NULL;
    return newPlayer;
}

void insertPlayer(char* name, int height, int weight, char* position){
    int idx = hash(name);
    Player* head = hashTable[idx];
    while(head){
        if(strcmp(head->name, name) == 0){
            head->height = height;
            head->weight = weight;
            strcpy(head->position, position);
            printf("Data pemain '%s' berhasil diperbarui.\n", name);
            return;
        }
        head = head->next;
    }
    Player* newPlayer = createPlayer(name, height, weight, position);
    newPlayer->next = hashTable[idx];
    hashTable[idx] = newPlayer;
    printf("Pemain '%s' berhasil ditambahkan\n", name);
}

Player* searchPlayer(char* name){
    int idx = hash(name);
    Player* head = hashTable[idx];
    while(head){
        if(strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

void viewPlayer(char* name){
    Player* p = searchPlayer(name);
    if(p){
        printf("-------------------------DATA PEMAIN-----------------------------\n");
        printf("+----------------------+--------+--------+----------------------+\n");
        printf("|        Nama          | Tinggi | Berat  |       Posisi         |\n");
        printf("+----------------------+--------+--------+----------------------+\n");
        printf("| %-20s | %6d | %6d | %-20s |\n", 
               p->name, p->height, p->weight, p->position);
        printf("+----------------------+--------+--------+----------------------+\n");
    }else{
        printf("Pemain dengan nama '%s' tidak ditemukan\n", name);
    }
}

void viewAll(){
    int found = 0;
    printf("---------------DAFTAR PEMAIN---------------\n");
    printf("+----------------------+--------+--------+----------------------+\n");
    printf("|        Nama          | Tinggi | Berat  |       Posisi         |\n");
    printf("+----------------------+--------+--------+----------------------+\n");
    for(int i = 0; i < SIZE; i++){
        Player* curr = hashTable[i];
        while(curr){
            printf("| %-20s | %6d | %6d | %-20s |\n", 
                   curr->name, curr->height, curr->weight, curr->position);
            curr = curr->next;
            found = 1;
        }
    }
    if(!found){
        printf("|        Tidak ada data pemain yang tersedia.                 |\n");
    }
    printf("+----------------------+--------+--------+----------------------+\n");
}

void deletePlayer(char* name){
    if(!isValidName(name)){
        printf("Nama tidak valid. Minimal 3 huruf dan hanya huruf/spasi.\n");
        return;
    }
    int idx = hash(name);
    Player* curr = hashTable[idx];
    Player* prev = NULL;
    while(curr){
        if(strcmp(curr->name, name) == 0){
            printf("Data pemain yang akan dihapus:\n");
            printf("+----------------------+--------+--------+----------------------+\n");
            printf("|        Nama          | Tinggi | Berat  |       Posisi         |\n");
            printf("+----------------------+--------+--------+----------------------+\n");
            printf("| %-20s | %6d | %6d | %-20s |\n", curr->name, curr->height, curr->weight, curr->position);
            printf("+----------------------+--------+--------+----------------------+\n");
            char confirm;
            printf("Apakah Anda yakin ingin menghapus pemain ini? [y/n]: ");
            scanf(" %c", &confirm);
            getchar();
            if(confirm == 'y' || confirm == 'Y'){
                if(prev) prev->next = curr->next;
                else hashTable[idx] = curr->next;
                free(curr);
                printf("Pemain '%s' berhasil dihapus.\n", name);
            } else {
                printf("Penghapusan dibatalkan.\n");
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Pemain '%s' tidak ditemukan.\n", name);
}

void addOrUpdatePlayer(){
    char name[50], position[20];
    int height, weight;

    do{
        printf("Nama pemain       : ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if(!isValidName(name)){
            printf("Nama tidak valid [Minimal 3 huruf dan hanya huruf/spasi]\n");
        }
    }while(!isValidName(name));

    do{
        printf("Tinggi (cm)       : ");
        scanf("%d", &height);
        getchar();
        if(!isValidHeight(height)){
            printf("Tinggi harus antara 140 - 250 cm\n");
        }
    }while(!isValidHeight(height));

    do{
        printf("Berat (kg)        : ");
        scanf("%d", &weight);
        getchar();
        if(!isValidWeight(weight)){
            printf("Berat harus antara 40 - 200 kg\n");
        }
    }while(!isValidWeight(weight));

    do{
        printf("Posisi            : ");
        fgets(position, sizeof(position), stdin);
        position[strcspn(position, "\n")] = '\0';
        if(!isValidPosition(position)){
            printf("Posisi tidak valid [Minimal 2 huruf dan hanya huruf/spasi]\n");
        }
    }while(!isValidPosition(position));

    insertPlayer(name, height, weight, position);
}

void searchAndShowPlayer(){
    char name[50];
    printf("Nama pemain yang dicari: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    Player* p = searchPlayer(name);
    if(p){
        printf("Pemain '%s' ditemukan.\n", p->name);
        printf("Tinggi : %d cm\n", p->height);
        printf("Berat  : %d kg\n", p->weight);
        printf("Posisi : %s\n", p->position);
    }else{
        printf("Pemain '%s' tidak ditemukan\n", name);
    }
}

void inputAndViewPlayer(){
    char name[50];
    printf("Masukkan nama pemain: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    viewPlayer(name);
}

void inputAndDeletePlayer(){
    char name[50];
    printf("Nama pemain yang ingin dihapus: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    deletePlayer(name);
}

int main() 
{
    int choice;

    do{
        printf("Sistem Management Pemain Gatotkaca Basketball\n");
        printf("1.Tambah/Update Pemain\n");
        printf("2.Cari Data Pemain\n");
        printf("3.Lihat Data Pemain\n");
        printf("4.Lihat Semua Pemain\n");
        printf("5.Hapus Pemain\n");
        printf("6.Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        getchar();
        system("cls");

        switch(choice){
            case 1:
                addOrUpdatePlayer();
                break;
            case 2:
                searchAndShowPlayer();
                break;
            case 3:
                inputAndViewPlayer();
                break;
            case 4:
                viewAll();
                break;
            case 5:
                inputAndDeletePlayer();
                break;
            case 6:
                printf("Terima kasih telah menggunakan program ini\n");
                break;
            default:
                printf("Menu tidak valid!\n");
                break;
        }
        if(choice != 6){
            printf("Tekan Enter untuk melanjutkan");
            getchar();
            system("cls");
        }
    }while(choice != 6);
    return 0;
}
