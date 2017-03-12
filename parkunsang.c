#include "20151571.h"

int STRCMP(char *str_cmp){
    int i;
    for ( i = 0; i < 16; ++i){
        if ( strcmp(Help[i], str_cmp) == 0)
            return i;
    }
    return -1;
}

int get_command(char *buffer){
    char sep[] = " ,\t";
    char *token = strtok(buffer, sep);
    int command_num;
    while(token != NULL){
        if ( ( command_num = STRCMP(token) ) != -1 )
            return command_num / 2;
        token = strtok(NULL, sep);
    }
    return Error;
}

void init( Hash *hash,  Shell_Memory *Sh_memory){
    int i;
    hash -> size = 20;
    for ( i = 0; i < hash->size; ++i ) {
        hash->Table[i] = NULL;
    }
    
    Sh_memory->last_address = 0;
    Sh_memory->max_address = 1048575;
    memset(Sh_memory->memory , 0 , sizeof(Sh_memory->memory));
}

int Hash_find( Hash *hash, char *mnemonic){
    int opcode = -1;
    int i;
    Hnode ptr;
    for ( i = 0; i < hash->size; ++i ){
        for ( ptr = hash->Table[i]; ptr != NULL; ptr = ptr -> next ){
            if ( strcmp( ptr->str_opcode , mnemonic ) == 0)
                return  ( opcode = ptr -> n_opcode );
        }
    }
    return opcode;
}

void Hash_insert( Hash *hash, int key, char *mnemonic){
    Hnode ptr;
    Hnode nptr;
    int Hash_size = hash->size;


    nptr = malloc(sizeof(Hash_node));
    strncpy ( nptr -> str_opcode, mnemonic, sizeof(nptr -> str_opcode) );
    nptr -> n_opcode = key;
    nptr -> next = NULL;

    ptr = hash->Table[key % Hash_size];

    if(ptr != NULL){
        for ( ; ptr -> next != NULL; ptr = ptr -> next);
        ptr -> next = nptr;
    }

    else
        hash->Table[key] = nptr;
}

void Link_insert( Lnode *head){
    Lnode nptr;
    Lnode ptr;

    nptr = malloc(sizeof(Linked_list));
    //nptr -> data = his_str;
    nptr -> next = NULL;

    if(*head != NULL){
       for(ptr = *head; ptr -> next != NULL; ptr = ptr -> next);
       ptr -> next = nptr;
    }

    else
        *head = nptr;
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
    for(ptr = head; ptr != NULL; ptr = ptr -> next)
        printf("%-5d %s\n", i++, ptr->data);
}

void print_memory(Shell_Memory Sh_memory, int start, int end){
    int str_hex = start / 16 * 16,
        end_hex = end / 16 * 16;
    int i, j;
    char *memory = Sh_memory.memory;

    if(start <= end && end <= Sh_memory.max_address){
        for ( i = str_hex; i <= end; i += 16){
            printf("%5x ", i);
            for(j = 0; j < 16; ++j){
                printf("%2x ", memory[i+j]);
            }    
            printf("; ");

            for(j = 0; j < 16; ++j){
                if(i + j >= start && i + j <= end){
                    if(memory[i+j] >= 0x20 && memory[i+j] <= 0x7E){
                        printf("%c", memory[i+j]);
                    }
                    else
                        printf(".");
                }
            }
            puts("");
        }
    }

    else{

    }
}

void command_dump(){
    int i, j;
    
}

void command_edit(char *memory, int address, int value){
    memory[address] = value;
}

void command_fill(char *memory, int start, int end, int value){
    int i;
    if(start <= end){
        for(i = start; i <= end; ++i)
            memory[i] = value;
    }
}

void command_reset(char *memory){
    memset(memory, 0, sizeof(memory));
}

void process_quit(){

}
/*
 *할당된 메모리 공간을 모두 해제해준다.
 */

void command_opcode( Hash *hash){
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
    
    while ( fgets(buffer, sizeof(buffer), fp) != NULL ){
        sscanf(buffer, "%x %s %s", &n_opcode, str_opcode, code );
        Hash_insert(hash, n_opcode, str_opcode);
    }
    
    fclose(fp);
}


void main_process(char *buffer){
    enum COMMAND command;
    int command_num;
    Shell_Memory Memory;
    Lnode head = NULL;
    Hash hash;

    init(&hash, &Memory);
    
    command_num = get_command(buffer);
    if(command_num != Error){
        //add_history();
        switch(command_num){
            case help:
                print_help();
                break;

            case dir:
                print_dir();
                break;

            case quit:
                process_quit();
                break;

            case history:
                print_histroy();
                break;

            case dump:
                command_dump();
                break;


            case edit:
                //command_edit(Hash.memory, );
                break;

            case Fill:
                //comamnd_fill();
                break;

            case Reset:
                //command_reset();
                break;

            case opcode:
                command_opcode(&hash);
                break;

            case opcodelist:
                print_opcode();
                break;
        }
    }
}
