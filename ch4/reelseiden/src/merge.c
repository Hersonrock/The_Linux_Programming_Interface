#include"../include/merge.h"
#include"../include/fileio.h"
#include"../include/mem.h"
#include"../include/split.h"

int merge(const char *path, char *buf){
        struct head *headerRead;
        int bufOffset = 0;
        char **outPaths; 

        headerRead = myAlloc(sizeof(struct head));
        readFile(PATH1, (char *)headerRead, HEADER_SIZE);
        outPaths= myAlloc(sizeof(char *) * headerRead->nSplit);
        for(size_t i = 0; i < headerRead->nSplit; i++){
                outPaths[i] = myAlloc(sizeof(char) * 20);
        }


        for(int i = 0; i < headerRead->nSplit; i++){
                sprintf(outPaths[i], "./piece%d", i + 1);        
                if(i){
                        readFile(outPaths[i], buf, headerRead->pieceS);
                        bufOffset = headerRead->headS - HEADER_SIZE + 
                                    headerRead->pieceS * (i - 1);
                        writeFile(buf, OUT, headerRead->pieceS,
                                0, bufOffset);
                }else
                {
                        readFile(outPaths[i], buf, headerRead->headS);
                        writeFile(buf, OUT, headerRead->headS - HEADER_SIZE,
                                        HEADER_SIZE, 0);
                }
        }

        for(size_t i = 0; i < headerRead->nSplit; i++){
                free(outPaths[i]);
        }
        free(headerRead);
        free(outPaths);


        return EXIT_SUCCESS;
}
