all:
	$gcc -w filters.c -o filters
	$gcc -w GrayToBin.c -o GrayToBin
	$gcc -w IntensityGray.c -o IntensityGray
	$gcc -w IntensityRGB.c -o IntensityRGB
	$gcc -w GrayToBin.c -o GrayToBin
	$gcc -w RGBToGray.c -o RGBToGray
	$gcc -Wall waterMarker.c -o waterMarker


