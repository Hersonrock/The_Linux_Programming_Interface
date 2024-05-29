#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>

#define MAX_PATH_SIZE 19 //matching pid_max 2**22 /proc/sys/kernel/pid_max 
                         // /proc/$$$$$$$/maps\0
#define MAX_FILE_SIZE 65536


long toKB(long input);
void readFile(char *buf, FILE *fd);
FILE *openFile(long pid);
int lineCount(char *buf);
void digestAddresses(char *buf, long *addresses, int count);
void printMap(long *addresses, int count);
long str_tol(char *ptr, char **endptr, int base);


int main(int argc, char *argv[]){
        long pid;
        FILE *fd;
        char buf[MAX_FILE_SIZE];
        int count = 0;
        
        if(argc != 2){
                fprintf(stderr, "USAGE: %s [PID]\n", argv[0]);
                _exit(EXIT_FAILURE);
        }

        pid = str_tol(argv[1], NULL, 10);
        if(pid > 4194304){ // pid_max
                fprintf(stderr, "Pid is too big\n");
                _exit(EXIT_FAILURE);
        }

        fd = openFile(pid);
        readFile(buf, fd); 
        
        count = lineCount(buf);
        count *= 2; //there will be two Hex values per line

        long addresses[count];
        memset(addresses, 0, sizeof(long) * count);

        digestAddresses(buf, addresses, count);
        printMap(addresses, count);

        fclose(fd);
        return 0;
}

FILE *openFile(long pid){

        FILE *fd;
        char map_path[MAX_PATH_SIZE];

        memset(map_path, '\0', MAX_PATH_SIZE);
        sprintf(map_path, "/proc/%ld/maps", pid);

        fd = fopen(map_path, "r");
        if(fd == NULL){

                fprintf(stderr,"error opening file /proc/%ld/maps\n", pid);
                _exit(EXIT_FAILURE);
        }
        
        return fd;

}
void readFile(char *buf, FILE *fd){

        memset(buf, '\0', sizeof(char) * MAX_FILE_SIZE);
        fread(buf, 1, MAX_FILE_SIZE - 1, fd);
        if ( feof(fd) == 0 ){ // ignored if the whole file is read          
                if ( ferror(fd) != 0){                                      
                        fprintf(stderr, "Error reached when reading file\n");            
                        _Exit(EXIT_FAILURE);                                              
                }                                                               
                fprintf(stderr, "Error EOF not reached\n");                              
                fprintf(stderr, "File bigger than limit\n");
                _Exit(EXIT_FAILURE);                                                      
        }                                                                      
}


int lineCount(char *buf){
        int counter = 0;
        for( int i = 0; i < MAX_FILE_SIZE - 1; i++){
                if(buf[i] == '\n')
                        counter++;
                if(buf[i] == '\0')
                        break;
        }
        return counter - 1; // skipping last line vsyscall 
                            // Because address is bigger than long long
}

void digestAddresses(char *buf, long *addresses, int count){
        
        char *endptr = buf;

        for( int i = 0; i < count; i++){

                addresses[i] = str_tol(endptr, &endptr, 16);
        
                endptr++;
                i++;
                addresses[i] = str_tol(endptr, &endptr, 16);

                while(!((*endptr == '\n') || (*endptr == '\0'))){
                        endptr++;
                }
        }

}

long str_tol(char *ptr, char **endptr, int base){
        long out = 0;
        out = strtol(ptr, endptr, base);
        if(errno == ERANGE){
                fprintf(stderr, "Argument out of range\n");
                if(out == LONG_MAX)
                        fprintf(stderr, "Overflow\n");
                if(out == LONG_MIN)
                        fprintf(stderr, "Underflow\n");

                _exit(EXIT_FAILURE);
        }
        if(errno == EINVAL){
                fprintf(stderr, "Unsupported value");
                _exit(EXIT_FAILURE);
        }



        return out;
}

void printMap(long *addresses, int count){
        
        long diff = 0;

        printf("--%lx--", addresses[0]);

        for (int i = 1; i < count; i++){
                diff = addresses[i] - addresses[i - 1];
                if ((diff != 0) && (i % 2 != 0) ){
                        printf("%ldKB", toKB(diff));
                        printf("--%lx--\n", addresses[i]);
                }
                else if ((diff != 0) && (i % 2 == 0) ){
                        printf("[%ldKB]\n", toKB(diff));
                        printf("--%lx--", addresses[i]);
                }
                else{ 
                        printf("--%lx--", addresses[i]);
                }
        }
}

long toKB(long input){
       long out = labs(input) / 1024;

       return out;
}
