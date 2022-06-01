// C program to implement
// Image manipulation module

#include "image.h"

// Driver code
int main()
{
	char P3[3] = "P3";
	char P2[3] = "P2";
	// test image reader
	Images *image = ReadNotCompressedImg("../../ImagesOutput/img.pgm");
	for(int i = 0;i<image->rows;i++){
		printf("\t");
		for(int j=0;j<image->cols;j++){
			printf("%d\r",image->image[i][j]);
		}
		printf("\n");
	}
	// test image writer
	image->outPath = "./out.pgm";
	printf("Image is %s", WriteNotCompressedImg(image) == 1? "now create\n":"not create\n");
	// test Hist computing
	double *H = GetHist(image);
	for(int i = 0;i<(((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))? 256:2);i++){
		printf("\t");
		printf("%f\r",H[i]);
		printf("\n");
	}
	// test Hist plotting
	image->chartName = "./output.png";
	printf("Plotting is %s", PlotHist(image) == 1? "now done\n":"not complete well\n");
	
	FreeIInstance(image);
}