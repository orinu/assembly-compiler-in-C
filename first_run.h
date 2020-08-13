#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h"
#include "utils.h"


#define MAX_ROW_LENGTH 80


void first_run(FILE *fp);
int check_line(char *line);
void init_binary_struct();
void zero_oprated();
void des_handle(char *operated_name);
void src_handle(char *operated_name);
void data_err(char * data_string);



