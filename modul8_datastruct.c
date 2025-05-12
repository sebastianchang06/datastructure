#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Game{
    char title[26];
    char genre[20];
    int stock;
    int height;
    struct Game *left, *right;
};

typedef struct Game Game;

int max(int a, int b){
    return(a > b) ? a : b;
}

int height(Game *node){
    return node ? node->height : 0;
}

Game *createNode(char *title, char *genre, int stock){
    Game *newNode = (Game*)malloc(sizeof(Game));
    strcpy(newNode->title, title);
    strcpy(newNode->genre, genre);
    newNode->stock = stock;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int getBalance(Game *node){
    return node ? height(node->left) - height(node->right) : 0;
}

Game *rightRotate(Game *y){
    Game *x = y->left;
    Game *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Game *leftRotate(Game *x){
    Game *y = x->right;
    Game *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Game *insert(Game *node, char *title, char *genre, int stock){
    if(!node)
        return createNode(title, genre, stock);
    int cmp = strcmp(title, node->title);
    if(cmp < 0)
        node->left = insert(node->left, title, genre, stock);
    else if(cmp > 0)
        node->right = insert(node->right, title, genre, stock);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if(balance > 1 && strcmp(title, node->left->title) < 0)
        return rightRotate(node);
    if(balance < -1 && strcmp(title, node->right->title) > 0)
        return leftRotate(node);
    if(balance > 1 && strcmp(title, node->left->title) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && strcmp(title, node->right->title) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void inOrder(Game *root){
    if(!root) return;
    inOrder(root->left);
    printf("Title: %s | Genre: %s | Stock: %d\n", root->title, root->genre, root->stock);
    inOrder(root->right);
}

Game *search(Game *root, char *title){
    if(!root) return NULL;
    int cmp = strcmp(title, root->title);
    if(cmp == 0) return root;
    if(cmp < 0) return search(root->left, title);
    return search(root->right, title);
}

Game *minValueNode(Game *node){
    Game *current = node;
    while(current->left)
        current = current->left;
    return current;
}

Game *deleteNode(Game *root, char *title){
    if(!root) 
	return root;
    int cmp = strcmp(title, root->title);
    if(cmp < 0)
        root->left = deleteNode(root->left, title);
    else if(cmp > 0)
        root->right = deleteNode(root->right, title);
    else{
        if(!root->left || !root->right){
            Game *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }else{
            Game *temp = minValueNode(root->right);
            strcpy(root->title, temp->title);
            strcpy(root->genre, temp->genre);
            root->stock = temp->stock;
            root->right = deleteNode(root->right, temp->title);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if(balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if(balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int isValidGenre(char *genre){
    return strcmp(genre, "Action") == 0 || strcmp(genre, "RPG") == 0 ||strcmp(genre, "Adventure") == 0 || strcmp(genre, "Card Game") == 0;
}

void toLowerStr(char *str){
    for(int i = 0; str[i]; i++) str[i] = tolower(str[i]);
}

int main() 
{
    Game *root = NULL;
    int choice;
    char title[30], genre[20], type[10];
    int stock, qty;
    while(1){
        printf("Bluejack GShop\n");
        printf("1.Insert Game\n2.View Game\n3.Update Stock\n4.Exit\n>> ");
        scanf("%d", &choice); getchar();

        if(choice == 1){
            printf("Input Game Title [5-25 characters]: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0;
            if(strlen(title) < 5 || strlen(title) > 25 || search(root, title)){
                printf("Invalid or duplicate title!\n");
                continue;
            }
            printf("Input Genre [Action | RPG | Adventure | Card Game]: ");
            scanf("%[^\n]", genre); getchar();
            if(!isValidGenre(genre)){
                printf("Invalid genre!\n");
                continue;
            }
            printf("Input Stock [min 1]: ");
            scanf("%d", &stock); getchar();
            if(stock < 1){
                printf("Stock must be at least 1!\n");
                continue;
            }
            root = insert(root, title, genre, stock);
            printf("Game inserted successfully!\n");
        }else if(choice == 2){
            if(!root){
                printf("Warehouse is empty!\n");
            }else{
                inOrder(root);
            }
        }else if(choice == 3){
            printf("Input game title to update: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0;
            Game *found = search(root, title);
            if(!found){
                printf("Data not found!\n");
                continue;
            }
            printf("Update Type [add/remove]: ");
            scanf("%s", type); getchar();
            toLowerStr(type);
            if(strcmp(type, "add") != 0 && strcmp(type, "remove") != 0){
                printf("Invalid update type!\n");
                continue;
            }
            printf("Input quantity: ");
            scanf("%d", &qty); getchar();
            if(strcmp(type, "add") == 0){
                if(qty < 1){
                    printf("Quantity must be at least 1!\n");
                    continue;
                }
                found->stock += qty;
                printf("Stock updated.\n");
            }else{
                if(qty < 1 || qty > found->stock){
                    printf("Invalid quantity to remove!\n");
                    continue;
                }
                found->stock -= qty;
                if(found->stock == 0){
                    root = deleteNode(root, title);
                    printf("Game removed due to out of stock.\n");
                }else{
                    printf("Stock updated.\n");
                }
            }
        }else if(choice == 4){
            printf("Goodbye!\n");
            break;
        }else{
            printf("Invalid choice!\n");
        }
    }
return 0;
}
