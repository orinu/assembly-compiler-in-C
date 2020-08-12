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
    /* if there is comma's return comma's+1 else ,if the first char after trim exsit return 1 else return 0 */
    int comma_counter = 0;
    
    // printf("line is: %s command  is: %s \n", line, command_name );
    int i;
    for ( i =0; i<strlen(line)-1 ; i++){
        if (line[i] == 44) {
            comma_counter++;
        }
    }  
    // printf("first the comma number is %d \n", comma_counter);
    if (comma_counter == 0){
        // printf("the line without command is: %s ",trim(line_with_out_command(line,strlen(command_name))));
        if(  trim (line_with_out_command(line,strlen(command_name)))[0]  != NULL) {
            /* return 1 operated if there is char is not space */
            return 1;   
        /* return 0 operated if there is no char */
        }return 0;
        /* return 1 + comma's number operated*/
    }  
    return  comma_counter+1;
    // if ( (strcmp(command_name ,"stop") !=0 ) && (strcmp(command_name ,"rts") !=0 ) ){
    //     operated_num= comma_counter++;
    // }operated_num=comma_counter;  
    // return operated_num;
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

/* return symbol name without choko */ 
const char * symbol_name_without_choko(char* name) {
    char *name_without = malloc(90 * sizeof(char));
    int i;
    for (i=0; i<strlen(name); i++) {
        name_without[i]=name[i+1];
    }
    return name_without;
}