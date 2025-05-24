#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_WORD 100
#define ALPHABET_SIZE 26

typedef struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
    char description[256];
}TrieNode;

TrieNode* createNode(){
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    node->description[0] = '\0';
    for(int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

int isValidWord(const char *word){
    if(strlen(word) < 2) return 0;
    for(int i = 0; word[i]; i++){
        if(!isalpha(word[i])) return 0;
    }
    return 1;
}

int isValidDescription(const char *desc){
    int wordCount = 0, inWord = 0;
    for(int i = 0; desc[i]; i++){
        if(isspace(desc[i])){
            if(inWord){
                wordCount++;
                inWord = 0;
            }
        }else{
            inWord = 1;
        }
    }
    if(inWord) wordCount++;
    return wordCount >= 2;
}

int isTrieEmpty(TrieNode *node){
    if(node->isEndOfWord) return 0;
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(node->children[i]){
            if(!isTrieEmpty(node->children[i])){
                return 0;
            }
        }
    }
    return 1;
}

int deleteWord(TrieNode *node, const char *word, int depth){
    if(!node) return 0;

    if(word[depth] == '\0'){
        if (!node->isEndOfWord) return 0;
        node->isEndOfWord = 0;
        node->description[0] = '\0';
        return isTrieEmpty(node);
    }

    int idx = tolower(word[depth]) - 'a';
    if(!node->children[idx]) return 0;

    int shouldDeleteChild = deleteWord(node->children[idx], word, depth + 1);

    if(shouldDeleteChild){
        free(node->children[idx]);
        node->children[idx] = NULL;
        return !node->isEndOfWord && isTrieEmpty(node);
    }
    return 0;
}

void insert(TrieNode *root, const char *word, const char *description){
    TrieNode *cur = root;
    for(int i = 0; word[i]; i++){
        int idx = tolower(word[i]) - 'a';
        if(!cur->children[idx]) cur->children[idx] = createNode();
        cur = cur->children[idx];
    }
    cur->isEndOfWord = 1;
    strcpy(cur->description, description);
}

TrieNode* search(TrieNode *root, const char *word){
    TrieNode *cur = root;
    for(int i = 0; word[i]; i++){
        int idx = tolower(word[i]) - 'a';
        if(!cur->children[idx])
            return NULL;
        cur = cur->children[idx];
    }
    return cur->isEndOfWord ? cur : NULL;
}

void printWordsWithPrefix(TrieNode *node, char *prefix, int level){
    if(node->isEndOfWord){
        prefix[level] = '\0';
        printf("%s\n", prefix);
    }
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(node->children[i]){
            prefix[level] = 'a' + i;
            printWordsWithPrefix(node->children[i], prefix, level + 1);
        }
    }
}

void viewAllWords(TrieNode *root){
    char buffer[MAX_WORD];
    printWordsWithPrefix(root, buffer, 0);
}

void pressEnter(){
    printf("Press enter to continue...\n");
    while(getchar() != '\n');
}

void menu(){
    printf("BOOGLE\n");
    printf("1.Release a new slang word\n");
    printf("2.Search a slang word\n");
    printf("3.View all slang words starting with a certain prefix\n");
    printf("4.View all slang words\n");
    printf("5.Delete a slang word\n");
    printf("6.Exit\n");
    printf("Choose menu: ");
}

int main() 
{
    TrieNode *root = createNode();
    int choice;
    char word[MAX_WORD], description[256], prefix[MAX_WORD], temp[MAX_WORD];

    while(1){
        menu();
        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, "%d", &choice);

        switch(choice){
            case 1:
                while(1){
                    printf("Input a new slang word [Must be >1 char & no space]: ");
                    fgets(word, sizeof(word), stdin);
                    word[strcspn(word, "\n")] = '\0';
                    if(isValidWord(word)) break;
                }
                while(1){
                    printf("Input description [Must be >2 words]: ");
                    fgets(description, sizeof(description), stdin);
                    description[strcspn(description, "\n")] = '\0';
                    if(isValidDescription(description)) break;
                }
                if(search(root, word)){
                    insert(root, word, description);
                    printf("Successfully updated a slang word.\n");
                }else{
                    insert(root, word, description);
                    printf("Successfully released new slang word.\n");
                }
                pressEnter();
                break;
                
            case 2:
                while(1){
                    printf("Input slang word to search [>1 char & no space]: ");
                    fgets(word, sizeof(word), stdin);
                    word[strcspn(word, "\n")] = '\0';
                    if (isValidWord(word)) break;
                }
                
                TrieNode *res = search(root, word);
                if(res){
                	printf("Slang word  : %s\n", word);
                    printf("Description : %s\n", res->description);
                }else{
                    printf("There is no word \"%s\" in the dictionary.\n", word);
                }
                pressEnter();
                break;
                
            case 3:
                printf("Input a prefix to be searched: ");
                fgets(prefix, sizeof(prefix), stdin);
                prefix[strcspn(prefix, "\n")] = '\0';
            
	            TrieNode *cur = root;
	            int found = 1;
	            for(int i = 0; prefix[i]; i++){
	                int idx = tolower(prefix[i]) - 'a';
	                if(!cur->children[idx]){
	                    found = 0;
	                    break;
	                }
	                	cur = cur->children[idx];
	                }
	                if(found){
	                	printf("Words starts with \"%s\":\n", prefix);
	                    char buffer[MAX_WORD];
	                    strcpy(buffer, prefix);
	                    printWordsWithPrefix(cur, buffer, strlen(prefix));
	                }else{
	                    printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
	                }       
                	pressEnter();
                	break;
                	
			case 4:
    			if(isTrieEmpty(root)){
        			printf("There is no slang word yet in the dictionary.\n");
    			}else{
			        printf("List of all slang words in the dictionary:\n");
			        viewAllWords(root);
			    }
			    pressEnter();
			    break;
			    
			case 5:
				while(1){
			        printf("Input slang word to delete [>1 char & no space]: ");
			        fgets(word, sizeof(word), stdin);
			        word[strcspn(word, "\n")] = '\0';
			        if (isValidWord(word)) break;
			    }

			    if(search(root, word)){
			        deleteWord(root, word, 0);
			        printf("Slang word \"%s\" successfully deleted from dictionary.\n", word);
			    }else{
			        printf("Slang word \"%s\" not found in dictionary.\n", word);
			    }
			    pressEnter();
			    break;
			    
            case 6:
                printf("Thank you... Have a nice day :)\n");
                return 0;
            	default:
                	printf("Invalid choice\n");
                	pressEnter();
        }
    }
    return 0;
}
