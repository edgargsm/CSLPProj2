

typedef struct{
    unsigned char pix[3];
}RgbPixel;

typedef struct{
    unsigned char pix;
}GrayPixel;

typedef struct{
    unsigned char pix;
}BitPixel;

typedef struct {
    RgbPixel **rgb;
    char *type;
    int x;
    int y;
    int gama;

}RGBIMAGE;

typedef struct {
    GrayPixel **gray;
    char *type;
    int x;
    int y;
    int gama;

}GRAYIMAGE;

typedef struct {
    BitPixel **bits;
    char *type;
    int x;
    int y;
    int gama;
}BINARYIMAGE;

RgbPixel **allocMemRGB(int x, int y){

    RgbPixel **c = (RgbPixel **)calloc(x,sizeof(RgbPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (RgbPixel *)calloc(y, sizeof(RgbPixel));
    }

    return c;
}

GrayPixel **allocMemGray(int x, int y){

    GrayPixel **c = (GrayPixel **)calloc(x,sizeof(GrayPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (GrayPixel *)calloc(y, sizeof(GrayPixel));
    }

    return c;
}

BitPixel **allocMemBit(int x, int y){

    BitPixel **c = (BitPixel **)calloc(x,sizeof(BitPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (BitPixel *)calloc(y, sizeof(BitPixel));
    }

    return c;
}

RGBIMAGE *load_RGB_from_file(char *name){
    FILE *f = fopen(name, "rb");

    if(f == NULL){
      printf("Error opening file %s! \n", name);
      exit(1);
    }

    RGBIMAGE *im = calloc(1, sizeof(RGBIMAGE));

    char *type = calloc(5, sizeof(char));       //image type (rgb, grayscale ...)
    char *dim = calloc(50, sizeof(char));       //image dimensions
    char *num = calloc(5, sizeof(char));        //pixel value gama (0-255)

    fgets(type, 5, f);
    fgets(dim, 50, f);
    fgets(num, 5, f);
    int x = atoi(strtok(dim, " "));
    int y = atoi(strtok(NULL, " "));
    int gama = atoi(num);

    im->type = type;
    im->x = x;
    im->y = y;
    im->gama = gama;
    
    im->rgb = allocMemRGB(x,y);


    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            for(int p = 0; p<3; p++){ //Red, Green, Blue
                fread(&im->rgb[i][n].pix[p], sizeof(unsigned char), 1, f);
            }
        }
    }
    fclose(f);

    return im;
}

GRAYIMAGE *load_Gray_from_file(char *name){
    FILE *f = fopen(name, "rb");

    if(f == NULL){
      printf("Error opening file %s! \n", name);
      exit(1);
    }

    GRAYIMAGE *im = calloc(1, sizeof(GRAYIMAGE));

    char *type = calloc(5, sizeof(char));       //image type (rgb, grayscale ...)
    char *dim = calloc(50, sizeof(char));       //image dimensions
    char *num = calloc(5, sizeof(char));        //pixel value gama (0-255)

    fgets(type, 5, f);
    fgets(dim, 50, f);
    fgets(num, 5, f);
    int x = atoi(strtok(dim, " "));
    int y = atoi(strtok(NULL, " "));
    int gama = atoi(num);

    im->type = type;
    im->x = x;
    im->y = y;
    im->gama = gama;
    
    im->gray = allocMemGray(x,y);


    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            fread(&im->gray[i][n].pix, sizeof(unsigned char), 1, f);
        }
    }
    fclose(f);

    return im;
}

BINARYIMAGE *load_Binary_from_file(char *name){
    FILE *f = fopen(name, "rb");

    if(f == NULL){
      printf("Error opening file %s! \n", name);
      exit(1);
    }

    BINARYIMAGE *im = calloc(1, sizeof(BINARYIMAGE));

    char *type = calloc(5, sizeof(char));       //image type (rgb, grayscale ...)
    char *dim = calloc(50, sizeof(char));       //image dimensions
    char *num = calloc(5, sizeof(char));        //pixel value gama (0-255)

    fgets(type, 5, f);
    fgets(dim, 50, f);
    fgets(num, 5, f);
    int x = atoi(strtok(dim, " "));
    int y = atoi(strtok(NULL, " "));
    int gama = atoi(num);

    im->type = type;
    im->x = x;
    im->y = y;
    im->gama = gama;
    
    im->bits = allocMemBit(x,y);
    int i = 0;
    int n = 0;
    while (!feof(f)){  
        unsigned char c;
        fread(&c, sizeof(unsigned char), 1, f);
        for(int p = 7; p>=0; p--){
            if((c | 1 << p) == c){
                im->bits[i][n].pix=(unsigned char)1;
            }
            else {
                im->bits[i][n].pix=(unsigned char)0;
            }
            if(n==y-1){
                i++;
                n = 0;
            }
            else {
                n++;
            }
            if(i==x-1){
                break;
            }
        }
    
    }
    fclose(f);
    return im;
}


void save_RGB_image_to_file(RGBIMAGE *im, char *name){
    FILE *wf = fopen(name, "wb");

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

void save_Gray_image_to_file(GRAYIMAGE *im, char *name){
    FILE *wf = fopen(name, "wb");

    int x = im->x;
    int y = im->y;
    strtok(im->type, "\n");

    fprintf(wf, "%s\n%d %d\n%d\n", im->type, x, y, im->gama);

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            fwrite(&(im->gray[i][n].pix), sizeof(unsigned char), 1, wf);
        }
    }
    fclose(wf);

}

void save_Binary_image_to_file(BINARYIMAGE *im, char *name){
    FILE *wf = fopen(name, "wb");

    int x = im->x;
    int y = im->y;
    strtok(im->type, "\n");

    fprintf(wf, "%s\n%d %d\n%d\n", im->type, x, y, im->gama);
    //printf("%s\n%d %d\n%d\n", im->type, x, y, im->gama);

    int count = 7;
    unsigned char c = 0;

    for(int i = 0; i<x; i++){ //Line
        for(int n = 0; n<y; n++){ //Column
            c = c | im->bits[i][n].pix<<count;
            count--;
            if(count==-1){
                count=7;
                fwrite(&c, 1, 1, wf);
                c=0;
            }
        }
    }
    fclose(wf);
}

RgbPixel getRGBPixel(RGBIMAGE *im, int x, int y){
    return im->rgb[x][y];
}

GrayPixel getGrayPixel(GRAYIMAGE *im, int x, int y){
    return im->gray[x][y];
}

BitPixel getBitPixel(BINARYIMAGE *im, int x, int y){
    return im->bits[x][y];
}
