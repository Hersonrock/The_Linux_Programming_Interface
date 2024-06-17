#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        //*****DEBUG****
        //int itemsReadDebug;
        //struct head *headDebug;
        //*************
        
        int bufOffset = 0;
        int itemsRead;
        int *pieceSize;
        char **paths;
        int nSplit = 10;
        struct head *header;


        //*****DEBUG****
        //headDebug = myAlloc(sizeof(struct head));
        //*************
        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        pieceSize = myAlloc(sizeof(int) * nSplit);
        paths = myAlloc(sizeof(char *) * nSplit);
        header = myAlloc(sizeof(struct head));
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
        }

        itemsRead = readFile(PATH, buf);
        split(nSplit, itemsRead, pieceSize, paths);

        /*
        header->headS = pieceSize[0];
        header->pieceS = pieceSize[1];
        header->nSplit = nSplit;
        
        printf("headS: %ld|pieceS: %ld|nSplit %d\n", header->headS,
                                                     header->pieceS,
                                                     header->nSplit);
                                                     */
        for(size_t i = 0; i < nSplit; i++){
                if(i == 0){
                        writeFile((char *)header, paths[i], HEADER_SIZE, 
                                        bufOffset, 0);
                        writeFile(buf, paths[i], pieceSize[i], 
                                        bufOffset, 24);
                }
                else{ 
                        bufOffset = pieceSize[0] + pieceSize[1] * (i - 1);
                        writeFile(buf, paths[i], pieceSize[i], bufOffset, 0);
                }
        }

        // *****DEBUG****
        /*
        itemsReadDebug = readFilePartial(PATH1, (char *)headDebug, HEADER_SIZE);
        printf("Reading frist %d bytes of %s\n", HEADER_SIZE, PATH0);
        printf("...read %d items\n", itemsReadDebug);
        printf("HeadS: %ld\n", headDebug->headS);
        printf("pieceS: %ld\n", headDebug->pieceS);
        printf("nSplit: %d\n", headDebug->nSplit);
        */
        //*************

        free(buf);
        free(pieceSize);
        free(header);
        //*****DEBUG****
        //free(headDebug);
        //*************
        for(size_t i = 0; i < nSplit; i++){
                free(paths[i]);
        }
        free(paths);

        return EXIT_SUCCESS;
}
