#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"
#include <math.h>
///@file
/**
Beginning in (X,Y) pixel from SrcImage and (0,0) pixel from WaterMarkImg (following right and down directions), will substitute
each SrcImage Pixel for an average of the the corresponding pixel from both images.

If the pixel value from the WaterMarkImg is 0 0 0 (Black) the SrcImage pixel will keep his original value (Create water mark with
no background colour)

If the WaterMarkImg has not enought space the program will resize automatically.

*/
void makeWaterMark(RGBIMAGE *im, RGBIMAGE *wtr, int x, int y){
    int xleft = im->x - x;              ///First Calculate the remaining space SrcImage has.
    int yleft = im->y - y;

    double xjump = (double) wtr->x / (double) xleft ;     ///Calculate how many pixels do we have to "jump" each time to fit WaterMarkImg
    double yjump = (double) wtr->y / (double) yleft;

    if (xjump <= 1){      ///If jump is less than 1 don do theese jumps, image fits.
        xjump = 1;
    }
    if (yjump <= 1)
        yjump = 1;
    
    double i2keepingfloat = 0;
    double n2keepingfloat = 0;
    for (int i = x, i2 = 0; i < im->x && i2 < wtr->x; i++,                                              ///Iterate over both images
                                                        i2keepingfloat = i2keepingfloat + xjump,      ///keep iterator with jumps and another (int) to iterate over the image
                                                        i2 = round(i2keepingfloat)){                    ///This is needed because if "jump" if ex: 1.4, the 0.4 will be forgot due to round. The image would not shrink at all.

        for (int n = y, n2 = 0; n < im->y && n2 < wtr->y; n++,
                                                            n2keepingfloat = n2keepingfloat + yjump,
                                                            n2 = round(n2keepingfloat)){

            unsigned char r1 = im->rgb[i][n].pix[0];
            unsigned char g1 = im->rgb[i][n].pix[1];
            unsigned char b1 = im->rgb[i][n].pix[2];
            unsigned char r2 = wtr->rgb[i2][n2].pix[0];
            unsigned char g2 = wtr->rgb[i2][n2].pix[1];
            unsigned char b2 = wtr->rgb[i2][n2].pix[2];

            if ((unsigned char)0 != r2 || (unsigned char)0 != g2 || (unsigned char)0 != b2 ){
                for (int p = 0; p<3; p++)
                    im->rgb[i][n].pix[p] = (unsigned char) ((im->rgb[i][n].pix[p]+wtr->rgb[i2][n2].pix[p]) / 2);
            }

            
        }
        n2keepingfloat = 0;
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

/**
Usage: bin/waterMarker [imageSrc] [imageWaterMark] [imageOut] [Coord:X] [Coord:Y] X,Y have to be positive integers.

Will load imageSrc and imageWaterMark, create the watermark beginning in (X,Y) coords. Finnaly, save the result in imageOut.
*/
int main(int argc, char *argv[]){


    if(argc!=6 || isNumeric(argv[4])==0 || atoi(argv[5])<0){
        printf("Usage: %s [imageSrc] [imageWaterMark] [imageOut] [Coord:X] [Coord:Y]\nX,Y have to be positive integers.\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    RGBIMAGE *im = load_RGB_from_file(argv[1]);
    RGBIMAGE *wtr = load_RGB_from_file(argv[2]);
    
    makeWaterMark(im, wtr, atoi(argv[4]), atoi(argv[5]));

    save_RGB_image_to_file(im, argv[3]);


}