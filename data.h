#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int dc;
extern int ic;
extern int ic_temp;
extern int data[2000];
extern int instruction_data[2000];
extern const char *label_names[100];
extern int label_ptl;
extern const char *label_entres[100];
extern int label_entry_ptl;
const char *external[100];
int external_ptl;


extern int ICF;
extern int IDF;


int get_rgister_number(char* r_name);
int check_if_rgister(char* r_name);
void init_data(); 
int get_opcode_number(char *command_name);
int get_funct_number(char *command_name);
int check_if_command_exist(char *command_name);
int check_operated_number(char *command_name, int operated_num);
void add_symbole(char* name, int val, char* spec);
void symbole_entry_flag(char *symbole_name);
int get_symbol_value(char *symbole_name);
int check_if_external(char *symbole_name);
int got_orignal_ic(int position_label);