
// C program to implement
// the above approach

#include "ipcv_utils.h"

// Driver code
int main()
{
    // declaration of variables
    Images *Image,*Inverse;
    Image = (Images *)malloc(sizeof(Images));
    // set testing default params
    Image->path = "./images/img.ppm";
    Image->chartName = "chart1.png";
    // TODO: verion 1 plot kde chart of image 
    // drawKDEChartOfImageWithinPathInputAndOutpout(Image);
    // TODO : version 2 
    // function which return image matrix and properties rows and columns.
    // function which take like entry image matrix, image properties and plot kde
    
    // Image->path = "./images/img.pgm";
    // Image->chartName = "chart2.png";
    LoadImageMatrix(Image);
    DrawKDEChartOfImageWithinImageMatrix(Image);
    // TODO : version 3 
    // function which write a new image
    // function which compute the contrast of a image
    // function which make equalization of image
    // 
    Image->outPath = "./images/test.ppm";
    WriteNewImage(Image);
    Inverse = (Images *)malloc(sizeof(Images));
    CopyImageData(Image,Inverse);
    Inverse->outPath = "./images/test1.ppm";
    Inverse->chartName = "inverse.png";
    Rotate90DegreeAntiClockwizeImage(Image,Inverse);
    // exit(0);
    WriteNewImage(Inverse);
    DrawKDEChartOfImageWithinImageMatrix(Inverse);
    // free malloc allocations
    // free(Image->path);
    // free(Image->chartName);
    // free(Image->outPath);

    // for (int i = 0; i < rows; i++)
    //     free(Image[i]);

    free(Image);
    // free(Inverse);
    return 0;
}
