#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"

void IncreaseIntensityRGB(RGBIMAGE *im, int mult) {

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                if(im->rgb[i][n].pix[p]*mult<=255){
                    im->rgb[i][n].pix[p] = (unsigned char) (im->rgb[i][n].pix[p]*mult);
                    //printf("%d\n",(unsigned char)(im->rgb[i][n].pix[p]));
                    //printf("%d\n",(unsigned char)(im->rgb[i][n].pix[p]*mult));
                }
                else {
                    im->rgb[i][n].pix[p] = (unsigned char) (255);
                }
            }
        }
    }
}

void DecreaseIntensityRGB(RGBIMAGE *im, int mult) {

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                im->rgb[i][n].pix[p] = (unsigned char) (im->rgb[i][n].pix[p]/mult);
                //printf("%d\n",(unsigned char)(c[i][n][p]));
                //printf("%d\n",(unsigned char)(c[i][n][p]/2));
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


int main(int argc, char *argv[]) {

    int flags, opt;

    int i = 0;
    int d = 0;

    while ((opt = getopt(argc, argv, "id")) != -1)
    {
        switch (opt)
        {
            case 'i':
                printf("Increase intensity of RGB image\n");
                i = 1;
                break;
            case 'd':
                printf("Decrease intensity of RGB image\n");
                d = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-d/-i] multiplier imageFileRead imageFileSave\nMultiplier has to be a positive integer./n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }


    if(argc!=5 || isNumeric(argv[2])==0 || atoi(argv[2])<0){
        printf("Usage: %s [-d/-i] multiplier imageFileRead imageFileSave\nMultiplier has to be a positive integer.\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    int mult = atoi(argv[2]);

    RGBIMAGE *im = load_RGB_from_file(argv[3]);

    if(i==1){
        //printf("Increse\n");
        IncreaseIntensityRGB(im, mult);
    }
    else if(d==1){
        DecreaseIntensityRGB(im, mult);
    }

    save_RGB_image_to_file(im, argv[4]);


}