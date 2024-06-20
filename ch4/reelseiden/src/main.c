#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        int bufOffset = 0;
        int itemsRead;
        int *pieceSize;
        char **paths;
        int nSplit = 10;
        struct head *headerToWrite;


        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        pieceSize = myAlloc(sizeof(int) * nSplit);
        paths = myAlloc(sizeof(char *) * nSplit);
        headerToWrite = myAlloc(sizeof(struct head));
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
        }

        itemsRead = readFile(PATH, buf);
        split(nSplit, itemsRead, pieceSize, paths);

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
                        bufOffset = pieceSize[0] - HEADER_SIZE + pieceSize[1] * (i - 1);
                        writeFile(buf, paths[i], pieceSize[i], bufOffset, 0);
                }
        }

        merge(OUT, buf);

        free(buf);
        free(pieceSize);
        free(headerToWrite);
        for(size_t i = 0; i < nSplit; i++){
                free(paths[i]);
        }
        free(paths);

        return EXIT_SUCCESS;
}
