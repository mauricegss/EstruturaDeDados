#include <stdio.h>

char a='A',b='B',c='C',d='D',e='E',f='F',g='G',h='H',i='I',xo='O';
int vde=0;

void Display()
{
    printf("\n\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c ",a,b,c,d,e,f,g,h,i);
}

void Jogada()
{
    char esc;
    if(xo=='X'){
        xo='O';
    } else {
        xo='X';
    }
    printf("\n\nEscolha a Letra para por %c: ",xo);
    scanf(" %c",&esc);
    switch(esc){
        case 'A':
        if(a!='A'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            a=xo;
        }
            break;
        case 'B':
        if(b!='B'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            b=xo;
        }
            break;
        case 'C':
        if(c!='C'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            c=xo;
        }
            break;
        case 'D':
        if(d!='D'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            d=xo;
        }
            break;
        case 'E':
        if(e!='E'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            e=xo;
        }
            break;
        case 'F':
        if(f!='F'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            f=xo;
        }
            break;
        case 'G':
        if(g!='G'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            g=xo;
        }
            break;
        case 'H':
        if(h!='H'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            h=xo;
        }
            break;
        case 'I':
        if(i!='I'){
            printf("\n\nJa foi selecionada. Perdeu a vez.");
        } else{
            i=xo;
        }
            break;
        default:
        printf("\n\nLetra invalida. Perdeu a vez.");
            break;
    }
}

void Verificar()
{
    if((a==b&&a==c)||(d==e&&d==f)||(g==h&&g==i)||(a==d&&a==g)||(b==e&&e==h)||(c==f&&c==i)||(a==e&&a==i)||(c==e&&c==g)){
        if (a=='X'||b=='X'||c=='X'){
            printf("\nX Ganhou!");
            vde++;
        } else {
            printf("\nO Ganhou!");
            vde++;
        }
    } else if ((a=='X'||a=='O')&&(b=='X'||b=='O')&&(c=='X'||c=='O')&&(d=='X'||d=='O')&&(e=='X'||e=='O')&&(f=='X'||f=='O')&&(g=='X'||g=='O')&&(h=='X'||h=='O')&&(i=='X'||i=='O')){
        printf("\n\nDeu Velha!");
        vde++;
    }
}

int main()
{
    while(vde!=1){
        Display();
        Jogada();
        Verificar();
        if(vde==1){
            Display();
        }
    }
}