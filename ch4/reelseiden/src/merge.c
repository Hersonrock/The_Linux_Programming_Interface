#include"../include/merge.h"
#include"../include/fileio.h"
#include"../include/mem.h"
#include"../include/split.h"


int readMetadata(const char *path, char *buf, size_t size){

        int fd = openFile(path, O_RDONLY, 0);
        ssize_t itemsRead;

        memset(buf, '\0', size * sizeof(char));
        
        errno = 0;
        itemsRead = read(fd, buf, (size_t)size);
        if(errno != 0){
                perror("Error reading file\n");
                return EXIT_FAILURE;
        }

        close(fd);
        return itemsRead;
}

int merge(const char *path, char *buf){
        struct head *headerRead;
        int bufOffset = 0;
        char *outPaths[10] = {
                [0] = "./piece1", 
                [1] = "./piece2", 
                [2] = "./piece3", 
                [3] = "./piece4", 
                [4] = "./piece5", 
                [5] = "./piece6", 
                [6] = "./piece7", 
                [7] = "./piece8", 
                [8] = "./piece9", 
                [9] = "./piece10" 
        };

        headerRead = myAlloc(sizeof(struct head));

        readMetadata(PATH1, (char *)headerRead, HEADER_SIZE);

        printf("Reading frist %d bytes of %s\n", HEADER_SIZE, PATH1);
        printf("HeadS: %ld\n", headerRead->headS);
        printf("pieceS: %ld\n", headerRead->pieceS);
        printf("nSplit: %d\n", headerRead->nSplit);

        for(int i = 0; i < headerRead->nSplit; i++){
                readFile(outPaths[i], buf);
                if(i){
                        bufOffset = headerRead->headS - HEADER_SIZE + 
                                    headerRead->pieceS * (i - 1);
                        writeFile(buf, OUT, headerRead->pieceS,
                                0, bufOffset);
                        continue;
                }
                
                writeFile(buf, OUT, headerRead->headS - HEADER_SIZE,
                                HEADER_SIZE, 0);
        }

        free(headerRead);

        return EXIT_SUCCESS;
}
