#include "../include/fileio.h"

int openFile(const char *path, int flags, mode_t mode){

        int fd;

        if((fd = open(path, flags, mode)) == -1){
                fprintf(stderr, "Failed opening file %s\n", path);
                perror("Failed opening file\n");
        }

        return fd;

}

int readFile(const char *path, char *buf){

        int fd = openFile(path, O_RDONLY, 0);
        ssize_t itemsRead;
        off_t curr,end;

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

        return itemsRead;
}

int writeFile(char *buf, const char *path, int itemN){
        
        int flags = O_WRONLY | O_CREAT | O_TRUNC; 
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

        int fd = openFile(path, flags, mode);
        
        errno = 0;
        if((write(fd, buf, itemN)) != itemN){
                fprintf(stderr, "Error, Partial Write\n");
                return EXIT_FAILURE;
        }

        if(errno != 0 ){
                perror("Failed writing to file\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
