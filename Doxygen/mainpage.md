# Authors
Edgar Morais, nmec: 89323  
João Silva, nmec: 88813

# Compile Everything
$ chmod +x compile.sh  
$ ./compile.sh

# Execute program
$ bin/programName [parameters]

# Programs

### structs.h
Contais structs to represent color, grayscale and binary images. Also constains functions to load and save images from/to files, access individual pixels.
_______________________________________________________________________________________________________________________________
### RGBToGray
Converts a color image to the corresponding grayscale version.  
-s to Split RGB into 3 grayscale images (one for each channel)  

**Usage:** bin/RGBToGray [-s] [imageSrc] [imageOut]
_______________________________________________________________________________________________________________________________
### GrayToBin
Converts a grayscale image to the corresponding binary version.  
-t to Convert grayscale to binary through threshold.  
-h to Convert grayscale to binary through histogram algorithm.  

**Usage:** bin/GrayToBin [-h/-t threshhold] [imageSrc] [imageOut]
_______________________________________________________________________________________________________________________________
### IntensityRGB
Allows to increase or decrease the intensity of a RGB image.  
-i to increase intensity.  
-d to decrease intensity.  
(multiplier is the number os times to multiplly the intensity).  

**Usage:** bin/IntensityRGB [-d/-i] [multiplier] [imageSrc] [imageOut]
_______________________________________________________________________________________________________________________________
### IntensityGray
Allows to increase or decrease the intensity of a grayscale image.  
-i to increase intensity.  
-d to decrease intensity.  
(multiplier is the number os times to multiplly the intensity).  

**Usage:** bin/IntensityGray [-d/-i] [multiplier] [imageSrc] [imageOut]
_______________________________________________________________________________________________________________________________
### filters
Apply a filter on an image.  
-s for Sharpen Filter.  
-e for Edge detection Filte.r  
(Buggy for images where x != y)  

**Usage:** bin/filters [-s/-e] [imageSrc] [imageOut]
_______________________________________________________________________________________________________________________________
### waterMarker
Includes a watermark on an image.  
**Usage:** bin/waterMarker [imageSrc] [imageWaterMark] [imageOut] [Coord:X] [Coord:Y]



