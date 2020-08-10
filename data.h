#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_rgister_number(char* r_name);
int check_if_rgister(char* r_name);
void init_data(); 
int get_opcode_number(char *command_name);
int get_funct_number(char *command_name);
int check_if_command_exist(char *command_name);
int check_operated_number(char *command_name, int operated_num);
void add_symbole(char* name, int val, char* spec);
void symbole_entry_flag(char *symbole_name);