#include "ipcv_utils.h"


void drawKDEChartOfImageWithinPathInputAndOutpout(Images *image) {
    // File pointer to read from file
    FILE *inf;
    // open file
    // printf("%s",image->path);exit(0);
    inf = fopen(image->path, "r");
    // catch error in file opening operation
    if (inf == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }
    // get the type of image in first line of image
    // char* format;
    fscanf(inf, "%s %*s", image->format);
    char P3[3] = "P3";
    char P2[3] = "P2";;
    // manage type of image
    if ((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))
    {
        // instructions
        // get the comment header of image in first line of image
        
        image->comment = (char *)malloc(100 * sizeof(char));
        fgets(image->comment, 100, inf);
        printf("ok3 %s \n",image->comment);
        // free(comment);
        // get the image matrix informations
        // int rows = 0, cols=0;
        fscanf(inf, "%d %d", &image->cols, &image->rows);
        image->image = (int **)malloc(image->rows * sizeof(int *));
        printf("00\n");
        // exit(0);
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            image->image[i] = (int *)malloc(image->cols * sizeof(int));
            for (int j = 0; j < image->cols; j++)
            {
                image->image[i][j] = 0;
            }
        }
        printf("0\n");
        // get image matrice color code and save in our custom image matrice
        int color;
        for (int i = 0; i < image->rows; i++)
        {
            for (int j = 0; j < image->cols; j++)
            {
                fscanf(inf, "%d", &color);
                image->image[i][j] = color;
            }
        }
        // computation

        int lenght;
        char P3[3] = "P3";
        char P2[3] = "P2";
        // manage type of image
        if ((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))  lenght = P3_K;
        
        double* x = (double *)malloc(lenght * sizeof(double));
        double* y = (double *)malloc(lenght * sizeof(double));
        for(int i = 0; i < lenght; i++) x[i] = i; // init y axis to space color values
        for(int i = 0; i < lenght; i++) y[i] = 0; // init x axis to 0
        // determine the frequence of each color
        for (int i = 0; i < image->rows; i++)
        {
            for (int j = 0; j < image->cols; j++)
            {
                y[image->image[i][j]]++;
            }
        }
        // for (int i = 0; i < lenght; i++) printf("%d -> %f\n",i,y[i]);
        // draw the chart
        _Bool success;
        StringReference *errorMessage;
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        errorMessage = (StringReference *)malloc(sizeof(StringReference));
        success = DrawScatterPlot(imageRef, 800, 600, x, lenght, y, lenght, errorMessage);

        if(success){
            size_t length;
            double *pngdata = ConvertToPNG(&length, imageRef->image);
            DeleteImage(imageRef->image);

            WriteToFile(pngdata, length, image->chartName);
        }else{
            fprintf(stderr, "Error: ");
            for(int i = 0; i < errorMessage->stringLength; i++){
                fprintf(stderr, "%c", errorMessage->string[i]);
            }
            fprintf(stderr, "\n");
        }

        // for (int i = 0; i < rows; i++)
        //     free(Image[i]);

        // free(Image);
        free(x);
        free(y);
    }
    else{
        // instructions
    }
    fclose(inf);
}

void drawKDEChartOfImageWithinImageMatrix(Images *image) {

    // computation
    int lenght;
    char P3[3] = "P3";
    char P2[3] = "P2";
    // manage type of image
    if ((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))  lenght = P3_K;
    
    double* x = (double *)malloc(lenght * sizeof(double));
    double* y = (double *)malloc(lenght * sizeof(double));
    for(int i = 0; i < lenght; i++) x[i] = i; // init y axis to space color values
    for(int i = 0; i < lenght; i++) y[i] = 0; // init x axis to 0
    // determine the frequence of each color
    for (int i = 0; i < image->rows; i++)
    {
        for (int j = 0; j < image->cols; j++)
        {
            y[image->image[i][j]]++;
        }
    }
    // for (int i = 0; i < lenght; i++) printf("%d -> %f\n",i,y[i]);
    // draw the chart
    _Bool success;
    StringReference *errorMessage;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlot(imageRef, 800, 600, x, lenght, y, lenght, errorMessage);

    if(success){
        size_t length;
        double *pngdata = ConvertToPNG(&length, imageRef->image);
        DeleteImage(imageRef->image);

        WriteToFile(pngdata, length, image->chartName);
    }else{
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

}

void LoadImageMatrix(Images *image) {
    // File pointer to read from file
    FILE *inf;
    // open file
    // printf("%s",image->path);exit(0);
    inf = fopen(image->path, "r");
    // catch error in file opening operation
    if (inf == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }
    // get the type of image in first line of image
    // char* format;
    fscanf(inf, "%s %*s", image->format);
    char P3[3] = "P3";
    char P2[3] = "P2";
    // manage type of image
    if ((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))
    {
        // instructions
        // get the comment header of image in first line of image
        
        image->comment = (char *)malloc(100 * sizeof(char));
        fgets(image->comment, 100, inf);
        // free(comment);
        // get the image matrix informations
        fscanf(inf, "%d %d", &image->cols, &image->rows);
        image->image = (int **)malloc(image->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            image->image[i] = (int *)malloc(image->cols * sizeof(int));
            for (int j = 0; j < image->cols; j++)
            {
                image->image[i][j] = 0;
            }
        }
        // get image matrice color code and save in our custom image matrice
        int color;
        for (int i = 0; i < image->rows; i++)
        {
            for (int j = 0; j < image->cols; j++)
            {
                // fread(&color, sizeof(struct ColorCode), 1, inf);
                fscanf(inf, "%d", &color);
                image->image[i][j] = color;
            }
        }
        
        fclose(inf);
    }
    else{
        // instructions
    }
}