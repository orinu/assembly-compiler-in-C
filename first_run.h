#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h"
#include "utils.h"


#define MAX_ROW_LENGTH 80

struct bits;
extern int dc;
extern int ic;
extern int ic_temp;
extern int data[2000];
extern int instruction_data[2000];
extern const char *label_names[100];
extern int label_ptl;


void init_binary_struct();
void update_pointers();

void zero_oprated();
void des_handle(char *operated_name);
void src_handle(char *operated_name);
const void check_line(const char *line);
void first_run(FILE *fp);