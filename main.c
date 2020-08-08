#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "data.c"
#include "utils.c"
#include "first_pass.c"

#define MAX_ROW_LENGTH 80

 struct bits {
        unsigned int are:3;
        unsigned int funct:5;
        unsigned int r_des:3;
        unsigned int ad_des:2;
        unsigned int r_src:3;
        unsigned int ad_src:2;
        unsigned int opcode:6;
    } binary;


const void check_line(const char *line) {
    /* memory save of the hole line */
    char *orignal_line = malloc(80*sizeof(char));
    strcpy(orignal_line, trim(line));

    /* memory save of the instruction line */
    char *instruction = malloc(80*sizeof(char));
    instruction= instruction_name(line);

    /*  if command */
    if (islower(instruction[0])>0){
        if (check_if_command_exist(instruction) == 0){
            /* cmmand not exist */ 
            /* err */
        }else {
            /* inesrt to the binary command the opcode, funct and are*/
            binary.opcode = get_opcode_number(instruction);
            binary.funct = get_funct_number(instruction);
            binary.are = 4;

            /* calculate how many opareted there are in the commannd */
            int operated_number = get_operated_number(orignal_line, instruction);
            /* check if number of operat ligal compare of command */ 
            if (check_operated_number(instruction,operated_number) == 1) {
                /* src adress and src register is 0 cuz one oprate */
                binary.ad_src = 0;
                binary.r_src = 0;

                /* after chaeck the number of opreated is ligal to the commnad*/
                char *operated_name =  get_operated_names( trim(line_with_out_command(orignal_line, strlen(instruction))) , operated_number  );
                /* handale oprate number of 1 */
                if (operated_number == 1) {
                    // printf("%s \n", orignal_line);
                    /*  if immediate */
                    if (operated_name[0] == 35) {
                        printf("%s is immediate\n", operated_name);
                        binary.ad_des =0;
                        binary.r_des =0;
                    /*  if register */
                    }else if(check_if_rgister(operated_name) ==1 ){
                        printf("%s is rgister\n", operated_name);
                        binary.ad_des =3;
                        binary.r_des = get_rgister_number(operated_name);
                    /* if label */
                    }else {
                        printf("%s is label\n", operated_name);
                        binary.r_des =0;
                        if (operated_name[0] == 38) {
                            binary.ad_des = 2;
                        }else {
                            binary.ad_des = 1;
                        }
                    }  
                    /* print binary code */
                        printf("%d \n \n" ,binary); 
                /* handle 2 number of operat ligal*/ 
                }else if (operated_number == 2) {
                    //    printf("%s\n", operated_name);
                }
                
                // printf ("%d \n",check_if_rgister(get_operated_names( trim(line_with_out_command(orignal_line, strlen(instruction))) , operated_number  )));
            }else {
                /* syntax error */
            }
    
        }
    }
    /*  if spec */
    if ((instruction[0]) == 46){
        // printf("%s is spec \n",instruction);
    }
}



int main(int argc, char *argv[]){
    init_data();
    // get_opcode("jsr");
    // add_symbole("MAIN", 100, "code");
    FILE *fp;
    char line[80];

    for(int i = 1; i < argc; i++)
    {    
        /* merage file name with .as */ 
        char* filename = malloc(strlen(argv[i])+4);
        strcpy(filename,argv[i]);
        strcat(filename,".as");
        // printf(" file name is %s \n \n",filename);

        /*  open file */
        fp = fopen(filename, "r");
        if(fp != NULL) { 
            
            printf("reading file name  %s \n \n" , filename);
            /* run on evrey line in the file */ 
            while(fgets(line,  MAX_ROW_LENGTH , fp) != NULL) {
                /* print line*/ 
                // printf("%s \n",line); 
                /* run on evrey char in line */
                int line_length = strlen(line);
                for (int j=0; j< line_length; j++) {
                    /* SYMBOL */ 
                    /*  if there is ":" symbol name*/
                    if ( line[j] == ':') {
                        char symbol_name[30] = "";
                        char spec[30] = "code";
                        char *ret;
                        int ic = 100;

                        /* get the name of the symbol*/
                        strncpy(symbol_name,line , j);
                        /* symbol name in symbole_name var */ 
                        // printf("%s \n", symbol_name);

                        /* looking for ".data"*/
                        ret = strstr(line, ".data");
                        if (ret != NULL) {
                            strcpy(spec, "data");
                            // printf(" %s \n ", spec) ; 
                        }

                        /* looking for ".string"*/
                        ret = strstr(line, ".string");
                        if (ret != NULL) {
                            strcpy(spec, "data");
                            // printf(" %s \n ", spec) ; 
                        }
                        /* aad symbol to the symbol table */
                        // add_symbole(symbol_name, ic, spec)
                        // char *returned_line =  trim(line_with_out_symbol(line, j+1));
                        // printf("%s \n ",returned_line);
                        // printf("%d \n  ",returned_line[0]);
                        // printf("%s \n",instruction_name(line_with_out_symbol(line, j+1)));
                        


                        check_line(line_with_out_symbol(line, j+1));
                    }
                }  
                check_line(line);
                
          

            }
        }
        else 
        {
            printf("fuck u all , the file not exit biaaaaatch \n");
        }
    }
    // free(filename);


	return 0;
}
