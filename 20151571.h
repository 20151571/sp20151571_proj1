#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


typedef struct Linked_list * link;
typedef struct Linked_list{
    int data;
    link next;
};

static const char help_list[][] = {
    "h[elp]",
    "d[ir]",
    "q[uit]",
    "hi[story]",
    "du[mp] [start, end] e[dit] address, value",
    "f[ill] start, end, value",
    "reset",
    "opcode mnemonic",
    "opcodelist"
}


void print_help();
void print_dir();
void print_history();

void dump();
void dump(int start);
void dump(int start, int end);

void edit(int address, int value);

void fill(int start, int end, int value);

void reset();

void process_quit();

