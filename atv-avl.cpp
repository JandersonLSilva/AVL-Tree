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

// Função que faz a rotação simples
void simple_rotation(Tree* t){
    if(tree->bal ==  -2 && tree->left->bal == -1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for -1
        Tree* node_p = t; // guardando a árvore atual
        Tree* node_u = t->left; // guardando o nó a esquerda da árvore atual

    }
    else if(tree->bal ==  2 && tree->right->bal == 1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for 1
        Tree* node_p = t; // guardando a árvore atual
        Tree* node_z = t->right; // guardando o nó a direita da árvore atual
    }
}

// Função que faz a rotação dupla da árvore
void double_rotaation(Tree* t){
    if(tree->bal ==  -2 && tree->left->bal == 1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for 1
        Tree* node_p = t; // guardando a árvore atual
        Tree* node_u = t->left; // guardando o nó a esquerda da árvore atual
        Tree* node_v = t->left->right; // guardando o nó a direita do nó a esquerda da árvore atual
    }
    else if(tree->bal ==  2 && tree->right->bal == -1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for -1
        Tree* node_p = t; // guardando a árvore atual
        Tree* node_z = t->right; // guardando o nó a direita da árvore atual
        Tree* node_y = t->right->left; // guardando o nó a esquerda do nó a direita da árvore atual
    }
}


// Função que inseri um nó ná arvore
void insert_node_Tree(Tree *tree, Tree *node){
    int bal_temp; // declara uma de balanceamento temporária

    // verificando se o valor do nó a ser inserido é menor que o valor do nó em questão
    if(node->data < tree->data){

        // verificando se o prŕoximo nó a esquerda da arvore atual está vazia
        if(tree->left == NULL) {
            tree->left = node; // insere o nó a esquerda da árvore, já que o nó está vazio

            tree->bal--; // diminui o balanceamento, já que o nó foi inserido a esquerda

            return; // finaliza a chamada atual da função
        }
        else { // se o nó a esquerda não estiver vazio
            bal_temp = tree->left->bal; // guarda o balanceamento atual do nó em questão

            insert_node_Tree(tree->left, node);
            // realiza a chamada da própia função, passando o nó a esquerda que ainda precisa ser comparada com o nó em questão

            if((bal_temp == 0) && (tree->left->bal != 0)){
                // se o balanceamento do nó esquerdo da arvore atual era 0 e passou a ser 1 ou -1, então continua a diminuir o balanceamento

                tree->bal--; // efetiva a diminuição

                if(tree->bal ==  -2 && tree->left->bal == -1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for -1
                    simple_rotation(tree); // chama a função de rotação simples
                }
                else if(tree->bal ==  -2 && tree->left->bal == 1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for 1
                    double_rotation(tree); // chama a função de rotação simples
                }
            }
            return; // finaliza a chamada atual da função
        }
    }

    // verificando se o valor do nó a ser inserido é maior que o valor do nó em questão
    if(node->data > tree->data){
        // verificando se o prŕoximo nó a direita da arvore atual está vazia
        if(tree->right == NULL) {
            tree->right = node; // insere o nó a direita da árvore, já que o nó está vazio

            tree->bal++;// aumenta o balanceamento, já que o nó foi inserido a direita

            return; // finaliza a chamada atual da função
        }
        else { // se o nó a esquerda não estiver vazio
            bal_temp = tree->right->bal; // guarda o balanceamento atual do nó em questão

            insert_node_Tree(tree->right, node);
            // realiza a chamada da própia função, passando o nó a direita que ainda precisa ser comparada com o nó em questão

            if((bal_temp == 0) && (tree->right->bal != 0)){
                // se o balanceamento do nó direito da arvore atual era 0 e passou a ser 1 ou -1, então continua a aumentar o balanceamento

                tree->bal++; // efetiva o aumento

                if(tree->bal ==  2 && tree->right->bal == 1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for 1
                    simple_rotation(tree); // chama a função de rotação simples
                }
                else if(tree->bal ==  2 && tree->right->bal == -1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for -1
                    double_rotation(tree); // chama a função de rotação dupla
                }
            }
            return; // finaliza a chamada atual da função
        }


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
