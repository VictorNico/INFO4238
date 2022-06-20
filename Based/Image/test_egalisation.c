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
	printf("\nEGALISATION\n");
	// image = ReadNotCompressedImg("../../ImagesOutput/egal.pgm");
	Images *egal = Egalization(image);
	// test image writer
	egal->outPath = "./egaloutput.pgm";
	printf("path : %s\n",egal->path);
	printf("outPath : %s\n",egal->outPath);
	// for(int i = 0;i<egal->rows;i++){
	// 	printf("\t");
	// 	for(int j=0;j<egal->cols;j++){
	// 		printf("%d\r",egal->image[i][j]);
	// 	}
	// 	printf("\n");
	// }
	printf("Image is %s", WriteNotCompressedImg(egal) == 1? "now create\n":"not create\n");
	// test Hist plotting
	egal->chartName = "./egaloutput.png";
	printf("chartName :%s\n",egal->chartName);
	GetHist(egal);
	printf("Plotting is %s", PlotHist(egal) == 1? "now done\n":"not complete well\n");
	
	FreeIInstance(image);
	FreeIInstance(egal);
}