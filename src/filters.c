#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

// Compilar com comando : cc -Wall -O2 -std=c99 program.c -o example -lm

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