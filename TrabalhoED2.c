//Feito por: Gabriel Castello Branco Ayres Nalesso e Maurice Golin Soares dos Santos

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contato {
    
    char nome[20];
    char numero[12];
    char email[20];
    struct contato *dir;
    struct contato *esq;
    
} Tcontato;

Tcontato *criarNo(char nome[],char numero[],char email[]);
Tcontato *insereNo(Tcontato *raiz, char nome[],char numero[],char email[]);
void imprimir(Tcontato *raiz);
Tcontato *buscar(Tcontato *raiz, char nome[]);
void alterar(Tcontato *raiz, char nome[], char numero[], char email[]);
void remover(Tcontato **raiz, char nome[]);
Tcontato **busca2(Tcontato **raiz, char nome[]);
Tcontato **buscaMenor(Tcontato **raiz);
void encerrar(Tcontato **raiz); // LIBERA TODOS AS ALOCACOES DINAMICAS

int main(){
    
    int op;
    char nome[20], numero[12], email[20];
    Tcontato *raiz = NULL;
    do{
        printf("0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - Alterar\n5 - Remover\n");
        scanf("%d",&op);
        switch(op){
            case 0:
                encerrar(&raiz); // Llibera alocacoes, e como "op == 0" não executa o "do while"
                break;
            case 1:
                printf("Insira o Nome: ");
                scanf("%s",nome);
                printf("Insira o Numero: ");
                scanf("%s",numero);
                printf("Insira o Email: ");
                scanf("%s",email);
                raiz = insereNo(raiz, nome, numero, email);
                break;
            case 2:
                imprimir(raiz);
                break;   
            case 3:
                printf("Insira o Nome: ");
                scanf("%s",nome);
                if(buscar(raiz, nome)){
                    printf("Encontrado!\n");
                } else {
                    printf("Não Encontrado!\n");
                }
                break;
            case 4:
                printf("Insira o seu Nome: ");
                scanf("%s",nome);
                printf("Insira o novo Numero:");
                scanf("%s",numero);
                printf("Insira o novo Email: ");
                scanf("%s",email);
                alterar(raiz, nome, numero, email);
                break;
            case 5:
                printf("Insira o Nome: ");
                scanf("%s",nome);
                remover(&raiz, nome);
                break;
        }
    } while(op!=0);
    
    return 0;
    
}

Tcontato *criarNo(char nome[],char numero[],char email[]){

    Tcontato *novo=malloc(sizeof(Tcontato)); // Aloca dinamicamente para um novo contato
    if(novo)
    {
        strcpy(novo->nome, nome); // Afilia o nome
        strcpy(novo->numero, numero); // Afilia o numero
        strcpy(novo->email, email); // Afilia o email
        // Não tem raízes por enquanto
        novo->dir=NULL; 
        novo->esq=NULL;
        return novo;
    }
    return NULL;
}

Tcontato *insereNo(Tcontato *raiz, char nome[],char numero[],char email[]){
    
    if(raiz==NULL){
        return criarNo(nome, numero, email); // Se acabou as raízes, parte para a alocacao
    } else {
        if (strcmp(nome,raiz->nome)==0){ // Se nome já existente, não pode alocar
            printf("Contato já inserido.\n");
            return NULL;
        } else if(strcmp(nome,raiz->nome)>0){ // Se palavra maior em ordem alfabética, raiz direita
            raiz->dir = insereNo(raiz->dir, nome, numero, email);
        } else { // Se não, chama para a raiz esquerda
            raiz->esq = insereNo(raiz->esq, nome, numero, email);
        }
        return raiz;
    }
}

void imprimir(Tcontato *raiz){ // Impressão em ordem, ou seja, em ordem alfabetica
    if (raiz != NULL) {
        imprimir(raiz->esq);
        printf("-----------------------------\n");
        printf("Nome: %s \n", raiz->nome);
        printf("Numero: %s \n", raiz->numero);
        printf("Email: %s \n", raiz->email);      
        imprimir(raiz->dir);
    }
}

Tcontato *buscar(Tcontato *raiz, char nome[]){

    if (raiz == NULL){ // Se não encontrado, retorna NULl
        return NULL;
    }
    if(strcmp(nome, raiz->nome)==0) { // Se encontrado, retorna endereço
        return raiz;
    }
    if(strcmp(nome,raiz->nome)>0){ // Se nome maior que o nome atual, chama para a raiz direita
        return buscar(raiz->dir, nome);
    } else{ // Se não, raiz esquerda
    return buscar(raiz->esq, nome);
    }
}

void alterar(Tcontato *raiz, char nome[], char numero[], char email[]){

    Tcontato *achei = buscar(raiz, nome); // Encontra e Guarda o endereço do contato
    if(achei){ // Se encontrado
        strcpy(achei->email,email); // Altera email
        strcpy(achei->numero,numero); // Altera numero
        printf("Alterado!\n");
    } else {
        printf("Contato nao Encontrado, Nao Alterado!\n");
    }
    

}

Tcontato **busca2(Tcontato **raiz, char nome[])
{
    //mesma lógica da busca só que para encontrar o pai
  if (*raiz == NULL)
    return NULL;
  while(*raiz!=NULL)
  {
      if(strcmp(nome, (*raiz)->nome)==0)
        return raiz;
      if(strcmp(nome, (*raiz)->nome) > 0)
        raiz = &((*raiz)->dir);
      else
        raiz = &((*raiz)->esq);
  }
  return raiz;
}

void remover(Tcontato **raiz, char nome[])
{
    Tcontato **pp = busca2(raiz, nome); //encontra o "pai" do nodo a ser removido
    if(((*pp)->dir==NULL) && (*pp)->esq==NULL)
    {
        //se não houver filhos 
        free(*pp);
        *pp=NULL;
        return;
    }
    Tcontato *filho=NULL;
    if(((*pp)->dir == NULL) != ((*pp)->esq==NULL))
    {
        //quando tem apenas 1 filho
        filho = (*pp)->esq==NULL?(*pp)->dir:(*pp)->esq;
        free(*pp);
        *pp = filho; //guarda o filho para ser devolvido a árvore
    }
    if(((*pp)->esq) && ((*pp)->dir))
    {
        //2 filhos
        Tcontato **pps=buscaMenor(&(*pp)->dir); //encontra o sucessor
        strcpy((*pp)->nome, (*pps)->nome);
        strcpy((*pp)->numero, (*pps)->numero);
        strcpy((*pp)->email, (*pps)->email);
        remover(pps, (*pps)->nome);
    }
}

Tcontato **buscaMenor(Tcontato **raiz)
{
    //mesma lógica da busca só que por ponteiro de ponteiro
    Tcontato **menor=raiz;
    while((*menor)->esq)
    {
        menor = &(*menor)->esq;
    }
    return menor;
}

void encerrar(Tcontato **raiz){
    
    // Mesma lógica da impressão porém em "pós-ordem", só que para liberar
    if (raiz != NULL) {
        encerrar((*raiz)->esq);
        encerrar((*raiz)->dir);
        free(*raiz);
        *raiz=NULL;
    }   
}