#include <stdio.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <stdlib.h>

static const char* filename = "test_file.txt";

struct utimbuf getFileStats(const char* filename){
	struct stat currentFileStats;
	struct utimbuf newFileStats;

	stat(filename, &currentFileStats);

	newFileStats.actime = currentFileStats.st_atime; // Save access timestamp
	newFileStats.modtime = currentFileStats.st_mtime; // Save modification timestamp

	return newFileStats;
}

void writeToFile(const char* filename, const char* data){
	FILE* filePointer = fopen(filename, "w");
	fprintf(filePointer, "%s", data);
   	fclose(filePointer);
}

void setFileStats(const char* filename, struct utimbuf fileStats){
	utime(filename, &fileStats);
}

int main() {
	struct utimbuf fileStatsBeforeWriting = getFileStats(filename);
	writeToFile(filename, "hello world");
	setFileStats(filename, fileStatsBeforeWriting);
	return 0;
}