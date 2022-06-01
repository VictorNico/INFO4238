// C program to implement
// Matrix manipulation module

#include "matrix.h"

// Driver code
int main()
{
	// test matrix creation
	int **matrix = CreateMatrix(10,10);
	for(int i = 0;i<10;i++){
		printf("\t");
		for(int j=0;j<10;j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
	int **matrix1 = CopyMatrix(matrix,10,10);
	for(int i = 0;i<10;i++){
		printf("\t");
		for(int j=0;j<10;j++){
			printf("%d\t",matrix1[i][j]);
		}
		printf("\n");
	}
	printf("Matrix allocated space is %s", FreeMatrix(matrix,10) == 1? "now free\n":"still allocate\n");
	printf("CopyMatrix allocated space is %s", FreeMatrix(matrix1,10) == 1? "now free\n":"still allocate\n");
}