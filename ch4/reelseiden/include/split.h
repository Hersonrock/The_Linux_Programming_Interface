#ifndef SPLIT
#define SPLIT
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_PATH_SIZE 10 
#define MAX_SPLIT_N 100
#define HEADER_SIZE 24

void split(int nSplit, int readItems, int *pieceSize, char **paths);
void splitFile(char *path, char *buf, int *pieceSize, char **paths, int nSplit);


#endif //SPLIT
