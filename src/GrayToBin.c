#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"

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

    /*FILE *f = fopen("writefGrayScale.pgm", "rb");
    int thresh = 122;
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
    
    FILE *wf = fopen("writefBinary.pbm", "wb");
    fprintf(wf, "P4\n%d %d\n1\n", x, y);

    int count = 7;
    unsigned char c = 0;
    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            if(gray[i][n]<=thresh){ //write 1
                c = c | 1<<count;
                count--;
            }
            else { //write 0
                count--;
            }
            if(count==-1){
                count=7;
                fwrite(&c, 1, 1, wf);
                c=0;
            }
        }
    }
    if(count!=7){
        fwrite(&c, sizeof(unsigned char), 1, wf);
    }

    fclose(wf);*/

}