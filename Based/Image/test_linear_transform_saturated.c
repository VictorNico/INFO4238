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
	printf("\nLINEAR TRANSFORMATION WITH SATURATION\n");
	Images *linearsat = LinearSaturatedTransform(image,70,250);
	// test image writer
	linearsat->outPath = "./linsatoutput.pgm";
	printf("path : %s\n",linearsat->path);
	printf("outPath : %s\n",linearsat->outPath);
	for(int i = 0;i<linearsat->rows;i++){
		printf("\t");
		for(int j=0;j<linearsat->cols;j++){
			printf("%d\r",linearsat->image[i][j]);
		}
		printf("\n");
	}
	printf("Image is %s", WriteNotCompressedImg(linearsat) == 1? "now create\n":"not create\n");
	// test Hist plotting
	linearsat->chartName = "./linsatoutput.png";
	printf("chartName :%s\n",linearsat->chartName);
	GetHist(linearsat);
	printf("Plotting is %s", PlotHist(linearsat) == 1? "now done\n":"not complete well\n");

	FreeIInstance(image);
	FreeIInstance(linearsat);
}