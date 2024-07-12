#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

#define INPUT_PATH "./inputFile"
#define MOVE 10
int main(int argc, char *argv[]){
        int fd;
        //mode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
        off_t  curr, new_off;

        //int open(const char *pathname, int flags, ...
        /* mode_t mode */ 
        fd = open(INPUT_PATH, O_RDONLY); 
        if(fd == -1){
                fprintf(stderr, "Failed open file %s\n", INPUT_PATH);
                return EXIT_FAILURE;
        }
        printf("File %s opened succefully\n", INPUT_PATH);
        curr = lseek(fd, 0 , SEEK_CUR);
        printf("File initial offset: %ld\n", curr);
        new_off = lseek(fd, MOVE , SEEK_SET);
        printf("Moving offset +%d bytes\n", MOVE);
        printf("File current offset: %ld\n", new_off);


        return EXIT_SUCCESS;
}

