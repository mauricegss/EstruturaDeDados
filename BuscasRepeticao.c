#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Vinicius Aparecido de Oliveira Hashizume
//Maurice Golin Soares dos Santos

int busca_linear(int vet[], int a, int b, int x)
{
    for(int i=a; i<=b; i ++)
    {
        if(vet[i]==x)
        {
            return i;
        }
    }
    return -1;
}

int busca_binaria(int vet[], int a, int b, int x)
{
    while(a<=b)
    {
        int m=a+(b-a)/2;
        if(vet[m]==x)
        {
            return m;
        }
        else if(vet[m] < x)
        {
            a= m+1;
        }
        else
        {
            b=m-1;
        }
    }
    return -1;
}

void ShellSort(int v[], int ini, int fim) {
	int h, i, aux, j;
	h = (fim-ini+2)/2;
	while(h > 0 )
	{
		i = h;
		while(i <= (fim-ini+1) )
		{	
			aux = v[i];
			j = i;
			while (j >=h && aux < v[j-h])
			{
				v[j] = v[j-h];
				j = j - h;	
			}
			v[j] = aux;
			i = i + 1;
		}
		h = h/2;
	}
}

int main()
{
    int i, vet[1000], op;
    srand(time(NULL));

    for (i=0; i<1000; i++)
    {
        vet[i]= rand()%5001;
    }

    printf("Qual busca você deseja realizar? \n1- Busca Linear \n2- Busca Binaria\n");
    scanf("%d", &op);

    if(op==1){
        
        clock_t ticks1[2];
        ticks1[0] = clock();
        busca_linear(vet,0,199999,96);
        ticks1[1] = clock();
        double tempo1 = (ticks1[1] - ticks1[0]) * 1000.0/CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.", tempo1);
        
    }
    
    if(op==2) {

	ShellSort(vet, 0, 199999);

        clock_t ticks2[2];
        ticks2[0] = clock();
        busca_binaria(vet,0,999,96);
        ticks2[1] = clock();
        double tempo2 = (ticks2[1] - ticks2[0]) * 1000.0/CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.", tempo2);
        
    }

    return 0;
}
