#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LENGTH 80
#define LABEL_FLAG -999898



extern int dc;
extern int ic;
extern int IC;
extern int ic_temp;
extern int data[2000];
extern int instruction_data[2000];
extern const char *label_names[100];
extern int label_ptl;
extern const char *label_entres[100];
extern int label_entry_ptl;
extern const char *external[100];
extern int external_ptl;
extern int line_number;
extern int err_flag;


extern int ICF;
extern int IDF;

void init_data(); 
void update_pointers();
int get_rgister_number(char* r_name);
int check_if_rgister(char* r_name);
int get_opcode_number(char *command_name);
int get_funct_number(char *command_name);
int check_if_command_exist(char *command_name);
int check_operated_number(char *command_name, int operated_num);
void add_symbole(char* name, int val, char* spec);
void symbole_entry_flag(char *symbole_name);
int get_symbol_value(char *symbole_name);
int check_if_external(char *symbole_name);
int got_orignal_ic(int position_label);
int check_if_sybol_exist(char *symbole_name);

