#ifndef __20151571__
    #define __20151571__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct LINKED_LIST * History;
typedef struct LINKED_LIST * Link;
typedef struct LINKED_LIST{
    char *data;
    Link next;
}Linked_list;

#ifndef HASH_SIZE
#define HASH_SIZE 20

typedef struct _HASH_{
    int Hash_size;
    struct HASH_Linked_list *Table[HASH_SIZE];
}Hash;
#endif


typedef struct HASH_Linked_list{
    int n_opcode;
    char * str_opcode;
    struct HASH_Linked_list *next;
}Hash_table;


typedef struct MEMORY{
    char memory[1048576];
}Memory;

static const char *help_list[] = {
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

static const char *help[] = {
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

void init();

void Hash_insert();
void Link_insert();

void print_help();
void print_dir();
void print_history();

void dump();
//void dump(int start);
//void dump(int start, int end);

void edit(int address, int value);

void fill(int start, int end, int value);

void reset();

void process_quit();

void opcode();

void main_process();

#endif
