#include '20151571.h'

void print_help(){
    int i;
    for(i = 0; i < 9; ++i)
        printf("%s\n", help_list[i]);
}

void print_dir(){
    DIR *dirp;
    struct dirent *direntp;
    struct stat buf;
    if( (dirp = opendir(",")) == NULL){
        printf("Can not Open Directory\n");
        return;
    }

    while( (direntp = readdir(dirp)) != NULL){
        stat(direntp->d_name, &buf);
        printf("%s", direntp->d_name);

        if( S_ISDIR(buf.st_mode) )
            printf("/");
        else if( S_ISREG(buf.st_mode) && buf.st_mode & 0111)
            printf("*");
        puts("");
    }
    closedir(dirp);
}


