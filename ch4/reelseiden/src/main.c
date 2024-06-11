#include "../include/fileio.h"

int main(int argc, char *argv[argc + 1]){

        char buf[MAX_FILE_SIZE];
        readFile(PATH, buf);

        return EXIT_SUCCESS;
}
