#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char *argv[]){
        printf("This process ID is %d\n",getpid());
        printf("Sleeping...\n");
        sleep(10);
        printf("killing process parent with ID %d\n", getppid());
        if (kill(getppid(),9) != 0){
                perror("Failed to Kill parent\n");
        }
        else{
                printf("Parent killed succesfully\n");
        }
        printf("This process parent now has ID %d\n", getppid());
        sleep(100);
        return 0;
}
