#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer{
    char name[25];
    char email[20];
    int points;
    char phone[14];
    struct Customer *left, *right;
};

struct Customer *root = NULL;

struct Customer *createCustomer(char *phone, char *name, char *email){
    struct Customer *newCustomer = (struct Customer *)malloc(sizeof(struct Customer));
    strcpy(newCustomer->phone, phone);
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->email, email);
    newCustomer->points = 10;
    newCustomer->left = newCustomer->right = NULL;
    return newCustomer;
}

struct Customer *insertCustomer(struct Customer *root, char *phone, char *name, char *email){
    if(!root)return createCustomer(phone, name, email);
    if(strcmp(phone, root->phone) < 0) root->left = insertCustomer(root->left, phone, name, email);
    else if(strcmp(phone, root->phone) > 0) root->right = insertCustomer(root->right, phone, name, email);
    return root;
}

struct Customer *searchCustomer(struct Customer *root, char *phone){
    if(!root || strcmp(root->phone, phone) == 0) return root;
    if(strcmp(phone, root->phone) < 0) return searchCustomer(root->left, phone);
    return searchCustomer(root->right, phone);
}

struct Customer *minValueNode(struct Customer *node){
    struct Customer *current = node;
    while(current && current->left) current = current->left;
    return current;
}

struct Customer *deleteCustomer(struct Customer *root, char *phone){
    if(!root) return root;
    if(strcmp(phone, root->phone) < 0) root->left = deleteCustomer(root->left, phone);
    else if(strcmp(phone, root->phone) > 0)root->right = deleteCustomer(root->right, phone);
    else{
        if(!root->left){
            struct Customer *temp = root->right;
            free(root);
            return temp;
        }else if(!root->right){
            struct Customer *temp = root->left;
            free(root);
            return temp;
        }
        struct Customer *temp = minValueNode(root->right);
        strcpy(root->phone, temp->phone);
        strcpy(root->name, temp->name);
        strcpy(root->email, temp->email);
        root->points = temp->points;
        root->right = deleteCustomer(root->right, temp->phone);
    }
    return root;
}

void inOrder(struct Customer *root){
    if(!root)return;
    inOrder(root->left);
    printf("Nomor HP: %s | Nama: %s | Email: %s | Poin: %d\n", root->phone, root->name, root->email, root->points);
    inOrder(root->right);
}

void processOrder(){
    char phone[14], name[25], email[20];
    printf("Masukkan nomor HP (10-13 digit):\n");
    scanf("%s", phone);
    if(!searchCustomer(root, phone)){
        printf("Pelanggan baru\n");
		printf("Masukkan nama:\n");
        scanf(" %s", name);
        printf("Masukkan email:");
        scanf("%s", email);
        root = insertCustomer(root, phone, name, email);
        printf("Pelanggan terdaftar dengan 10 poin!\n");
    }else{
        printf("Pelanggan sudah ada. Memproses pesanan...\n");
    }
}

void viewCustomers(){
    if(!root)
	printf("Tidak ada data pelanggan!\n");
    else inOrder(root);
}

void removeCustomer(){
    char phone[14];
    printf("Masukkan nomor HP pelanggan yang ingin dihapus:\n");
    scanf("%s", phone);
    if(!searchCustomer(root, phone)){
        printf("Data tidak valid!\n");
    }else{
        root = deleteCustomer(root, phone);
        printf("Pelanggan berhasil dihapus!\n");
    }
}

void freeAll(struct Customer *root){
    if(!root)return;
    freeAll(root->left);
    freeAll(root->right);
    free(root);
}

int main()
{
    int pilih;
    do{
    	printf("BlueBucks\n");
    	printf("===============\n");
        printf("1.Proses Pesanan\n");
		printf("2.Lihat Semua Pelanggan\n");
		printf("3.Hapus Pelanggan\n");
		printf("4.Keluar\n");
		printf("Pilihan anda:\n");
        scanf("%d", &pilih);
        switch(pilih){
            case 1: 
				processOrder(); 
				break;
            case 2: 
				viewCustomers(); 
				break;
            case 3: 
				removeCustomer(); 
				break;
            case 4: 
				freeAll(root); 
				printf("Keluar dari program...\n");
				break;
            default: 
				printf("Pilihan tidak valid!\n");
        }
    }while(pilih!= 4);
    return 0;
}
