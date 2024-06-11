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
#define MAX_FILE_SIZE 536870912 //512MiB
#define PATH "./inputFile"

int openFile(const char *path, int flags);
int readFile(const char *path, char *buf);
int writeFile(const char *path);

#endif // FILEIO
