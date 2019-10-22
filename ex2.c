#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
RGBIMAGE im;


RgbPixel **allocMem(int x, int y){

    RgbPixel **c = (RgbPixel **)calloc(x,sizeof(RgbPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (RgbPixel *)calloc(y, sizeof(RgbPixel));
    }

    return c;
}

RGBIMAGE *load_from_file(char *name){
    FILE *f = fopen(name, "rb");

    if(f == NULL){
      printf("Error! \n");
      exit(1);
    }

    char *type = calloc(5, sizeof(char));       //image type (rgb, grayscale ...)
    char *dim = calloc(50, sizeof(char));       //image dimensions
    char *num = calloc(5, sizeof(char));        //pixel value gama (0-255)

    fgets(type, 5, f);
    fgets(dim, 50, f);
    fgets(num, 5, f);
    int x = atoi(strtok(dim, " "));
    int y = atoi(strtok(NULL, " "));
    int gama = atoi(num);

    im.type = type;
    im.x = x;
    im.y = y;
    im.gama = gama;
    
    im.rgb = allocMem(x,y);


    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                fread(&im.rgb[i][n].pix[p], sizeof(unsigned char), 1, f);
            }
        }
    }
    fclose(f);

    return &im;
}

void save_image_to_file(RGBIMAGE *im, char *name){
    FILE *wf = fopen("lena2.ppm", "wb");

    int x = im->x;
    int y = im->y;
    strtok(im->type, "\n");

    fprintf(wf, "%s\n%d %d\n%d\n", im->type, x, y, im->gama);
    //printf("%s\n%d %d\n%d\n", im->type, x, y, im->gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                //printf("%u,", im->rgb[i][n].pix[p]);
                fwrite(&(im->rgb[i][n].pix[p]), sizeof(unsigned char), 1, wf);
            }
            //printf("   ");
        }
        //printf("\n");
    }

    fclose(wf);
}

RgbPixel get_pixel(RGBIMAGE *im, int x, int y){
    if (x <= im->x && y <= im->y){
        return im->rgb[x][y];
    }
}

void set_pixel(RGBIMAGE *im, int x, int y, RgbPixel value){
    if (x <= im->x && y <= im->y){
        im->rgb[x][y] = value;
    }
}




int main() {

    RGBIMAGE *im = load_from_file("lena.ppm");
    RgbPixel p = get_pixel(im, 10, 10);

    for(int x = 50 ; x < 400; x++){
        for(int y = 50 ; y< 400; y++){
            set_pixel(im, x, y, p);
        }
    }
    save_image_to_file(im, "lena2.ppm");
}