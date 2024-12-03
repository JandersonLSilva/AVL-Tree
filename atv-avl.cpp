// Grupo:
// Felipe Marciel Scalco - RA: 2565838
// Janderson Lima Silva - RA: 2565862
// Matheus Vinicius Engelesberger - RA: 2576260
// Raphael dos Santos Souza - RA: 2565951


#include <iostream>
#include <stdlib.h>

using namespace std;


#define bool h;

// Declarando uma estrutura chamada Tree no formato de Arvore binária
struct tree{
    int data;
    struct tree *left;
    struct tree *right;
    int bal;
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
    node->bal = 0;
    return node;
}

void insert_node_Tree(Tree *tree, Tree *node){
    if(node->data < tree->data){
        // if(tree->bal == 0){
        //     h = true;
        // }
        // else{
        //     h = false;
        // }
        // if(h == true) tree->bal--;

        if(tree->left == NULL) {
            tree->left = node;
        }
        else {
            insert_node_Tree(tree->left, node);
        }

    }
    if(node->data > tree->data){
        if(tree->right == NULL) {
            tree->right = node;
        }
        else {
            insert_node_Tree(tree->right, node);
        }
        tree->bal++;

    }
}

// Função que insere um nó
Tree* insert_node(Tree* t, int value){
    if(t == NULL) {
        t = create_node(value); // cria uma nó com sub-arvores nulas
        return t; // retorno a arvore com um unico nó
    };

    t = insert_node_Tree(
        t, create_node(value)
    );

    return t;
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
    int value

    for(True){
        cin >> value;
        cout << "Value: " << value << endl;

        // Se for -1 finaliza a execução
        if(value == -1) exit();

        // Se for 0 finaliza a árvore
        if(value == 0) t = init();

        t = insert_node(t, value);
    }



    // print_pre_order(t);
    cout << endl;

    return 0;
}
