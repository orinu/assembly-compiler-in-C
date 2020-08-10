#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

/* return line with no starting symbol*/ 
 char* line_with_out_symbol(char *line, int ptl){
    char *new_line = malloc(90 * sizeof(char));
    int i;
    int j;
    for ( i=ptl, j=0; i<strlen(line); i++, j++ ) {
        new_line[j] = line[i];
    }
    // printf("%s",new_line);
    return new_line;
}

/* return line with no starting symbol*/ 
 char* line_with_out_command(char *line,  int ptl ){
    char *line_with_out_command = malloc(90 * sizeof(char));
    int i;
    int j;
    for ( i=ptl, j=0; i<strlen(line); i++, j++ ) {
        line_with_out_command[j] = line[i];
    }
    return line_with_out_command;
}

 char* trim(char *line) {
    char *line_with_out_spaces = malloc(90 * sizeof(char));

    int start =0;
    int end =strlen(line)-1;

    if (!line)
        return NULL;   //  NULL string
    if (!*line)
        return line;   //  empty string

    while (isspace(line[start])) 
    {
        start++;
    }
    while (isspace(line[end])) 
    {
        end--;
    }
    int j;
    for (int j=0; start<end+1; start++ ,j++) {
        line_with_out_spaces[j] = line[start];
    }
    return line_with_out_spaces;
}

 char* instruction_name(char *line) {
    char *command_name;
    command_name = strtok(line, " ");
    return command_name;
}

/* check how many oprated there are */
int  get_operated_number(char* line, char* command_name) {
    int comma_counter = 0;
    int operated_num = 0;
    // printf("line is: %s command  is: %s \n", line, command_name );
    int i;
    for ( i =0; i<strlen(line)-1 ; i++){
        if (line[i] == 44) {
            comma_counter ++;
        }
    } 
    if ( (strcmp(command_name ,"stop") !=0 ) && (strcmp(command_name ,"rts") !=0 ) ){
        operated_num= comma_counter++;
    }operated_num=comma_counter;  
    return operated_num;
}

/*  get operated names */ 
const char * get_operated_names(char* line, int operated_number) {
    char *operated_names_values = malloc(90 * sizeof(char));
    /* return operand name for 1 oprand*/ 
    if (operated_number == 1){
        return line;
    /* return operand name for 2 oprand*/ 
    } else if (operated_number == 2){
        char *operated_names;
        /* cut the twp oprated */
        operated_names = strtok(line, ",");
        while (operated_names != NULL) { 
          strcat(operated_names_values,operated_names);  
          strcat(operated_names_values," ");  
          operated_names = strtok(NULL, ",");  
        }
        return operated_names_values; 
    }
}


// const void check_line(const char *line) {
//     char *instruction= instruction_name(line);
//     /*  if cmmand */
//     if (islower(instruction[0])>0){
//         printf("%s  \n", instruction);
//     }
//     /*  if spec */
//     if ((instruction[0]) == 46){
//         printf("%s is spec \n",instruction);
//     }
// }
