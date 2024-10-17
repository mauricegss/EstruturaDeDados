#include <stdio.h>

int main()
{
    int i1,i2,j1,j2;
    do 
        {
        printf("Diga o numero de linhas da matriz A: ");
        scanf("%i",&i1);
        printf("Diga o numero de colunas da matriz A: ");
        scanf("%i",&j1);
        printf("\nDiga o numero de linhas da matriz B: ");
        scanf("%i",&i2);
        printf("Diga o numero de colunas da matriz B: ");
        scanf("%i",&j2);
        if(j1!=i2)
            {
        printf("\nImpossivel multiplicar as matrizes\n");
            }
        } while (j1!=i2);
    
    int a1[i1][j1],a2[i2][j2];
    int resp[i1][j2];
    
    printf("\nPrimeira Matriz: \n");
    for(int cont1=1; cont1<=i1;cont1++)
        {
        for(int cont2=1;cont2<=j1;cont2++)
            {
            printf("Insira o a(%i,%i): ",cont1,cont2);
            scanf("%i",&a1[cont1-1][cont2-1]);
            }
        }
   
    printf("\nSegunda Matriz: \n");
    for(int cont3=1; cont3<=i2;cont3++)
        {
        for(int cont4=1;cont4<=j2;cont4++)
            {
            printf("Insira o b(%i,%i): ",cont3,cont4);
            scanf("%i",&a2[cont3-1][cont4-1]);
            }
        }
    
    printf("\nMatriz A*B: \n");
    for(int cont5=1;cont5<=i1;cont5++)
        {
        for(int cont6=1;cont6<=j2;cont6++)
            {
            resp[cont5-1][cont6-1]=0;
            int cont7=i2;
            while(cont7>=1)
                {
                resp[cont5-1][cont6-1]= resp[cont5-1][cont6-1] + (a1[cont5-1][cont7-1]*a2[cont7-1][cont6-1]);
                cont7--;
                }
                printf("%i ",resp[cont5-1][cont6-1]);
                if(cont6%j2==0)
                    {
                    printf("\n");
                    }
            }
        }
    return 0;
}
