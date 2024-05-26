#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

extern char etext, edata, end;

int main(int argc, char *argv[]){
        char *heapStart = sbrk(0);
        sbrk(8);
        char *heapEnd = sbrk(0);
        //strcpy(heapStart, "abcdefg\0");

        printf("PID:%d\n", getpid());
        
        printf("Final   brk= %p\n", heapEnd);
        printf("Initial brk= %p\n", heapStart);
        printf("BSS end      %p\n", &end);
        printf("edata end    %p\n", &edata);
        printf("etext end    %p\n", &etext);
        //printf("This is the content of heap: %s\n", heapStart);
        
        while(1){
                sleep(100);
        }

        return 0;
}
