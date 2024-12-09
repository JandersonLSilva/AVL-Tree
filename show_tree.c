#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
  int value;
  struct TreeNode *rNode;
  struct TreeNode *lNode;
  int b;
}TreeNode;

TreeNode* createNode(int value);
TreeNode* freeNode(TreeNode *tree);
TreeNode* insertValue(TreeNode *tree, int value);

void showTree(TreeNode *tree);
void showLayer(TreeNode *tree, int countLayer, int layer, char nodeType);
void showAfterLayer(TreeNode *tree, int countLayer, int layer, char nodeType);

TreeNode* fillTree(TreeNode *tree);

int getLength(TreeNode *a);
int countNode(TreeNode *a, int count);
void showChar(char c, int number);
int getSpacesByLength(int length);

int main(){
  TreeNode *a = createNode(10);
  a = insertValue(a, 5);
  a = insertValue(a, 2);
  a = insertValue(a, 1);
  a = insertValue(a, 3);
  a = insertValue(a, 7);
  a = insertValue(a, 6);
  a = insertValue(a, 8);
  a = insertValue(a, 15);
  a = insertValue(a, 18);
  a = insertValue(a, 17);
  a = insertValue(a, 19);
  a = insertValue(a, 12);
  a = insertValue(a, 11);
  a = insertValue(a, 13);

  showTree(a);

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
  return tree;
}

void showTree(TreeNode *tree){
  TreeNode *b = tree;
  int length = getLength(b);

  // countOutsideFolhas(a);
  //
  // b = padronizaArvore(b, 1, comprimento);
  //
  for(int i = 1; i <= length; i++){
      // if(i > 1){
      //     showPreCamada(a, 1, i);
      //     printf("\n");
      // }
      showLayer(tree, 1, i, 'r');
      printf("\n");
      if(i < length){
          showAfterLayer(tree, 1, i, 'r');
          printf("\n");
      }
  }
}

void showLayer(TreeNode *tree, int countLayer, int layer, char nodeType){
  if(countLayer == layer){
      int length = getLength(tree);
      int spaces = getSpacesByLength(length - 1);
      int rightSpaces = nodeType == 'r' ? spaces + 1 : spaces;
      showChar(' ', spaces);
      printf("%d", tree->value);
      showChar(' ', rightSpaces);
  }

  if(countLayer < layer){
      if(tree->lNode) showLayer(tree->lNode, countLayer + 1, layer, 'l');
      if(tree->rNode) showLayer(tree->rNode, countLayer + 1, layer, 'r');
  }
}

void showAfterLayer(TreeNode *tree, int countLayer, int layer, char nodeType){
    if(countLayer == layer){
          int length = getLength(tree);
          int leftSpace = pow(2, length-1);
          int bars = getSpacesByLength(length - 2);

          showChar(' ', leftSpace);
          showChar('_', bars);
          printf("|");
          showChar('_', bars);
          showChar(' ', leftSpace);

          if(nodeType == 'r'){
            printf(" ");
          }
    }

    if(countLayer < layer){
        if(tree->lNode) showAfterLayer(tree->lNode, countLayer+1, layer, 'l');
        if(tree->rNode) showAfterLayer(tree->rNode, countLayer+1, layer, 'r');
    }
}

int getLength(TreeNode *a){
    int length = countNode(a, 1);
    return length;
}

int countNode(TreeNode *a, int count){
    int right = 0, left = 0, bigger;

    if(a->rNode != NULL){
        right = countNode(a->rNode, 1);
    }
    if(a->lNode != NULL){
        left = countNode(a->lNode, 1);
    }
    if(right > left){
        bigger = right;
    }
    else{
        bigger = left;
    }
    count += bigger;
    return count;
}

void showChar(char c, int number){
    for(int i = 0; i < number; i++){
        printf("%c", c);
    }
}

int getSpacesByLength(int length){
  int spaces = 1;
  for(int i = 0; i < length; i ++){
    spaces = spaces*2 + 1;
  }

  return spaces;
}

/*
3 - 15
2 - 7
1 - 3
0 - 1

1 - 2 / 1 / 4
2 - 4 / 3 / 7
3 - 8 / 7 /


                5
             ___|___
            |      |
            3      8
           _|_    _|_
          |  |   |  |
          2  4   7  9


                       9
                _______|______
               |             |
               7             8
            ___|___       ___|___
           |      |      |      |
           3      8      3      8
          _|_    _|_    _|_    _|_
         |  |   |  |   |  |   |  |
         2  4   7  9   2  4   7  9





*/
