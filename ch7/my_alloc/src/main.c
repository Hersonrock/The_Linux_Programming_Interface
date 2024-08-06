#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


#define ALIGN_SIZE 8 
#define HEADER_SIZE ALIGN_SIZE / 2
#define INPUT_SIZE 10

typedef struct{
        int header;
        char payload;
}block_struct;

int get_block_size(int in_size);
int main(int argc, char *argv[]){
        char buff[INPUT_SIZE];
        int payload_size, block_size, padding;
        char *f_break = sbrk(0);
        block_struct block;
         
        printf("Aligned to %d Bytes\n", ALIGN_SIZE);
        printf("Provide payload_size to allocate: ");
        fgets(buff, INPUT_SIZE, stdin);
        payload_size = (int)strtol(buff, NULL, 10);
        block_size = get_block_size(payload_size);
        padding = block_size - payload_size - HEADER_SIZE;
        printf("Block size will be: %d\n", block_size);
        printf("|Header|Payload|Padding|\n");
        printf("|%6d|%7d|%7d|\n", HEADER_SIZE, payload_size, padding);
        block.header = block_size | 0x1;

        printf("block.header: 0x%08x\n", block.header);

        brk(f_break); 
        return EXIT_SUCCESS;
}
int get_block_size(int in_size){
        in_size += HEADER_SIZE;
        int size = (in_size / ALIGN_SIZE) * ALIGN_SIZE;
        if(in_size % ALIGN_SIZE) size += ALIGN_SIZE;

        return size;
}

