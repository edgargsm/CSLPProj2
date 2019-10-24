#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"


makeWaterMark(RGBIMAGE *im, RGBIMAGE *wtr, int x, int y){

    for (int i = x, i2 = 0 ; i < im->x && i2 < wtr->x; i++, i2++){
        for (int n = y, n2 = 0; n < im->y && n2 < wtr->y; n++, n2++){
            
            unsigned char r1 = im->rgb[i][n].pix[0];
            unsigned char g1 = im->rgb[i][n].pix[1];
            unsigned char b1 = im->rgb[i][n].pix[2];
            unsigned char r2 = wtr->rgb[i2][n2].pix[0];
            unsigned char g2 = wtr->rgb[i2][n2].pix[1];
            unsigned char b2 = wtr->rgb[i2][n2].pix[2];

            printf("%u %u %u\n", r2,g2,b2);
            if ((unsigned char)255 != r2 || (unsigned char)255 != g2 || (unsigned char)255 != b2 ){
                for (int p = 0; p<3; p++)
                    im->rgb[i][n].pix[p] = (unsigned char) ((im->rgb[i][n].pix[p]+wtr->rgb[i2][n2].pix[p]) / 2);
            }
        }
    }

}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
        return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}


int main(int argc, char *argv[]){


    if(argc!=6 || isNumeric(argv[4])==0 || atoi(argv[5])<0){
        printf("Usage: %s [imageSrc] [imageWaterMark] [imageOut] [Coord:X] [Coord:Y]\nX,Y have to be positive integers.\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    RGBIMAGE *im = load_RGB_from_file(argv[1]);
    RGBIMAGE *wtr = load_RGB_from_file(argv[2]);
    
    makeWaterMark(im, wtr, atoi(argv[4]), atoi(argv[5]));

    /*RGBIMAGE *sharp = calloc(1, sizeof(RGBIMAGE));
    sharp->rgb = allocMemRGB(50,50);
    for (int i = 0; i < 50; i++){
        for (int n = 0; n < 50; n++){
            for (int p = 0; p<3; p++){
                sharp->rgb[i][n].pix[p] = (unsigned char) 255;
                if (i < 30 && i > 20)
                    sharp->rgb[i][n].pix[p] = (unsigned char) 0;
            }
        }   
    }
    sharp->type = "P6";
    sharp->x=50;
    sharp->y=50;
    sharp->gama=255;
    save_RGB_image_to_file(sharp, "water.ppm");*/



    save_RGB_image_to_file(im, argv[3]);
}