#include "../include/fileio.h"

int main(int argc, char *argv[argc + 1]){

        char *buf;
        buf = malloc(sizeof(char) * MAX_FILE_SIZE);
        int itemsRead;

        itemsRead = readFile(PATH, buf);
        writeFile(buf, OUT_PATH, itemsRead);

        free(buf);
        return EXIT_SUCCESS;
}
