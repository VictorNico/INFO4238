#include "file.h"

// look up access to send path
// read
_Bool RAccess(char *path){
	return access(path,R_OK) == 0?1:0;
}
// found
_Bool FAccess(char *path){
	return access(path,F_OK) == 0?1:0;
}
// executable
_Bool XAccess(char *path){
	return access(path,X_OK) == 0?1:0;
}
// write
_Bool WAccess(char *path){
	return access(path,W_OK) == 0?1:0;
}

// open and return a stream reader
FILE *GetReadStream(char *path){
	// verify access to path
	if(!FAccess(path)){
		// catch error in file opening operation
	    fprintf(stderr,"\n1 Error to open the file\n");
	}else if(FAccess(path) && !RAccess(path)){
		// catch error in file opening operation
	    fprintf(stderr,"\n2 Error to open the file\n");
	}else{ 
		// File pointer to read from file
	    FILE *readerStream;
	    // open file
	    readerStream = fopen(path, "r");
	    
	    return readerStream;
	}
	return NULL;
	
}
// open and return a stream writer
FILE *GetWriteStream(char *path){
	// verify access to path
	if(FAccess(path) && !WAccess(path)){
		// catch error in file opening operation
	    fprintf(stderr,"\n1 Error to open the file\n");
	}else{ 
		// if(!FAccess(path) && !WAccess(path)){
		// 	// catch error in file opening operation
		//     fprintf(stderr,"\n2 Error to open the file\n");
		// }else{
			// File pointer to read from file
	    FILE *readerStream;
	    // open file
	    readerStream = fopen(path, "w");
		return readerStream;
		// }
	}
	return NULL;
	
}
// close a file stream
_Bool CloseStream(FILE *file){
	if (file == NULL)
    {
        fprintf(stderr,
                "\nInvalid File Stream, please pass a valid stream\n");
        return 0;
    }
    fclose(file);
    return 1;
}
