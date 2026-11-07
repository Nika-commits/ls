#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

char *get_username(){
    struct passwd name = *getpwuid(getuid());
    return name.pw_name;
}

enum FLAGS {
    L, 
    T, 
    S
}; 

int main(int argc, char *argv[]){
    printf("Hi, %s \n", get_username());
    
    if(argc > 2){
        printf("Please enter at most 2 flags \n");
        return 0;
    }

    const char *path = (argc > 1) ? argv[1] : ".";
    printf("%s \n", path);
    return 0;
}

