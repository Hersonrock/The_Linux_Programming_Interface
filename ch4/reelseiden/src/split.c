#include "../include/split.h"
#include "../include/fileio.h"
#include "../include/mem.h"

void split(int nSplit, int readItems, int *pieceSize, char *path ,char **paths){

        int step = readItems / nSplit;
        float fstep = readItems % nSplit;

        for(size_t i = 0; i < nSplit; i++){
        
                if(i){
                        pieceSize[i] = step;
                }
                else if(fstep > 0){
                        pieceSize[i] = step + fstep + HEADER_SIZE;
                }else{
                        pieceSize[i] = step + HEADER_SIZE;
                }
                sprintf(paths[i], "./piece%ld", i + 1);        
        }

}
void splitFile(char *path, char *buf, int *pieceSize, char **paths, int nSplit){
        int bufOffset = 0;
        int itemsRead;

        struct head *headerToWrite;
        headerToWrite = myAlloc(sizeof(struct head));

        itemsRead = readFile(path, buf, MAX_FILE_SIZE);
        split(nSplit, itemsRead, pieceSize, path, paths);

        headerToWrite->headS = pieceSize[0];
        headerToWrite->pieceS = pieceSize[1];
        headerToWrite->nSplit = nSplit;
        
        for(size_t i = 0; i < nSplit; i++){
                if(i == 0){
                        writeFile((char *)headerToWrite, paths[i], HEADER_SIZE, 
                                        bufOffset, 0);
                        writeFile(buf, paths[i], pieceSize[i] - HEADER_SIZE, 
                                        bufOffset, HEADER_SIZE);
                }
                else{ 
                        bufOffset = pieceSize[0] - HEADER_SIZE + pieceSize[1] *
                                (i - 1);
                        writeFile(buf, paths[i], pieceSize[i], bufOffset, 0);
                }
        }

        free(headerToWrite);
}
