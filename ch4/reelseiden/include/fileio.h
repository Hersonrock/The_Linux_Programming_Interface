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
#define MAX_FILE_SIZE 536870912 
#define PATH "./inputFile"
#define OUT_PATH "./outFile"

int openFile(const char *path, int flags, mode_t mode);
int readFile(const char *path, char *buf);
int writeFile(char *buf, const char *path, int itemN);

#endif // FILEIO
