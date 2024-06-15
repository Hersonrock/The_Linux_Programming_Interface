#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        int itemsRead;
        int *pieceSize;
        char **paths;
        int nSplit = 20;

        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        pieceSize = myAlloc(sizeof(int) * nSplit);
        paths = myAlloc(sizeof(char *) * nSplit);
        for(size_t i = 0; i < nSplit; i++){
                paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
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
