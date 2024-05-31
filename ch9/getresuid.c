#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main(int argc, char *argv[]){
        uid_t ruidInt = 0, euidInt = 0, suidInt = 0;
        uid_t *ruid = &ruidInt, *euid = &euidInt, *suid = &suidInt;

        if(getresuid(ruid, euid, suid) == -1){
                fprintf(stderr,"Failed to get ID's\n"); 
                if(errno == EFAULT){
                        fprintf(stderr, "One of the arguments specified "  
                                        "address is outside of the calling "
                                        "program's address space\n");
                }
        }
        else{
                printf("ruid=%d, euid=%d, suid=%d\n", ruidInt, euidInt, 
                                suidInt);
        }
        return 0;
}
