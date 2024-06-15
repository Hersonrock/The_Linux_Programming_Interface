#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        int itemsRead;
        int *pieceSize;
        char **paths;
        char *headerBuf;
        int nSplit = 20;
        struct head header;


        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        pieceSize = myAlloc(sizeof(int) * nSplit);
        paths = myAlloc(sizeof(char *) * nSplit);
        headerBuf = myAlloc(sizeof(struct head));
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
        }

        itemsRead = readFile(PATH, buf);
        split(nSplit, itemsRead, pieceSize, paths);

        header.headS = pieceSize[0];
        header.pieceS = pieceSize[1];
        header.nSplit = nSplit;
        //printf("sizeof struct head: %ld\n", sizeof(struct head));
        for(size_t i = 0; i < nSplit; i++){
                if(!i){
                        writeFile(headerBuf, paths[i], HEADER_SIZE);
                }
                writeFile(buf, paths[i], pieceSize[i]);
        }

        free(buf);
        free(pieceSize);
        free(headerBuf);
        for(size_t i = 0; i < nSplit; i++){
                free(paths[i]);
        }
        free(paths);

        return EXIT_SUCCESS;
}
