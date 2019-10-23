#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"


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
    /*RGBIMAGE *im = load_RGB_from_file("lena.ppm");
    GRAYIMAGE *gim = RGBToGray(im);
    save_Gray_image_to_file(gim, "writefGrayScale.pgm");


    /*FILE *f = fopen("lena.ppm", "rb");
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
    unsigned char ***c = (unsigned char ***)calloc(x,sizeof(unsigned char *));
    for(int i = 0; i<x; i++){
        c[i] = (unsigned char **)calloc(y, sizeof(unsigned char *));
    }

    for(int i = 0; i<x; i++){
        for(int n = 0; n<y; n++){
            c[i][n] = calloc(3, sizeof(unsigned char));
        }
    }

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                fread(&c[i][n][p], sizeof(unsigned char), 1, f);
            }
        }
    }
    fclose(f);

    printf("Description: type %s   -- dim %d %d   -- num %d   --\n",strtok(type, "\n"), x, y, gama);
    //Type for grayscale image : P5
    unsigned char **gray = (unsigned char**)calloc(x, sizeof(unsigned char*));
    for(int i = 0; i<x; i++){
        gray[i] = (unsigned char*)calloc(y, sizeof(unsigned char));
    }

    for(int i = 0; i<x; i++){
        for(int n = 0; n<y; n++){
            int g = (c[i][n][0] *0.33) + (c[i][n][1] *0.59) + (c[i][n][2] *0.11);
            if(g>255){
                gray[i][n] = 255;
            }
            else{
                gray[i][n] = (unsigned char) g;
            }
        }
    }

    
    FILE *wf = fopen("writefGrayScale.pgm", "wb");
    fprintf(wf, "P5\n%d %d\n%d\n", x, y, gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            fwrite(&gray[i][n], sizeof(unsigned char), 1, wf);
        }
    }
    fclose(wf);

    /*
    FILE *wf1 = fopen("writefGrayScaleR.pgm", "wb");
    FILE *wf2 = fopen("writefGrayScaleG.pgm", "wb");
    FILE *wf3 = fopen("writefGrayScaleB.pgm", "wb");
    fprintf(wf1, "P5\n%d %d\n%d\n", x, y, gama);
    fprintf(wf2, "P5\n%d %d\n%d\n", x, y, gama);
    fprintf(wf3, "P5\n%d %d\n%d\n", x, y, gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            fwrite(&c[i][n][0], sizeof(unsigned char), 1, wf1);
            fwrite(&c[i][n][1], sizeof(unsigned char), 1, wf2);
            fwrite(&c[i][n][2], sizeof(unsigned char), 1, wf3);
        }
    }
    fclose(wf1);
    fclose(wf2);
    fclose(wf3);*/


}