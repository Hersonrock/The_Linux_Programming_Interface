#ifndef FILEIO
#define FILEIO  
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<string.h>

#define DEBUG 0
#define MAX_FILE_SIZE 536870912  //512MB
#define MAX_PATH_SIZE 20 
#define PATH "./inputFile"
//#define OUT_PATH "./outFile"
#define PATH1 "./piece1"
#define PATH2 "./piece2"
#define OUT "./outMerged"

struct head{
        long headS;
        long pieceS;
        int nSplit;
};
int openFile(const char *path, int flags, mode_t mode);
int readFile(const char *path, char *buf, size_t size);
int writeFile(char *buf, const char *path, int itemN, 
                int bufOffset, off_t seekOffset);

#endif // FILEIO
