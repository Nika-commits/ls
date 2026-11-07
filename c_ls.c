#include <pwd.h>
#include <stdbool.h>
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

bool has_a_flag = false;
int main(int argc, char *argv[]){
    printf("Hi, %s \n", get_username());
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1){
        switch (opt) {
            case 'a':
                has_a_flag = true;
                break;
            default:
                fprintf(stderr, "usage: %s [-a] [path] \n", argv[0]);
                return 1;
        }
    }

    if(argc > 2){
        fprintf(stderr, "Error: Too many arguements \n");
        return 1;
    }

    const char *path = (optind < argc) ? argv[optind] : ".";
    DIR *dir = opendir(path);
    if(!dir){
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if(!has_a_flag && entry->d_name[0] == '.') continue;
        printf("%s \n", entry->d_name);
    }
    closedir(dir);

    return 0;
}


