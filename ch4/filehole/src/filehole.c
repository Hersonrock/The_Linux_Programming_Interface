#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<ctype.h>

void printr(char *buff, char mode, int nRead){
        for(int j = 0; j < nRead; j++){
                if(mode == 'r'){
                        char c = isprint(buff[j]) ? buff[j] : '?';
                        fputc(c, stdout);
                }
                else{
                        printf("%02x ", buff[j]);
                }
        }
        printf("\n");
}
int main(int argc, char *argv[]){
        int fd;
        int openFlags;
        mode_t openMode;
        char *buff;
        long length, offset;
        ssize_t nRead,nWritten;


        if(argc < 3 || strcmp(argv[1], "--help") == 0){
                printf("[USAGE] %s {r<length>|R<length>|w<string>|s<offset>}"
                                "...\n",argv[0]);
                _exit(1);
        }       

        openFlags = O_CREAT|O_RDWR;
        openMode = S_IRWXU|S_IRWXG|S_IROTH;
        
        fd = open(argv[1],openFlags,openMode);
        if(fd == -1){
                printf("Error opening %s\n", argv[1]);
                _exit(1);
        }
        
        for(int iparam = 2; iparam < argc; iparam++){
                switch(argv[iparam][0]){
                        case 'r':
                        case 'R':
                                length = strtol((argv[iparam] +  1), NULL, 10);
                                buff = malloc(length);
                                if( buff == NULL){
                                        printf("Error allocating on stack\n");
                                        _exit(1);
                                }
                                nRead = read(fd, buff, (size_t)length);
                                if(nRead == -1){
                                        printf("Error writing to file\n");
                                        _exit(1);
                                }
                                if(nRead != 0){
                                        printf("%s: ",argv[iparam]);
                                        printr(buff, argv[iparam][0], 
                                                        (int)nRead);
                                }
                                else{
                                        printf("%s: EOF\n",argv[iparam]);
                                }
                                free(buff);
                                break;
                        case 'w':
                                nWritten = write(fd, argv[iparam]+1,
                                                strlen(argv[iparam]+1));
                                if(nWritten == -1){
                                        printf("Error writing to %s\n",
                                                        argv[1]);
                                        _exit(1);
                                }
                                printf("%s: wrote %ld bytes\n",
                                                argv[iparam],(long)nWritten);
                                break;
                        case 's':
                                offset = strtol(argv[iparam] + 1, NULL, 10);
                                if((lseek(fd, offset, SEEK_SET) == -1)){
                                        printf("Failed to seek\n");
                                        _exit(1);
                                }
                                printf("%s: seek succeeded\n", argv[iparam]);
                                break;
                        default:
                                printf("Argument must start with " 
                                                "[rRws]: %s\n",argv[iparam]);
                }
        }
        return 0;
}
