
///
///Estrutura utilizada para representar um pixel de uma imagem RGB
///
typedef struct{
    unsigned char pix[3];
}RgbPixel;
///
///Estrutura utilizada para representar um pixel de uma imagem Grayscale
///
typedef struct{
    unsigned char pix;
}GrayPixel;
///
///Estrutura utilizada para representar um pixel de uma imagem binária
///
typedef struct{
    unsigned char pix;
}BitPixel;
///
///Estrutura utilizada para representar uma imagem RGB, com o seu tipo(P6),nº de linhas(x) e colunas(y)
/// e a gama de representação de cada pixel(255)
///Foi utilizado um array bidimensional de pixeis para facilitar o acesso a pixeis individuais.
///
typedef struct {
    RgbPixel **rgb;
    char *type;
    int x;
    int y;
    int gama;
}RGBIMAGE;
///
///Estrutura utilizada para representar uma imagem Grayscale, com o seu tipo(P5),nº de linhas(x) e colunas(y)
/// e a gama de representação de cada pixel(255)
///Foi utilizado um array bidimensional de pixeis para facilitar o acesso a pixeis individuais.
///
typedef struct {
    GrayPixel **gray;
    char *type;
    int x;
    int y;
    int gama;
}GRAYIMAGE;
///
///Estrutura utilizada para representar uma imagem binária, com o seu tipo(P4),nº de linhas(x) e colunas(y)
/// e a gama de representação de cada pixel(1)
///Foi utilizado um array bidimensional de pixeis para facilitar o acesso a pixeis individuais.
///Os valores dos pixeis binários são 0 / 1 para facilitar a a escrita da imagem em um ficheiro.
///Desta forma para escrever em um ficheiro byte a byte é necessário fazer um 'ou' do byte com um shift left do valor do pixel. E depois escrever o byte no ficheiro.
///
typedef struct {
    BitPixel **bits;
    char *type;
    int x;
    int y;
    int gama;
}BINARYIMAGE;
///
///Função utilizada para alocar memória para o array de pixeis para uma imagem RGB
///
RgbPixel **allocMemRGB(int x, int y){
    RgbPixel **c = (RgbPixel **)calloc(x,sizeof(RgbPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (RgbPixel *)calloc(y, sizeof(RgbPixel));
    }
    return c;
}
///
///Função utilizada para alocar memória para o array de pixeis para uma imagem Grayscale
///
GrayPixel **allocMemGray(int x, int y){
    GrayPixel **c = (GrayPixel **)calloc(x,sizeof(GrayPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (GrayPixel *)calloc(y, sizeof(GrayPixel));
    }
    return c;
}
///
///Função utilizada para alocar memória para o array de pixeis para uma imagem binária
///
BitPixel **allocMemBit(int x, int y){
    BitPixel **c = (BitPixel **)calloc(x,sizeof(BitPixel *));       //alloc matrix
    for(int i = 0; i<x; i++){
        c[i] = (BitPixel *)calloc(y, sizeof(BitPixel));
    }
    return c;
}
///
///Função utilizada para carregar uma imagem RGB para uma estrutura de dados apartir de um ficheiro
///
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
///
///Função utilizada para carregar uma imagem Grayscale para uma estrutura de dados apartir de um ficheiro
///
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
///
///Função utilizada para carregar uma imagem binária para uma estrutura de dados apartir de um ficheiro
///
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
///
///Função utilizada para escrever em um ficheiro uma imagem RGB presente em uma estrutura de dados 
///
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
///
///Função utilizada para escrever em um ficheiro uma imagem Grayscale presente em uma estrutura de dados 
///
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
///
///Função utilizada para escrever em um ficheiro uma imagem binária presente em uma estrutura de dados 
///
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
///
///Devolve o pixel de uma imagem RGB presente na linha 'x' e coluna 'y'
///
RgbPixel getRGBPixel(RGBIMAGE *im, int x, int y){
    return im->rgb[x][y];
}
///
///Devolve o pixel de uma imagem Grayscale presente na linha 'x' e coluna 'y'
///
GrayPixel getGrayPixel(GRAYIMAGE *im, int x, int y){
    return im->gray[x][y];
}
///
///Devolve o pixel de uma imagem binária presente na linha 'x' e coluna 'y'
///
BitPixel getBitPixel(BINARYIMAGE *im, int x, int y){
    return im->bits[x][y];
}
