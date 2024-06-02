#include<sys/time.h>
#include<stddef.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>

int main(int argc, char *argv[]){

        struct timeval tv;
        char *time;
        gettimeofday(&tv, NULL);
        
        time = ctime(&tv.tv_sec);
        
        printf("Seconds since epoc %ld\n", tv.tv_sec);
        printf("This means it is %s\n", time);
        sleep(5);

        return 0;
}
