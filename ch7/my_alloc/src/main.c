#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdint.h>

#define ALIGN_SIZE 16
#define HEADER_SIZE ALIGN_SIZE / 2
#define SIZE 5

int64_t get_block_size(int64_t in_size);
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

        //print64_ting values
        for(size_t i = 0; i < SIZE; i++){
                printf("Payload[%ld] = %d\n", i, payload_ptr[i]);
        }

        //Freeing memory forcefully
        brk(heap_start);
        return EXIT_SUCCESS;
}
int64_t get_block_size(int64_t in_size){
        in_size += HEADER_SIZE;
        int64_t size = (in_size / ALIGN_SIZE) * ALIGN_SIZE;
        if(in_size % ALIGN_SIZE) size += ALIGN_SIZE;
        printf("size= %ld\n", size);
        return size;
}

void *my_alloc(size_t size){
        int64_t block_size = get_block_size(size);
        int64_t header = block_size | 0x1;
        char *blk_ptr = sbrk(block_size);

        memcpy(blk_ptr, &header, sizeof(header));
        memset(blk_ptr + sizeof(header), 0, size);

        return blk_ptr + HEADER_SIZE;
}
