#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

char *get_username(){
    struct passwd name = *getpwuid(getuid());
    return name.pw_name;
}

int main(void){
    printf("Hi, %s\n", get_username());
    return 0;
}

