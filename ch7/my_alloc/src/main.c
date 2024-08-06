#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#define ALIGN_SIZE 8
#define HEADER_SIZE ALIGN_SIZE / 2
#define SIZE 5
#define PAYLOAD_SIZE SIZE * sizeof(int)

typedef struct{
        int header;
        char payload[PAYLOAD_SIZE];
}block_struct;

int get_block_size(int in_size);
int main(int argc, char *argv[]){
        int block_size;
        char *f_break = sbrk(0);
        block_struct block;
        int payload[SIZE] = {4, 3, 5, 6, 1}; 
        char *blk_ptr;

        printf("Aligned to %d Bytes\n", ALIGN_SIZE);
        block_size = get_block_size(PAYLOAD_SIZE);
        block.header = block_size | 0x1;
        memcpy(block.payload, payload, PAYLOAD_SIZE);

        blk_ptr = sbrk(block_size);
        memcpy(blk_ptr, &block, sizeof(block_struct)); 

        block_struct *new_block = (block_struct *)blk_ptr;
        int *new_payload = (int *)new_block->payload;
        for(size_t i = 0; i < SIZE; i++){
                printf("Payload[%ld] = %d\n", i, new_payload[i]);
        }

        brk(f_break); 
        return EXIT_SUCCESS;
}
int get_block_size(int in_size){
        in_size += HEADER_SIZE;
        int size = (in_size / ALIGN_SIZE) * ALIGN_SIZE;
        if(in_size % ALIGN_SIZE) size += ALIGN_SIZE;

        return size;
}

