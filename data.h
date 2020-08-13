#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LENGTH 80
#define LABEL_FLAG -999898
#define MAX_SIZE 10000




extern int dc;
extern int ic;
extern int IC;
extern int ic_temp;
extern int data[MAX_SIZE];
extern int instruction_data[MAX_SIZE];
extern char *label_names[MAX_SIZE];
extern int label_ptl;
extern char *label_entres[MAX_SIZE];
extern int label_entry_ptl;
extern char *external[MAX_SIZE];
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
int check_if_symbol_exist(char *symbole_name);

