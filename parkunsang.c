#include "20151571.h"

const char *help_list[] = {
    "h[elp]",
    "d[ir]",
    "q[uit]",
    "hi[story]",
    "du[mp] [start, end]",
    "e[dit] address, value",
    "f[ill] start, end, value",
    "reset",
    "opcode mnemonic",
    "opcodelist"
};

const char *Help[] = {
    "h",
    "help",
    "d",
    "dir",
    "q",
    "quit",
    "hi",
    "history",
    "du",
    "dump",
    "e",
    "edit",
    "f",
    "fill",
    "reset",
    "opcode mnemonic",
    "opcodelist"
};

int values[5];
char *instruction[10];
char str_copy[256];
Hash hash_table;
History Hhead = NULL;
Lnode Lhead = NULL;
Shell_Memory Sh_memory;

int min(int a, int b){
    return a < b ? a : b;
}

void str_replace(char *target, const char *orig, const char *repl){
    char buffer[256] = { 0 };
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t orig_len = strlen(orig);
    size_t repl_len = strlen(repl);
    while (1) {
        const char *p = strstr(tmp, orig);
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, repl, repl_len);
        insert_point += repl_len;
        tmp = p + orig_len;
    }
    strcpy(target, buffer);
}

int get_values(char *buffer){
    char *token;
    char *error;
    char sep[] = " \t";
    int idx= 0, flag = 1;
    int value;
    token = strtok(buffer, sep);
    while(token != NULL){
        token = strtok(NULL, sep);
        if ( token == NULL)
            break;
        if ( strcmp( token , "," ) == 0 ){
            if ( flag )
                return -1;
            else
                flag = 1;
        }
        else{
            value = (int)strtol(token, &error, 16);
            if( *error != '\0')
                return -1;
            values[idx++] = value;
            flag = 0;
        }
    }
    return 1;
}

int command_find(char *str_cmp){
    int i;
    int size = sizeof(Help) / sizeof(char *);
    printf("command is %s\n", str_cmp);
    for ( i = 0; i < size; ++i){
        if ( strcmp(Help[i], str_cmp) == 0)
            return i;
    }
    printf("there is no comamnd\n");
    return -1;
}

int get_command(char *buffer){
    char sep[] = " \t";
    char *token = strtok(buffer, sep);
    int command_num;
    while(token != NULL){
        if ( ( command_num = command_find(token) ) != -1 )
            return ( command_num <= 11 ? command_num / 2 : command_num - 5);
        token = strtok(NULL, sep);
    }
    return -1;
}

void get_opcode(){
    FILE *fp;
    char buffer[256];
    int n_opcode;
    char str_opcode[100];
    char code[100];

    fp = fopen("opcode.txt", "r");
    if ( fp == NULL){
        printf("FILE OPEN ERROR\n");
        return;
    }

    while ( fgets(buffer, sizeof(buffer), fp) != NULL ){
        sscanf(buffer, "%x %s %s", &n_opcode, str_opcode, code );
        Hash_insert(n_opcode, str_opcode);
    }

    fclose(fp);
}



void add_histroy(char *command){
    History ptr = Hhead;
    History nptr;

    nptr = malloc(sizeof(Linked_list));
    nptr -> next = NULL;
    strncpy(nptr->command, command, sizeof(nptr->command));

    if(ptr != NULL){
        for(; ptr-> next != NULL; ptr = ptr -> next);
        ptr -> next = nptr;
    }
    else
        Hhead = nptr;
}

void init(){
    int i;
    hash_table.size = 20;
    for ( i = 0; i < hash_table.size; ++i ) {
        hash_table.Table[i] = NULL;
    }
    
    Sh_memory.last_address = 1048575;
    Sh_memory.max_address = 1048575;
    for( i = 0; i < Sh_memory.max_address; ++i)
        Sh_memory.memory[i] = 0;
    get_opcode();
}

int Hash_find(char *mnemonic){
    int opcode = -1;
    int i;
    Hnode ptr;
    for ( i = 0; i < hash_table.size; ++i ){
        for ( ptr = hash_table.Table[i]; ptr != NULL; ptr = ptr -> next ){
            if ( strcmp( ptr->str_opcode , mnemonic ) == 0)
                return  ( opcode = ptr -> n_opcode );
        }
    }
    return opcode;
}

void Hash_insert(int key, char *mnemonic){
    Hnode ptr;
    Hnode nptr;
    int Hash_size = hash_table.size;
    
    nptr = malloc(sizeof(Hash_Node));
    strncpy ( nptr -> str_opcode, mnemonic, sizeof(nptr -> str_opcode) );
    nptr -> n_opcode = key;
    nptr -> next = NULL;

    key = key % Hash_size;
    ptr = hash_table.Table[key];

    if(ptr != NULL){
        nptr -> next = ptr;
        hash_table.Table[key] = nptr;
    }

    else
        hash_table.Table[key] = nptr;
}

void Link_insert(){
    Lnode nptr;
    Lnode ptr;

    nptr = malloc(sizeof(Linked_list));
    //nptr -> data = his_str;
    nptr -> next = NULL;

    if(Lhead != NULL){
       for(ptr = Lhead; ptr -> next != NULL; ptr = ptr -> next);
       ptr -> next = nptr;
    }

    else
        Lhead = nptr;
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
    if( (dirp = opendir(".")) == NULL){
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
        printf("\t");
    }
    puts("");
    closedir(dirp);
}


void print_history(){
    History ptr;
    int i = 1;
    for(ptr = Hhead; ptr != NULL; ptr = ptr -> next)
        printf("%-5d %s\n", i++, ptr->command);
}

void print_opcodelist(){
    Hnode ptr;
    for ( int i = 0; i < 20; ++i){
        printf("%d : ", i);
        for ( ptr = hash_table.Table[i]; ptr != NULL; ptr = ptr -> next){
            printf("[%s,%d]", ptr->str_opcode, ptr->n_opcode);
            if(ptr -> next != NULL)
                printf(" -> ");
        }
        puts("");
    }
}

int print_memory(int start, int end){
    int str_hex = start / 16 * 16,
        end_hex = end / 16 * 16;
    int i, j;
    char *memory = Sh_memory.memory;
    
    if(start <= end && start >= 0){
        end = end <= Sh_memory.max_address ? end : Sh_memory.max_address ;
        Sh_memory.last_address = end;
        for ( i = str_hex; i <= end_hex; i += 16){
            printf("%05X ", i);
            for(j = 0; j < 16; ++j){
                if(start <= i + j && i + j <= end)
                    printf("%02X ", memory[i+j]);
                else
                    printf("   ");
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
                else
                    printf(".");
            }
            puts("");
        }
        return 1;
    }
    else
        return -1;
}


void command_dump(){
    int len = 0;
    int start_address = ( Sh_memory.last_address + 1 ) % 
        ( Sh_memory.max_address + 1 ) ,
        end_address = min ( start_address + 159, Sh_memory.max_address ); 
    char *Error1 = '\0', *Error2 = '\0';

    for ( int i = 0; instruction[i] != NULL; ++i, len++);
    
    if ( len == 2){
        start_address = (int)strtol(instruction[1], &Error1, 16);
        if(*Error1 == ','){
            end_address = (int)strtol(Error1+1, &Error2, 16);
            Error1 = '\0';
        }
        if ( start_address > Sh_memory.max_address ||
               start_address > end_address || *Error2 != '\0'){
            printf("Address Error!\nStart_address exceeds max_address\n");
            return;
        }
        end_address = min ( end_address, Sh_memory.last_address );
    }

    else if ( len == 3){
        if ( instruction[1][ strlen(instruction[1]) - 1] == ',' )
            instruction[1][ strlen(instruction[1]) -1 ] = '\0';

        else if( instruction[2][0] == ',' ){
            for ( int i = 0;  i < strlen(instruction[2]); ++i)
                instruction[2][i] = instruction[2][i+1];
        }

        start_address = (int)strtol(instruction[1], &Error1, 16);
        end_address = (int)strtol(instruction[2], &Error2, 16);
        

        if ( *Error1 != '\0' || *Error2 != '\0' || start_address > end_address ||
                start_address > Sh_memory.max_address ){
            printf("Address Error!\nStart_address exceeds max_address\n");
            return;
        }
    }

    else if ( len == 4){
        start_address = (int)strtol(instruction[1], &Error1, 16);
        end_address = (int)strtol(instruction[3], &Error2, 16);
        
        if ( *Error1 != '\0' || *Error2 != '\0' || 
                strcmp(instruction[2], ",") != 0 || start_address > end_address ||
                start_address > Sh_memory.max_address ){
            printf("Address Error!\nStart_address exceeds max_address\n");
            return;
        }
    }

    else if( len > 4){
        printf("Address Error!\nStart_address exceeds max_address\n");
        return;
    }
    Sh_memory.last_address = end_address;
    print_memory ( start_address, end_address );
}

int command_edit(char *buffer){
    int address, value;
    int len = 0, num = 0, flag = 1;
    char *Error1 ='\0', *Error2 = '\0';
    char *token;
	char tmp[256];
    char sep[] = " \t";
	strncpy(tmp, buffer, sizeof(tmp));

	for ( int i = 0; i < strlen(tmp); ++i)
        if ( tmp[i] == ',')
            num++;
    if(num != 1)
        return -1;

    str_replace(tmp, ",",  " , ");
    if( get_values(tmp) == -1)
        return -1;

    address = values[0]; value = values[1];
    
    if( 0 <= address && address <= Sh_memory.max_address){
        Sh_memory.memory[address] = value;
        print_memory(address, address);
        return 1;
    }
    return -1;
}

int command_fill(char *buffer){
    int num = 0, flag = 1;
    int arr[5];
    int start, end, value;
    char *token, *error;
    char sep[] = " \t";
	char tmp[256];

	strncpy(tmp, buffer, sizeof(tmp));

    for( int i = 0; i < strlen(buffer); ++i)
        if( buffer[i] == ',')
            num++;
    if(num != 2)
        return -1;

	str_replace(tmp, ",", " , ");

    if ( get_values(tmp) == - 1)
        return -1;

    start = values[0], end = values[1], value = values[2];

    if(start >= 0 && start <= end && end <= Sh_memory.max_address){
        for(int i = start; i <= end; ++i)
            Sh_memory.memory[i] = value;
        print_memory(start, end);
        return 1;
    }
    return -1;
}

void command_reset(){
    char *memory = Sh_memory.memory;
    int i;
    for ( i = 0; i < Sh_memory.max_address; ++i )
        memory[i] = 0;
    print_memory(0, 160);
}

void process_quit(){
    printf("hihi\n");
    Lnode lptr;
    History hptr;

    for ( ; Lhead != NULL; ){
        lptr = Lhead;
        Lhead = Lhead->next;
        free(lptr);
    }

    for ( int i = 0; i < hash_table.size; ++i ){
        for ( ; Hhead != NULL; ){
            hptr = Hhead;
            Hhead = Hhead->next;
            free(hptr);
        }
    }
    exit(0);
}
/*
 *할당된 메모리 공간을 모두 해제해준다.
 */

void command_opcode( ){

}

int command_check(char *user_str){
    char sep[] = " \t";
    char *token;
    int i = 0, command_num = -1, len = 0;
    token = strtok(user_str, sep);

    if(token == NULL)
        return -1;

    command_num = command_find(token);
    if(command_num == -1)
        return -1;
    
    while ( token != NULL ){
        if(i > 6)
            return -1;
        len++;
        instruction[i++] = token;
        token = strtok(NULL, sep);
    }
    instruction[i] = NULL;
    
    if ( ( 0 <= command_num && command_num <= 7 ) || command_num ==  14 
            || command_num == 16 )
        if ( len > 1 )
            return -1;
    
    if( 0 <= command_num && command_num <= 13)
        return command_num / 2;
    else if ( command_num > 13)
        return command_num - 6;
    
    return -1;
}

void main_process(char *buffer){
    enum COMMAND command;
    int command_num, Error_code;
    char *mnemonic;

    strncpy( str_copy, buffer, sizeof(str_copy));
    command_num = command_check(str_copy);

    printf("command_num is : %d\n", command_num);
    if(command_num != -1){
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
                print_history();
                break;

            case dump:
                command_dump();
                break;


            case edit:
                strncpy( str_copy, buffer, sizeof(str_copy));
                Error_code = command_edit(str_copy);
                break;

            case Fill:
                strncpy( str_copy, buffer, sizeof(str_copy));
                Error_code = command_fill(str_copy);
                break;

            case Reset:
                command_reset();
                break;

            case opcode:
                command_opcode();
                break;

            case opcodelist:
                print_opcodelist();
                break;
        }
    }

    else
        printf("There is no command\nplease rewrite command\n");
}
