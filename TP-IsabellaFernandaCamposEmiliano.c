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
    int quant;
} LISTA;

void inicializa(LISTA *l);
void imprime(LISTA *l);
void insere(ATOMO x, LISTA *l);

void printAtomo(ATOMO atomo){
    printf("\tNumero: %d\n\tNome: %s\n\tAminoacido: %s\n",atomo.num,atomo.nome,atomo.aminoacido);
    printf("\tx: %f\n\ty: %f\n\tz: %f\n",atomo.x,atomo.y,atomo.z);
}


int numero_atom(FILE* arq,LISTA* lista){
    char ch,charAux;
    char line[81],stringAux[90];
    int cont=0, intAux, result;
    ATOMO atomo;

    do{
        fgets(stringAux,5,arq);
        fscanf(arq,"%[^\n]s",line);

        ch = getc(arq);
        if(strcmp(stringAux,"ATOM")==0){
            result = sscanf(line," %6d  %3s %3s %c %3d   %f %f %f %[^\n]s",&atomo.num,&atomo.nome,&atomo.aminoacido,&charAux,&intAux,&atomo.x,&atomo.y,&atomo.z,&stringAux);
            insere(atomo,lista);
            cont++;
        }
        else if(strcmp(stringAux,"END ")==0){
            break;
        }
    }while(!feof(arq));
}

int menu (LISTA *lista){
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
    printf("8. Sair\n");
    while(c--){putc('-',stdout);}

    printf("\nSelecione: ");
    scanf("%d",&escolha);

    switch(escolha){
        case 1 :
            //inserir funcao a se executar
            imprime(lista);
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
            printf("Digite o numero do atomo: ");
            scanf("%d",&c);

            imprimirEspecifico(lista,c);
            break;
        case 7 :

            break;
        case 8:
            printf("\nSaindo...\n");
            break;
    }

    return escolha;printf("\nSaindo...\n");
}

int main(int argc, char* argv[]){
    LISTA lista;
    inicializa(&lista);

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

    printf("Numero de atomos: %d\n\n",lista.quant);

    //liberado
    while(menu(&lista)!=8){}

    fclose(arq);
    return 0;
}

void inicializa(LISTA *l){
    l->primeiro = (CELULA*)malloc(sizeof(CELULA));
    l->ultimo = l->primeiro;
    l->ultimo->prox == NULL;
    l->quant = 0;
}

void imprime(LISTA *l){
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    //system("cls");
    while(aux != NULL){
        printf("Atomo %d:\n",i+1);
        printAtomo(aux->item);
        putc('\n',stdout);
        aux = aux->prox;
        i++;
    }
}

void imprimirEspecifico(LISTA *l,int num){
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    while(aux != NULL && aux->item.num!=num){
        aux = aux->prox;
    }

    if(aux == NULL){
        printf("Atomo com o numero %d nao existe!\n",num);
    } else {
        printAtomo(aux->item);
    }
}

void insere(ATOMO x, LISTA *l){
    l->ultimo->prox = (CELULA*)malloc(sizeof(CELULA)*1);
    l->ultimo = l->ultimo->prox;
    l->ultimo->item = x;
    l->ultimo->prox = NULL;
    l->quant++;
}

