// C program to implement
// Image manipulation module
#include "image.h"


// Driver code
int main()
{
	char P3[3] = "P3";
	char P2[3] = "P2";
	// test image reader
	printf("\nREAD WRITE\n");
	Images *image = ReadNotCompressedImg("../../ImagesOutput/egal.pgm");
	printf("\nLINEAR TRANSFORMATION\n");
	Images *linear = LinearTransform(image);
	// test image writer
	linear->outPath = "./linoutput.pgm";
	printf("path : %s\n",linear->path);
	printf("outPath : %s\n",linear->outPath);
	for(int i = 0;i<linear->rows;i++){
		printf("\t");
		for(int j=0;j<linear->cols;j++){
			printf("%d\r",linear->image[i][j]);
		}
		printf("\n");
	}
	printf("Image is %s", WriteNotCompressedImg(linear) == 1? "now create\n":"not create\n");
	// test Hist plotting
	linear->chartName = "./linoutput.png";
	printf("chartName :%s\n",linear->chartName);
	GetHist(linear);
	printf("Plotting is %s", PlotHist(linear) == 1? "now done\n":"not complete well\n");

	FreeIInstance(image);
	FreeIInstance(linear);
}