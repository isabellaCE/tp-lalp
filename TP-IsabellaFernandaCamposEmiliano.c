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
#include <string.h>

typedef struct ATOMO{
  int num;
  char nome[4];
  char aminoacido[4];
  float x;
  float y;
  float z;
} ATOMO;

typedef struct CELULA {
    ATOMO item;
    struct CELULA *prox;
} CELULA;

typedef struct LISTA {
    CELULA *primeiro;
    CELULA *ultimo;
} LISTA;

void inicializa(LISTA *l);
void imprime(LISTA *l);
void insere(ATOMO x, LISTA *l);

void printAtomo(ATOMO atomo){
    printf("{\nNumero: %d\nNome: %s\nAminoacido: %s\n",atomo.num,atomo.nome,atomo.aminoacido);
    printf("x: %f\ny: %f\nz: %f\n}\n",atomo.x,atomo.y,atomo.z);
}


int numero_atom(FILE* arq,LISTA* lista){
    char ch,charAux;
    char stringAux[90];
    int cont=0, intAux, result;
    ATOMO atomo;

    do{
        fgets(stringAux,5,arq);
        if(strcmp(stringAux,"ATOM")==0){
            result = fscanf(arq," %6d  %3s %3s %c %3d   %f %f %f %[^\n]s",&atomo.num,&atomo.nome,&atomo.aminoacido,&charAux,&intAux,&atomo.x,&atomo.y,&atomo.z,&stringAux);
            ch = getc(arq);
            printAtomo(atomo);
            cont++;
        } else{
            fseek(arq,77,SEEK_CUR);
        }
        //printf("[%d](%d)[%c][%s]\n",result,ftell(arq),fgetc(arq),stringAux);

    }while(result!=EOF);
    system("pause");
    insere(atomo,lista);
    imprime(lista);

}

void menu (LISTA *lista){
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
    LISTA lista;
    ATOMO test;
    inicializa(&lista);
    test.num=5;
    insere(test,&lista);
    test.num=7;
    insere(test,&lista);
    imprime(&lista);

    int i;
    char aux;
    FILE *arq;

    arq = fopen("1pen.pdb", "r");

/*
    for(i=0;i<argc;i++)
        printf("[%d] = %s\n",i,argv[i]);
*/
    if(arq == NULL){
        printf("Erro!!");
        fclose(arq);
        return 0;
    }

    numero_atom(arq,&lista);

    //liberado
    menu(&lista);

    fclose(arq);
    return 0;
}

void inicializa(LISTA *l){
    l->primeiro = (CELULA*)malloc(sizeof(CELULA));
    l->ultimo = l->primeiro;
    l->ultimo->prox == NULL;
}

void imprime(LISTA *l){
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    system("cls");
    while(aux != NULL){
        printf("ITEM %d DA LISTA: \t", i+1);
        printf("%d \n", aux->item.num);
        aux = aux->prox;
        i++;
    }
}

void insere(ATOMO x, LISTA *l){
    l->ultimo->prox = (CELULA*)malloc(sizeof(CELULA)*1);
    l->ultimo = l->ultimo->prox;
    l->ultimo->item = x;
    l->ultimo->prox = NULL;
}

