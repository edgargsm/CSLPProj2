#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convertions.h"

///@file

/// Função utilizada para aplicar o filtro de edge detection a uma imagem GrayScale.
/// Este filtro foi aplicado de acordo com um kernel que está definido dentro da função
///
GRAYIMAGE *edgeDetection(GRAYIMAGE *im){
    int kernel[3][3] = {{-1,-1,-1},
                        {-1, 8,-1},
                        {-1,-1,-1}};

    GRAYIMAGE *edge = calloc(1, sizeof(GRAYIMAGE));

    edge->type = im->type;
    edge->x = im->x;
    edge->y = im->y;
    edge->gama = im->gama;

    edge->gray = allocMemGray(im->x,im->y);

    int v;
    for(int i = 1; i<im->x-1; i++){ //Line
        for(int n = 1; n<im->y-1; n++){ //Column
                v = 0;

                for(int i2 = 0; i2<3; i2++){
                    for(int n2 = 0; n2<3; n2++){
                        v = v + (kernel[i2][n2]*im->gray[i-1+i2][n-1+n2].pix);
                    }
                }

                if(v<0){
                    v = -1*v;
                }
                if(v>255){
                    v = 255;
                }
                unsigned char ch = (unsigned char) (v);
                edge->gray[i][n].pix = ch;
        }
    }
    return edge;
}

///
/// Função utilizada para aplicar um filtro de sharpen a uma imagem RGB.
/// Este filtro foi aplicado de acordo com um kernel que está definido dentro da função
///
RGBIMAGE *SharpenFilter(RGBIMAGE *im){
    int kernel[3][3] = {{0,-1,0},
                        {-1, 5,-1},
                        {0,-1,0}};
    RGBIMAGE *sharp = calloc(1, sizeof(RGBIMAGE));

    sharp->type = im->type;
    sharp->x = im->x;
    sharp->y = im->y;
    sharp->gama = im->gama;

    sharp->rgb = allocMemRGB(im->x,im->y);

    int v;
    for(int i = 1; i<im->x-1; i++){ //Line
        for(int n = 1; n<im->y-1; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                v = 0;

                for(int i2 = 0; i2<3; i2++){
                    for(int n2 = 0; n2<3; n2++){
                        v = v + (kernel[i2][n2]*im->rgb[i-1+i2][n-1+n2].pix[p]);
                    }
                }
    
                if(v<0){
                    v = -1*v;
                }
        
                if(v>255){
                    v = 255;
                }
                unsigned char ch = (unsigned char) (v);
                sharp->rgb[i][n].pix[p] = ch;
            }
        }
    }
    return sharp;
}


///
///Este programa aplica filtros a imagens RGB.\n
///Ele pode ser utilizado da seguinte forma: ./filters [-s/-e] inputFile outputFile\n
///Se a opção -s for utilizada o output vai ser de uma imagem RGB originária da aplicação do filtro 'sharpen' sobre a imagem de input.\n
///E se a opção -e for utilizada o output vai ser uma imagem GrayScale originária da aplicação do filtro 'edge detection' sobre a imagem de input.\n
///Este programa contém um bug que nós não conseguimos resolver em que apenas imagens com dimensões quadradas podem ser filtradas.\n
///Quando é utilizada uma imagem com outras dimensões o output não é o correto de aplicação do filtro.\n
///Imagens com que funciona : lena.ppm, peppers.ppm, airplane.ppm, house.ppm, boat.ppm, baboon.ppm\n
///Imagens com que não funciona : bike3.ppm, anemone.ppm, monarch.ppm, arial.ppm\n
///
int main(int argc, char *argv[]) {

    int flags, opt;

    int s = 0;
    int e = 0;

    while ((opt = getopt(argc, argv, "se")) != -1)
    {
        switch (opt)
        {
            case 's':
                printf("Sharpen Filter\n");
                s = 1;
                break;
            case 'e':
                printf("Edge detection Filter\n");
                e = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-s/-e] imageFileRead imageFileSave \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(argc!=4){
        printf("Usage: %s [-s/-e] imageFileRead imageFileSave \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(e == 1){
        RGBIMAGE *im = load_RGB_from_file(argv[2]);
        GRAYIMAGE *gim = RGBToGray(im);
        GRAYIMAGE *edge = edgeDetection(gim);
        save_Gray_image_to_file(edge, argv[3]);
    }
    else if(s == 1){
        RGBIMAGE *im = load_RGB_from_file(argv[2]);
        RGBIMAGE *sharp = SharpenFilter(im);
        save_RGB_image_to_file(sharp, argv[3]);
    }


}
