#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"
///
///Função utilizada para converter uma imagem Grayscale dada como argumento
///em uma imagem binária através de um 'threshold' dado por argumento da função.
///O bit tem valor 1 se o valor do bit for mais baixo que o 'threshold'
/// e 0 caso contrário.
///
BINARYIMAGE *GrayToBinaryThreshold(GRAYIMAGE *im, int thresh){
    
    BINARYIMAGE *bim = calloc(1, sizeof(BINARYIMAGE));

    bim->type = "P4";
    bim->x = im->x;
    bim->y = im->y;
    bim->gama = 1;

    bim->bits = allocMemBit(bim->x,bim->y);

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            if(im->gray[i][n].pix<=thresh){ //write 1
                bim->bits[i][n].pix = (unsigned char)1;
            }
            else { //write 0
                bim->bits[i][n].pix = (unsigned char)0;
            }
        }
    }
    return bim;
}
///
///Função utilizada para converter uma imagem Grayscale dada como argumento
///em uma imagem binária através de um algoritmo de histograma.
///Este algoritmo conta o número de ocurrencias de cada intensidade(0-255) e
/// e depois define um 'threshold' médio através desse histograma.
///O resto do algoritmo funcionda de forma similar á outra função de conversão
///com o 'thrshold' calculado.
///
BINARYIMAGE *GrayToBinaryHistogram(GRAYIMAGE *im){

    BINARYIMAGE *bim = calloc(1, sizeof(BINARYIMAGE));

    bim->type = "P4";
    bim->x = im->x;
    bim->y = im->y;
    bim->gama = 1;

    bim->bits = allocMemBit(bim->x,bim->y);

    int hist[256] = {0};
    int thresh = 0;

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            hist[(int)im->gray[i][n].pix]++;
        }
    }

    int sum = 0;

    for(int i = 0; i<256; i++){
        sum =  sum + hist[i];
        if(sum>=(im->x*im->y)/2){
            thresh = i;
            break;
        }
    }

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            if(im->gray[i][n].pix<=thresh){ //write 1
                bim->bits[i][n].pix = (unsigned char)1;
            }
            else { //write 0
                bim->bits[i][n].pix = (unsigned char)0;
            }
        }
    }
    return bim;
}
///
///Função utilizda para averiguar se uma string tem valor numérico ou não.
///
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
        return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
///
///Este programa converte uma imagem Grayscale em uma imagem binária.
///Podem ser utilizados 2 algoritmos.
///O algoritmo de 'threshold' que utiliza a função GrayToBinaryThreshold(). Este algoritmo pode ser
///utilizado chamando o programa com a opção -t e com um valor de 'threshold'(entre 0 e 255) após este argumento.
/// Também é necessário mais 2 argumentos com o nome da imagem a converter e com o nome 
///do ficheiro onde se vai escrever a imagem convertida (Ex: ./GrayToBin -t 122 fileToConvert outputFile).
///O outro algoritmo é o de histogramas. Este pode ser utilizado utilizando o argumento -h
/// para além dos argumentos dos ficheiros de inout e output (Ex: ./GrayToBin -h fileToConvert outputFile). 
///
int main(int argc, char *argv[]) {

    int flags, opt;

    int t = 0;
    int thresh = 0;
    int h = 0;

    while ((opt = getopt(argc, argv, "t:h")) != -1)
    {
        switch (opt)
        {
            case 't':
                printf("Convert grayscale to binary through threshold %d\n", atoi(optarg));
                if (isNumeric(optarg)==0){
                    printf("Value of argument -t has to be a number between 0 and 255\n");
                    exit(EXIT_FAILURE);
                }
                thresh =  atoi(optarg);
                t = 1;
                break;
            case'h':
                printf("Convert grayscale to binary through histogram algorithm\n");
                h = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-h/-t threshhold] imageFileRead imageFileSave\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if((t == 0 && h == 0) || (t==1 && argc!=5) || (h==1 && argc!=4)){
        printf("Usage: %s [-h/-t threshhold] imageFileRead imageFileSave\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if(t==1){
        if(thresh>255 || thresh<0){
            printf("Value of argument -t has to be between 0 and 255\n");
        }
        printf("Loading image from %s \n", argv[3]);
        GRAYIMAGE *gim = load_Gray_from_file(argv[3]);
        BINARYIMAGE *bim = GrayToBinaryThreshold(gim, thresh);
        printf("Saving binary image on %s \n", argv[4]);
        save_Binary_image_to_file(bim, argv[4]);
    }
    else {
        printf("Loading image from %s \n", argv[2]);
        GRAYIMAGE *gim = load_Gray_from_file(argv[2]);
        BINARYIMAGE *bim = GrayToBinaryHistogram(gim);
        printf("Saving binary image on %s \n", argv[3]);
        save_Binary_image_to_file(bim, argv[3]);
    }

    
}