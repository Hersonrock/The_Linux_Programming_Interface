#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define TEST_SIZE 24
int main(int argc, char *argv[]){
        
        char *heapStart = sbrk(0);
        printf("Program start of heap: %p\n", heapStart);
        
        printf("\tAloccating %d bytes[HEAP]\n", TEST_SIZE);
        char *dummyData = malloc(sizeof(char) * TEST_SIZE);
        printf("\tLocation of allocated data %p\n", dummyData);

        char *heapCurr = sbrk(0);
        printf("Current addr of heap:  %p\n", heapCurr);

        printf("\tAloccating %d bytes[HEAP]\n", TEST_SIZE);
        dummyData = malloc(sizeof(char) * TEST_SIZE);
        printf("\tLocation of allocated data %p\n", dummyData);

        heapCurr = sbrk(0);
        printf("Current addr of heap:  %p\n", heapCurr);

        return EXIT_SUCCESS;
}
