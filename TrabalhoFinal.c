#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Vetor{
    int codigo;
    char processo[30];
    int prioridade;
    char estado[30]; 
}Vetor;

typedef struct AVL {
    int codigo;
    char processo[30];
    int prioridade;
    char estado[30]; 
    int bal; // Indice de balanceamento
    struct AVL *esq; // Ponteiro para a subarvore esquerda
    struct AVL *dir; // Ponteiro para a subarvore direita
} AVL;

typedef struct MaxHeap{
    Vetor* vetor;
    int capacidade;
} MaxHeap;

// TUDO ISSO PARA AVL /////////////////////////////////////////////////////
int InserirAVL(AVL **p, int x, char processo[], int prioridade, char estado[]);
AVL *del(AVL **p);
int delete(AVL **p, int x);
int bal_esq(AVL **p);
int bal_dir(AVL **p);
AVL *busca_no(AVL **p, int x) ;
void em_ordem(AVL **p); 
int altura(AVL **p);
int rot_dir(AVL **p);
int rot_esq(AVL **p);
//////////////////////////////////////////////////////////////////////////

// TUDO ISSO PARA HEAP MAX ////////////////////////////////////////////////
void troca(Vetor *v1, Vetor *v2); // OK
void heapify(MaxHeap* heap, int i); // OK
MaxHeap* criarMaxHeap(int capacidade); // OK
void InserirHeap(MaxHeap* heap, int codigo, char processo[], int prioridade, char estado[]); // OK
int remover(MaxHeap* heap); // OK
void imprimirHeap(MaxHeap* heap); // OK
void destruirHeap(MaxHeap* heap); // OK
//////////////////////////////////////////////////////////////////////////

// TUDO ISSO PARA HASH //////////////////////////////////////////////////
void inicializa(Vetor vh[], int tam); // OK
void imprimeL(Vetor vh[],int* tam, char estado[]); // OK
void imprimeQ(Vetor vh[],int* tam, char estado[]); // OK
void cheio(Vetor vh[], int* tam); // NOVO
int InsereLinear(Vetor vh[], int chave, char processo[], int prioridade, char estado[], int* colisaoL, int* tam); // OK
int InsereQuad(Vetor vh[], int chave, char processo[], int prioridade, char estado[], int* colisaoQ, int* tam); // OK
int remocaoL(Vetor vh[], int chave, int *tam);
int remocaoQ(Vetor vh[], int chave, int *tam);
/////////////////////////////////////////////////////////////////////////

// A FAZER /////////////////////////////////////////////////////////////
void alterarHeap(MaxHeap* heap, int codigo, int np);
void desbloquear(Vetor vh[], int* tam, int chave);
void bloquear(Vetor vh[], int* tam, int chave);
void deleteTUDO(AVL **p);
void rhe(MaxHeap* heap, int chave);
///////////////////////////////////////////////////////////////////////
FILE *entrada, *sAVL, * shash, *sheap;

int main() {
    entrada = fopen("c:\\Users\\Gabriel\\Documents\\Programação\\ED2\\Trabalho2\\entrada.txt", "r");
    sAVL = fopen("c:\\Users\\Gabriel\\Documents\\Programação\\ED2\\Trabalho2\\AVL.txt", "w");
    shash = fopen("c:\\Users\\Gabriel\\Documents\\Programação\\ED2\\Trabalho2\\hash.txt", "w");
    sheap = fopen("c:\\Users\\Gabriel\\Documents\\Programação\\ED2\\Trabalho2\\heap.txt", "w");
    int colisaoL=0, colisaoQ=0, tam=10;
    int* CL = &colisaoL; 
    int* CQ = &colisaoQ; 
    int* TAM = &tam;
    Vetor HashLinear[tam], HashQuadratico[tam];
	
    AVL *raiz = NULL;
	MaxHeap* heap = criarMaxHeap(10);
    int val1, val2;
    char opcao[20], s1[20], s2[20];
	inicializa(HashLinear, tam);
    inicializa(HashQuadratico, tam);
    
    if(entrada != NULL){
        do{
            fscanf(entrada, "%s", opcao);
            if(strcmp(opcao, "InserirAVL") == 0){
                fscanf(entrada, "%d", &val1);
                fscanf(entrada, "%s", s1);
                fscanf(entrada, "%d", &val2);
                fscanf(entrada, "%s", s2);
                InserirAVL(&raiz, val1,s1,val2,s2);
                InserirHeap(heap,val1,s1,val2,s2);
                cheio(HashLinear, TAM);
                cheio(HashQuadratico, TAM);
                InsereLinear(HashLinear,val1,s1,val2,s2,CL,TAM);
                InsereQuad(HashQuadratico,val1,s1,val2,s2,CQ,TAM);
            }
            if(strcmp(opcao, "ListarAVL") == 0){
                em_ordem(&raiz);
            }
            if(strcmp(opcao, "TerminarAVL") == 0){
                fscanf(entrada, "%d", &val1);
                delete(&raiz,val1);
                fprintf(sAVL, "AVL deletada!\n");
            }
            if(strcmp(opcao, "AlterarHeap") == 0){
                fscanf(entrada, "%d", &val1);
                fscanf(entrada, "%d", &val2);
                alterarHeap(heap, val1, val2);
            }
            if(strcmp(opcao, "ListarHeap") == 0){
                imprimirHeap(heap);
            }
            if(strcmp(opcao, "RemoverHeap") == 0){
                remover(heap);
            }
            if(strcmp(opcao, "BloquearHash") == 0){
                fscanf(entrada, "%d", &val1);
                bloquear(HashLinear,TAM, val1);
                bloquear(HashQuadratico,TAM, val1);
            }
            if(strcmp(opcao, "ListarHash") == 0){
                fscanf(entrada, "%s", s1);
                imprimeL(HashLinear, TAM, s1);
                imprimeQ(HashQuadratico, TAM, s1);
            }
            if(strcmp(opcao, "DesbloquearHash") == 0){
                fscanf(entrada, "%d", &val1);
                desbloquear(HashLinear,TAM, val1);
                desbloquear(HashQuadratico,TAM, val1);
            }
            if(strcmp(opcao, "RemoverHash") == 0){
                fscanf(entrada, "%d", &val1);
                remocaoL(HashLinear, val1, TAM);
                remocaoQ(HashQuadratico, val1, TAM);
            }
            if(strcmp(opcao, "Terminar") == 0){
                fscanf(entrada, "%d", &val1);
                fscanf(entrada, "%s", s1);
                delete(&raiz,val1);
                remocaoL(HashLinear, val1, TAM);
                remocaoQ(HashQuadratico, val1, TAM);
                rhe(heap,val1);
            }
        }while(strcmp(opcao, "Encerrar") != 0);
        deleteTUDO(&raiz);
        destruirHeap(heap);
        fprintf(shash,"Total de Colisoes Lineares: %d\n", colisaoL);
        fprintf(shash,"Total de Colisoes Quadraticas: %d\n", colisaoQ);
    }
    fclose(entrada);
    fclose(sAVL);
    fclose(shash);
    fclose(sheap);
    return 0;
}

// AVL

int InserirAVL(AVL **p, int x, char processo[], int prioridade, char estado[]) {
    int cresceu;

    // O no raiz esta vazio
    if(*p == NULL) {
    	fprintf(sAVL, "Arvore vazia! Criando raiz...\n");
        *p = (AVL *) malloc(sizeof(AVL));
        (*p)->codigo = x;
        strcpy((*p)->processo, processo);
        (*p)->prioridade = prioridade;
        strcpy((*p)->estado, estado);
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;
		fprintf(sAVL, "Raiz criada!\n");
        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->codigo >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        // puts("Chamando insereAVL (esquerda) again");
        cresceu = InserirAVL(&(*p)->esq, x,processo, prioridade, estado);

        // Se cresceu for diferente de 0, logo a arvore cresceu
        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore direita era maior entao nao ha crescimento
                case 1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a subarvore direita tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = -1;
                    cresceu = 1;
                    break;
                // Se a subarvore da esquerda ja era maior entao deve-se re-balancear
                case -1:
                    if((*p)->esq->bal == -1) {
                        // Rotacao para a direita
                        rot_dir(p);
                        // Arruma os balanceamentos
                        (*p)->bal = (*p)->dir->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Rotaciona primeiro a esquerda
                        rot_esq(&(*p)->esq);
                        // Depois rotaciona a direita
                        rot_dir(p);
                        // Acerta balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    // Verifica se tem que inserir a direita
    else if((*p)->codigo < x) {
        // Tenta inserir a direita e ve se a sub-arvore cresceu
        cresceu = InserirAVL(&(*p)->dir, x,processo, prioridade,estado);

        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore esquerda era maior entao nao ha crescimento
                case -1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a arvore esquerda tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = 1;
                    cresceu = 1;
                    break;
                // Se a arvore da direita ja era maior entao deve-se re-balancear
                case 1:
                    // Verifica qual o caso de re-balanceamentos
                    if((*p)->dir->bal == 1) {
                        // Rotacao para a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        (*p)->bal = (*p)->esq->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Primeiro a direita
                        rot_dir(&(*p)->dir);
                        // Depois a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    else
        cresceu = 0;

    return cresceu;
}

AVL *del(AVL **p) {
    AVL *aux = (*p), *pai = (*p);

    if(aux->dir == NULL){
        *p = aux->esq;
        return aux;
    }

    while(aux->dir != NULL) {
        pai = aux;
        aux = aux->dir;
    }

    pai->dir = aux->esq;
    return aux;
}

int delete(AVL **p, int x) {
    AVL *q, *aux = NULL;
    int flag = 0;

    if((*p) == NULL) {
    	fprintf(sAVL, "Processo nao encontrado para remocao!\n");
        return 0;
    }
    else if((*p)->codigo > x) {
        flag = delete(&(*p)->esq, x);

        if(flag){
            bal_esq(&(*p));
        }
    }
    else if((*p)->codigo < x) {
        flag = delete(&(*p)->dir, x);

        if(flag){
            bal_dir(&(*p));
        }
    }
    else {
        q = (*p);

        if(q->dir == NULL) {
            (*p) = q->esq;
            return 1;
        }
        else if(q->esq == NULL) {
            (*p) = q->dir;
            free(q);
            return 1;
        }
        else {
            aux = del(&q->esq);
            (*p)->codigo = aux->codigo;
            strcpy((*p)->processo, aux->processo);
            (*p)->prioridade = aux->prioridade;
            strcpy((*p)->estado, aux->estado);
            (*p)->bal = aux->bal;
            free(aux);
            fprintf(sAVL, "Processo removido!\n");
        }
    }
}

int bal_esq(AVL **p) {
    AVL *p1, *p2;

    if((*p) == NULL) {
        return 0;
    }

    if((*p)->bal == -1) {
        (*p)->bal = 0;
        return 1;
    }
    else if((*p)->bal == 0) {
        (*p)->bal = 1;
        return 0;
    }
    else {
        p1 = (*p)->dir;

        if(p1->bal >= 0) {
            (*p)->dir = p1->esq;
            p1->esq = (*p);

            if(p1->bal == 0) {
                (*p)->bal = 1;
                p1->bal = -1;
            }
            else {
                (*p)->bal = 0;
                p1->bal = 0;
            }

			(*p) = p1;

			return 1;
        }
        else {
            p2 = p1->esq;
            p1->esq = p2->dir;
            p2->dir = p1;
            (*p)->dir = p2->esq;
            p2->esq = (*p);

            if(p2->bal == 1) {
                (*p)->bal = -1;
            }
            else {
                (*p)->bal = 0;
            }

            if(p2->bal == -1) {
                p1->bal = 1;
            }
            else {
                p1->bal = 0;
            }

            (*p) = p2;
            p2->bal = 0;

            return 1;
        }
    }
}

int bal_dir(AVL **p) {
    AVL *p1, *p2;
    int b2;

    if((*p) == NULL) {
        return 0;
    }

    if((*p)->bal == 1) {
        (*p)->bal = 0;
        return 1;
    }
    else if((*p)->bal == 0) {
        (*p)->bal = -1;
        return 0;
    }
    else {
        p1 = (*p)->esq;

        if(p1->bal <= 0) {
            (*p)->esq = p1->dir;
            p1->dir = (*p);

            if(p1->bal == 0) {
                (*p)->bal = -1;
                p1->bal = 1;
                (*p) = p1;
                return 0;
            }
            else {
                (*p)->bal = 0;
                p1->bal = 0;
                (*p) = p1;
                return 1;
            }
        }
        else {
            p2 = p1->dir;
            b2 = p2->bal;
            p1->dir = p2->esq;
            p2->esq = (*p);

            if(p2->bal == -1) {
                (*p)->bal = 1;
            }
            else {
                (*p)->bal = 0;
            }

            if(p2->bal == 1) {
                p1->bal = -1;
            }
            else {
                p1->bal = 0;
            }

            (*p) = p2;
            p2->bal = 0;

            return 1;
        }
    }
}

AVL *busca_no(AVL **p, int x) {
    if((*p) == NULL) {
        fprintf(sAVL, "A arvore esta vazia.");
        return NULL;
    }

    if((*p)->codigo == x) {
        return (*p);
    }
    else {
        if(x>(*p)->codigo) {
            return busca_no(&(*p)->dir, x);
        }
        else {
            return busca_no(&(*p)->esq, x);
        }
    }
}

int rot_dir(AVL **p) {
    AVL *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->esq;
    aux = q->dir;
    q->dir = (*p);
    (*p)->esq = aux;
    (*p) = q;

    return 0;
}

int rot_esq(AVL **p) {
    AVL *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->dir;
    aux = q->esq;
    q->esq = (*p);
    (*p)->dir = aux;
    (*p) = q;

    return 0;
}

void em_ordem(AVL **p) {
    if((*p) != NULL){
        em_ordem(&(*p)->esq);
        fprintf(sAVL, "%d ", (*p)->codigo);
        fprintf(sAVL, "%s ", (*p)->processo);
        fprintf(sAVL, "%d ", (*p)->prioridade);
        fprintf(sAVL, "%s ", (*p)->estado);
        fprintf(sAVL, "\n");
        em_ordem(&(*p)->dir);
    }
}

int altura(AVL **p) {
    int alt_esq = 0, alt_dir = 0;

    if((*p) == NULL) {
        return -1;
    }
    else {
        alt_esq = altura(&(*p)->esq);
        alt_dir = altura(&(*p)->dir);

        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}

void deleteTUDO(AVL **p){

    if ((*p) != NULL) {
        deleteTUDO(&(*p)->esq);
        deleteTUDO(&(*p)->dir);
        free(*p);
        *p=NULL;
    }

}

// Heap

void troca(Vetor *v1, Vetor *v2) {
    Vetor aux = *v1;
    *v1 = *v2;
    *v2 = aux;
}

void heapify(MaxHeap* heap, int i) {
    int maior = i;
    int filhoEsquerda = 2 * i;
    int filhoDireita = 2 * i + 1;

    // Nodo pai possui dois filhos
    if (filhoEsquerda <= heap->vetor[0].prioridade && filhoDireita <= heap->vetor[0].prioridade) {
        if (heap->vetor[filhoEsquerda].prioridade > heap->vetor[maior].prioridade && heap->vetor[filhoEsquerda].prioridade > heap->vetor[filhoDireita].prioridade) {
            maior = filhoEsquerda;
        }
        else if (heap->vetor[filhoDireita].prioridade > heap->vetor[maior].prioridade && heap->vetor[filhoDireita].prioridade > heap->vetor[filhoEsquerda].prioridade) {
            maior = filhoDireita;
        }
    }
    // Nodo pai possui apenas o filho da esquerda
    else if (filhoEsquerda <= heap->vetor[0].prioridade && heap->vetor[filhoEsquerda].prioridade > heap->vetor[maior].prioridade) {
        maior = filhoEsquerda;
    }
    // Nodo pai possui apenas o filho da direita
    else if (filhoDireita <= heap->vetor[0].prioridade && heap->vetor[filhoDireita].prioridade > heap->vetor[maior].prioridade) {
        maior = filhoDireita;
    }
    // Se um dos filhos ? maior do que o pai, o maior filho assume o lugar do pai
    if (maior != i) {
        troca(&heap->vetor[i], &heap->vetor[maior]);
        heapify(heap, maior);
    }
}

MaxHeap* criarMaxHeap(int capacidade) {
    MaxHeap* heap = (MaxHeap*) malloc(sizeof(MaxHeap));
    heap->vetor = (Vetor*) malloc(capacidade * sizeof(Vetor));
    heap->vetor[0].prioridade = 0;
    heap->capacidade = capacidade;
    fprintf(sheap, "Heap Iniciado!\n");
    return heap;
}

void InserirHeap(MaxHeap* heap, int codigo, char processo[], int prioridade, char estado[]) {
    if (heap != NULL && heap->vetor != NULL) {

        // Se o heap estiver vazio, a chave ? insirida na raiz
        if (heap->vetor[0].prioridade == 0) {
            heap->vetor[1].codigo = codigo;
            strcpy(heap->vetor[1].processo,processo);
            heap->vetor[1].prioridade = prioridade;
            strcpy(heap->vetor[1].estado,estado);
            heap->vetor[0].prioridade++;
        }
        else {
            // Se o heap estiver cheio, sua capacidade ? dobrada antes da inser??o da chave.
            if (heap->vetor[0].prioridade == heap->capacidade) {
                Vetor* vet = realloc(heap->vetor, heap->capacidade * 2);
                fprintf(sheap, "Heap foi Aumentado!\n");
                if (vet != NULL) {
                    heap->vetor = vet;
                }
                else {
                    fprintf(sheap, "Heap cheio! N?o ? poss?vel inserir mais elementos.\n");
                    return;
                }
            }
            heap->vetor[0].prioridade++;
            int i = heap->vetor[0].prioridade;
            int pai = i / 2;
            heap->vetor[i].codigo = codigo;
            strcpy(heap->vetor[i].processo,processo);
            heap->vetor[i].prioridade = prioridade;
            strcpy(heap->vetor[i].estado,estado);

            while (i > 1 && heap->vetor[i].prioridade > heap->vetor[pai].prioridade) {
                troca(&heap->vetor[i], &heap->vetor[pai]);
                i = pai;
                pai = i / 2;
            }
        }
        fprintf(sheap, "Código %d Alocado no Heap!\n", codigo);
    }
}

int remover(MaxHeap* heap) {
    if (heap != NULL && heap->vetor != NULL) {
        if (heap->vetor[0].prioridade == 0) {
            printf("Heap vazio!\n");
            return -1;
        }
        fprintf(sheap, "Processo de Código %d, Prioridade %d foi Removido do Heap!\n", heap->vetor[1].codigo, heap->vetor[1].prioridade);
        int raiz = heap->vetor[1].prioridade;
        heap->vetor[1] = heap->vetor[heap->vetor[0].prioridade];
        heap->vetor[0].prioridade--;
        heapify(heap, 1);
        return raiz;
    }
}

void imprimirHeap(MaxHeap* heap) {
	int i;
    if (heap != NULL && heap->vetor != NULL) {
        if (heap->vetor[0].prioridade == 0) {
            fprintf(sheap, "Heap vazio!\n");
        }
        else {
            fprintf(sheap, "Imprimindo Heap: \n");
            for (i = 1; i <= heap->vetor[0].prioridade; i++) {
                fprintf(sheap, "Posicao %d: ", i);
                fprintf(sheap, "%d ", heap->vetor[i].codigo);
                fprintf(sheap, "%s ", heap->vetor[i].processo);
                fprintf(sheap, "%d ", heap->vetor[i].prioridade);
                fprintf(sheap, "%s ", heap->vetor[i].estado);   
				fprintf(sheap, "\n");               
            }
        }
    }
}

void destruirHeap(MaxHeap* heap) {
    free(heap->vetor);
    free(heap);
    fprintf(sheap, "Heap Destruido!\n");
}

void alterarHeap(MaxHeap* heap, int codigo, int np){
	int i;
    for (i = 1; i <= heap->vetor[0].prioridade; i++) {
        if(heap->vetor[i].codigo==codigo) {
            heap->vetor[i].prioridade = np;
            heapify(heap,1);
            fprintf(sheap, "Prioridade Alterada!\n");
            return;
        }                
    }
    fprintf(sheap, "Nenhum Processo com o Codigo foi encontrado para alterar a prioridade!\n");
    
}

// Hash

void inicializa(Vetor vh[], int tam) {
    int i;
    for(i=0; i<(tam); i++){
        vh[i].codigo = -1;
        strcpy(vh[i].processo,"VAZIO");
        vh[i].prioridade = -1;
        strcpy(vh[i].estado,"VAZIO");
    }
    fprintf(shash, "Hash Iniciado!\n");
}

void imprimeL(Vetor vh[], int* tam, char estado[]) {
    int i;
    fprintf(shash, "Imprimindo Hash Linear:\n");
    for(i=0; i < (*tam); i++){
        if(strcmp(vh[i].estado,estado)==0){
            fprintf(shash, "Posicao %d: ", i);
            fprintf(shash, "%d ", vh[i].codigo);
            fprintf(shash, "%s ", vh[i].processo);
            fprintf(shash, "%d ", vh[i].prioridade);
            fprintf(shash, "%s ", vh[i].estado);
            fprintf(shash, "\n");  
        }
 
    }  
}

void imprimeQ(Vetor vh[], int* tam, char estado[]) {
    int i;
    fprintf(shash, "Imprimindo Hash Quadratico:\n");
    for(i=0; i < (*tam); i++){
        if(strcmp(vh[i].estado,estado)==0){
            fprintf(shash, "Posicao %d: ", i);
            fprintf(shash, "%d ", vh[i].codigo);
            fprintf(shash, "%s ", vh[i].processo);
            fprintf(shash, "%d ", vh[i].prioridade);
            fprintf(shash, "%s ", vh[i].estado);
            fprintf(shash, "\n");  
        }
 
    }  
}

int InsereLinear(Vetor vh[], int chave, char processo[], int prioridade, char estado[], int* colisaoL, int* tam) {
    int incr, hx, cl=0;
    fprintf(shash, "Inserindo na hash linear\n");
    for(incr = 0; incr < (*tam); incr++) {
        hx = (chave + incr) % (*tam);
        if(vh[hx].codigo == -1){
            break; //achei lugar! Saia e insira!    
        } else {
            (*colisaoL)++;//geral ->para todo armazenamento
            cl++;//colisao para inserir a chave do momento
            fprintf(shash, "Colisao Linear Ocorrida!\n");
        }
    }
    vh[hx].codigo = chave;
    vh[hx].prioridade = prioridade;
    strcpy(vh[hx].estado,estado);
    strcpy(vh[hx].processo,processo);
    fprintf(shash, "Processo de Codigo %d Inserido na Hash Linear\n", chave);
    fprintf(shash, "Colisoes Lineares ate Inserir: %d\n", cl);
    return cl;
}

int InsereQuad(Vetor vh[], int chave, char processo[], int prioridade, char estado[], int* colisaoQ, int* tam)
{
    int incr, hx,cq=0;
    fprintf(shash, "Inserindo na hash quadratica\n");
    for(incr = 0; incr < (*tam); incr++){
        hx = (chave + incr*incr) % (*tam);
        if(vh[hx].codigo== -1){
            break; //achei lugar! Saia e insira!
        } else {
            (*colisaoQ)++;//geral ->para todo armazenamento
            cq++;//colisao para inserir a chave do momento
            fprintf(shash, "Colisao Quadratica Ocorrida!\n");
        }
    }
    vh[hx].codigo = chave;
    vh[hx].prioridade = prioridade;
    strcpy(vh[hx].estado,estado);
    strcpy(vh[hx].processo,processo);
    fprintf(shash, "Processo de Codigo %d Inserido na Hash Quadratica\n", chave);
    fprintf(shash, "Colisoes Quadraticas ate Inserir: %d\n", cq);
    return cq;
}

int remocaoL(Vetor vh[], int chave, int* tam){
    int i;
    for(i=0;i<(*tam);i++){
        if(vh[i].codigo==chave){
            vh[i].codigo = -1;
            strcpy(vh[i].processo,"VAZIO");
            vh[i].prioridade = -1;
            strcpy(vh[i].estado,"VAZIO");
            fprintf(shash, "Processo de Codigo %d Removido da Hash Linear!\n",chave);
            return 0;
        }
    }
    fprintf(shash, "Codigo %d nao encontrado na Hash Linear para remocao!\n",chave);
}

int remocaoQ(Vetor vh[], int chave, int* tam){
    int i;
    for(i=0;i<(*tam);i++){
        if(vh[i].codigo==chave){
            vh[i].codigo = -1;
            strcpy(vh[i].processo,"VAZIO");
            vh[i].prioridade = -1;
            strcpy(vh[i].estado,"VAZIO");
            fprintf(shash, "Processo de Codigo %d Removido da Hash Quadratica!\n",chave);
            return 0;
        }
    }
    fprintf(shash, "Codigo %d nao encontrado na Hash Quadratica para remocao!\n",chave);
}

void cheio(Vetor vh[], int* tam){
    int i;
    for(i=0;i<(*tam);i++){
        if(vh[i].codigo==-1){
            return;
        }
    }
    (*tam)=(*tam)*2;
    fprintf(shash, "Hash foi aumentado!\n");
    for(i=(*tam)/2;i<(*tam);i++){
        vh[i].codigo = -1;
        strcpy(vh[i].processo,"VAZIO");
        vh[i].prioridade = -1;
        strcpy(vh[i].estado,"VAZIO");
    }   
    return;
}

void desbloquear(Vetor vh[], int* tam, int chave){
    int i;
    for(i=0;i<(*tam);i++){
        if(vh[i].codigo==chave){
            strcpy(vh[i].estado,"PRONTO");
            fprintf(shash, "DESBLOQUEADO!\n");
        }
    }
}

void bloquear(Vetor vh[], int* tam, int chave){
    int i;
    for(i=0;i<(*tam);i++){
        if(vh[i].codigo==chave){
            strcpy(vh[i].estado,"BLOQUEADO");
            fprintf(shash, "BLOQUEADO!\n");
        }
    }
}

void rhe(MaxHeap* heap, int chave){
    int i;
    for (i = 1; i <= heap->vetor[0].prioridade; i++) {
        if(heap->vetor[i].codigo==chave) {
            heap->vetor[i] = heap->vetor[heap->vetor[0].prioridade];
            heap->vetor[0].prioridade--;
            heapify(heap, 1);
            fprintf(shash, "Removido Heap Especifico!\n");
            return;
        }                
    }    

}