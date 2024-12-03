#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Arv{
    char info;
    struct Arv *irmao;
    struct Arv *filho;
}Arv;

typedef struct Lista{
    int camada;
    int tam;
    struct NoLista *prim;
}Lista;

typedef struct NoLista{
    char info;
    struct NoLista *prox;
}NoLista;

Lista* initLista();
void pushLista(Lista *l, char v);
void verLista(Lista *l);
int vaziaLista(Lista *l);
void matarLista(Lista *l);

Arv* create (char c);
void insert (Arv* a, Arv* filho);
void del (Arv* a);
void showArvCont(Arv *a);
void showArv(Arv *a, int broke);
void showArvore(Arv *a);
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
Arv *getCamadaArvore(Arv *a, int countCamada, int camada);

//Exerc cio 1:
//int folhas (Arv* a);

//Exerc cio 2:
//int ocorrencias (Arv* a, char x);

//Exerc cio 3:
//int igual (Arv* a, Arv* b);

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

    /*Lista *l = initLista();
    pushLista(l, 'a');
    pushLista(l, 'b');
    pushLista(l, 'c');
    verLista(l);


    printf("Comprimento A - %d\n", getComp(a));
    printf("Comprimento B - %d\n", getComp(b));
    printf("Comprimento C - %d\n", getComp(c));
    printf("\n");

    /*printf("Exercicio 1: \n");
    printf("Folhas A - %d\n", folhas(a));
    printf("Folhas B - %d\n", folhas(b));
    printf("Folhas C - %d\n", folhas(c));
    printf("\n");

    printf("Exercicio 2: \n");
    printf("Ocorrencias de a em A - %d\n", ocorrencias(a, 'a'));
    printf("Ocorrencias de a em B - %d\n", ocorrencias(b, 'a'));
    printf("Ocorrencias de a em C - %d\n", ocorrencias(c, 'a'));
    printf("\n");

    printf("Exercicio 3: [0: Diferente | 1: Igual]\n");
    printf("A == B - %d\n", igual(a, b));
    printf("A == C - %d\n", igual(a, c));
    printf("A == D - %d\n", igual(a, d));
    printf("A == A - %d\n", igual(a, a));*/
    printf("\n");

    del(a);
    del(c);

    return 1;
}

Lista* initLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));

    l->camada = 0;
    l->tam = 0;
    l->prim = NULL;

    return l;
}

void pushLista(Lista *l, char v){
    NoLista *no = (NoLista*)malloc(sizeof(NoLista));
    no->info = v;
    no->prox = NULL;

    l->tam++;

    if(l->prim == NULL){
        l->prim = no;
        return;
    }

    NoLista *aux = l->prim;
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    aux->prox = no;
}

void verLista(Lista *l){
    if(vaziaLista(l)){
        printf("Lista vazia!!\n\n");
        return;
    }

    printf("Camada: %d | Tamanho: %d\n", l->camada, l->tam);

    NoLista *aux = l->prim;
    while(aux != NULL){
        printf("%c - ", aux->info);
        aux = aux->prox;
    }

    printf("\n\n");
}

int vaziaLista(Lista *l){
    return l == NULL;
}

void matarLista(Lista *l){
    NoLista *aux = l->prim;

    while(aux != NULL){
        NoLista *ant = aux;
        aux = aux->prox;
        free(ant);
    }

    free(l);
}

Arv *create(char v){
    Arv *arv;

    arv = (Arv*)malloc(sizeof(Arv));
    arv->info = v;
    arv->irmao = NULL;
    arv->filho = NULL;

    return arv;
}

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
}

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
}

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
}

int countEsqOutside(Arv *a){
    Arv *aux = a;
    int count = 0;

    count += countFilhos(aux)/2;

    if(aux->filho != NULL) count += countDirOutside(aux->filho);

    return count;
}

int countOutsideFolhas(Arv *a){
    Arv *aux = a->filho;
    int count = 0;

    while(aux->irmao != NULL){
        aux = aux->irmao;
    }

    count += countDirOutside(aux);
    count += countEsqOutside(a->filho);

    return count;
}

void showChar(char c, int num){
    for(int i = 0; i < num; i++){
        printf("%c", c);
    }
}

Arv* padronizaArvore(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        return a;
    }

    if(a->irmao != NULL) padronizaArvore(a->irmao, countCamada, camada);

    if(a->filho == NULL) a->filho = create('*');
    padronizaArvore(a->filho, countCamada+1, camada);

    return a;
}

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
}

void showPreCamada(Arv *a, int countCamada, int camada){
    if(countCamada == camada){
        int spaces = a->filho != NULL ? countFolhas(a->filho)-1 : 0;

        /*int folhas = countFolhas(a->filho);
        int outsideFolhas = countOutsideFolhas(a);
        int insideFolhas = folhas - outsideFolhas;*/

        showChar(' ', spaces);
        printf("| ");
        showChar(' ', spaces);

        if(a->irmao) showPreCamada(a->irmao, countCamada, camada);
    }

    if(countCamada < camada){
        if(a->filho) showPreCamada(a->filho, countCamada+1, camada);
        if(a->irmao) showPreCamada(a->irmao, countCamada, camada);
    }
}

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
}

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
}

void showArv(Arv *a, int broke){
    Arv *auxA = a;

    while(auxA != NULL){
        int spaces = auxA->filho != NULL ? countFolhas(auxA->filho)-2 : 1;
        showChar(' ', spaces);
        printf("%c", auxA->info);
        auxA = auxA->irmao;
    }

    if(broke) printf("\n");

    auxA = a;
    while(auxA != NULL){

        if(auxA->filho != NULL) {
            int hasBroke = 1;
            if(auxA->irmao != NULL) hasBroke = auxA->irmao->filho == NULL;

            showArv(auxA->filho, hasBroke);
        }

        /*else {
            showChar(' ', 1);
            printf("*");
        }*/

        auxA = auxA->irmao;
    }

}

/*void showArv(Arv *a){
    Arv *arvShow = create('#');

    int comprimento = getComp(a);
    for(int i = 1; i <= comprimento; i++){
        Arv *v = getCamadaArvore(a, 0, (comprimento-i));
        Arv *cam = create('+');
        insert(cam, v);
        insert(arvShow, cam);

        //printf("Arvore camada %d\n", comprimento-i);
        //showArvore(v);
        //printf("\n\n");
    }

    printf("Arvore show\n");
    showArvore(arvShow);
    printf("\n\n");

    Arv *auxArv = arvShow->filho;

    for(int i = 0; i < 6; i++){
        Arv *auxShow = auxArv->filho;

        printf("Camada %d: ", i);
        while(auxShow != NULL){
            Arv *auxShow2 = auxShow->filho;

            while(auxShow2 != NULL){
                printf("%c ", auxShow2->info);
                auxShow2 = auxShow2->irmao;
            }

            auxShow = auxShow->irmao;
        }
        printf("\n");

        auxArv = auxArv->irmao;
    }

    auxArv = arvShow->filho;
    Arv *auxA = a;

    for(int i = 0; i < 6; i++){
        int folhas = countFolhas(auxA);
        Arv *auxShow = auxArv->filho;

        while(auxShow != NULL){
            Arv *auxShow2 = auxShow->filho;
            while(auxShow2 != NULL){
                showChar(' ', folhas-1);
                printf("%c ", auxShow2->info);


                auxShow2 = auxShow2->irmao;
            }

            auxShow = auxShow->irmao;
        }
        printf("\n");
        /*showChar(' ', folhas-1);
        printf("|\n");
        showChar('_', (folhas*2)-1);
        printf("\n");*/

        /*auxArv = auxArv->irmao;
    }
}*/

Arv *getCamadaArvore(Arv *a, int countCamada, int camada){
    Arv *cam = create('-');

    if(countCamada == camada){
        Arv *aux = a;

        while(aux != NULL){
            if(cam->filho == NULL) cam->filho = create(aux->info);
            else{
                Arv *auxCam = cam->filho;
                while(auxCam->irmao != NULL){
                    auxCam = auxCam->irmao;
                }
                auxCam->irmao = create(aux->info);
            }

            aux = aux->irmao;
        }
    }
    if(countCamada < camada){
        if(a->filho != NULL) cam = getCamadaArvore(a->filho, countCamada+1, camada);
        else insert(cam, create('*'));

        if(a->irmao != NULL) {
            Arv *auxC = cam;

            while(auxC->irmao != NULL){
                auxC = auxC->irmao;
            }

            auxC->irmao = getCamadaArvore(a->irmao, countCamada, camada);
        };
    }

    return cam;
}

void showArvore(Arv *a){
    printf("%c ", a->info);

    if(a->filho != NULL)showArvore(a->filho);
    if(a->irmao != NULL)showArvore(a->irmao);
}

int getComp(Arv *a){
    int comp = countNo(a, 1);
    return comp;
}

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
}
/*
//Exerc cio 1:
int folhas (Arv* a){
    int count = 0;

    if(empty(a)) return count;

    count++;
    count += folhas(a->dir);
    count += folhas(a->esq);

    return count;
}

//Exerc cio 2:
int ocorrencias (Arv* a, char x){
    int count = 0;

    if(empty(a)) return count;

    if(a->info == x) count++;

    count += ocorrencias(a->dir, x);
    count += ocorrencias(a->esq, x);

    return count;
}

//Exerc cio 3:
int igual (Arv* a, Arv* b){
    if(empty(a) && empty(b)) return 1;
    if(empty(a) || empty(b)) return 0;

    if(a->info != b->info) return 0;

    if(!igual(a->dir, b->dir)) return 0;
    if(!igual(a->esq, b->esq)) return 0;

    return 1;
}*/


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
















