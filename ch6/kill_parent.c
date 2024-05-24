#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char *argv[]){
        pid_t parentPID,childPID;
        
        parentPID = getpid();
        printf("This process PPID is %d\n", getppid());
        printf("This process PID is %d\n",parentPID);
        //printf("killing process parent with ID %d\n", getppid());
        childPID = fork(); 
        printf("Child PID is %d\n", childPID);
        if (kill(parentPID,15) != 0){
                perror("Failed to Kill parent\n");
        }
        else{
                printf("Parent killed succesfully\n");
        }
        printf("The current PPID is %d\n", getppid());        
        sleep(100);
        printf("Sleep over, exiting pid %d, with ppid %d\n", getpid(), 
                getppid());
        return 0;
}
