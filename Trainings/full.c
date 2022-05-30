
// C program to implement
// the above approach
#include "pbPlots.h"
#include "supportLib.h"
// constant declaration
#ifndef P3_K
#define P3_K 256
#endif
#ifndef P2_k
#define P2_k 2
#endif
// prototype
void drawHistogramLineChart(char *path, char *chartName);

// Driver code
int main()
{
    drawHistogramLineChart("./images/img.ppm", "chart.png");
    return 0;
}


void drawHistogramLineChart(char *path, char *chartName) {
    // File pointer to read from file
    FILE *inf;
    // open file
    // printf("ok0");
    inf = fopen(path, "r");
    // catch error in file opening operation
    if (inf == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }
    // printf("ok");
    // get the type of image in first line of image
    char* format;
    fscanf(inf, "%s %*s", format);
    // char fileType[] = {format[0], format[1]};
    // strcat(fileType, a);
    // memcpy(fileType, type, 2);
    // printf("ok1 %s %ld\n", format, sizeof(format));
    
    char P3[3] = "P3";
    char P2[3] = "P2";
    printf("%d\n", strcmp(format, P3));
    printf("%d %d \n",P3_K,P2_k);
    // manage type of image
    if (strcmp(format, P3) == 0)
    {
        // instructions
        // get the comment header of image in first line of image
        
        char* comment = (char *)malloc(100 * sizeof(char));
        fgets(comment, 100, inf);
        // fscanf(inf, "%s %*s", comment);
        // fread(&comment, sizeof(char*), 1, inf);
        printf("ok3 %s \n",comment);
        free(comment);
        // get the image matrix informations
        int rows = 0, cols=0;
        fscanf(inf, "%d %d", &cols, &rows);
        
        // fread(&details, sizeof(struct ImageDetails), 1, inf);
        printf("ok4 cols:%d rows:%d\n", cols, rows);
        int** Image = (int **)malloc(rows * sizeof(int *));
        printf("00\n");
        // exit(0);
        // initialise the matrice to 0
        for (int i = 0; i < rows; i++)
        {
            Image[i] = (int *)malloc(cols * sizeof(int));
            for (int j = 0; j < cols; j++)
            {
                Image[i][j] = 0;
            }
        }
        printf("0\n");
        // get image matrice color code and save in our custom image matrice
        int color;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                // fread(&color, sizeof(struct ColorCode), 1, inf);
                fscanf(inf, "%d", &color);
                Image[i][j] = color;
            }
        }
        // computation
        double* x = (double *)malloc(P3_K * sizeof(double));
        double* y = (double *)malloc(P3_K * sizeof(double));
        for(int i = 0; i < P3_K; i++) x[i] = i; // init y axis to space color values
        for(int i = 0; i < P3_K; i++) y[i] = 0; // init x axis to 0
        // determine the frequence of each color
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                y[Image[i][j]]++;
            }
        }
        // for (int i = 0; i < P3_K; i++) printf("%d -> %f\n",i,y[i]);
        // draw the chart
        _Bool success;
        StringReference *errorMessage;
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        errorMessage = (StringReference *)malloc(sizeof(StringReference));
        success = DrawScatterPlot(imageRef, 800, 600, x, P3_K, y, P3_K, errorMessage);

        if(success){
            size_t length;
            double *pngdata = ConvertToPNG(&length, imageRef->image);
            DeleteImage(imageRef->image);

            WriteToFile(pngdata, length, chartName);
        }else{
            fprintf(stderr, "Error: ");
            for(int i = 0; i < errorMessage->stringLength; i++){
                fprintf(stderr, "%c", errorMessage->string[i]);
            }
            fprintf(stderr, "\n");
        }

        for (int i = 0; i < rows; i++)
            free(Image[i]);

        free(Image);
        free(x);
        free(y);
    }
    else if (strcmp(format , P2) == 0){
        // instructions
    }
}