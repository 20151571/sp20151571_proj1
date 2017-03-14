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

int command_find(char *str_cmp);
int get_command(char *buffer);
void add_history(History *head, char *command);

void init( Hash * ,  Shell_Memory *);

int Hash_find( Hash *, char *);

void Hash_insert( Hash *, int , char *mnemonic);
void Link_insert(Lnode *head );

void print_help();
void print_dir();
void print_history(History Hhead);
void print_opcode(Hash *);
int print_memory(Shell_Memory *Sh_memory, int , int );

void command_dump();
//void dump(int start);
//void dump(int start, int end);

int command_edit(Shell_Memory *Sh_memory, int address, int value);

int command_fill(Shell_Memory *Sh_memory, int start, int end, int value);

void command_reset(Shell_Memory *Memory);


void process_quit();

void command_opcode( Hash *);

int command_check(char *buffer, int *address, int *start, int *end, int *value);

void main_process(char *buffer);

#endif
