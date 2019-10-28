/*

main.c for use with dispatcher.c

Do not edit the contents of this file.
*/

#include <stdio.h>
#include <string.h>
#include "dispatcher.h"
 
 
int main(int argc, char **argv) {
    int quantum;
    int harddrive_response_time;
    
    if(argc == 3) {
        sscanf( argv[1], "%d", &quantum);
        sscanf( argv[2], "%d", &harddrive_response_time);
    } else{
        printf("Wrong # of parameters provided to program\n");
        return -1;
    } 
    
    dispatcher( stdin, quantum, harddrive_response_time);
    return 0;
}
