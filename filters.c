#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
///
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

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
                int v = 0;
                int count = 0;
                if(i!=0 && n!=0){
                    v = v + (kernel[0][0]*im->gray[i-1][n-1].pix);
                    count++;
                }
                if(i!=0){
                    v = v + (kernel[0][1]*im->gray[i-1][n].pix);
                    count++;
                }
                if(i!=0 && n!=im->y-1){
                    v = v + (kernel[0][2]*im->gray[i-1][n+1].pix);
                    count++;
                }
                if(n!=0){
                    v = v + (kernel[1][0]*im->gray[i][n-1].pix);
                    count++;
                }
                v = v + (kernel[1][1]*im->gray[i][n].pix);
                count++;
                if(n!=im->y-1){
                    v = v + (kernel[1][2]*im->gray[i][n+1].pix);
                    count++;
                }
                if(i!=im->x-1 && n!=0){
                    v = v + (kernel[2][0]*im->gray[i+1][n-1].pix);
                    count++;
                }
                if(i!=im->x-1){
                    v = v + (kernel[2][1]*im->gray[i+1][n].pix);
                    count++;
                }
                if(i!=im->x-1 && n!=im->y-1){
                    v = v + (kernel[2][2]*im->gray[i+1][n+1].pix);
                    count++;
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
    
    RGBIMAGE *sharp = calloc(1, sizeof(GRAYIMAGE));

    sharp->type = im->type;
    sharp->x = im->x;
    sharp->y = im->y;
    sharp->gama = im->gama;

    sharp->rgb = allocMemRGB(im->x,im->y);

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                int v = 0;
                int count = 0;
                if(i!=0 && n!=0){
                    v = v + (kernel[0][0]*im->rgb[i-1][n-1].pix[p]);
                    count++;
                }
                if(i!=0){
                    v = v + (kernel[0][1]*im->rgb[i-1][n].pix[p]);
                    count++;
                }
                if(i!=0 && n!=im->y-1){
                    v = v + (kernel[0][2]*im->rgb[i-1][n+1].pix[p]);
                    count++;
                }
                if(n!=0){
                    v = v + (kernel[1][0]*im->rgb[i][n-1].pix[p]);
                    count++;
                }
                v = v + (kernel[1][1]*im->rgb[i][n].pix[p]);
                count++;
                if(n!=im->y-1){
                    v = v + (kernel[1][2]*im->rgb[i][n+1].pix[p]);
                    count++;
                }
                if(i!=im->x-1 && n!=0){
                    v = v + (kernel[2][0]*im->rgb[i+1][n-1].pix[p]);
                    count++;
                }
                if(i!=im->x-1){
                    v = v + (kernel[2][1]*im->rgb[i+1][n].pix[p]);
                    count++;
                }
                if(i!=im->x-1 && n!=im->y-1){
                    v = v + (kernel[2][2]*im->rgb[i+1][n+1].pix[p]);
                    count++;
                }
                if(v<0){
                    v = -1*v;
                }
                /*if(gray[i][n]==0){
                    v = v/8;
                }*/
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
///Este programa aplica filtros a imagens RGB.
///Ele pode ser utilizado da seguinte forma: ./filters [-s/-e] inputFile outputFile
///Se a opção -s for utilizada o output vai ser de uma imagem RGB originária da aplicação do filtro 'sharpen' sobre a imagem de input.
///E se a opção -e for utilizada o output vai ser uma imagem GrayScale originária da aplicação do filtro 'edge detection' sobre a imagem de input.
///Este programa contém um bug que nós não conseguimos resolver em que apenas imagens com dimensões quadradas podem ser filtradas.
///Quando é utilizada uma imagem com outras dimensões o output não é o correto de aplicação do filtro.
///Imagens com que funciona : lena.ppm, peppers.ppm, airplane.ppm, house.ppm, boat.ppm, baboon.ppm
///Imagens com que não funciona : bike3.ppm, anemone.ppm, monarch.ppm, arial.ppm
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