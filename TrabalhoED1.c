#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Altura Min / Max = 3 / 10 km
// Quando aterrisando pode passar altura minima
// Como as funcoes TEMPESTADE / NEBLINA / TURBULENCIA sao muito parecidas = tudo sera explicado na funcao TEMPESTADE
// Por: Gabriel Castello Branco Ayres Nalesso e Maurice Golin Soares dos Santos

typedef struct Aviao {
    int tempo_estimado;
    int pista;
    int codigo;
    int estado; 
    int tempo_de_voo; // Tempo que ficou no ar
    char modelo[20];
    char destino[20];
    float distancia;
    float velocidade; // em Km/min
    float distancia_percorrida; // "Eixo X"
    float altura; // "Eixo Y"
    struct Aviao *prox;
} aviao;

typedef struct cabeca {
    aviao *inicio, *fim;
} tpis;

typedef struct noaeroporto { // = lista de listas
    tpis *cabecao; // = Endereço para Pista
    struct noaeroporto *prox; // = Para a proxima pista
} tmpis; 

tpis *criapista(); 
void insere_aviao(tpis *f, int p, int codigo, char modelo[], char destino[], float distancia, float velocidade, int estado, float altura, int tempo_estimado);
// Pista, Num da Pista, Codigo, Modelo, Destino, Distancia, Velocidade, Estado, Altura, Tempo Estimado
void decolar(FILE* l, tpis *f, tpis *v);
void removerInicioFila(tpis *f);
void imprime(tpis *p);
void buscar(tpis *p, int chave);
void aviao_move(tpis *v);
void iniciasimulacao(FILE* l, int k, tpis *v);
void liberarvoando(tpis **f);
void colisao(FILE* l, tpis *v);
void tempestade(FILE* l, int k, tpis *v);
void neblina(FILE* l, int k, tpis *v);
void turbulencia(FILE* l, int k, tpis *v);
void aterrisando(tpis *v);
int aleatorio(tpis *v); 
tpis *acha_pista(tmpis** m, int p); // Retorna a pista desejada da lista de pistas
void criaaero(tmpis **p);
void fim(FILE* l, tpis* p, tmpis **f);  // Desaloca tudo e gera o log.txt
void liberaraeroporto(tmpis **f);

int main() {

    srand(time(NULL));
    char funcao [20], model[20], destiny[20];
    int pisty, cod, t_e;
    float disty;
    FILE *log, *entrada;
    tmpis *aeroporto = NULL;
    tpis *voando = criapista();
    entrada = fopen("d://Arquivos//Facul//Projeto//entrada.txt", "r"); //Simone favor colocar o caminho da entrada aqui
    log = fopen("d://Arquivos//Facul//Projeto//log.txt", "w"); //Simone favor colocar o caminho do arquivo log aqui

    fscanf(entrada, "%s", funcao);

    while (strcmp(funcao, "fim")!=0) {

    if(strcmp(funcao, "pistas")==0) {
        fscanf(entrada, "%d", &pisty);
        while(pisty!=0) {
            criaaero(&aeroporto); // Para criar as pistas
            pisty--;
        }
    }

    if (strcmp(funcao, "insere_aviao") == 0) {
        fscanf(entrada, "%d", &pisty);
        fscanf(entrada, "%d", &cod);
        fscanf(entrada, "%s", model);
        fscanf(entrada, "%s", destiny);
        fscanf(entrada, "%f", &disty);
        fscanf(entrada, "%d", &t_e);
        insere_aviao(acha_pista(&aeroporto, pisty), pisty, cod, model, destiny, disty, 0.0, 1, 0.0, t_e);
    }

    if(strcmp(funcao, "decolar") == 0) {
        fscanf(entrada, "%d", &pisty);
        decolar(log, acha_pista(&aeroporto, pisty), voando);
    }

    if(strcmp(funcao, "tempestade")==0) {
        fscanf(entrada, "%d", &pisty);
        tempestade(log, pisty, voando);
    }

    if(strcmp(funcao, "neblina")==0) {
        fscanf(entrada, "%d", &pisty);
        neblina(log, pisty, voando);
    }

    if(strcmp(funcao, "turbulencia")==0) {
        fscanf(entrada, "%d", &pisty);
        turbulencia(log, pisty, voando);
    }

    if(strcmp(funcao, "iniciasimulacao")==0) {
        fscanf(entrada, "%d", &pisty);
        iniciasimulacao(log, pisty, voando);
    }

    fscanf(entrada, "%s", funcao);

    }

    fim(log, voando, &aeroporto);
    fclose(log);
    fclose(entrada);
    return 0;
}

void criaaero(tmpis **p){ // cria a lista sem cabeça que irá receber as pistas(filas)
    tmpis *novo = (tmpis*)malloc(sizeof(tmpis));
    novo->cabecao = criapista(); // Gera 
    novo->prox = (*p);
    *p = novo;
}

tpis *acha_pista(tmpis** m, int p){
    tmpis *aux = (*m);
    int i;
    for(i = 1; i < p; i++){ // avança a lista conforme o número da pista desejado
        aux = aux -> prox;
    }
    return aux->cabecao; // retorna a pista encontrada para ser utilizada pelas demais funções
}

tpis *criapista() { // Insercao em FILA com cabeca
    tpis *novo;
    novo = (tpis *)malloc(sizeof(tpis));
    if (novo) {
        novo->inicio = NULL;
        novo->fim = NULL;
        return novo;
    } else {
        return NULL;
    }
}

void decolar(FILE* l, tpis *f, tpis *v) { // Transferencia em listas
    if (f->inicio) {
        insere_aviao(v,f->inicio->pista, f->inicio->codigo, f->inicio->modelo, f->inicio->destino, f->inicio->distancia, 40, 2, 10.0, f->inicio->tempo_estimado);
        removerInicioFila(f);
        colisao(l,v); // Sempre verificar colisao
        // IA determina que todos comecam na altura maxima, caso mais de um decole ao mesmo tempo, os avioes vao descendo a partir das colisoes
    }
}

void removerInicioFila(tpis *f) { // Remocao em FILA com cabeca
    aviao *aux = f->inicio;
    if (aux) {
        f->inicio = f->inicio->prox;
        free(aux);
        if (f->inicio == NULL) {
            f->fim = NULL;
        }
    } else {
        printf("\nLista Vazia!\n");
    }
}

void imprime(tpis *p) { // Imprime toda a fila/lista
    aviao *aux=p->inicio;
	if(aux){
		while(aux){
            printf("\n----------------------------\n");
            printf("\nCodigo: %d", aux->codigo);
            printf("\nPista de Origem: %d",aux->pista);
            printf("\nEstado: %d", aux->estado);
            printf("\nTempo de Voo: %d min", aux->tempo_de_voo);
            printf("\nTempo Estimado %d min",aux->tempo_estimado);
            printf("\nModelo: %s", aux->modelo);
            printf("\nDestino: %s", aux->destino);
            printf("\nDistancia: %.2f km", aux->distancia);
            printf("\nVelocidade: %.2f km/min", aux->velocidade);
            printf("\nDistancia Percorrida: %.2f km", aux->distancia_percorrida);
            printf("\nAltura: %.2f km", aux->altura);
            printf("\n----------------------------\n");
			aux=aux->prox;
		}
	} else {
		printf("\nLista vazia!\n");
	}
}

void buscar(tpis *p, int chave) {
    aviao *aux = p->inicio;
    if(aux) {
        while(aux) {
            if(aux->codigo == chave) { // Para achar o aviao com o codigo
                printf("\n----------------------------\n");
                printf("\nCodigo: %d", aux->codigo);
                printf("\nPista de Origem: %d",aux->pista);
                printf("\nEstado: %d", aux->estado);
                printf("\nTempo de Voo: %d min", aux->tempo_de_voo);
                printf("\nTempo Estimado %d min",aux->tempo_estimado);
                printf("\nModelo: %s", aux->modelo);
                printf("\nDestino: %s", aux->destino);
                printf("\nDistancia: %.2f km", aux->distancia);
                printf("\nVelocidade: %.2f km/min", aux->velocidade);
                printf("\nDistancia Percorrida: %.2f km", aux->distancia_percorrida);
                printf("\nAltura: %.2f km", aux->altura);
                printf("\n----------------------------\n");
                return;
            }
            aux = aux->prox;
        }
        printf("\nAviao nao encontrado!\n");
    } else {
        printf("\nLista vazia!\n");
    }
}

void aviao_move(tpis *v) {
    aviao *aux = v->inicio;
    if(aux) {
		while(aux) {
		    aux->distancia_percorrida=aux->distancia_percorrida+aux->velocidade;
            aux->tempo_de_voo=aux->tempo_de_voo+1;
			aux=aux->prox;
		}
	} else {
		printf("\nLista vazia!\n");
	}
}

void iniciasimulacao(FILE* l, int k, tpis *v) {
    int i;
    if(v->inicio) {
    for(i=0;i<k;i++) {
        aviao_move(v);
        colisao(l,v);
    }
    } else {
        printf("\nLista Vazia\n");
    }

}

void liberarvoando(tpis **f) {
	while((*f)->inicio) {           // Limpar a lista
		removerInicioFila(*f);      //
	}                               //
    free(*f);   // Liberar a cabeça
    *f = NULL;  //
}

void colisao(FILE* l, tpis *v) {
    aviao *aux1 = v->inicio;
    aviao *aux2 = v->inicio;
    // Funcao ira comparar um aviao com os outros, por isso 2 auxiliares
    if(aux1) {
		while(aux1) {
            if(aux1->distancia_percorrida>=aux1->distancia*0.9) {   // Verifica se precisa aterrisar
                aterrisando(v);                                     //
            }                                                       //
            while(aux2) {
                if((aux1->altura==aux2->altura)&&(aux1->distancia_percorrida==aux2->distancia_percorrida)&&(aux1->codigo!=aux2->codigo)){
                    // Compara se estao no mesmo "Eixo X" e Eixo Y"
                    fprintf(l,"\nAviao de Codigo [%d] (quase colidiu com) Aviao de Codigo [%d]\n",aux1->codigo,aux2->codigo); // Manda arquivo log com colisao
                    aux2->altura=aux2->altura-0.1; // Diminui altura de um aviao
                    colisao(l,v); // Verifica se sera necessaria outra alteracao
                    break;
                } else if (aux1->altura<3.0&&aux1->estado==2){ // Verifica se passou da altura minima caso esteja voando
                    fprintf(l,"\nAviao de Codigo [%d] (quase colidiu com) Altura Minima\n",aux1->codigo);  // Manda arquivo log com colisao
                    aux1->altura=10.0; // Se ultrapassou, ira para altura maxima
                    colisao(l,v); // Verifica se sera necessaria outra alteracao
                    break;
                }
                aux2=aux2->prox;
            }
            aux1 = aux1->prox;
        }	
	} else {
		printf("\nLista vazia!\n");
    }
}

void tempestade(FILE* l, int k, tpis *v){
    aviao *aux = v->inicio;
    if(aux){
    iniciasimulacao(l, k, v); // Melhor do que aviao_move()
    int i = aleatorio(v); // Seleciona um aviao aleatorio
    while(i!=0){                // Vai ate o aviao sorteado
        aux = aux->prox;        //
        i--;                    //
    }                           //
    fprintf(l,"\nAviao de Codigo [%d] (sofreu com Tempestade)\n",aux->codigo); // Manda arquivo log com o imprevisto
    aux->altura=aux->altura-0.3;            // Realiza as alteracoes
    aux->velocidade=aux->velocidade*0.9;    //
    colisao(l,v);     // Sempre necessario verificar colisao
    } else {
        printf("\nLista Vazia\n");
    }
}

void neblina(FILE* l, int k, tpis *v){
    aviao *aux = v->inicio;
    if(aux){
    iniciasimulacao(l,k, v);
    int i = aleatorio(v);
    aux = v->inicio;
    while(i!=0){                
        aux = aux->prox;        
        i--;                    
    }                           
    while(i!=0){
        aux = aux->prox;
        i--;
    }
    fprintf(l,"\nAviao de Codigo [%d] (sofreu com Neblina)\n",aux->codigo);
    aux->distancia_percorrida=aux->distancia_percorrida-0.5;
    aux->velocidade=aux->velocidade*0.95;
    colisao(l,v);
    } else {
        printf("\nLista Vazia\n");
    }
}

void turbulencia(FILE* l, int k, tpis *v){
    aviao *aux = v->inicio;
    if(aux){
    iniciasimulacao(l, k, v);
    int i = aleatorio(v);
    aux = v->inicio;
    while(i!=0){               
        aux = aux->prox;        
        i--;                    
    }                           
    while(i!=0){
        aux = aux->prox;
        i--;
    }
    fprintf(l,"\nAviao de Codigo [%d] (sofreu com Turbulencia)\n",aux->codigo);
    aux->velocidade=aux->velocidade*0.75;
    colisao(l,v);
    } else {
        printf("\nLista Vazia\n");
    }

}

void aterrisando(tpis *v) {
    // Como so e necessaria a funcao aterrisando e nao aterrisado, a funcao so diminui percentualmente a velocidade e altura
    // Entao nessa funcao as alturas e velocidades nunca chegarao a 0
    // Porem poderia ser feito que caso a altura chegasse a menos de 1 km o aviao poderia entrar em um fila "aterrisados"
    // E sua velocidade = 0, distancia percorrida = distancia total, altura = 0
    aviao *aux = v->inicio;
	while(aux) {
        if(aux->distancia_percorrida<=aux->distancia*0.1){
            aux->estado=3;
            aux->velocidade=aux->velocidade*0.90; // Velocidade vai diminuindo 10%
            aux->altura=aux->altura*0.90; // Altura vai diminuindo 10%
        }
    aux=aux->prox;
    }
}

int aleatorio(tpis *v) {
    int i=0;
    aviao *aux = v->inicio;
    if(aux){      
        while (aux){                // Conta os avioes
            i++;                    //    
            aux=aux->prox;          //   
        }                           // 
        i = (rand()%i);         // Sorteia um aviao
    } else {
        printf("\nLista Vazia\n");
    }

    return i;
}

void insere_aviao(tpis *f, int p, int codigo, char modelo[], char destino[], float distancia, float velocidade, int estado, float altura, int tempo_estimado) {
    aviao *novo = (aviao *)malloc(sizeof(aviao));
    if (novo) {
        strcpy(novo->modelo, modelo);
        strcpy(novo->destino, destino);
        novo->tempo_estimado=tempo_estimado;
        novo->pista = p;
        novo->codigo = codigo;
        novo->estado = estado;
        novo->tempo_de_voo=0;
        novo->distancia = distancia;
        novo->velocidade = velocidade;
        novo->distancia_percorrida = 0;
        novo->altura = altura;
        novo->prox = NULL;
        if (f->fim != NULL) {
            f->fim->prox = novo;
        }
        f->fim = novo;
        if (f->inicio == NULL) {
            f->inicio = novo;
        }
    }
}

void fim(FILE* l, tpis* p, tmpis **f) {
    aviao *aux=p->inicio;
    int cont=0;
    if(aux){
        while(aux){ // imprime as informações dos aviões no log
            if(aux->estado==3){
                fprintf(l,"\n----------------------------");
                fprintf(l,"\nCodigo: %d", aux->codigo);
                if(aux->tempo_de_voo>aux->tempo_estimado){
                    fprintf(l,"\nAviao Atrasou");
                } else if(aux->tempo_de_voo<aux->tempo_estimado){
                    fprintf(l,"\nAviao Adiantou");
                } else {
                    fprintf(l,"\nAviao Chegou na Hora Exata");
                }
                fprintf(l,"\nTempo de Voo: %d min", aux->tempo_de_voo);
                fprintf(l,"\nTempo Estimado: %d min", aux->tempo_estimado);
                fprintf(l,"\n----------------------------\n");
                cont++;
            }
            aux=aux->prox;
        }
        if(cont==0){
            fprintf(l,"\nNenhum Aviao chegou a Aterrisar");
        }
    } else {
        fprintf(l,"\nNenhum Aviao chegou a Aterrisar");
        printf("\nNenhum Aviao chegou a Voar\n");
    }
    liberarvoando(&p); // libera os aviões que estão voando, necessário outra função pois é uma lista com cabeça
    liberaraeroporto(&(*f)); // libera o aeroporto e suas pistas

}

void liberaraeroporto(tmpis **f) { // Remoção no começo em Lista sem Cabeca
    tmpis *aux = (*f);
	if(*f) {
		*f = (*f)->prox;
		free(aux);
	}
}