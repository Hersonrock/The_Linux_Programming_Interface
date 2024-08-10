#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define ALIGN_SIZE 16
#define HEADER_SIZE ALIGN_SIZE / 2
#define SIZE 5

int get_block_size(int in_size);
void *my_alloc(size_t size);
int main(int argc, char *argv[]){
        char *heap_start = sbrk(0);
        int *payload_ptr;

        //allocating memory
        payload_ptr = my_alloc(SIZE * sizeof(int));

        //asigning values
        for(size_t i = 0; i < SIZE; i++){
                payload_ptr[i] = i + 1;
        }

        //printing values
        for(size_t i = 0; i < SIZE; i++){
                printf("Payload[%ld] = %d\n", i, payload_ptr[i]);
        }

        //Freeing memory forcefully
        brk(heap_start);
        return EXIT_SUCCESS;
}
int get_block_size(int in_size){
        in_size += HEADER_SIZE;
        int size = (in_size / ALIGN_SIZE) * ALIGN_SIZE;
        if(in_size % ALIGN_SIZE) size += ALIGN_SIZE;
        return size;
}

void *my_alloc(size_t size){
        int block_size = get_block_size(size);
        int header = block_size | 0x1;
        char *blk_ptr = sbrk(block_size);

        memcpy(blk_ptr, &header, sizeof(header));
        memset(blk_ptr + sizeof(header), 0, size);

        return blk_ptr + HEADER_SIZE;
}
