#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


const char* line_with_out_symbol(char *line, int ptl){
    char *new_line = malloc(90 * sizeof(char));
    for (int i=ptl, j=0; i<strlen(line); i++, j++ ) {
        new_line[j] = line[i];
    }
    // printf("%s",new_line);
    return new_line;
}

const char* trim(char *line) {
    char line_with_out_spaces[25];
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

    // printf("%d",(end-start));
    // char *line_with_out_spaces=(char *)malloc((end-start)*sizeof(char));
        
    for (int j=0; start<end; start++ ,j++) {
        line_with_out_spaces[j] = line[start];
    }
    return line_with_out_spaces;
}

const char* instruction_name(char *line) {
    char *command_name;
    command_name = strtok(line, " ");
    return command_name;
}


const void check_line(const char *line) {
    char *instruction= instruction_name(line);
    /*  if cmmand */
    if (islower(instruction[0])>0){
        printf("%s  \n", instruction);
    }
    /*  if spec */
    if ((instruction[0]) == 46){
        printf("%s is spec \n",instruction);
    }


}
