#include"../include/merge.h"
#include"../include/fileio.h"

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
