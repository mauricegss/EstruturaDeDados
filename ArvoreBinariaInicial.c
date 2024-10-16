#include <stdio.h>
#include <stdlib.h>

typedef struct TNo{
    int chave;
    //campos
    struct TNo *dir;
    struct TNo *esq;
}TNoABP;

TNoABP *criarNo(int chave);
TNoABP *insereNoRec(TNoABP *raiz, int chave);
TNoABP *buscarNo(TNoABP *raiz, int chave);
//rotinas de travessia
void emOrdem(TNoABP *raiz);
void preOrdem(raiz);
void posOrdem(raiz);

int main()
{
    TNoABP *raiz=NULL, *achou=NULL;
    int op=1, chave;
    while(op!=5)
    {
        printf("\n1-Inserir 2-Buscar 3-Travessia:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:{
                printf("\nInforme chave:");
                scanf("%d",&chave);
                raiz = insereNoRec(raiz, chave);
            }break;
            case 2:{
                printf("\nInforme chave:");
                scanf("%d",&chave);
                achou = buscarNo(raiz, chave);
                if(achou)
                    printf("Achei %d %p", achou->chave, achou);
                else
                    printf("\nElemento nao encontrado!");
            }break;
            case 3:{
                printf("\nImprimindo em Ordem:\n");
                emOrdem(raiz);
                printf("\nImprimindo em Pre-Ordem:\n");
                preOrdem(raiz);
                printf("\nImprimindo em Pos-Ordem:\n");
                posOrdem(raiz);
            }

        }
    }
}
//criando 1 n� na mem�ria - n�o est� ligado na �rvore
TNoABP *criarNo(int chave)
{
    TNoABP *novo=malloc(sizeof(TNoABP));
    if(novo)
    {
        novo->chave=chave;
        novo->dir=NULL;
        novo->esq=NULL;
        return novo;
    }
    return NULL;
}

TNoABP *insereNoRec(TNoABP *raiz, int chave)
{
    //caso base - �rvore vazia mas tamb�m para a sub-arvore vazia
    if(raiz==NULL)
        return criarNo(chave);
    else
        if(chave < raiz->chave)
            raiz->esq = insereNoRec(raiz->esq, chave);
        else
            raiz->dir = insereNoRec(raiz->dir, chave);
   // return raiz;
}

void emOrdem(TNoABP *raiz){
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        emOrdem(raiz->dir);
    }
}

void preOrdem(TNoABP *raiz){
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void posOrdem(TNoABP *raiz){
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

TNoABP *buscarNo(TNoABP *raiz, int chave)
{
    if(raiz==NULL)
        printf("\nArvore vazia!");
    while(raiz) //while(raiz!=NULL)
    {
        if(raiz->chave==chave)
            return raiz;
        if(chave < raiz->chave)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return NULL;
}
