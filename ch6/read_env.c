#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

extern char **environ;
int main(int argc, char *argv[]){

        char **ep;
        
        char *var;
        var = getenv("LOGNAME");
        printf("LOGNAME = %s \n\n", var);


        for(ep = environ; *ep != NULL; ep++)
                fputs(*ep, stdout);

        return 0;
}
