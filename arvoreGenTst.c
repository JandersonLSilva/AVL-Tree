#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Arv{
    char info;
    struct Arv *irmao;
    struct Arv *filho;
}Arv;

Arv* create (char c);
void insert (Arv* a, Arv* filho);
void del (Arv* a);
void showArvCont(Arv *a);
void showCamada(Arv *a, int countCamada, int camada);
void showPreCamada(Arv *a, int countCamada, int camada);
void showPosCamada(Arv *a, int countCamada, int camada);
void showChar(char c, int num);
int countFolhas(Arv *a);
int countOutsideFolhas(Arv *a);
int countDirOutside(Arv *a);
int countEsqOutside(Arv *a);
Arv* padronizaArvore(Arv *a, int countCamada, int camada);
int getComp(Arv *a);
int countNo(Arv *a, int count);
void camadaInsert(Arv *ins, Arv *val);

int main(){
    Arv *a = create('a'), *b = create('b'), *c = create('c'), *d = create('d'), *e = create('e'), *f = create('f'), *g = create('g');

    insert(f, create('1'));
    insert(f, create('2'));
    insert(f, create('3'));
    insert(f, create('4'));
    //insert(f, create('5'));

    insert(e, create('w'));
    insert(e, f);

    insert(d, create('y'));
    insert(d, create('p'));
    insert(d, e);

    insert(c, create('j'));
    insert(c, create('k'));
    insert(c, create('l'));

    insert(b, d);

    insert(g, create('6'));
    insert(g, create('7'));
    insert(g, c);
    insert(g, create('8'));

    insert(a, b);
    insert(a, create('t'));
    insert(a, g);
    insert(a, create('h'));
    //insert(a, c);

    printf("Arvore A: \n");
    showArvCont(a);
    printf("\n\n");

    printf("Arvore B: \n");
    showArvCont(b);
    printf("\n\n");

    printf("Arvore C: \n");
    showArvCont(c);
    printf("\n\n");

    printf("Arvore D: \n");
    showArvCont(d);
    printf("\n\n");

    del(a);
    del(c);

    scanf("%d");

    return 1;
}

Arv *create(char v){
    Arv *arv;

    arv = (Arv*)malloc(sizeof(Arv));
    arv->info = v;
    arv->irmao = NULL;
    arv->filho = NULL;

    return arv;
} //###

void del (Arv* a){
    if(a->irmao != NULL) del(a->irmao);
    if(a->filho != NULL) del(a->filho);

    free(a);
}

void insert (Arv* a, Arv* filho){
    Arv *auxF = filho;

    while(auxF->irmao != NULL){
        auxF = auxF->irmao;
    }

    auxF->irmao = a->filho;
    a->filho = filho;
}

int countFolhas(Arv *a){
    int count = 0;

    if(a->filho != NULL) count += countFolhas(a->filho);
    else count++;

    if(a->irmao != NULL) count += countFolhas(a->irmao);

    return count;
} //###

int countFilhos(Arv *a){
    int count = 0;

    if(a != NULL){
        Arv *aux = a->filho;

        while(aux!=NULL){
            aux = aux->irmao;
            count++;
        }
    }

    return count;
} //###

int countDirOutside(Arv *a){
    Arv *aux = a;
    int count = 0;

    count += countFilhos(aux)/2;

    if(aux->filho != NULL){
        aux = aux->filho;

        while(aux->irmao != NULL){
            aux = aux->irmao;
        }

        count += countDirOutside(aux);
    }

    return count;
} //###

int countEsqOutside(Arv *a){
    Arv *aux = a;
    int count = 0;

    count += countFilhos(aux)/2;

    if(aux->filho != NULL) count += countDirOutside(aux->filho);

    return count;
} //###

int countOutsideFolhas(Arv *a){
    Arv *aux = a->filho;
    int count = 0;

    while(aux->irmao != NULL){
        aux = aux->irmao;
    }

    count += countDirOutside(aux);
    count += countEsqOutside(a->filho);

    return count;
} //###

void showChar(char c, int num){
    for(int i = 0; i < num; i++){
        printf("%c", c);
    }
} //###

Arv* padronizaArvore(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        return a;
    }

    if(a->irmao != NULL) padronizaArvore(a->irmao, countCamada, camada);

    if(a->filho == NULL) a->filho = create('*');
    padronizaArvore(a->filho, countCamada+1, camada);

    return a;
} //###

void showArvCont(Arv *a){
    Arv *b = a;
    int comprimento = getComp(b);

    countOutsideFolhas(a);

    b = padronizaArvore(b, 1, comprimento);

    for(int i = 1; i <= comprimento; i++){
        if(i > 1){
            showPreCamada(a, 1, i);
            printf("\n");
        }
        showCamada(a, 1, i);
        printf("\n");
        if(i < comprimento){
            showPosCamada(a, 1, i);
            printf("\n");
        }
    }
} //###

void showPreCamada(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        int spaces = a->filho != NULL ? countFolhas(a->filho)-1 : 0;

        showChar(' ', spaces);
        printf("| ");
        showChar(' ', spaces);

        if(a->irmao) showPreCamada(a->irmao, countCamada, camada);
    }

    if(countCamada < camada){
        if(a->filho) showPreCamada(a->filho, countCamada+1, camada);
        if(a->irmao) showPreCamada(a->irmao, countCamada, camada);
    }
} //###

void showCamada(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        int spaces = a->filho != NULL ? countFolhas(a->filho)-1 : 0;
        showChar(' ', spaces);
        printf("%c ", a->info);
        showChar(' ', spaces);

        if(a->irmao != NULL) showCamada(a->irmao, countCamada, camada);
    }

    if(countCamada < camada){
        if(a->filho) showCamada(a->filho, countCamada+1, camada);
        if(a->irmao) showCamada(a->irmao, countCamada, camada);
    }
} //###

void showPosCamada(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        if(a->filho !=NULL){
            int filhosQuantidade = countFilhos(a);

            int folhas = countFolhas(a->filho);
            int outsideFolhas = countOutsideFolhas(a);
            int insideFolhas = folhas - outsideFolhas;
            int bars = filhosQuantidade == 1 ? 0 : insideFolhas-1;
            int lastBars = bars + (bars > 0 ? folhas - filhosQuantidade : 0);
            int filhoSpace = a->filho->filho != NULL ? countFolhas(a->filho->filho)-1 : 0;

            Arv *auxX = a->filho;
            while(auxX->irmao != NULL){
                auxX = auxX->irmao;
            }
            int lastSpace = auxX->filho != NULL ? countFolhas(auxX->filho)-1 : 0;

            showChar(' ', filhoSpace);
            showChar('_', bars);
            printf("|");
            showChar('_', bars);
            showChar(' ', lastSpace);

            printf(" ");
        }

        if(a->irmao) showPosCamada(a->irmao, countCamada, camada);
    }

    if(countCamada < camada){
        if(a->filho) showPosCamada(a->filho, countCamada+1, camada);
        if(a->irmao) showPosCamada(a->irmao, countCamada, camada);
    }
} //###

int getComp(Arv *a){
    int comp = countNo(a, 1);
    return comp;
} //###

int countNo(Arv *a, int count){
    int filho = 0, irmao = 0, maior;

    if(a->filho != NULL){
        filho = countNo(a->filho, 1);
    }
    if(a->irmao != NULL){
        irmao = countNo(a->irmao, 0);
    }
    if(filho > irmao){
        maior = filho;
    }
    else{
        maior = irmao;
    }
    count += maior;
    return count;
} //###


/*







             ______|____________
             |         |       |
             a         x       h
         ____|____  ___|___              (N_filhos X 2) - 1
         | | | | |  | | | |
         b c d e q  w j k l


                  a
            ______|______
            |           |
            c           b
          __|__         |
          | | |         |
          l k j         d
          | | |     ____|____
          | | |     |     | |
          * * *     e     p y
          | | |     |     | |
          | | |     |     | |
          * * *     f     * *
          | | | ____|____ | |
          | | | | | | | | | |
          * * * 5 4 3 2 1 * *



*/
