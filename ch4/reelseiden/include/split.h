#ifndef SPLIT
#define SPLIT
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_PATH_SIZE 20 
#define MAX_SPLIT_N 100
#define HEADER_SIZE 24
#define CHAR_INPUT_SIZE 3
#define SPLIT_INPUT_SIZE 4

void split(int nSplit, int readItems, int *pieceSize,
          char *path , char * pieceName, char **paths);
void splitFile(char *path, char *buf, int *pieceSize, char *pieceName, 
                char **paths, int nSplit);
void initInput(char *pathInput, char *pieceName, int *nSplit);



#endif //SPLIT
