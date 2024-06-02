#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>


int main(int argc, [[maybe_unused]] char *argv[argc + 1]){
#ifdef _POSIX_MQ_PRIO_MAX
        printf("POSIX MQ PRIO MAX: %d\n", _POSIX_MQ_PRIO_MAX);
#else
        printf("_POSIX_MQ_PRIO_MAX is not defined on this system.\n");
#endif

        printf("Limit on message priority in POSIX message queue %d\n",
                        _SC_MQ_PRIO_MAX);
        printf("Limit on path name %d \n", _PC_NAME_MAX);

        return EXIT_SUCCESS;

};
