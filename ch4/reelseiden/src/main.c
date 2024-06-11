#include "../include/fileio.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        buf = malloc(sizeof(char) * MAX_FILE_SIZE);
        int itemsRead;
        int pieceSize[2] = { 
                [0] = 0,
                [1] = 0
        };
        char *paths[2] = {
                [0] = PATH1,
                [1] = PATH2
        };

        itemsRead = readFile(PATH, buf);

        pieceSize[0] = itemsRead / 2;
        pieceSize[1] = itemsRead - pieceSize[0]; 

        writeFile(buf, paths[0], pieceSize[0]);
        writeFile(buf, paths[1], pieceSize[1]);

        free(buf);
        return EXIT_SUCCESS;
}
