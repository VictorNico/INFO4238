// C program to implement
// Image manipulation module
#include "image.h"


// Driver code
int main()
{
	char P3[3] = "P3";
	char P2[3] = "P2";
	// test image reader
	Images *image = ReadNotCompressedImg("../../ImagesOutput/lin.pgm");
	for(int i = 0;i<image->rows;i++){
		printf("\t");
		for(int j=0;j<image->cols;j++){
			printf("%d\r",image->image[i][j]);
		}
		printf("\n");
	}
	// test image writer
	image->outPath = "./output.pgm";
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


	Images *linearsat = LinearSaturatedTransform(image,50,170);
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

	Images *egal = Egalization(image);
	// test image writer
	egal->outPath = "./egaloutput.pgm";
	printf("path : %s\n",egal->path);
	printf("outPath : %s\n",egal->outPath);
	for(int i = 0;i<egal->rows;i++){
		printf("\t");
		for(int j=0;j<egal->cols;j++){
			printf("%d\r",egal->image[i][j]);
		}
		printf("\n");
	}
	printf("Image is %s", WriteNotCompressedImg(egal) == 1? "now create\n":"not create\n");
	// test Hist plotting
	egal->chartName = "./egaloutput.png";
	printf("chartName :%s\n",egal->chartName);
	GetHist(egal);
	printf("Plotting is %s", PlotHist(egal) == 1? "now done\n":"not complete well\n");
	
	FreeIInstance(image);
	FreeIInstance(linear);
	FreeIInstance(linearsat);
	FreeIInstance(egal);
}