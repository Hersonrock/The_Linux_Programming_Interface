#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>

#define MAX_PATH_SIZE 19 //matching pid_max 2**22  
#define MAX_FILE_SIZE 65536


long toKB(long input);
void readFile(char buff[MAX_FILE_SIZE], const size_t size, FILE *fd);
FILE *openFile(char map_path[MAX_PATH_SIZE], long pid);
int lineCount(char buf[MAX_FILE_SIZE], FILE *fd);

int main(int argc, char *argv[]){
        long pid;
        FILE *fd;
        char map_path[MAX_PATH_SIZE];
        char buf[MAX_FILE_SIZE];
        int count = 0;

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

        fd = openFile(map_path, pid);
        readFile(buf, MAX_FILE_SIZE, fd); 
        count = lineCount(buf, fd);

        fclose(fd);
        return 0;
}

FILE *openFile(char map_path[MAX_PATH_SIZE], long pid){

        FILE *fd;

        memset(map_path, '\0', MAX_PATH_SIZE);
        sprintf(map_path, "/proc/%ld/maps", pid);

        fd = fopen(map_path, "r");
        if(fd == NULL){
                fprintf(stderr,"error opening file /proc/%ld/maps\n", pid);
                _exit(EXIT_FAILURE);
        }
        
        return fd;

}
void readFile(char buf[MAX_FILE_SIZE], const size_t size, FILE *fd){

        fread(buf, 1, MAX_FILE_SIZE, fd);
        if ( feof(fd) == 0 ){ // ignored if the whole file is read          
                if ( ferror(fd) != 0){                                      
                        printf("Error reached when reading file\n");            
                        _Exit(EXIT_FAILURE);                                              }                                                               
                printf("Error EOF not reached\n");                              
                _Exit(EXIT_FAILURE);                                                      
        }                                                                      
}


int lineCount(char buf[MAX_FILE_SIZE], FILE *fd){
        int counter = 0;
        for( int i = 0; i < MAX_FILE_SIZE; i++){
                if(buf[i] == '\n')
                        counter++;
                if(!feof(fd))
                        break;
        }

        return counter;
}
long toKB(long input){
       long out = labs(input) / 1024;

       return out;
}
