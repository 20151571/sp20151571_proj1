#ifndef __20151571__
    #define __20151571__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum COMMAND{
    help, dir, quit, history, dump, edit,
    Fill, Reset, opcode, opcodelist,
    Error
};
typedef struct LINKED_LIST * History;
typedef struct LINKED_LIST * Lnode;
typedef struct HASH_Linked_List * Hnode;

typedef struct LINKED_LIST{
    char command[50];
    Lnode next;
}Linked_list;

#ifndef HASH_SIZE
#define HASH_SIZE 20

typedef struct _HASH_{
    int size;
    Hnode Table[HASH_SIZE];
}Hash;
#endif


typedef struct HASH_Linked_List{
    int n_opcode;
    char str_opcode[50];
    Hnode next;
}Hash_Node;

typedef struct MEMORY{
    char memory[1048576];
    int last_address;
    int max_address;
}Shell_Memory;

int min(int a, int b);

int command_find(char *str_cmp);
int get_command(char *buffer);
void add_history(char *command);

void init();

int Hash_find(char *);

void Hash_insert(int , char *mnemonic);
void Link_insert();

void print_help();
void print_dir();
void print_history();
void print_opcodelist();
int print_memory(int , int );

void command_dump();
//void dump(int start);
//void dump(int start, int end);

int command_edit(int address, int value);

int command_fill(int start, int end, int value);

void command_reset();


void process_quit();

void command_opcode();

int command_check(char *buffer, int *address, int *start, int *end, int *value);

void main_process(char *buffer);

#endif
