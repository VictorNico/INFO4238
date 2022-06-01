<#include "ipcv_utils.h"


void DrawKDEChartOfImageWithinPathInputAndOutpout(Images *image) {
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
        image->cols = image->cols * 3;
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
        fscanf(inf, "%s %*s", image->format);
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

void DrawKDEChartOfImageWithinImageMatrix(Images *image) {

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
    // char P3[3] = "P3";
    // char P2[3] = "P2";
    // manage type of image
    // if (strcmp(image->format, P3) == 0){
    //     for (int i=0;i<image->rows; i++){
    //         for (int j=0; j<image->cols*3; j++){
    //             y[image->image[i][j]]++;
    //         }
    //     }
    // }else if(strcmp(image->format, P2) == 0){
        for (int i=0;i<image->rows; i++){
            for (int j=0; j<image->cols; j++){
                y[image->image[i][j]]++;
            }
        }
    // }
    // for (int i = 0; i < image->rows; i++)
    // {
    //     for (int j = 0; j < image->cols; j++)
    //     {
    //         y[image->image[i][j]]++;
    //     }
    // }
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
    if (strcmp(image->format, P3) == 0)
    {
        // instructions
        // get the comment header of image in first line of image
        
        image->comment = (char *)malloc(100 * sizeof(char));
        fgets(image->comment, 100, inf);
        // free(comment);
        // get the image matrix informations
        fscanf(inf, "%d %d", &image->cols, &image->rows);
        image->cols = image->cols * 3;
        image->image = (int **)malloc(image->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            image->image[i] = (int *)malloc((image->cols*3) * sizeof(int));
            for (int j = 0; j < image->cols; j++)
            {
                image->image[i][j] = 0;
            }
        }
        // get image matrice color code and save in our custom image matrice
        int color;
        fscanf(inf, "%d", &color); // move out the first pixel which code max color value
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
    else if (strcmp(image->format , P2) == 0){
        // instructions
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
}

void WriteNewImage(Images *image){
    FILE *file=NULL;
    file = fopen(image->outPath,"w");
    if (file == NULL){
        exit(0);
    }else{
        fprintf(file,"%s\n",image->format);
        fprintf(file,"# Create by DTVN TEAM\n");
        
        char P3[3] = "P3";
        char P2[3] = "P2";
        // manage type of image
        if (strcmp(image->format, P3) == 0){
            // fprintf(file,"255\n");
            // for (int i=0;i<image->rows; i++){
            //     for (int j=0; j<image->cols*3; j++){
            //         fprintf(file, "%d\n", image->image[i][j]);
            //     }
            // }

            if(image->rotated == true){
                fprintf(file,"%d %d\n",image->cols, image->rows/3);
            }else{
                fprintf(file,"%d %d\n",image->cols/3, image->rows);
            }
        }else if(strcmp(image->format, P2) == 0){
            fprintf(file,"%d %d\n",image->cols, image->rows);
        }
        fprintf(file,"255\n");
        for (int i=0;i<image->rows; i++){
            for (int j=0; j<image->cols; j++){
                fprintf(file, "%d\n", image->image[i][j]);
            }
        }    
    }
    fclose(file);
}

void InvertComputation(Images *image,Images *imageC){
    // declare knowledge type
    char P3[3] = "P3";
    char P2[3] = "P2";

    // manage type of image
    // if (strcmp(image->format, P3) == 0){
    //     // 
    //     imageC->image = (int **)malloc(image->rows * sizeof(int *));
    //     // initialise the matrice to 0
    //     for (int i = 0; i < image->rows; i++)
    //     {
    //         imageC->image[i] = (int *)malloc((image->cols*3) * sizeof(int));
    //         for (int j = 0; j < image->cols*3; j++)
    //         {
    //             imageC->image[i][j] = 0;
    //         }
    //     }
    //     for (int i=0;i<image->rows; i++){
    //         for (int j=0; j<image->cols*3; j++){
    //             imageC->image[i][j] = 255 - image->image[i][j];
    //         }
    //     }
    // }else 
    if((strcmp(image->format, P2) == 0) || (strcmp(image->format, P3) == 0)){
        // 
        imageC->image = (int **)malloc(image->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            imageC->image[i] = (int *)malloc(image->cols * sizeof(int));
            for (int j = 0; j < image->cols; j++)
            {
                imageC->image[i][j] = 0;
            }
        }
        for (int i=0;i<image->rows; i++){
            for (int j=0; j<image->cols; j++){
                imageC->image[i][j] = 255 - image->image[i][j];
            }
        }
    }
}

void GetInteger(char *message,int *variable){
    char *buffer;
    size_t bufSize = 100;
    size_t flag;
    int temp;

    buffer = (char *)malloc(bufSize * sizeof(char));
    if(buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }
    do{
        printf("%s: ",message);
        getline(&buffer,&bufSize,stdin);
        flag = sscanf( buffer, "%d", variable);

    }while(flag == 0);
    free(buffer);
}

void GetString(char *message,char *variable){
    char *buffer;
    size_t bufSize = 100;
    size_t flag;
    int temp;

    buffer = (char *)malloc(bufSize * sizeof(char));
    if(buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }
    do{
        printf("%s: ",message);
        getline(&buffer,&bufSize,stdin);
        flag = sscanf( buffer, "%s", variable);

    }while(flag == 0);
    free(buffer);
}

void GetChar(char *message,char *variable){
    char *buffer;
    size_t bufSize = 100;
    size_t flag;
    int temp;

    buffer = (char *)malloc(bufSize * sizeof(char));
    if(buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }
    do{
        printf("%s: ",message);
        getline(&buffer,&bufSize,stdin);
        flag = sscanf( buffer, "%c", variable);

    }while(flag == 0);
    free(buffer);
}

void Rotate90DegreeClockwizeImage(Images *image, Images *imageR){
    
    // declare knowledge type
    char P3[3] = "P3";
    char P2[3] = "P2";

    // manage type of image
    if ((strcmp(image->format, P2) == 0) || (strcmp(image->format, P3) == 0)){
        // 
        imageR->image = (int **)malloc(image->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            imageR->image[i] = (int *)malloc((image->cols*3) * sizeof(int));
            for (int j = 0; j < image->cols*3; j++)
            {
                imageR->image[i][j] = 0;
            }
        }
        for(int i = 0; i<image->rows; i++){
            for(int j = (image->cols-1)*3; j>=0; j--){
                imageR->image[i][j] = image->image[j][i];
            }
        }
    }else if(strcmp(image->format, P2) == 0){
        // 
        imageR->image = (int **)malloc(image->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < image->rows; i++)
        {
            imageR->image[i] = (int *)malloc(image->cols * sizeof(int));
            for (int j = 0; j < image->cols; j++)
            {
                imageR->image[i][j] = 0;
            }
        }
        for(int i = 0; i<image->rows; i++){
            for(int j = (image->cols-1); j>=0; j--){
                imageR->image[i][j] = image->image[j][i];
            }
        }
    }
}


void Rotate90DegreeAntiClockwizeImage(Images *image, Images *imageR){
    
    // declare knowledge type
    char P3[3] = "P3";
    char P2[3] = "P2";
    // printf("rows:%d cols:%d\n",image->rows,image->cols);
    // manage type of image
    if ((strcmp(image->format, P2) == 0) || (strcmp(image->format, P3) == 0)){
        // 
        // final rotate image variable
        // rotate dimensions
        imageR->rows = image->cols;
        imageR->cols = image->rows;
        // create the matrix
        imageR->image = (int **)malloc(imageR->rows * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < imageR->rows; i++)
        {
            imageR->image[i] = (int *)malloc(imageR->cols * sizeof(int));
            for (int j = 0; j < imageR->cols; j++)
            {
                imageR->image[i][j] = 0;
            }
        }

        // temp variable to compute rotation
        // length must be square, so get the max of cols or rows parameter
        int length;
        if(image->cols > image->rows){
            length = image->cols;
        }else{
            length = image->rows;
        }
        // create instances
        int **temp = (int **)malloc(length * sizeof(int *));
        int **tempR = (int **)malloc(length * sizeof(int *));
        // initialise the matrice to 0
        for (int i = 0; i < length; i++)
        {
            temp[i] = (int *)malloc(length * sizeof(int));
            tempR[i] = (int *)malloc(length * sizeof(int));
            for (int j = 0; j < length; j++)
            {
                temp[i][j] = 0;
                tempR[i][j] = 0;
            }
        }
        // copy init matrix inside the square format
        for (int i = 0; i < image->rows; i++)
        {
            for (int j = 0; j < image->cols; j++)
            {
                temp[i][j] = image->image[i][j];
            }
        }
        // rotate the square format 
        for(int i = length-1; i>=0; i--){
            for(int j = 0; j<length; j++){
                tempR[i][j] = temp[j][i];
            }
        }
        // printf("rows:%d cols:%d\n",imageR->rows,imageR->cols);
        // printf("1");
        // exit(0);

        // save the result rotation inside the output matrix
        for(int i = 0; i<imageR->rows; i++){
            for(int j = 0; j<imageR->cols; j++){
                imageR->image[i][j] = tempR[i][j];
            }
        }
        // indicate rotate image type
        imageR->rotated = true;
        for (int i = 0; i < image->rows; i++){
            free(temp[i]);
            free(tempR[i]);
        }
        free(temp);
        free(tempR);
        // printf("rows:%d cols:%d\n",imageR->rows,imageR->cols);
    }
    // else if(strcmp(image->format, P2) == 0){
    //     // 
    //     imageR->image = (int **)malloc(image->rows * sizeof(int *));
    //     // initialise the matrice to 0
    //     for (int i = 0; i < image->rows; i++)
    //     {
    //         imageR->image[i] = (int *)malloc(image->cols * sizeof(int));
    //         for (int j = 0; j < image->cols; j++)
    //         {
    //             imageR->image[i][j] = 0;
    //         }
    //     }
    //     printf("11");
    //     exit(0);
    //     for(int i = image->rows-1; i>=0; i--){
    //         for(int j = 0; j<image->cols; j++){
    //             imageR->image[i][j] = image->image[j][i];
    //         }
    //     }
    // }
}

void CopyImageData(Images *image,Images *imageC){
    imageC->outPath = (char *) malloc(100*sizeof(char));
    memcpy(imageC->outPath, image->outPath, 100*sizeof(char));

    // imageC->format = malloc(3*sizeof(char));
    memcpy(imageC->format, image->format, 3*sizeof(char));

    imageC->chartName = (char *)malloc(100*sizeof(char));
    memcpy(imageC->chartName, image->chartName, 100*sizeof(char));

    imageC->comment = (char *)malloc(100*sizeof(char));
    memcpy(imageC->comment, image->comment, 100*sizeof(char));

    imageC->path = (char *)malloc(100*sizeof(char));
    memcpy(imageC->path, image->path, 100*sizeof(char));

    // //Calculate length of array Hist    
    // //Create another array Hist with the size of Hist.    
    // imageC->Hist = malloc(sizeof(image->Hist)/sizeof(image->Hist[0]));  
        
    // //Copying all elements of one array into another    
    // for (int i = 0; i < sizeof(image->Hist)/sizeof(image->Hist[0]); i++) {     
    //     imageC->Hist[i] = image->Hist[i];     
    // }

    imageC->rows = image->rows;
    imageC->cols = image->cols;
}

// "%d in decimal =  %lld in binary"

long long IntToBin(int n) {
  long long bin = 0;
  int rem, i = 1;

  while (n!=0) {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
  }

  return bin;
}

int BinToInt(long long n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}