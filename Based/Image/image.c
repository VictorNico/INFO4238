#include "image.h"


// create image instance
Images *CreateIInstance(){
	Images *img = (Images *)malloc(sizeof(Images));
	if(img == NULL){
		// catch error
		fprintf(stderr,"\nError to instance the image structure\n");
		return NULL;
	}else{
		return img;

	}
}
// free image instance
_Bool FreeIInstance(Images *img){
	if(img){ // check if exist and allocated
		// free malloc allocations
		// if(img->path && img->path != NULL){ // check if exist and allocated
	 //    	printf("\t1");
	 //    	free(img->path);
	 //    	img->path = NULL;
	 //    }
	 //    if(img->chartName && img->chartName != NULL){ // check if exist and allocated
	 //    	printf("\t2");
	 //    	free(img->chartName);
	 //    	img->chartName = NULL;
	 //    }
	    if(img->comment && img->comment != NULL){ // check if exist and allocated
	    	printf("\t3");
	    	free(img->comment);
	    	img->comment = NULL;
	    }
	    // if(img->outPath && img->outPath != NULL){ // check if exist and allocated
	    // 	printf("\t4");
	    // 	free(img->outPath);
	    // 	img->outPath = NULL;
	    // }
	    if(img->Hist && img->Hist != NULL) {// check if exist and allocated
	    	printf("\t5");
	    	free(img->Hist);
	    	img->Hist = NULL;
	    }
		if(img->image && img->image != NULL) // check if exist and allocated
	    {
	    	printf("\t6");
	    	FreeMatrix(img->image,img->rows);
	    	img->image = NULL;
	    }
		printf("\t7");
	    free(img);
	    img = NULL;
	    return 1;
	}
	return 0;
}
// load image file content
Images *ReadNotCompressedImg(char *path){
	FILE *file = GetReadStream(path); // get stream
	if(file == NULL){ // 
		// catch error
		fprintf(stderr,"\nError to open the file\n");
	}else{
		Images *img = CreateIInstance(); // create image struct instance
		if(img == NULL){
			return NULL;
		}else{
			img->path = path; // set path
			fscanf(file, "%s %*s", img->format); // get format
			img->comment = (char *)malloc(100 * sizeof(char));
	        fgets(img->comment, 100, file); // get comment
	        fscanf(file, "%d %d", &img->cols, &img->rows);  // get cols and rows
	        int color;
	        fscanf(file, "%d", &color); // get max pixel
	        img->maxPixel = color;
	        img->image = CreateMatrix(img->cols,img->rows);
	        char P3[3] = "P3";
	        // manage type of image
	        if (strcmp(img->format, P3) == 0){
	            img->cols = img->cols*3;
	        }
	        for (int i = 0; i < img->rows; i++)
	        {
	            for (int j = 0; j < img->cols; j++)
	            {
	                // fread(&color, sizeof(struct ColorCode), 1, file);
	                fscanf(file, "%d", &color);
	                img->image[i][j] = color;
	            }
	        }
	        CloseStream(file); // close stream
	        
	        return img;
		}

	}
	return NULL;

}
// write image
_Bool WriteNotCompressedImg(Images *image){
	FILE *file = GetWriteStream(image->outPath); // get stream
	if(file == NULL){ // 
		// catch error
		fprintf(stderr,"\nError to open the file\n");
	}else{
		fprintf(file,"%s\n",image->format); // save format
        fprintf(file,"# Create by DTVN TEAM\n"); // set comment 
        char P3[3] = "P3";
        char P2[3] = "P2";
        // manage type of image
        if (strcmp(image->format, P3) == 0){
            fprintf(file,"%d %d\n",image->cols/3, image->rows); // set spatial resolution
        }else if(strcmp(image->format, P2) == 0){
            fprintf(file,"%d %d\n",image->cols, image->rows); // set spatial resolution
        }
        fprintf(file,"%d\n",image->maxPixel); // set max pixel value
        for (int i=0;i<image->rows; i++){
            for (int j=0; j<image->cols; j++){
                fprintf(file, "%d\n", image->image[i][j]); // set pixels values
            }
        }
        CloseStream(file); // close stream
        
        return 1;
	}
	return 0;
}
// get image Histogram
double *GetHist(Images *image){
	char P3[3] = "P3";
	char P2[3] = "P2";
	image->Hist = CreateVector(((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))? 256:2);
	if(image->Hist == NULL){
		fprintf(stderr,"\nHist vector creation doesn't end with success\n");
		return NULL;
	}else{
		for (int i = 0; i < image->rows; i++)
        {
            for (int j = 0; j < image->cols; j++)
            {
                image->Hist[image->image[i][j]]++;
            }
        }
        return image->Hist;
	}
}
// plot hist img
_Bool PlotHist(Images *image){
	if(image->Hist != NULL){
		char P3[3] = "P3";
		char P2[3] = "P2";
		int lenght = ((strcmp(image->format, P3) == 0) || (strcmp(image->format , P2) == 0))? 256:2;	
		double *axis = CreateVector(lenght);
		if(axis == NULL){
			fprintf(stderr,"\nHist vector creation doesn't end with success\n");
			return NULL;
		}else{
			for(int i = 0; i < lenght; i++) 
				axis[i] = i; // init y axis to space color values
			_Bool success;
		    StringReference *errorMessage;
		    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
		    errorMessage = (StringReference *)malloc(sizeof(StringReference));
		    success = DrawScatterPlot(imageRef, 800, 600, axis, lenght, image->Hist, lenght, errorMessage);

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
		    free(axis);
	        return 1;
		}
	}
	return 0;
}
// get luminance
double GetLuminance(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int sum = 0;
	    for (int i = 0; i < image->rows; i++)
	        for (int j = 0; j < image->cols; j++)
	            sum += image->image[i][j];
	
	    return sum / (image->cols * image->rows);
	}
	return NULL;
}
// get image maximum pixel
int GetMaxiPixel(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int max = 0;
	    for (int i = 0; i < n_ligne; i++)
	        for (int j = 0; j < n_col; j++)
	            if (image->image[i][j] > max)
	                max = image->image[i][j];
	    return max;
	}
	return NULL;
}
// get image minimum pixel
int GetMiniPixel(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int max = 0;
	    for (int i = 0; i < n_ligne; i++)
	        for (int j = 0; j < n_col; j++)
	            if (image->image[i][j] < max)
	                max = image->image[i][j];
	    return max;
	}
	return NULL;
}
// compute contrast within ecart type approach
double GetContrastEcartType(Images *image)
{
    double moy = GetLuminance(image);
    double result = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result += pow((double)(d[i][j]) - moy, 2.0);

    return sqrt(result / (n_col * n_ligne));
}
// compute contrast within min max approach
double GetContrastMinMax(int **d, int n_ligne, int n_col)
{
    int min = GetMiniPixel(d, n_ligne, n_col), max = GetMaxiPixel(d, n_ligne, n_col);
    return ((double)(max - min)) / (max + min);
}
