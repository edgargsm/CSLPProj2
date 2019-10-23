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

    /*FILE *f = fopen("lena.ppm", "rb");
    char *type = calloc(5, sizeof(char));
    char *dim = calloc(50, sizeof(char));
    int x;
    int y;
    char *num = calloc(5, sizeof(char));
    int gama;
    int kernel[3][3] = {{-1,-1,-1},
                        {-1, 8,-1},
                        {-1,-1,-1}};
    
    //int **im = (int *) calloc();

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
                //c[i][n][p] = 1;
                //c[i][n][p] = 0;
                fread(&c[i][n][p], sizeof(unsigned char), 1, f);
            }
        }
    }

    fclose(f);

    //fread( c, sizeof(char), 100, f);
    printf("Description: type %s   -- dim %d %d   -- num %d   --\n",strtok(type, "\n"), x, y, gama);
    
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
    

    FILE *wf = fopen("edgeOutput.pgm", "wb");
    
    //fprintf(wf, "P6\n512 512\n255\n");
    fprintf(wf, "P5\n%d %d\n%d\n", x, y, gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
                int v = 0;
                int count = 0;
                if(i!=0 && n!=0){
                    v = v + (kernel[0][0]*gray[i-1][n-1]);
                    count++;
                }
                if(i!=0){
                    v = v + (kernel[0][1]*gray[i-1][n]);
                    count++;
                }
                if(i!=0 && n!=y-1){
                    v = v + (kernel[0][2]*gray[i-1][n+1]);
                    count++;
                }
                if(n!=0){
                    v = v + (kernel[1][0]*gray[i][n-1]);
                    count++;
                }
                v = v + (kernel[1][1]*gray[i][n]);
                count++;
                if(n!=y-1){
                    v = v + (kernel[1][2]*gray[i][n+1]);
                    count++;
                }
                if(i!=x-1 && n!=0){
                    v = v + (kernel[2][0]*gray[i+1][n-1]);
                    count++;
                }
                if(i!=x-1){
                    v = v + (kernel[2][1]*gray[i+1][n]);
                    count++;
                }
                if(i!=x-1 && n!=y-1){
                    v = v + (kernel[2][2]*gray[i+1][n+1]);
                    count++;
                }
                if(v<0){
                    v = -1*v;
                }
                
                if(v>255){
                    v = 255;
                }
                unsigned char ch = (unsigned char) (v);
                fwrite(&ch, sizeof(unsigned char), 1, wf);
        }
    }

    fclose(wf);*/

}