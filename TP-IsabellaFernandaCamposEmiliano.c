/*Nome: Isabella Fernanda Campos Emiliano
 *Matricula: 201711130257
 *Nome: Juan Vitor Saar Silvério
 *Matricula: c
 *Nome: Marcus Vinicius Arcanjo Braga
 *Matricula: 201811130160
 *Nome: Samuel Pedro Fernandes Amorim
 *Matricula:201811130240
 *Descricao:
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct atomo{
  int num;
  char nome[4];
  char aminoacido[4];
  float x;
  float y;
  float z;
} Atomo;

typedef struct item{
    Atomo atomo;                 
    struct item *prox;                        
} Item;

typedef struct {
    Item *primeiro;
    Item *ultimo;
    int quant;
} Header;

int numero_atom(FILE* arq){
    char ch;
    int cont;

    while( (ch=fgetc(arq))!= EOF ){
			if(ch == 'A'){
                if(ch+1 == 'T'){
                    if(ch+2 == 'O'){
                        if(ch+3 == 'M'){
			            atomo.num++;
                        }
                    }
                }
            }    
    }
}

void menu (){
    int c = 60 , escolha;
    printf("LEITOR DE ATOMOS\n");
    while(c--){printf("-");}
    c=60;
    printf("\n");
    printf("1. Listar todos os atomos\n");
    printf("2. Gerar arquivo de saída \n");
    printf("3. Exibir na tela a quantidade de atomos de cada tipo \n");
    printf("4. Exibir na tela a quantidade de aminoacidos de cada tipo\n");
    printf("5. Exibir na tela a quantidade total de aminoacidos presentes no arquivo \n");
    printf("6. Listar os dados de um atomo especifico\n");
    printf("7. Listar os dados de todos os atomos que tenham o mesmo tipo informado pelo usuario\n");
    while(c--){printf("-");}
        scanf("%d",&escolha);
    switch(escolha){
        case 1 :
            //inserir funcao a se executar
        break;
        case 2 :

        break;
        case 3 :

        break;
        case 4 :

        break;
        case 5 :

        break;
        case 6 :

        break;
        case 7 :
        
        break;
    }
}

int main(int argc, char* argv[]){

    Header cabeca;
    cabeca->primeiro = NULL;
    cabeca->ultimo = cabeca->primeiro;

    int i;
    char aux;
    FILE *arq;

    arq = fopen(argv[1], "r");


    for(i=0;i<argc;i++)
        printf("[%d] = %s\n",i,argv[i]);

    if(arq == NULL){
        printf("Erro!!");
        fclose(arq);
        return 0;
    } 
    
    //liberado
    menu();
    
    fclose(arq);
    return 0;
}

/*
comentarios aq.
OK
*/

