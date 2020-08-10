#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


 char* line_with_out_symbol(char *line, int ptl);
 char* line_with_out_command(char *line,  int ptl );
 char* trim(char *line);
 char* instruction_name(char *line);
int  get_operated_number(char* line, char* command_name);
const char * get_operated_names(char* line, int operated_number);