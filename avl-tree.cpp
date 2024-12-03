// Grupo:
// Felipe Marciel Scalco - RA: 2565838
// Janderson Lima Silva - RA: 2565862
// Matheus Vinicius Engelesberger - RA: 2576260
// Raphael dos Santos Souza - RA: 2565951

#include <iostream>
#include <stdlib.h>

using namespace std;

// Declarando uma estrutura chamada Tree no formato de Arvore binária
struct tree{
    int data;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

// Função que inicializa uma estrutura de Arvore binária
Tree* init(){
    return NULL;
}

// Função que cria um nó em uma estrutura de Arvore binária
Tree* create_node(int v){
    Tree *node = (Tree*)malloc(sizeof(Tree));

    node->data = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_node(Tree *tree, Tree *node){
    if(node->data < tree->data){
        if(tree->left == NULL) tree->left = node;
        else insert_node(tree->left, node);
    }
    if(node->data > tree->data){
        if(tree->right == NULL) tree->right = node;
        else insert_node(tree->right, node);
    }
}

Tree* create_insert_Node(Tree *tree, int v){
    if(tree == NULL) {
        tree = create_node(v);
    }
    else insert_node(tree, create_node(v));
    return tree;
}

// Função que imprime uma estrutura de Arvore binária na forma Pre-Ordem
void print_pre_order(Tree* t){
    if(t!=NULL){
        cout << (char) (t->data) << " ";
        print_pre_order(t->left);
        print_pre_order(t->right);
    }
}

// 50, 30, 70, 20, 60, 80, 15, 10, 5
int main(){
    Tree* t = init();

    t = create_insert_Node(t, 50);
    t = create_insert_Node(t, 30);
    t = create_insert_Node(t, 70);
    t = create_insert_Node(t, 20);
    t = create_insert_Node(t, 60);
    t = create_insert_Node(t, 80);
    t = create_insert_Node(t, 15);
    t = create_insert_Node(t, 10);
    t = create_insert_Node(t, 5);



    print_pre_order(t);
    cout << endl;

    return 0;
}
