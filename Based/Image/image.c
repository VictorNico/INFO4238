#include "image.h"

// BASED IMAGE COMPUTING
// create image instance

// 1-UTILS

Images *CreateIInstance()
{
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
_Bool FreeIInstance(Images *img)
{
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
		// printf("\t7");
	    free(img);
	    img = NULL;
	    return 1;
	}
	return 0;
}
// copy instance
_Bool CopyImageData(Images *src,Images *dst)
{
	printf("\t7");
	if(src->outPath != NULL){
	    dst->outPath = (char *) malloc(100*sizeof(char));
	    memcpy(dst->outPath, src->outPath, 100*sizeof(char));
	}
	printf("\t7");
	if((sizeof(src->format)/sizeof(src->format[0]))>0){
	    // imageC->format = malloc(3*sizeof(char));
	    memcpy(dst->format, src->format, 3*sizeof(char));
	}
	printf("\t7");
	if(src->chartName != NULL){
	    dst->chartName = (char *)malloc(100*sizeof(char));
	    memcpy(dst->chartName, src->chartName, 100*sizeof(char));
	}
	printf("\t7");
	if(src->comment != NULL){
	    dst->comment = (char *)malloc(100*sizeof(char));
	    memcpy(dst->comment, src->comment, 100*sizeof(char));
	}
	printf("\t7");
	if(src->path != NULL){
	    dst->path = (char *)malloc(100*sizeof(char));
	    memcpy(dst->path, src->path, 100*sizeof(char));
	}
	printf("\t7");
	if(src->rows)
    	dst->rows = src->rows;
	if(src->cols)
    	dst->cols = src->cols;
    if(src->maxPixel)
    	dst->maxPixel = src->maxPixel;	
    printf("\t7");
    return 1;
}
// load image file content
Images *ReadNotCompressedImg(char *path)
{
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
_Bool WriteNotCompressedImg(Images *image)
{
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

// 2- BASED OPERATIONS

// get image Histogram
double *GetHist(Images *image)
{
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
_Bool PlotHist(Images *image)
{
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
	return -1;
}
// get image maximum pixel
int GetMaxiPixel(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int max = 0;
	    for (int i = 0; i < image->rows; i++)
	        for (int j = 0; j < image->cols; j++)
	            if (image->image[i][j] > max)
	                max = image->image[i][j];
	    return max;
	}
	return -1;
}
// get image minimum pixel
int GetMiniPixel(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int max = 256;
	    for (int i = 0; i < image->rows; i++)
	        for (int j = 0; j < image->cols; j++)
	            if (image->image[i][j] < max)
	                max = image->image[i][j];
	    return max;
	}
	return -1;
}
// compute contrast within ecart type approach
double GetContrastEcartType(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    double means = GetLuminance(image);
	    double result = 0;
	    for (int i = 0; i < image->rows; i++)
	        for (int j = 0; j < image->cols; j++)
	            result += pow((double)(image->image[i][j]) - means, 2.0);

    	return sqrt(result / (image->rows * image->cols));
    }
    return -1;
}
// compute contrast within min max approach
double GetContrastMinMax(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
	    int min = GetMiniPixel(image), max = GetMaxiPixel(image);
	    printf("\nmin:%d\tmax:%d\n",min,max);
	    return ((double)(max - min)) / (max + min);
	}
	return -1;
}
// addition bettween two images
Images *AdditionOfTwoImages(Images *image1,Images *image2)
{
	if((image1 != NULL && image1->image != NULL && image1->rows != 0 && image1->cols != 0) && 
		(image2 != NULL && image2->image != NULL && image2->rows != 0 && image2->cols != 0) &&
		(image1->rows==image2->rows && image1->cols==image2->cols)){
	    Images *result = CreateIInstance();
		if(CopyImageData(image1,result)){
			return NULL;
		}
		result->image = CreateMatrix(image1->cols,image1->rows);
	    for (int i = 0; i < image1->rows; i++)
	    {
	        for (int j = 0; j < image1->cols; j++)
	        {
	            result->image[i][j] = image1->image[i][j] + image2->image[i][j];
	            if (result->image[i][j] >= 255)
	                result->image[i][j] = 255;
	        }
	    }
	    return result;
	}
	return NULL;
}
// Image factor times
Images *ImageTime(Images *image, double factor)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
		Images *result = CreateIInstance();
		if(CopyImageData(image,result)){
			return NULL;
		}
	    result->image = CreateMatrix(image->cols,image->rows);
	    for (int i = 0; i < image->rows; i++)
	    {
	        for (int j = 0; j < image->cols; j++)
	        {
	            result->image[i][j] = factor * image->image[i][j];
	            if (result->image[i][j] > 255)
	                result->image[i][j] = 255;
	            if (result->image[i][j] < 0)
	                result->image[i][j] = 0;
	        }
	    }
	    return result;
	}
	return NULL;
}
// soustraction between two images
Images *SoustractionOfTwoImages(Images *image1,Images *image2)
{
    if((image1 != NULL && image1->image != NULL && image1->rows != 0 && image1->cols != 0) && 
		(image2 != NULL && image2->image != NULL && image2->rows != 0 && image2->cols != 0) &&
		(image1->rows==image2->rows && image1->cols==image2->cols)){
	    Images *result = CreateIInstance();
		if(CopyImageData(image1,result)){
			return NULL;
		}
		result->image = CreateMatrix(image1->cols,image1->rows);
	    for (int i = 0; i < image1->rows; i++)
	    {
	        for (int j = 0; j < image1->cols; j++)
	        {
	            result->image[i][j] = image1->image[i][j] - image2->image[i][j];
	            if (result->image[i][j] < 0)
	                result->image[i][j] = 0;
	        }
	    }
	    return result;
	}
	return NULL;
}
// // AND binary image computation
// Images *et_(int **d1, int **d2, int n_ligne, int n_col, int a)
// {
//     int **d = create_matrix(n_ligne, n_col);
//     int i = 0, j = 0;
//     for (i = 0; i < n_ligne; i++)
//     {
//         for (j = 0; j < n_ligne; j++)
//         {
//             d[i][j] = a;
//             if (d1[i][j] == 0)
//                 d[i][j] = d2[i][j];
//         }
//     }
//     return d;
// }
// // OR binary image computation
// Images *ou_(int **d1, int **d2, int n_ligne, int n_col, int a)
// {
//     int **d = create_matrix(n_ligne, n_col);
//     int i = 0, j = 0;
//     for (i = 0; i < n_ligne; i++)
//     {
//         for (j = 0; j < n_ligne; j++)
//         {
//             d[i][j] = a;
//             if (d1[i][j] == 1)
//                 d[i][j] = d2[i][j];
//         }
//     }
//     return d;
// }

// TRANSFORMATION COMPUTING
// linear transformation
Images *LinearTransform(Images *image)
{ 
    if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
        Images *result = CreateIInstance();
        if(CopyImageData(image,result) == 0){
        	fprintf(stderr,"\nError during Image copy\n");
            return NULL;
        }
        result->image = CreateMatrix(image->cols,image->rows);
        int min = GetMiniPixel(image), max = GetMaxiPixel(image);
        int LUT[256];
        for (int i = 0; i < 256; i++)
            LUT[i] = (255 * (i - min)) / (max - min);

        for (int i = 0; i < image->rows; i++)
            for (int j = 0; j < image->cols; j++)
                result->image[i][j] = LUT[image->image[i][j]];
        return result;
    }
    fprintf(stderr,"\nEmpty Image\n");
    return NULL;
}
// linear transformation with saturation
Images *LinearSaturatedTransform(Images *image, int min, int max)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
        Images *result = CreateIInstance();
        if(CopyImageData(image,result) == 0){
        	fprintf(stderr,"\nError during Image copy\n");
            return NULL;
        }
	    result->image = CreateMatrix(image->cols,image->rows);
        int mini = GetMiniPixel(image), maxi = GetMaxiPixel(image);
        if((mini<min) && (min<max) && (max<maxi)){
    	    for (int i = 0; i < image->rows; i++){
    	        for (int j = 0; j < image->cols; j++){
    	            result->image[i][j] = (255 * (image->image[i][j] - min)) / (max - min);
	    	        if (result->image[i][j] < 0)
	    	            result->image[i][j] = 0;
	    	        if (result->image[i][j] > 255)
	    	            result->image[i][j] = 255;
    	        }
    	    }

    	    return result;
    	}
    	fprintf(stderr,"\nError predicat : Imin<min<max<Imax is not satisfy \n");
    	return NULL;
	}
	fprintf(stderr,"\nEmpty Image\n");
	return NULL;
}
// Linear Piece Wise Transformer
Images *LinearPieceWiseTransform(Images *image, int smax, int smin, int s)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
        Images *result = CreateIInstance();
        if(CopyImageData(image,result) == 0){
        	fprintf(stderr,"\nError during Image copy\n");
            return NULL;
        }
        // copy image data
        result->image = CreateMatrix(image->cols,image->rows);
        for (int i = 0; i < image->rows; i++)
            for (int j = 0; j < image->cols; j++)
                result->image[i][j] = image->image[i][j];
        // copy hist
        result->Hist = CreateVector(256);
        for (int i = 0; i < image->rows; i++)
        	result->Hist[i] = image->Hist[i];
        // compute pente l,m,n
        double l = 0, m=0, n=0;
        int mini = GetMiniPixel(image), maxi = GetMaxiPixel(image);
        l = round((Hist[smin] - Hist[mini])/(smin-mini));
        m = round((Hist[smax] - Hist[smin])/(smax-smin));
        n = round((Hist[maxi] - Hist[smax])/(maxi-smax));
        // apply ponctual transformation
        for (int i = 0; i < image->rows; i++){
	        for (int j = 0; j < image->cols; j++){
    	        if (mini <= image->image[i][j] < smin)
    	            result->image[i][j] = (int)image->image[i][j] * l;
    	        if (smin <= image->image[i][j] < smax)
    	            result->image[i][j] = (int) m*(image->image[i][j]-smin) + image->image[i][j];
    	        if (smax <= image->image[i][j] < maxi)
    	            result->image[i][j] = (int) n*(image->image[i][j]-smax) + image->image[i][j];
    	        // control dynamic stretch
    	        if (result->image[i][j] < 0)
    	            result->image[i][j] = 0;
    	        if (result->image[i][j] > 255)
    	            result->image[i][j] = 255;
	        }
	    }
        return result;
    }
    fprintf(stderr,"\nEmpty Image\n");
    return NULL;
}
// histogram egalization
Images *Egalization(Images *image)
{
	if(image != NULL && image->image != NULL && image->rows != 0 && image->cols != 0){
        Images *result = CreateIInstance();
        if(CopyImageData(image,result) == 0){
        	fprintf(stderr,"\nError during Image copy\n");
            return NULL;
        }
        // copy image data
        result->image = CreateMatrix(image->cols,image->rows);
        for (int i = 0; i < image->rows; i++)
            for (int j = 0; j < image->cols; j++)
                result->image[i][j] = image->image[i][j];
        // copy hist
        result->Hist = CreateVector(256);
        for (int i = 0; i < image->rows; i++)
        	result->Hist[i] = image->Hist[i];
        // compute normalize histogram
        double area = image->rows*image->cols;
        for (int i = 0; i < image->rows; i++)
        	result->Hist[i] = image->Hist[i]/area;
        // compute cumulate sum Hist
        double sum = 0;
        double *cumH = CreateVector(256);
        for (int i = 0; i < 256; i++){
        	// printf("%d",i);
            sum = sum + result->Hist[i];
            cumH[i] = sum;
        }
        int Dm = 256;
        for (int i = 0; i < image->rows; i++)
            for (int j = 0; j < image->cols; j++)
                result->image[i][j] = (int) Dm*cumH[image->image[i][j]];
        return result;
    }
    fprintf(stderr,"\nEmpty Image\n");
    return NULL;
}
// int **interpolation_knn(int **d, int n_ligne, int n_col, int ki, int kj){
//     int **result = create_matrix(n_ligne*ki, n_col*kj);
//     int i=0, j=0, vali=0,valj=0;
//     for (i = 0; i < n_ligne; i++)
//         for (j = 0; j < n_col; j++)
//             for (vali = i*ki; vali < ki*(i+1); vali++)
//                 for (valj = j*kj; valj < kj*(j+1); valj++)
//                     result[vali][valj] = d[i][j];
//     return result;
// }
// int **interpolation_bilineaire(int **d, int n_ligne, int n_col){
//     int nl= n_ligne*2-1,nc= n_col*2-1;
//     int **result = create_matrix(nl, nc);
//     int i=0, j=0;
//     for (i = 0; i < n_ligne; i++){
//         for (j = 0; j < n_col; j++){
//             result[2*i][2*j]=d[i][j];
//             if (2*i+1 < nl)
//             {
//                 result[2*i+1][2*j]=(d[i][j]+d[i+1][j])/2;
//             }
//             if (2*j+1 < nc)
//             {
//                 result[2*i][2*j+1]=(d[i][j]+d[i][j+1])/2;
//             }
//             if (2*i+1 < nl && 2*j+1 < nc )
//             {
//                 result[2*i+1][2*j+1]=(d[i][j]+d[i+1][j]+d[i][j+1]+d[i+1][j+1])/4;
//             }
//         }
//     }
//     return result;
// }



// 3- CONVOLUTIONS



// 4- EDGES DETECTION


