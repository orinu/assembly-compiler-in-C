#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ROW_LENGTH 80


#include "second_run.h"


void second_run(FILE *fp) {
    char line[80];
     while(fgets(line,  MAX_ROW_LENGTH , fp) != NULL) {
       /* memory save of the hole line */
       char *orignal_line = malloc(80*sizeof(char));
       strcpy(orignal_line, trim(line));

       /* memory save of the instruction line */
       char *instruction = malloc(80*sizeof(char));
       instruction= trim(instruction_name(line));
         if( strcmp(instruction ,".entry") ==0 ){
           printf("in the sec run, the line is %s \n",orignal_line);
           printf("in the sec run, this is entry %s \n",instruction);
           /* string without ".data" */
           char *data_string = trim(line_with_out_command(orignal_line,strlen(instruction)));
           printf("the string without command %s \n",data_string);
           symbole_entry_flag(data_string);
         }
     }
}

