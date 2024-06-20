#ifndef MERGE
#define MERGE
#include<stddef.h>
int readMetadata(const char *path, char *buf, size_t size);
int merge(const char *path, char *buf);
#endif //MERGE
