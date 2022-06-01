// header
#include "../Header/header.h"
// prototypes
_Bool RAccess(char *path);
_Bool FAccess(char *path);
_Bool XAccess(char *path);
_Bool WAccess(char *path);
FILE *GetReadStream(char *path);
FILE *GetWriteStream(char *path);
_Bool CloseStream(FILE *file);