#include "../include/fileio.h"
#include "../include/split.h"
#include "../include/merge.h"
#include "../include/mem.h"

#define CHAR_INPUT_SIZE 3
int main(int argc, char *argv[argc + 1]){

        char *buf;
        int *pieceSize;
        char **paths;
        int nSplit = 2;
        char input[CHAR_INPUT_SIZE];
        char splitInput[4];

        buf = myAlloc(sizeof(char) * MAX_FILE_SIZE);
        
        printf("Reelseiden......\n");
        printf("[s]plit\n");
        printf("[m]erge\n");
        printf("What do you want to do?: ");
        
        fgets(input, CHAR_INPUT_SIZE, stdin);
        if(input[0] == 's'){
        /// Split process
                printf("How many pieces[2-100]: ");
                fflush(stdout);
                memset(splitInput, 0, sizeof(splitInput)); 
                fgets(splitInput, 4, stdin);
                nSplit = atoi(splitInput);
                if(nSplit < 2 || nSplit > 100){
                        fprintf(stderr,"Invalid number of pieces\n");
                        return EXIT_FAILURE;
                }

                paths = (char **)myAlloc(sizeof(char *) * nSplit);
                for(size_t i = 0; i < nSplit; i++){
                        paths[i] = myAlloc(sizeof(char) * MAX_PATH_SIZE);
                }
                pieceSize = myAlloc(sizeof(int) * nSplit);

                splitFile(PATH, buf, pieceSize, paths, nSplit);
                free(pieceSize);
                for(size_t i = 0; i < nSplit; i++){
                        free(paths[i]);
                }
                free(paths);

        } 
        else if (input[0] == 'm'){
        // Merge process
                merge(OUT, buf);
        }
        else{

        }

        free(buf);

        return EXIT_SUCCESS;
}
