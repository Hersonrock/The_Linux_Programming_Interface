#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define NAME "SHELL"
#define VALUE "test"
extern char **environ;

size_t sizeof_str(char *input);
int my_setenv(char *name, char *value, int overwrite, char *string);
int my_unsetenv(char *name);

int main(int argc, char *argv[]){

        size_t str_size = sizeof_str(NAME) + sizeof_str(VALUE) + 2;
        char *string = malloc(sizeof(char) * str_size);

        my_setenv(NAME, VALUE, 1, string);
        printf("[main]Variable value set %s\n", getenv("SHELL"));
        my_unsetenv(NAME);
        printf("[main]Variable %s exists?: %s\n", NAME, getenv("SHELL"));

        free(string);
        return EXIT_SUCCESS;
}
int my_setenv(char *name, char *value, int overwrite, char *string){
        
        strcat(string, name);
        strcat(string, "=");
        strcat(string, value);
        if(getenv(name) == NULL || overwrite != 0){       
                putenv(string);
        }else {
                printf("ENV variable already exists\n");
        }
        return 0;
}

size_t sizeof_str(char *input){
        size_t n = 0;
        for(size_t i = 0;;i++){
                if(input[i] == '\n' || input[i] == '\0'){
                        break;
                }
                n++;
        }
        return n;
}
int my_unsetenv(char *name){
        char **ep;
        char *env_name; 
        if(getenv(name) == NULL){
                printf("ENV var does not exist\n");
                return -1;
        }

        for(ep = environ; *ep != NULL; ep++){
                env_name = strtok(*ep, "=");
                if(!strcmp(name,env_name)){
                        *ep = NULL;
                }
        }
        return 0;
}
