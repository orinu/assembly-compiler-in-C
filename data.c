#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

 struct action {
        char name[10];
        int opcode;
        int funct;
        int operated_num;        
    } actions[17];

 struct symbol {
        char name[10];
        int value;
        char spec[10]; /* specification */
    } *pSymbol, *rePtl;

/* counter for symble */
int symbol_counter = 0;
int symbol_size_memory = 7;

/* rgisters */
const char *register_name[] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

/* get rigster number */
int get_rgister_number(char* r_name) {
  int count =0;
  int i;
  for ( i=0; i<8; i++) {
      if (strcmp(r_name ,register_name[i]) == 0) {
          return i;
      } 
  } return -1;
}

/* check if rgister */ 
int check_if_rgister(char* r_name) {
  int i;
  for (i=0; i<8; i++) {
      if (strcmp(r_name ,register_name[i]) == 0) {
          return 1;
      } 
  } return 0;
}

void init_data() 
{

/* init command data */
strcpy(actions[0].name ,"mov");
actions[0].opcode = 0;
actions[0].funct = 0;
actions[0].operated_num = 2;

strcpy(actions[1].name ,"cmp");
actions[1].opcode = 1;
actions[1].funct = 0;
actions[1].operated_num = 2;

strcpy(actions[2].name ,"add");
actions[2].opcode = 2;
actions[2].funct = 1;
actions[2].operated_num = 2;

strcpy(actions[3].name ,"sub");
actions[3].opcode = 2;
actions[3].funct = 2;
actions[3].operated_num = 2;


strcpy(actions[4].name ,"lea");
actions[4].opcode = 4;
actions[4].funct = 0;
actions[4].operated_num = 2;


strcpy(actions[5].name ,"clr");
actions[5].opcode = 5;
actions[5].funct = 1;
actions[5].operated_num = 1;


strcpy(actions[6].name ,"not");
actions[6].opcode = 5;
actions[6].funct = 2;
actions[6].operated_num = 1;


strcpy(actions[7].name ,"inc");
actions[7].opcode = 5;
actions[7].funct = 3;
actions[7].operated_num = 1;


strcpy(actions[8].name ,"dec");
actions[8].opcode = 5;
actions[8].funct = 4;
actions[8].operated_num = 1;


strcpy(actions[9].name ,"jmp");
actions[9].opcode = 9;
actions[9].funct = 1;
actions[9].operated_num = 1;

strcpy(actions[10].name ,"bne");
actions[10].opcode = 9;
actions[10].funct = 2;
actions[10].operated_num = 1;

strcpy(actions[11].name ,"jsr");
actions[11].opcode = 9;
actions[11].funct = 3;
actions[11].operated_num = 1;

strcpy(actions[12].name ,"red");
actions[12].opcode = 12;
actions[12].funct = 0;
actions[12].operated_num = 1;

strcpy(actions[13].name ,"prn");
actions[13].opcode = 13;
actions[13].funct = 0;
actions[13].operated_num = 1;

strcpy(actions[14].name ,"rts");
actions[14].opcode = 14;
actions[14].funct = 0;
actions[14].operated_num = 0;

strcpy(actions[15].name ,"stop");
actions[15].opcode = 15;
actions[15].funct = 0;
actions[15].operated_num = 0;

/* init symbol data */
pSymbol = (struct symbol *)malloc(symbol_size_memory*sizeof(struct symbol));

}

/* get opcode of command by name */ 
int get_opcode_number(char *command_name) {
    int i;
    for ( i=0; i<17; i++) {
    if (strcmp(command_name ,actions[i].name) == 0) {
        return actions[i].opcode;
    }
  } return 0;
}
/* get funct of command by name */ 
int get_funct_number(char *command_name) {
    int i;
    for ( i=0; i<17; i++) {
    if (strcmp(command_name ,actions[i].name) == 0) {
        return actions[i].funct;
    }
  } return 0;
}

/* check if command exist */
int check_if_command_exist(char *command_name) {
    int i;
    for ( i=0; i<17; i++) {
    if (strcmp(command_name ,actions[i].name) == 0) {
        return 1;
    }
 
}  
return 0;
}

/* check if number of operated is ligal*/ 
int check_operated_number(char *command_name, int operated_num) {
    int i;
    for ( i=0; i<16; i++) {
      if (strcmp(command_name ,actions[i].name) == 0) {
        if (actions[i].operated_num == operated_num ) {
            return 1;
        }return 0;
      }   
    }
} 


/* add symbole to the table */   
void add_symbole(char* name, int val, char* spec) {
    // cheack if there is inaf memoery for the table symbol
    if (symbol_counter == symbol_size_memory ) {
        //add memory
        symbol_size_memory += 7;
        rePtl = (struct symbol *)realloc(pSymbol, symbol_size_memory*sizeof(struct symbol));
        //if the realloc wasnt saccess abort
        if (!rePtl) {
            printf("memory allocation faild");
            exit(0);
        }
        pSymbol = rePtl;
    }
    //add the income data of the symbol to the table (struct)
    strcpy(pSymbol[symbol_counter].name ,name);
    pSymbol[symbol_counter].value = val;
    strcpy(pSymbol[symbol_counter].spec ,spec);

    printf("name is: %s  , value is: %d  , spec is: %s \n \n",pSymbol[symbol_counter].name, pSymbol[symbol_counter].value, pSymbol[symbol_counter].spec);
    // printf("symbol_size_memory %d \n \n",symbol_size_memory);
    // printf("symbol_counter %d \n \n",symbol_counter);
    // inc counter
    symbol_counter ++;

}
