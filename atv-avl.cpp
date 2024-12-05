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
Tree* simple_rotation(Tree* tree){
    if(tree->bal ==  -2 && tree->left->bal == -1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for -1

        Tree* node_p = tree; // guarda a árvore atual
        Tree* node_u = tree->left; // guarda o nó da esquerda da árvore atual

        // Atribuindo os novos balanceamentos:
        node_p->bal = 0;
        node_u->bal = 0;

        node_p->left = node_u->right; // atribui o nó a direita do nó 'u', á esquerda do nó 'p'

        node_u->right = node_p; // atrubui o nó 'p', à direita do no 'u'

        tree = node_u; // atribui o nó 'u', ao nó atual
        cout << "RSD " << node_p->data << endl;
    }
    else if(tree->bal ==  2 && tree->right->bal == 1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for 1
        Tree* node_p = tree; // guarda a árvore atual
        Tree* node_z = tree->right; // guarda o nó da direita da árvore atual

        // Atribuindo os novos balanceamentos:
        node_p->bal = 0;
        node_z->bal = 0;

        node_p->right = node_z->left; // atribui o nó a esquerda do nó 'z', à direita do nó 'p'

        node_z->left = node_p; // atribui o nó 'p', á esquerda do nó 'z'

        tree = node_z; // atribui o nó 'z', ao nó atual
        cout << "RSE " << node_p->data << endl;
    }
    return tree;
}

// Função que faz a rotação dupla da árvore
Tree* double_rotation(Tree* tree){
    if(tree->bal ==  -2 && tree->left->bal == 1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for 1
        Tree* node_p = tree; // guarda o nó da árvore atual
        Tree* node_u = tree->left; // guarda o nó da esquerda da árvore atual
        Tree* node_v = tree->left->right; // guarda o nó da direita do nó a esquerda da árvore atual

        // Atribuindo os novos balanceamentos:
        node_p->bal = 1;
        node_u->bal = 0;
        node_v->bal = 0;

        node_u->right = node_v->left; // atribui o nó a esquerda do nó 'v', à direita do nó 'u'

        node_p->left = node_v->right; // atribui o nó a direita do nó 'v', à esquerda do nó 'p'

        node_v->left = node_u; // atribui o nó 'u', à esquerda dó nó 'v'
        node_v->right = node_p; // atribui o nó 'p', à direita do nó 'v'

        tree = node_v; // atribui o nó 'z', ao nó atual
        cout << "RDD " << node_p->data << endl;
    }
    else if(tree->bal ==  2 && tree->right->bal == -1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for -1
        Tree* node_p = tree; // guarda da árvore atual
        Tree* node_z = tree->right; // guarda o nó da direita da árvore atual
        Tree* node_y = tree->right->left; // guarda o nó da esquerda do nó a direita da árvore atual

        // Atribuindo os novos balanceamentos:
        node_p->bal = -1;
        node_z->bal = 0;
        node_y->bal = 0;

        node_z->left = node_y->right; // atribui o nó a direita do nó 'y', à esquerda do nó 'z'
        node_p->right = node_y->left; // atribui o nó a direita do nó 'y', à direita do nó 'p'

        node_y->left = node_p; // atribui o nó 'p', à esquerda do nó 'y'
        node_y->right = node_z; // atribui o nó 'z', à direita do nó 'y'

        tree = node_y; // atribui o nó 'y', ao nó atual
        cout << "RDE " << node_p->data << endl;
    }
    return tree;
}


// Função que inseri um nó ná arvore
Tree* insert_node_Tree(Tree *tree, Tree *node){
    int bal_temp; // declara uma de balanceamento temporária

    // verificando se o valor do nó a ser inserido é menor que o valor do nó em questão
    if(node->data < tree->data){

        // verificando se o prŕoximo nó a esquerda da arvore atual está vazia
        if(tree->left == NULL) {
            tree->left = node; // insere o nó a esquerda da árvore, já que o nó está vazio

            tree->bal--; // diminui o balanceamento, já que o nó foi inserido a esquerda

        }
        else { // se o nó a esquerda não estiver vazio
            bal_temp = tree->left->bal; // guarda o balanceamento atual do nó em questão

            tree->left = insert_node_Tree(tree->left, node);
            // realiza a chamada da própia função, passando o nó a esquerda que ainda precisa ser comparada com o nó em questão

            if((bal_temp == 0) && (tree->left->bal != 0)){
                // se o balanceamento do nó esquerdo da arvore atual era 0 e passou a ser 1 ou -1, então continua a diminuir o balanceamento

                tree->bal--; // efetiva a diminuição

                if(tree->bal ==  -2 && tree->left->bal == -1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for -1
                    tree = simple_rotation(tree); // chama a função de rotação simples
                }
                else if(tree->bal ==  -2 && tree->left->bal == 1){ // se o balanço da árvore atual for -2 e o balanço do nó a esquerda for 1
                    tree = double_rotation(tree); // chama a função de rotação simples
                }
            }
        }
    }

    // verificando se o valor do nó a ser inserido é maior que o valor do nó em questão
    else if(node->data > tree->data){
        // verificando se o prŕoximo nó a direita da arvore atual está vazia
        if(tree->right == NULL) {
            tree->right = node; // insere o nó a direita da árvore, já que o nó está vazio

            tree->bal++;// aumenta o balanceamento, já que o nó foi inserido a direita
        }
        else { // se o nó a esquerda não estiver vazio
            bal_temp = tree->right->bal; // guarda o balanceamento atual do nó em questão

            tree->right = insert_node_Tree(tree->right, node);
            // realiza a chamada da própia função, passando o nó a direita que ainda precisa ser comparada com o nó em questão

            if((bal_temp == 0) && (tree->right->bal != 0)){
                // se o balanceamento do nó direito da arvore atual era 0 e passou a ser 1 ou -1, então continua a aumentar o balanceamento

                tree->bal++; // efetiva o aumento

                if(tree->bal ==  2 && tree->right->bal == 1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for 1
                    tree = simple_rotation(tree); // chama a função de rotação simples
                }
                else if(tree->bal ==  2 && tree->right->bal == -1){ // se o balanço da árvore atual for 2 e o balanço do nó a direita for -1
                    tree = double_rotation(tree); // chama a função de rotação dupla
                }
            }
        }
    }
    return tree; // finaliza a chamada atual da função
}

// Função que insere um nó
Tree* insert_node(Tree* t, int value){
    if(t == NULL) {
        t = create_node(value); // cria uma nó com sub-arvores nulas
        return t; // retorno a arvore com um unico nó
    };

    t = insert_node_Tree(
        t, create_node(value)
    ); //

    return t;
}

// Função que libéra dámemória uma estrutura de Arvore binária na forma Pre-Ordem
void delPosOrder(Tree* t){
    if(t!=NULL){
        delPosOrder(t->left);
        delPosOrder(t->right);
        free(t);
    }
}

// 50, 30, 70, 20, 60, 80, 15, 10, 5
int main(){
    Tree* t = init();
    int value;

    while(true){
        cin >> value;

        // Se for -1 finaliza a execução
        if(value == -1) break;

        // Se for 0 finaliza a árvore
        if(value == 0) {
            cout << "Bal = " << t->bal << endl;
            delPosOrder(t);
        }
        else{
            t = insert_node(t, value);
        }

    }

    cout << "fim" << endl;


    return 0;
}
