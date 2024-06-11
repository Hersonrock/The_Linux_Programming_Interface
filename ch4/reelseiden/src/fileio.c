#include "../include/fileio.h"

int openFile(const char *path, int flags){

        int fd;

        if((fd = open(path, flags)) == -1){
                fprintf(stderr, "Failed opening file %s\n", path);
                perror("Filed opening file\n");
        }

        return fd;

}

int readFile(const char *path, char *buf){

        int fd = openFile(path, O_RDONLY);
        ssize_t itemsRead;
        off_t curr,end;

        buf = malloc(MAX_FILE_SIZE * sizeof(char));
        memset(buf, '\0', MAX_FILE_SIZE * sizeof(char));
        
        errno = 0;
        itemsRead = read(fd, buf, (size_t)MAX_FILE_SIZE);
        if(errno != 0){
                perror("Error reading file\n");
                return EXIT_FAILURE;
        }

        if(DEBUG){
                errno = 0;
                curr = lseek(fd, 0, SEEK_CUR);
                end = lseek(fd, 0 , SEEK_END);
                if(errno != 0){
                        perror("Error with lseek\n");
                        return EXIT_FAILURE;
                }

                if(curr == end){
                        printf("Read whole file,EOF reached\n");

                }
                else if(curr < end){
                        printf("File is bigger than MAX_FILE_SIZE\n");
                }

                printf("Offset is at: %ld\n", curr);
                printf("End is at: %ld\n", end);
                printf("itemsRead: %ld\n", itemsRead);
        }


        free(buf);

        return EXIT_SUCCESS;
}

