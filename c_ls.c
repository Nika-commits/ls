#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

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
        fprintf(stderr, "Error: Too many arguements \n");
        return 1;
    }

    const char *path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(path);
    if(!dir){
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0] == '.') continue;
        printf("%s \n", entry->d_name);
    }
    closedir(dir);

    return 0;
}


