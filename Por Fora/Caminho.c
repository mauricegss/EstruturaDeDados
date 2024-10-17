#include <stdio.h>

int main()
{
	
	//Variáveis
    int i,j;
    int dist=0;
    int cont,cont1;
    int ini1,ini2,fim1,fim2;
    
    // Tamanho da Matriz
    do{
    printf("Coordenadas da Matriz: \n");
    scanf("%i%i",&i,&j);
	} while(i<=0&&j<=0);
	int matriz[i][j]; 

    // Atribuir 0
    for(cont=0;cont<i;cont++){
        for(cont1=0;cont1<j;cont1++){
            matriz[cont][cont1]=0;
        }
    }
    
    // Posição Inicial e Final
    do{
    printf("Coordenadas do Lobo: \n");
    scanf("%i%i",&ini1,&ini2);
	} while(ini1<=0||ini2<=0||ini1>i||ini2>j);
    matriz[ini1-1][ini2-1]=1;
    do{
    printf("Coordenadas da Presa: ");
    scanf("%i%i",&fim1,&fim2);
	} while(fim1<=0||fim2<=0||fim1>i||fim2>j);
    matriz[fim1-1][fim2-1]=2;
    
    // Se ambos na mesma posição no Início
	if(ini1==fim1&&ini2==fim2){
		matriz[fim1-1][fim2-1]=3;
	}
	
    //Display
    for(cont=0;cont<i;cont++){
    	printf("\n");
        for(cont1=0;cont1<j;cont1++){
            printf("%i ",matriz[cont][cont1]);
        }
    }
    
    //Ir para a Linha da Presa
    do{
    	if(ini1<fim1){
    		matriz[ini1-1][ini2-1]=0;
    		ini1++;
    		matriz[ini1-1][ini2-1]=1;
    		dist++;
    		//Display
    		if(matriz[ini1-1][ini2-1]==matriz[fim1-1][fim2-1]){
				matriz[ini1-1][ini2-1]=3;
			}    		
    		printf("\n");
    		for(cont=0;cont<i;cont++){
    		    printf("\n");
        	    for(cont1=0;cont1<j;cont1++){
                    printf("%i ",matriz[cont][cont1]);
        	    }
    	    }
		} else if(ini1>fim1){
			matriz[ini1-1][ini2-1]=0;
    		ini1--;
    		matriz[ini1-1][ini2-1]=1;
    		dist++;
    		//Display
    		if(matriz[ini1-1][ini2-1]==matriz[fim1-1][fim2-1]){
				matriz[ini1-1][ini2-1]=3;
			}
    		printf("\n");
    		for(cont=0;cont<i;cont++){
    		    printf("\n");
        	    for(cont1=0;cont1<j;cont1++){
                    printf("%i ",matriz[cont][cont1]);
        	    }
    		}
		}
	} while(ini1!=fim1);
    
    //Ir para a Coluna da Presa
    do{
    	if(ini2<fim2){
    		matriz[ini1-1][ini2-1]=0;
    		ini2++;
    		matriz[ini1-1][ini2-1]=1;
    		dist++;
    		//Display
    		if(matriz[ini1-1][ini2-1]==matriz[fim1-1][fim2-1]){
				matriz[ini1-1][ini2-1]=3;
			}    		
    		printf("\n");
    		for(cont=0;cont<i;cont++){
    		    printf("\n");
        	    for(cont1=0;cont1<j;cont1++){
                    printf("%i ",matriz[cont][cont1]);
        	    }
    		}
		} else if(ini2>fim2){
			matriz[ini1-1][ini2-1]=0;
    		ini2--;
    		matriz[ini1-1][ini2-1]=1;
    		dist++;
    		//Display
    		if(matriz[ini1-1][ini2-1]==matriz[fim1-1][fim2-1]){
				matriz[ini1-1][ini2-1]=3;
			}    		
    		printf("\n");
    		for(cont=0;cont<i;cont++){
    		    printf("\n");
        	    for(cont1=0;cont1<j;cont1++){
                    printf("%i ",matriz[cont][cont1]);
        	    }
    		}
		}
	} while(ini2!=fim2);

	//Distância
    printf("\n\nDistancia = %i",dist);
    
}
