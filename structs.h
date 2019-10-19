

typedef struct{
    unsigned char pix[3];
}RgbPixel;

typedef struct{
    unsigned char pix;
}GrayPixel;

typedef struct {
    RgbPixel **rgb;
    int **gray;
    int **bin;
}image;

typedef struct {
    RgbPixel **rgb;
    char *type;
    int x;
    int y;
    char *gama;

}RGBIMAGE;
