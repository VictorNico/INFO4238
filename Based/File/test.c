// C program to implement
// File manipulation module

#include "file.h"

// Driver code
int main()
{
	// test reader getting stream
	FILE *reader = GetReadStream("../../ImagesOutput/test1.png");
	printf("%s", reader != NULL? "is ok\n":"not ok\n");
	// test writer getting stream
	FILE *writer = GetWriteStream("writer.cpp");
	printf("%s", writer != NULL? "is ok\n":"not ok\n");
	// testing close stream

	printf("readerStream is %s", CloseStream(reader) == 1? "now closed\n":"still opened\n");
	printf("writerStream is %s", CloseStream(writer) == 1? "now closed\n":"still opened\n");

}