#include "20151571.h"

void init(){
    
}

int Hash_find(char *mnemonic){
    int opcode = -1;
    int i;
    Hash ptr;
    for ( i = 0; i < Hash_size; ++i ){
        for ( ptr = Table[i]; ptr != NULL; ptr = ptr -> next ){
            if ( strcmp( ptr->str_opcode , mnemonic ) == 0)
                return  ( opcode = ptr -> n_opcode );
        }
    }
    return opcode;
}

void Hash_insert(int key){
    Hash ptr;
    Hash nptr;
    key = key % Hash_size;

    nptr = malloc(sizeof(Hash_table));
    //nptr -> command = 
    nptr -> next = NULL;

    ptr = Hash_table[key];

    if(ptr != NULL){
        for ( ; ptr -> next != NULL; ptr = ptr -> next);
        ptr -> next = nptr;
    }

    else
        Hash_table[key] = nptr;
}

void Link_insert(){
    Link *nptr;
    Link ptr;

    nptr = malloc(sizeof(Link));
    //nptr -> data = his_str;
    nptr -> next = NULL;

    if(head != NULL){
       for(ptr = head; ptr -> next != NULL; ptr = ptr -> next);
       ptr -> next = nptr;
    }
}

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

        else if( (buf.st_mode & S_IXUSR) ||
                (buf.st_mode & S_IXGRP) ||
                (buf.st_mode & S_IXOTH) )
            printf("*");
        puts("");
    }
    closedir(dirp);
}


void print_history(History head){
    History ptr;
    int i = 1;
    for(ptr = head; ptr != NULL; ptr = ptr -> link)
        printf("%-5d %s\n", i++, ptr->data);
}

void print_memory(int start, int end){
    int str_hex = start / 16 * 16,
        end_hex = end / 16 * 16;
    int i, j;
    
    if(start <= end && end <= max_size){
        for ( i = str_hex; i <= end; i += 16){
            printf("%5x ", i);
            for(j = 0; j < 16; ++j){
                printf("%2x ", memory[i+j]);
            }    
            printf("; ");

            for(j = 0; j < 16; ++j){
                if(i + j >= str && i + j <= end){
                    if(memory[i+j] >= 0x20 && memory[i+j] <= 0x7E){
                        printf("%c", memory[i+j]);
                    }
                    else
                        printf(".")
                }
            }
            puts("");
        }
    }

    else{

    }
}

void dump(){
    int i, j;
    
}

void dump(int start){

}

void dump(int start, int end){
    
}

void edit(int address, int value){
    memory[address] = value;
}

void fill(int start, int end, int value){
    int i;
    if(start <= end){
        for(i = start; i <= end; ++i)
            memory[i] = value;
    }
}

void reset(){
    memset(memory, 0, sizeof(memory));
}

void process_quit(){

}
/*
 *할당된 메모리 공간을 모두 해제해준다.
 */

void opcode(){
    FILE *fp;
    char buffer[256];
    int n_opcode;
    char str_opcode[30];
    char code[30];

    fp = fopen("opcode.txt", "r");
    if ( fp == NULL){
        printf("FILE OPEN ERROR\n");
        return;
    }
    
    while ( fgets(fp, buffer, sizeof(buffer)) != NULL ){
        sscanf(buffer, "%x %s %s", &n_opcode, str_opcode, code )
        Hash_insert();
    }
    
    fclose(fp);
}


void main_process(){

}
