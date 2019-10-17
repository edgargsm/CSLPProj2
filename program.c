#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

// Compilar com comando : cc -Wall -O2 -std=c99 program.c -o example -lm

int main() {

    FILE *f = fopen("peppers.ppm", "rb");
    char *type = calloc(5, sizeof(char));
    char *dim = calloc(50, sizeof(char));
    int x;
    int y;
    char *num = calloc(5, sizeof(char));
    int gama;
    
    
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
    int ***c = (int ***)calloc(x,sizeof(int *));
    for(int i = 0; i<x; i++){
        c[i] = (int **)calloc(y, sizeof(int *));
    }

    for(int i = 0; i<x; i++){
        for(int n = 0; n<y; n++){
            c[i][n] = calloc(3, sizeof(int));
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

    //fread( c, sizeof(char), 100, f);
    printf("Description: type %s   -- dim %d %d   -- num %d   --\n",strtok(type, "\n"), x, y, gama);
    //printf("First row:\n");

    /*for(int p = 0; p<3; p++){
        for(int i = 0; i<x; i++){
            for(int n = 0; n<y; n++){
                printf("%d,", c[i][n][p]);
            }
            printf("\n");
        }
        printf("\n\n");
    }*/

    fclose(f);

    FILE *wf = fopen("writef.ppm", "wb");
    
    //fprintf(wf, "P6\n512 512\n255\n");
    fprintf(wf, "%s\n%d %d\n%d\n", type, x, y, gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                //c[i][n][p] = 1;
                //c[i][n][p] = 0;
                fwrite(&c[i][n][p], sizeof(unsigned char), 1, wf);
            }
        }
    }

    fclose(wf);

}