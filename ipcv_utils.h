
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
  double* Hist;
  char format[3];
  char* chartName;
  char* outPath;
  char* comment;
  char* path;
  _Bool rotated;
};

// prototype
void DrawKDEChartOfImageWithinPathInputAndOutpout(Images *image);
void LoadImageMatrix(Images *image);
void DrawKDEChartOfImageWithinImageMatrix(Images *image);
// TODO: 
void WriteNewImage(Images *image);
void InvertComputation(Images *image,Images *imageC);
void GetInteger(char *message,int *variable);
void GetString(char *message,char *variable);
void GetChar(char *message,char *variable);
void Rotate90DegreeClockwizeImage(Images *image,Images *imageR);
void Rotate90DegreeAntiClockwizeImage(Images *image,Images *imageR);
void CopyImageData(Images *image,Images *imageC);
long long IntToBin(int n);
int BinToInt(long long n);
// void smoothComputation(Images *image,Images *imageC);
// void IncBrightnessComputation(Images *image, Images *imageL);
// void DecBrightnessComputation(Images *image, Images *imageL);
// void IncContrastComputation(Images *image, Images *imageL);
// void DecContrastComputation(Images *image, Images *imageL);
// void EqualizationComputation(Images *image, Images *imageE);

/*
  about invalidate format of custom write files, it's due to missing that the first pixel code the max length of value so will be 1 or 255.
*/