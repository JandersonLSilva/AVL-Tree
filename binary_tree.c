#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int value;
  struct TreeNode *rNode;
  struct TreeNode *lNode;
  int b;
}TreeNode;

TreeNode* createNode(int value);
TreeNode* freeNode(TreeNode *tree);
TreeNode* insertValue(TreeNode *tree, int value);

int main(){
  int opt;
  TreeNode *tree;

  printf("Algoritimo gerenciador de arvores binarias\n");
  printf("Aproveite\n\n");

  while(true){
    printf("Valor: ");
    scanf("%d", &opt);

    if(opt == 0){
      if(tree == NULL) printf("A arvore ja esta vazia\n");
      else{
        printf("Bal = %d\n", tree->b);
        printf("Resetando arvore\n");
        tree = freeNode(tree);
      }
    }else if(opt == -1){
      break;
    }else{
      tree = insertValue(tree, opt);
    }
  }

  printf("FIM");
  return 0;
}

TreeNode* createNode(int value){
  TreeNode *tree = (TreeNode*)malloc(sizeof(TreeNode));
  tree->value = value;
  tree->rNode = NULL;
  tree->lNode = NULL;
  tree->b = 0;

  return tree;
}

TreeNode* freeNode(TreeNode *tree){
  printf("Limpando %d - ", tree->value);
  if(tree->rNode != NULL) freeNode(tree->rNode);
  if(tree->lNode != NULL) freeNode(tree->lNode);
  printf("\n");
  free(tree);
  return NULL;
}

TreeNode* insertValue(TreeNode *tree, int value){
  if(tree == NULL){
    tree = createNode(value);
  }else{
      if(value > tree->value){
        tree->rNode = insertValue(tree->rNode, value);
        //colocar rotações - balanceamento
        tree->b++;
      }else if(value < tree->value){
        tree->lNode = insertValue(tree->lNode, value);
        tree->b--;
      }
  }
  printf("Bal - %d = %d\n", tree->value, tree->b);
  return tree;
}
