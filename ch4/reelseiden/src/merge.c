#include"../include/merge.h"
#include"../include/fileio.h"
#include"../include/mem.h"
#include"../include/split.h"

void mergeInit(char *piece1Path, char *outPath){

        memset(piece1Path, 0, MAX_PATH_SIZE); 
        printf("Input path of head piece: ");
        fgets(piece1Path, MAX_PATH_SIZE, stdin); 
        char *new_line = strchr(piece1Path, '\n');
        if(new_line != NULL) *new_line = '\0';

        memset(outPath, 0, MAX_PATH_SIZE); 
        printf("What would be the name of the Output File?: ");
        fgets(outPath, MAX_PATH_SIZE, stdin);
        new_line = strchr(outPath, '\n');
        if(new_line != NULL) *new_line = '\0';
}

int merge(char *piece1Path, char *outPath, char *buf){
        struct head *headerRead;
        int seekOffset = 0;
        char **outPaths; 

        headerRead = myAlloc(sizeof(struct head));
        readFile(piece1Path, (char *)headerRead, HEADER_SIZE);
        outPaths= myAlloc(sizeof(char *) * headerRead->nSplit);
        for(size_t i = 0; i < headerRead->nSplit; i++){
                outPaths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
        }

        char *trailing_1 = strchr(piece1Path, '1');
        if(trailing_1 != NULL) *trailing_1 = '\0';

        for(size_t i = 0; i < headerRead->nSplit; i++){
                sprintf(outPaths[i], "./%s%ld", piece1Path, i + 1);        
                if(i){
                        readFile(outPaths[i], buf, headerRead->pieceS);
                        seekOffset = headerRead->headS - HEADER_SIZE + 
                                    headerRead->pieceS * (i - 1);
                        writeFile(buf, outPath, headerRead->pieceS,
                                0, seekOffset);
                }else
                {
                        readFile(outPaths[i], buf, headerRead->headS);
                        writeFile(buf, outPath, headerRead->headS - HEADER_SIZE,
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
