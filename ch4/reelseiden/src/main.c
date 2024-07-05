#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        int *pieceSize;
        char **paths;
        int nSplit = 2;
        char input[CHAR_INPUT_SIZE];
        char inPath[MAX_PATH_SIZE];
        char outPath[MAX_PATH_SIZE];
        char piece1Path[MAX_PATH_SIZE];

        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        
        printf("Reelseiden......\n");
        printf("[s]plit\n");
        printf("[m]erge\n");
        printf("What do you want to do?: ");
        fgets(input, CHAR_INPUT_SIZE, stdin);

        if(input[0] == 's'){
        /// Split process

                initInput(inPath, &nSplit);

                paths = (char **)myAlloc(sizeof(char *) * nSplit);
                for(size_t i = 0; i < nSplit; i++){
                        paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
                }
                pieceSize = myAlloc(sizeof(int) * nSplit);

                splitFile(inPath, buf, pieceSize, paths, nSplit);
                free(pieceSize);
                for(size_t i = 0; i < nSplit; i++){
                        free(paths[i]);
                }
                free(paths);

        } 
        else if (input[0] == 'm'){
        // Merge process
                mergeInit(piece1Path, outPath);
                merge(piece1Path, outPath, buf);
        }
        else{

        }

        free(buf);

        return EXIT_SUCCESS;
}
