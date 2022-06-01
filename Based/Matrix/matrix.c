#include "matrix.h"

// create an empty matrix
int **CreateMatrix(int cols, int rows){
	// check whether cols or rows dim is equals to zero
	printf("\tStarting Matrix creation process\n");
	if(cols == 0 || rows == 0){
		// catch error in exception or anormal length
	    fprintf(stderr,"\nError exception: anormal length\n");
	}else{
		printf("\tProgression:\t");
		int **matrix = (int **)calloc(rows, sizeof(int *));
		// check whetter if allocate memory has end with success
		if( matrix == NULL){
			// catch error in exception or anormal length
	    	fprintf(stderr,"\nAllocation error, stackoverflow: it's not possible to allocate memory\n");
	    	return NULL;
		}else{
			for(int i = 0; i<rows; i++){
				matrix[i] = (int *)calloc(cols, sizeof(int));
				if( matrix[i] == NULL){
					// catch error in exception or anormal length
			    	fprintf(stderr,"\nAllocation error, stackoverflow: it's not possible to allocate memory\n");
			    	return NULL;
				}
				for(int j = 0; j<((i*10)/rows);j++) 
					printf("");
			}
			printf("\tcomplete\n");
			printf("\tMatrix creation process Ended\n");
			return matrix;
		}
	}
	return NULL;
}
// copy a matrix content
int **CopyMatrix(int **src, int cols, int rows){
	// check whether cols or rows dim is equals to zero
	printf("\tStarting Matrix Copy process\n");
	if(cols == 0 || rows == 0){
		// catch error in exception or anormal length
	    fprintf(stderr,"\nError exception: anormal length\n");
	}else if(src == NULL){
		// catch error matrix src
	    fprintf(stderr,"\nNULL matrix referenced\n");
	}else{
	 	int **dst = CreateMatrix(cols,rows);
		printf("\tProgression:\t");
		for(int i = 0; i<rows; i++){
			for(int j=0;j<10;j++){
				dst[i][j] = src[i][j];
			}
			for(int k = 0; k<((i*10)/rows);k++) 
				printf("");
		}
		printf("\tcomplete\n");
		printf("\tMatrix Copy process Ended\n");
		return dst;
		
	}
	return NULL;
}
// free allocated memory space of a matrix
_Bool FreeMatrix(int **src, int rows){
	// check whether rows dim is equals to zero
	printf("\tStarting Matrix Free process\n");
	if(rows == 0){
		// catch error in exception or anormal length
	    fprintf(stderr,"\nError exception: anormal length\n");
	}else if(src == NULL){
		// catch error matrix src
	    fprintf(stderr,"\nNULL matrix referenced\n");
	}else{
		printf("\tProgression:\t");
		for(int i = 0; i<rows; i++){
			free(src[i]);
			for(int j = 0; j<((i*10)/rows);j++) 
				printf("");
		}
		printf("\tcomplete\n");
		printf("\tMatrix Free process Ended\n");
		return 1;
	}
	return 0;
}

double *CreateVector(int length){
	// check whether cols or rows dim is equals to zero
	printf("\tStarting Vector creation process\n");
	if(length == 0){
		// catch error in exception or anormal length
	    fprintf(stderr,"\nError exception: anormal length\n");
	}else{
		printf("\tProgression:\t");
		double *vect = (double *)calloc(length, sizeof(double));
		// check whetter if allocate memory has end with success
		if( vect == NULL){
			// catch error in exception or anormal length
	    	fprintf(stderr,"\nAllocation error, stackoverflow: it's not possible to allocate memory\n");
	    	return NULL;
		}else{
			// for(int i = 0; i<rows; i++){
			// 	vect[i] = (int *)calloc(cols, sizeof(int));
			// 	if( vect[i] == NULL){
			// 		// catch error in exception or anormal length
			//     	fprintf(stderr,"\nAllocation error, stackoverflow: it's not possible to allocate memory\n");
			//     	return NULL;
			// 	}
				for(int j = 0; j<10;j++) 
					printf("");
			// }
			printf("\tcomplete\n");
			printf("\tVector creation process Ended\n");
			return vect;
		}
	}
	return NULL;
}
