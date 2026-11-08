#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> 

// takes a mode and string buffer and modifies it to represent file information based on mode
void mode_string(mode_t mode, char *str){
    if (S_ISDIR(mode)) str[0] = 'd';
    else if (S_ISLNK(mode)) str[0] = 'l';
    else if (S_ISCHR(mode)) str[0] ='c';
    else if (S_ISBLK(mode)) str[0] = 'l';
    else if (S_ISFIFO(mode)) str[0] = 'p';
    else if (S_ISSOCK(mode)) str[0] = 's';
    else str[0] = '-';

    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';

    str[10] = '\0';
}

// gets the username of the caller.
char *get_username(){
    struct passwd name = *getpwuid(getuid());
    return name.pw_name;
}

// -a flag which shows hidden files as well containing (.).
bool is_show_all = false;

struct file_info {
    char *filename;
    int file_size;
};

int main(int argc, char *argv[]){
   
    printf("Hi, %s \n", get_username());
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1){
        switch (opt) {
            case 'a':
                is_show_all = true;
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
        if(!is_show_all && entry->d_name[0] == '.') continue;
        printf("%s \n", entry->d_name);
    }
    closedir(dir);

    return 0;
}


