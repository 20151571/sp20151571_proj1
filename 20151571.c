#include "20151571.h"

int main(void){
    char buffer[256];
    const int Max_len = 256; 
    enum COMMAND command;

    while(1){
        printf("sicsim> ");
        fgets(buffer, Max_len, stdin);
        
        if ( buffer[strlen(buffer) -1 ] == '\n')
            buffer[strlen(buffer) - 1 ] = '\0';
        
        command = command_check(buffer);
        //main_process(buffer);
    }
    return 0;
}
