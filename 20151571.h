#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>



typedef struct Link_list * link;
typedef struct Link_list{
    int data;
    link next;    
};



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

