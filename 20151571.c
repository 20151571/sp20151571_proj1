#include "20151571.h"

int main(void){
    char buffer[256];
    const int Max_len = 256; 
    Hash hash_table;
    History Hhead;
    Lnode head = NULL;
    Shell_Memory Memory;

    init(&hash_table, &Memory);

    while(1){
        printf("sicsim> ");
        fgets(buffer, Max_len, stdin);
        if ( buffer[strlen(buffer) -1 ] == '\n')
            buffer[strlen(buffer) - 1 ] = '\0';
        main_process(buffer);
    }
    return 0;
}
