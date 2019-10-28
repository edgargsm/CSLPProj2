#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

///
///Função utilizada para converter uma imagem RGB(dada como argumento)
///em uma imagem Grayscale em que se calcula o valor de cada pixel através do valor
///dos pixeis de todos os canais da imagem RGB.
///
GRAYIMAGE *RGBToGray(RGBIMAGE *im){
    GRAYIMAGE *gim = calloc(1, sizeof(GRAYIMAGE));

    gim->type = "P5";
    gim->x = im->x;
    gim->y = im->y;
    gim->gama = im->gama;

    gim->gray = allocMemGray(gim->x,gim->y);

    for(int i = 0; i<gim->x; i++){ //Line
        for(int n = 0; n<gim->y; n++){ //Column
            int g = (im->rgb[i][n].pix[0] *0.33) + (im->rgb[i][n].pix[1] *0.59) + (im->rgb[i][n].pix[2] *0.11);
            if(g>255){
                gim->gray[i][n].pix = 255;
            }
            else{
                gim->gray[i][n].pix = (unsigned char) g;
            }
        }
    }
    return gim;
}
///
///Função utilizada para converter uma imagem RGB(dada como argumento)
///em uma imagem Grayscale em que o valor do pixel é dado pelo valor do mesmo pixel
///do canal vermelho da imagem RGB.
//
GRAYIMAGE *RGBRedToGray(RGBIMAGE *im){
    GRAYIMAGE *gim = calloc(1, sizeof(GRAYIMAGE));

    gim->type = "P5";
    gim->x = im->x;
    gim->y = im->y;
    gim->gama = im->gama;

    gim->gray = allocMemGray(gim->x,gim->y);

    for(int i = 0; i<gim->x; i++){ //Line
        for(int n = 0; n<gim->y; n++){ //Column
            gim->gray[i][n].pix = im->rgb[i][n].pix[0];
        }
    }
    return gim;
}
///
///Função utilizada para converter uma imagem RGB(dada como argumento)
///em uma imagem Grayscale em que o valor do pixel é dado pelo valor do mesmo pixel
///do canal verde da imagem RGB.
//
GRAYIMAGE *RGBGreenToGray(RGBIMAGE *im){
    GRAYIMAGE *gim = calloc(1, sizeof(GRAYIMAGE));

    gim->type = "P5";
    gim->x = im->x;
    gim->y = im->y;
    gim->gama = im->gama;

    gim->gray = allocMemGray(gim->x,gim->y);

    for(int i = 0; i<gim->x; i++){ //Line
        for(int n = 0; n<gim->y; n++){ //Column
            gim->gray[i][n].pix = im->rgb[i][n].pix[1];
        }
    }
    return gim;
}
///
///Função utilizada para converter uma imagem RGB(dada como argumento)
///em uma imagem Grayscale em que o valor do pixel é dado pelo valor do mesmo pixel
///do canal azul da imagem RGB.
//
GRAYIMAGE *RGBBlueToGray(RGBIMAGE *im){
    GRAYIMAGE *gim = calloc(1, sizeof(GRAYIMAGE));

    gim->type = "P5";
    gim->x = im->x;
    gim->y = im->y;
    gim->gama = im->gama;

    gim->gray = allocMemGray(gim->x,gim->y);

    for(int i = 0; i<gim->x; i++){ //Line
        for(int n = 0; n<gim->y; n++){ //Column
            gim->gray[i][n].pix = im->rgb[i][n].pix[2];
        }
    }
    return gim;
}

///
///Este programa converte uma imagem RGB em uma ou mais imagens Grayscale.
///No caso de não serem utilizadas quaisquer opções na execução do programa
///é necessário passar como argumentos os nomes dos ficheiros com a imagem a converter
///e onde se vai escrever a imagem convertida.(Ex: ./RGBToGray fileToConvert outputFile)
///Se for utilizada a opção -s é necessário passar como argumento 4 ficheiros.
///O que vai ser convertido e 3 ficheiros onde vão ser guardadas as conversões de grayscale
///de cada um dos canais da imagem original(Red, Green e Blue). (Ex: ./RGBToGray fileToConvert outputFileRed outputFileGreen outputFileBlue) 
///
int main(int argc, char *argv[]) {

    int flags, opt;

    int s = 0;

    while ((opt = getopt(argc, argv, "s")) != -1)
    {
        switch (opt)
        {
            case 's':
                printf("Split RGB into 3 grayscale images (one for each channel)\n");
                s = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-s] imageFileRead imageFileSave ...\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    if (s==1){
        if(argc!=6){
            printf("Não foi introduzido o número correto de argumentos.\nUtilização para geração de três imagens grayscale:\n");
            printf("%s -s imgToRead imgToSaveR imgToSaveG imgToSaveB\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        printf("Loading image from %s \n", argv[2]);
        RGBIMAGE *im = load_RGB_from_file(argv[2]);
        GRAYIMAGE *gimR = RGBRedToGray(im);
        GRAYIMAGE *gimG = RGBGreenToGray(im);
        GRAYIMAGE *gimB = RGBBlueToGray(im);
        printf("Saving red image channel grayscale image on %s \n", argv[3]);
        save_Gray_image_to_file(gimR, argv[3]);
        printf("Saving green image channel grayscale image on %s \n", argv[4]);
        save_Gray_image_to_file(gimG, argv[4]);
        printf("Saving blue image channel grayscale image on %s \n", argv[5]);
        save_Gray_image_to_file(gimB, argv[5]);

    }
    else {
        if(argc!=3){
            printf("Não foi introduzido o número correto de argumentos.\nUtilização para geração de uma imagem grayscale:\n");
            printf("%s imgToRead imgToSave\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        printf("Loading image from %s \n", argv[1]);
        RGBIMAGE *im = load_RGB_from_file(argv[1]);
        GRAYIMAGE *gim = RGBToGray(im);
        printf("Saving grayscale image on %s \n", argv[2]);
        save_Gray_image_to_file(gim, argv[2]);

    }

    return 0;
    
}