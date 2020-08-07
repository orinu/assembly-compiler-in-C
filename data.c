#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 struct action {
        char name[10];
        int opcode;
        int funct;
    } actions[16];

 struct symbol {
        char name[10];
        int value;
        char spec[10]; /* specification */
    } *pSymbol, *rePtl;

/* counter for symble */
int symbol_counter = 0;
int symbol_size_memory = 7;



void init_data() 
{

/* init command data */
strcpy(actions[0].name ,"mov");
actions[0].opcode = 0;
actions[0].funct = 0;

strcpy(actions[1].name ,"cmp");
actions[1].opcode = 1;
actions[1].funct = 0;

strcpy(actions[2].name ,"add");
actions[2].opcode = 2;
actions[2].funct = 1;

strcpy(actions[3].name ,"sub");
actions[3].opcode = 2;
actions[3].funct = 2;


strcpy(actions[4].name ,"lea");
actions[4].opcode = 4;
actions[4].funct = 0;


strcpy(actions[5].name ,"clr");
actions[5].opcode = 5;
actions[5].funct = 1;


strcpy(actions[6].name ,"not");
actions[6].opcode = 5;
actions[6].funct = 2;


strcpy(actions[7].name ,"inc");
actions[7].opcode = 5;
actions[7].funct = 3;


strcpy(actions[8].name ,"dec");
actions[8].opcode = 5;
actions[8].funct = 4;


strcpy(actions[9].name ,"jmp");
actions[9].opcode = 9;
actions[9].funct = 1;

strcpy(actions[10].name ,"bne");
actions[10].opcode = 9;
actions[10].funct = 2;

strcpy(actions[11].name ,"jsr");
actions[11].opcode = 9;
actions[11].funct = 3;

strcpy(actions[12].name ,"red");
actions[12].opcode = 12;
actions[12].funct = 0;

strcpy(actions[13].name ,"prn");
actions[13].opcode = 13;
actions[13].funct = 0;

strcpy(actions[14].name ,"rts");
actions[14].opcode = 14;
actions[14].funct = 0;

strcpy(actions[15].name ,"stop");
actions[15].opcode = 15;
actions[15].funct = 0;

/* init symbol data */
pSymbol = (struct symbol *)malloc(symbol_size_memory*sizeof(struct symbol));

}

/* get opcod of command by name */ 
void get_opcode(char* command_name) 
{
      printf("%s \n",command_name);
for (int i=0; i<16; i++) {
    if (strcmp(command_name ,actions[i].name) == 0) {
        printf("the funct of %s is %d\n \n",  actions[i].name, actions[i].funct);  
    }
 }
}

/* add symbole to the table */     //לבדוק שלא קיים, אם קיים להחזיק
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
