#include"../include/mem.h"
#include<stdlib.h>
#include<stdio.h>


void *myAlloc(size_t size){

        void *p = malloc(size);

        if(p == NULL){
                fprintf(stderr, "Error allocating memory\n");
                return NULL;
        }

        return p;
}

