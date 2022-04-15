
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
// custom type definition
struct Images;
typedef struct Images Images;

// structure implementation
struct Images{
  int **image;
  int rows;
  int cols;
  char* format;
  char* chartName;
  char* comment;
  char* path;
};

// prototype
void drawKDEChartOfImageWithinPathInputAndOutpout(Images *image);
void LoadImageMatrix(Images *image);
void drawKDEChartOfImageWithinImageMatrix(Images *image);
void WriteNewImage(Images *image);
void ContrastComputation(Images *image,Images *imageC);
void LuminanceComputation(Images *image, Images *imageL);
void EqualizeComputation(Images *image, Images *imageE);
