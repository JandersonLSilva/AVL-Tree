#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int value;
  struct TreeNode *rNode;
  struct TreeNode *lNode;
  int b;
}TreeNode;

int main(){
  int opt;
  TreeNode *tree;

  printf("Algoritimo gerenciador de arvores binarias\n");
  printf("Aproveite\n\n");

  while(true){
    printf("Valor: ");
    scanf("%d", &opt);

    if(opt == 0){
      printf("Bal = XX\n");
      printf("Resetando arvore");
    }else if(opt == -1){
      break;
    }else{
      printf("else");
    }
  }

  printf("FIM");
  return 0;
}
