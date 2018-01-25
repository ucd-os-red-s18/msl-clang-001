#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int count;
    char* word;
    struct node *left;
    struct node *right;
};

struct node* newNode(char* data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->word = data;
    node->left = NULL;
    node->right = NULL;
    node->count = 1;

    return(node);
}

struct node* insert(struct node * node, char* data){
    if(node == NULL){
        return(newNode(data));
    }
    else{
        if(strcmp(data, node->word) == 0){
            node->count += 1;
            return(node);
        }
        if(strcmp(data, node->word) < 0) {
            node->left = insert(node->left, data);
        }
        else{
            node->right = insert(node->right, data);
        }
        return(node);
    }
}


void writeFile(FILE * fp, struct node* root){
    if(root!= NULL){
        writeFile(fp, root->left);
        fprintf(fp, "%s", root->word);
        fprintf(fp, ": %d",root->count);
        writeFile(fp, root->right);
    }
}
int main(int argc, char **argv) {
    struct node *root;
    char data[20];
    root = NULL;
    FILE *f;
    f = fopen("C:/Users/khoan/Desktop/msl-clang-001-master/input02.txt", "r");
    while(fscanf(f, "%s", data) != EOF){
        root = insert(root, data);
    }
    if(f == NULL){
        printf("can't find input file");
        exit(1);
    }
    fclose(f);
    FILE *w = fopen("C:/Users/khoan/Desktop/msl-clang-001-master/output.txt", "w");
    if(w == NULL){
        printf("can't find write file");
        exit(2);
    }
    writeFile(w, root);
    fclose(w);
    free(root);
    exit(0);
}