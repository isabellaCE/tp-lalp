/*Nome: Isabella Fernanda Campos Emiliano
 *Matricula: 201711130257
 *Nome: Juan Vitor Saar Silvério
 *Matricula: 201711130109
 *Nome: Marcus Vinicius Arcanjo Braga
 *Matricula: 201811130160
 *Nome: Samuel Pedro Fernandes Amorim
 *Matricula:201811130240
 *Descricao: Um programa que
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ATOMO
{
    int num;
    char nome[4];
    char aminoacido[4];
    char tpAminoacido[4];
    float x;
    float y;
    float z;
} ATOMO;

typedef struct CELULA
{
    ATOMO item;
    struct CELULA *prox;
} CELULA;

typedef struct LISTA
{
    CELULA *primeiro;
    CELULA *ultimo;
    int quant;
} LISTA;

typedef struct ITEM
{
    char nome[4];
    int quant;
} ITEM;

void inicializa(LISTA *l);
void imprime(LISTA *l);
void insere(ATOMO x, LISTA *l);
void imprimirEspecifico(LISTA *l, int num);
void tipos_atomo(LISTA *l, FILE *out);
void tipos_aminoacido(LISTA *l, FILE *out);
void quantAminoacido(LISTA *l, FILE *out);
void listar_dados(LISTA *l, char tipo[]);

void printAtomo(ATOMO atomo)
{
    printf("\tNumero: %d\n\tNome: %s\n\tAminoacido: %s\n", atomo.num, atomo.nome, atomo.aminoacido);
    printf("\tx: %.3f\n\ty: %.3f\n\tz: %.3f\n", atomo.x, atomo.y, atomo.z);
}

int numero_atom(FILE *arq, LISTA *lista)
{
    char ch, charAux;
    char line[81], stringAux[90];
    int intAux, result;
    ATOMO atomo;

    do
    {
        fgets(stringAux, 5, arq);
        fscanf(arq, "%[^\n]s", line);

        ch = getc(arq);
        if (strcmp(stringAux, "ATOM") == 0)
        {
            result = sscanf(line, " %6d  %3s %3s %c %3s   %f %f %f %[^\n]s", &atomo.num, &atomo.nome, &atomo.aminoacido, &charAux, &atomo.tpAminoacido, &atomo.x, &atomo.y, &atomo.z, &stringAux);
            insere(atomo, lista);
        }
        else if (strcmp(stringAux, "END ") == 0)
        {
            break;
        }
    } while (!feof(arq));
}

void gerar_saida(LISTA *l, char saidaFile[]){
    FILE *saida = fopen(saidaFile, "w");

    tipos_atomo(l, saida);
    tipos_aminoacido(l, saida);
    fprintf(saida,"Quantidade total de átomos presentes no arquivo: %d\n",l->quant);
    quantAminoacido(l, saida);

    fclose(saida);
    printf("Arquivo de saida gerado com sucesso!\n");
}

int menu(LISTA *lista, char saida[]){
    char ch[4];
    int c = 60, escolha;
    printf("LEITOR DE ATOMOS\n");
    while (c--){
            printf("-");
    }
    c = 60;
    printf("\n");
    printf("1. Listar todos os atomos\n");
    printf("2. Gerar arquivo de saida \n");
    printf("3. Exibir na tela a quantidade de atomos de cada tipo \n");
    printf("4. Exibir na tela a quantidade de aminoacidos de cada tipo\n");
    printf("5. Exibir na tela a quantidade total de aminoacidos presentes no arquivo \n");
    printf("6. Listar os dados de um atomo especifico\n");
    printf("7. Listar os dados de todos os atomos que tenham o mesmo tipo informado pelo usuario\n");
    printf("8. Sair\n");
    while (c--)
    {
        putc('-', stdout);
    }

    printf("\nSelecione: ");
    scanf("%d", &escolha);

    switch (escolha){
    case 1:
        //inserir funcao a se executar
        imprime(lista);
        break;
    case 2:
        gerar_saida(lista,saida);
        break;
    case 3:
        tipos_atomo(lista, stdout);
        break;
    case 4:
        tipos_aminoacido(lista, stdout);
        break;
    case 5:
        quantAminoacido(lista,stdout);
        break;
    case 6:
        printf("Digite o numero do atomo: ");
        scanf("%d", &c);

        imprimirEspecifico(lista, c);
        break;
    case 7:
        printf("Digite o tipo do atomo: ");
        scanf("%s",ch);
        listar_dados(lista , ch);
        break;
    case 8:
        printf("\nSaindo...\n");
        break;
    }

    return escolha;
}

int main(int argc, char *argv[]){
    LISTA lista;
    inicializa(&lista);

    FILE *arq;
    arq = fopen(argv[1], "r"); // 1PEN.PDB

    /*
    for(i=0;i<argc;i++)
        printf("[%d] = %s\n",i,argv[i]);
*/
    if (arq == NULL){
        printf("Erro!!");
        fclose(arq);
        return 0;
    }

    numero_atom(arq, &lista);
    fclose(arq);

    printf("Numero de atomos: %d\n\n", lista.quant);

    //liberado
    while (menu(&lista,argv[2]) != 8){}

    return 0;
}

void listar_dados(LISTA *l, char tipo[]){
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    while (aux != NULL)
    {
        if (strcmp(tipo, aux->item.nome) == 0){
            printf("Atomo %d: \n",i+1);
            printAtomo(aux->item);
            i++;
        }

        aux = aux->prox;
    }

}

void quantAminoacido(LISTA *l, FILE *out)
{
    int i = 0, count = 0, existe = 0;
    CELULA *aux = l->primeiro->prox;
    ITEM *tipos = (ITEM *)malloc(sizeof(ITEM));

    while (aux != NULL)
    {
        existe = 0;
        //aqui vem o código
        for (i = 0; i < count; i++)
        {
            if (strcmp(tipos[i].nome, aux->item.tpAminoacido) == 0)
            {
                tipos[i].quant++;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            count++;
            tipos = (ITEM *)realloc(tipos, sizeof(ITEM) * count);
            strcpy(tipos[count - 1].nome, aux->item.tpAminoacido);
            tipos[count - 1].quant = 1;
        }

        aux = aux->prox;
    }

    fprintf(out, "Quantidade total de aminoacidos presentes no arquivo: %d\n", count);
}

void inicializa(LISTA *l)
{
    l->primeiro = (CELULA *)malloc(sizeof(CELULA));
    l->ultimo = l->primeiro;
    l->ultimo->prox == NULL;
    l->quant = 0;
}

void imprime(LISTA *l)
{
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    //system("cls");
    while (aux != NULL)
    {
        printf("Atomo %d:\n", i + 1);
        printAtomo(aux->item);
        putc('\n', stdout);
        aux = aux->prox;
        i++;
    }
}

void tipos_atomo(LISTA *l, FILE *out)
{
    int i = 0, count = 0, existe = 0;
    CELULA *aux = l->primeiro->prox;
    ITEM *tipos = (ITEM *)malloc(sizeof(ITEM)); // {n: 2, c:1}

    while (aux != NULL)
    {
        existe = 0; //0
        //aqui vem o código
        for (i = 0; i < count; i++)
        {
            if (strcmp(tipos[i].nome, aux->item.nome) == 0)
            {
                tipos[i].quant++;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            count++;
            tipos = (ITEM *)realloc(tipos, sizeof(ITEM) * count);
            strcpy(tipos[count - 1].nome, aux->item.nome);
            tipos[count - 1].quant = 1;
        }

        aux = aux->prox;
    }

    fprintf(out, "Atomos de cada tipo presentes no arquivo:\n");
    for (i = 0; i < count; i++){
        fprintf(out, "%s: %d\n", tipos[i].nome, tipos[i].quant);
    }
}

void tipos_aminoacido(LISTA *l, FILE *out)
{
    int i = 0, count = 0, existe = 0;
    CELULA *aux = l->primeiro->prox;
    ITEM *tipos = (ITEM *)malloc(sizeof(ITEM));

    while (aux != NULL)
    {
        existe = 0;
        //aqui vem o código
        for (i = 0; i < count; i++)
        {
            if (strcmp(tipos[i].nome, aux->item.aminoacido) == 0)
            {
                tipos[i].quant++;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            count++;
            tipos = (ITEM *)realloc(tipos, sizeof(ITEM) * count);
            strcpy(tipos[count - 1].nome, aux->item.aminoacido);
            tipos[count - 1].quant = 1;
        }//quant;

        aux = aux->prox;
    }

    fprintf(out, "Aminoacidos de cada tipo presentes no arquivo:\n");
    for (i = 0; i < count; i++)
    {
        fprintf(out, "%s: %d\n", tipos[i].nome, tipos[i].quant);
    }
}

void imprimirEspecifico(LISTA *l, int num)
{
    int i = 0;
    CELULA *aux = l->primeiro->prox;

    while (aux != NULL && aux->item.num != num){
        aux = aux->prox;
    }
    //aux ==null ou aux = celula do atomo certo

    if (aux == NULL){
        printf("Atomo com o numero %d nao existe!\n", num);
    }
    else{
        printAtomo(aux->item);
    }
}

void insere(ATOMO x, LISTA *l)
{
    l->ultimo->prox = (CELULA *)malloc(sizeof(CELULA) * 1);
    l->ultimo = l->ultimo->prox;
    l->ultimo->item = x;
    l->ultimo->prox = NULL;
    l->quant++;
}
