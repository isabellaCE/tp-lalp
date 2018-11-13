#include <stdio.h>
#include <stdlib.h>

int main(){

    char dados[]="1pen.pdb";
    char aux;

    FILE *arq;

    arq = fopen(dados, "r");

    if(arq == NULL){
        printf("Erro!!");
    } else {
        while((aux=fgetc(arq))!= EOF ){

            putchar(aux);
        }
    }
    fclose(arq);
    return 0;

}

