#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>

#define MAX_PATH_SIZE 19 //matching pid_max 2**22  


long toKB(long input);

int main(int argc, char *argv[]){
        long pid;
        int fd;
        char map_path[MAX_PATH_SIZE];
        int offset;

        if(argc != 2){
                fprintf(stderr, "USAGE: %s [PID]\n", argv[0]);
                _exit(EXIT_FAILURE);
        }
        errno = 0;
        pid = strtol(argv[1], NULL, 10);
        if(errno == ERANGE){
                fprintf(stderr, "argument out of range");
                _exit(EXIT_FAILURE);
        }
        memset(map_path, '\0', MAX_PATH_SIZE);
        sprintf(map_path, "/proc/%ld/maps", pid);
        fd = open(map_path, O_RDONLY);
        if(fd == -1){
                fprintf(stderr,"error opening file /proc/%ld/maps\n", pid);
                _exit(EXIT_FAILURE);
        }

        errno = 0;
        lseek(fd, -1, SEEK_END);
        if (errno == -1)
                printf("LOL it fails\n");
        offset = lseek(fd, 0, SEEK_CUR);
        lseek(fd, 0, SEEK_SET);
        
        printf("File size is %d bytes\n", offset);

        close(fd);



        return 0;
}


long toKB(long input){
       long out = labs(input) / 1024;

       return out;
}
