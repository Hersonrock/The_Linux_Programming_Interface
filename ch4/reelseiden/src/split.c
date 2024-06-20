#include "../include/split.h"


void split(int nSplit, int readItems, int *pieceSize, char **paths){

        int step = readItems / nSplit;
        float fstep = readItems % nSplit;
        //int extra = readItems - (step * nSplit);

        for(size_t i = 0; i < nSplit; i++){
        
                if(i){
                        pieceSize[i] = step;
                }
                else if(fstep > 0){
                        pieceSize[i] = step + fstep + HEADER_SIZE;
                }else{
                        pieceSize[i] = step + HEADER_SIZE;
                }
                sprintf(paths[i], "./piece%ld", i + 1);        
        }

}
