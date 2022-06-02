// header
#include "../Header/header.h"
// header
#include "../File/file.h"
#include "../Matrix/matrix.h"
// libs importation
#include "../../Libs/Plot/pbPlots.h"
#include "../../Libs/Plot/supportLib.h"
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
  int maxPixel;
  double* Hist;
  char format[3];
  char* chartName;
  char* outPath;
  char* comment;
  char* path;
  _Bool rotated;
};
// prototypes
Images *ReadNotCompressedImg(char *path);
_Bool WriteNotCompressedImg(Images *image);
_Bool FreeIInstance(Images *img);
double *GetHist(Images *image);
_Bool PlotHist(Images *image);
double GetLuminance(Images *image);
_Bool CopyImageData(Images *src,Images *dst);
double GetContrastEcartType(Images *image);
double GetContrastMinMax(Images *image);
Images *AdditionOfTwoImages(Images *image1,Images *image2);
Images *ImageTime(Images *image, double factor);
Images *SoustractionOfTwoImages(Images *image1,Images *image2);
Images *LinearTransform(Images *image);
Images *LinearSaturatedTransform(Images *image, int min, int max);