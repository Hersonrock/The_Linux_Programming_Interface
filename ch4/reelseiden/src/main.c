#include "../include/fileio.h"
#include "../include/split.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        buf = malloc(sizeof(char) * MAX_FILE_SIZE);
        int itemsRead;
        int *pieceSize;
        char **paths;
        int nSplit = 20;
        pieceSize = malloc(sizeof(int) * nSplit);
        paths = malloc(sizeof(char *) * nSplit);
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = malloc(sizeof(char) * MAX_PATH_SIZE);
        }

        itemsRead = readFile(PATH, buf);

        split(nSplit, itemsRead, pieceSize, paths);

        for(size_t i = 0; i < nSplit; i++){
                writeFile(buf, paths[i], pieceSize[i]);
        }

        free(buf);
        for(size_t i = 0; i < nSplit; i++){
                free(paths[i]);
        }
        free(paths);


        return EXIT_SUCCESS;
}
