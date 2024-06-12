#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"


void allocCheck(void *ptr){
        if(ptr == NULL){
                fprintf(stderr, "Error allocating memory\n");
                _exit(-1);
        }
}

int main(int argc, char *argv[argc + 1]){

        char *buf;
        buf = malloc(sizeof(char) * MAX_FILE_SIZE);
        allocCheck(buf);

        int itemsRead;
        int *pieceSize;
        char **paths;
        int nSplit = 20;
        pieceSize = malloc(sizeof(int) * nSplit);
        allocCheck(pieceSize);
        
        paths = malloc(sizeof(char *) * nSplit);
        allocCheck(paths);
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = malloc(sizeof(char) * MAX_PATH_SIZE);
                allocCheck(paths[i]);
        }

        itemsRead = readFile(PATH, buf);

        split(nSplit, itemsRead, pieceSize, paths);

        for(size_t i = 0; i < nSplit; i++){
                writeFile(buf, paths[i], pieceSize[i]);
        }

        free(buf);
        free(pieceSize);
        for(size_t i = 0; i < nSplit; i++){
                free(paths[i]);
        }
        free(paths);


        return EXIT_SUCCESS;
}
