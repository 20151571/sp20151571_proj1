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
typedef struct HASH_Linked_list * Hnode;

typedef struct LINKED_LIST{
    char *data;
    Lnode next;
}Linked_list;

#ifndef HASH_SIZE
#define HASH_SIZE 20

typedef struct _HASH_{
    int size;
    Hnode Table[HASH_SIZE];
}Hash;
#endif


typedef struct HASH_Linked_list{
    int n_opcode;
    char str_opcode[10];
    Hnode *next;
}Hash_node;


typedef struct MEMORY{
    char memory[1048576];
    int last_address;
    int max_address;
}Shell_Memory;



 char *help_list[] = {
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

 char *Help[] = {
    "h",
    "help",
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

int STRCMP(char *str_cmp);
int get_command(char *buffer);
void add_history(char *command);

void init( Hash * ,  Shell_Memory *);

int Hash_find( Hash *, char *);

void Hash_insert( Hash *, int , char *mnemonic);
void Link_insert(Lnode *head );

void print_help();
void print_dir();
void print_history();
void print_opcode();

void command_dump();
//void dump(int start);
//void dump(int start, int end);

void command_edit(char *memory, int address, int value);

void command_fill(char *memory, int start, int end, int value);

void command_reset(char *memory);

void process_quit();

void command_opcode( Hash *);

void main_process(char *buffer);

#endif
