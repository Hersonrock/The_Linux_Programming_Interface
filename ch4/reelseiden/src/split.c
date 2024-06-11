#include "../include/split.h"


void split(int nSplit, int readItems, int *offsets, char **paths){

        int step = readItems / nSplit;
        float fstep = readItems % nSplit;
        int extra = readItems - (step * nSplit);

        for(size_t i = 0; i < nSplit; i++){
        
                if(i){
                        offsets[i] = step;
                }
                else if(fstep > 0){
                        offsets[i] = step + extra;
                }else{
                        offsets[i] = step;
                }
                sprintf(paths[i], "./piece%ld", i + 1);        
        }

}
