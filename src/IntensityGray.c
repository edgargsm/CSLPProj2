#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"

void IncreaseIntensityGray(GRAYIMAGE *im, int mult) {

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            if(im->gray[i][n].pix*mult<=255){
                im->gray[i][n].pix = (unsigned char) (im->gray[i][n].pix*mult);
                //printf("%d\n",(unsigned char)(im->rgb[i][n].pix[p]));
                //printf("%d\n",(unsigned char)(im->rgb[i][n].pix[p]*mult));
            }
            else {
                im->gray[i][n].pix = (unsigned char) (255);
            }
        }
    }
}

void DecreaseIntensityGray(GRAYIMAGE *im, int mult) {

    for(int i = 0; i<im->x; i++){ //Line
        for(int n = 0; n<im->y; n++){ //Column
            im->gray[i][n].pix = (unsigned char) (im->gray[i][n].pix/mult);
            //printf("%d\n",(unsigned char)(c[i][n][p]));
            //printf("%d\n",(unsigned char)(c[i][n][p]/2));
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
                printf("Increase intensity of Grayscale image\n");
                i = 1;
                break;
            case 'd':
                printf("Decrease intensity of Grayscale image\n");
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

    GRAYIMAGE *im = load_Gray_from_file(argv[3]);

    if(i==1){
        //printf("Increse\n");
        IncreaseIntensityGray(im, mult);
    }
    else if(d==1){
        DecreaseIntensityGray(im, mult);
    }

    save_Gray_image_to_file(im, argv[4]);

    /*FILE *f = fopen("writefGrayScale.pgm", "rb");
    char *type = calloc(5, sizeof(char));
    char *dim = calloc(50, sizeof(char));
    int x;
    int y;
    char *num = calloc(5, sizeof(char));
    int gama;
    
    if(f == NULL){
      printf("Error!");
      exit(1);
    }
    fgets(type, 5, f);
    fgets(dim, 50, f);
    fgets(num, 5, f);
    x = atoi(strtok(dim, " "));
    y = atoi(strtok(NULL, " "));
    gama = atoi(num);

    unsigned char **gray = (unsigned char **)calloc(x,sizeof(unsigned char *));
    for(int i = 0; i<x; i++){
        gray[i] = (unsigned char*)calloc(y, sizeof(unsigned char));
    }

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            fread(&gray[i][n], sizeof(unsigned char), 1, f);
        }
    }

    printf("Description: type %s   -- dim %d %d   -- num %d   --\n",strtok(type, "\n"), x, y, gama);
    

    
    FILE *wf = fopen("increasedIntensityGray.pgm", "wb");
    fprintf(wf, "P5\n%d %d\n%d\n", x, y, gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            if(gray[i][n]*2<=255){
                gray[i][n] = (unsigned char) (gray[i][n]*2);
                printf("%d\n",(unsigned char)(gray[i][n]));
                printf("%d\n",(unsigned char)(gray[i][n]*2));
            }
            else {
                gray[i][n] = (unsigned char) (255);
            }
            fwrite(&gray[i][n], sizeof(unsigned char), 1, wf);
        }
    }
    

    fclose(wf);*/

}