#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h"
#include "utils.h"
#include "first_run.h"



#define MAX_ROW_LENGTH 80

 struct bits {
        unsigned int are:3;
        unsigned int funct:5;
        unsigned int r_des:3;
        unsigned int ad_des:2;
        unsigned int r_src:3;
        unsigned int ad_src:2;
        unsigned int opcode:6;
    } binary ;


void init_binary_struct() {
        binary.are = 0;
        binary.funct = 0;
        binary.r_des = 0;
        binary.ad_des = 0;
        binary.r_src = 0;
        binary.ad_src = 0;
        binary.opcode = 0;
}

void zero_oprated() {
        binary.r_des = 0;
        binary.ad_des = 0;
        binary.r_src = 0;
        binary.ad_src = 0;
}

void des_handle(char *operated_name) {
/*  if immediate */
  if (operated_name[0] == 35) {
      /* get number of immadte*/
      char number_of_imm[100];
      int i;
      for (i=0;i<strlen(operated_name);i++) {
          number_of_imm[i]=operated_name[i+1];
      }
    //   printf("%s is immediate\n", operated_name);
      /* insert the binary part of command*/
      binary.ad_des =0;
      binary.r_des =0;

      /* insert the immdate value to the ic array*/
      /* add 100 to lsb */
      int immadte = atoi(number_of_imm)<<3;
      immadte = immadte ^ 4;
      /* save */
      instruction_data[ic_temp] = immadte;
      ic_temp++;

  /*  if register */
  }else if(check_if_rgister(operated_name) ==1 ){
    //   printf("%s is rgister\n", operated_name);
      binary.ad_des =3;
      binary.r_des = get_rgister_number(operated_name);
  /* if label */
  }else {
    //   printf("%s is label\n", operated_name);
      binary.r_des =0;
      instruction_data[ic_temp] = -999898;
      ic_temp++;
      /* add to label array */
      label_names[label_ptl] = operated_name;
      label_ptl++;
      /* check if &*/
      if (operated_name[0] == 38) {
          binary.ad_des = 2;
      }else {
          binary.ad_des = 1;
      }
  }  
}

void src_handle(char *operated_name) {
/*  if immediate # */
  if (operated_name[0] == 35) {
      /* get number of immadte*/
      char number_of_imm[100];
      int i;
      for ( i=0;i<strlen(operated_name);i++) {
          number_of_imm[i]=operated_name[i+1];
      }
      binary.ad_src =0;
      binary.r_src =0;
      /* insert the immdate value to the ic array*/
      /* add 100 to lsb */
      int immadte = atoi(number_of_imm)<<3;
      immadte = immadte ^ 4;
      /* save */
      instruction_data[ic_temp] = immadte;
      ic_temp++;

  /*  if register */
  }else if(check_if_rgister(operated_name) ==1 ){
    //   printf("%s is rgister\n", operated_name);
      binary.ad_src =3;
      binary.r_src = get_rgister_number(operated_name);
  /* if label */
  }else {
    //   printf("%s is label\n", operated_name);
      binary.r_src =0;
      instruction_data[ic_temp] = -999898;
      ic_temp++;
      /* add to label array */
      label_names[label_ptl] = operated_name;
      label_ptl++;
      /* check if &*/
      if (operated_name[0] == 38) {
          binary.ad_src = 2;
      }else {
          binary.ad_src = 1;
      }
  }  
}

const void check_line(const char *line) {

    /* init binary data */
    init_binary_struct();
    /* memory save of the hole line */
    char *orignal_line = malloc(80*sizeof(char));
    strcpy(orignal_line, trim(line));

    /* memory save of the instruction line */
    char *instruction = malloc(80*sizeof(char));
    instruction= trim(instruction_name(line));

    /*  if command */
    if (islower(instruction[0])>0){
            printf("the line is :%s \n",line);
            // printf("the instruction is :%s \n",instruction);
        if (check_if_command_exist(instruction) == 0){
            // printf("the line is :%s \n",line);
            // printf("the instruction is :%s \n",instruction);
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

                /* print the command */
                // printf("%s \n", orignal_line);
                // printf("the operated_number is %d \n", operated_number);

                /* after chaeck the number of opreated is ligal to the commnad*/
                char *operated_name =  get_operated_names( trim(line_with_out_command(orignal_line, strlen(instruction))) , operated_number  );
                /* handale oprate number of 0 */
                if (operated_number == 0) {
                    zero_oprated();
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    update_pointers();
                       /* print binary code */
                    printf(" %d \n \n" ,*k );
                }
                /* handale oprate number of 1 */
                else if (operated_number == 1) {
                    
                    des_handle(operated_name);
       
                    
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    update_pointers();
                    /* print binary code */
                    printf(" %d \n \n" ,*k );


                /* handle 2 number of operat ligal*/ 
                }else if (operated_number == 2) {
                    char *first_operat = malloc(10 * sizeof(char));
                    char *sec_operat = malloc(10 * sizeof(char));
                    int i = 0;
                    int j =0;
                    /* get first op */
                    while (operated_name[i] != 32)
                    {
                        first_operat[i] = operated_name[i];
                        i++;
                    }
                    first_operat = trim(first_operat);
                
                    /* get sec op */
                    while (operated_name[i] != '\0')
                    {
                        sec_operat[j] = operated_name[i];
                        i++;
                        j++;
                    }
                    sec_operat = trim(sec_operat);
                    
                    /* insert binary code after analaze */
                    src_handle(first_operat);
                    des_handle(sec_operat);
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    update_pointers();
                     printf(" %d \n \n" ,*k );

                    /* print the binary value */
                    // printf("%d \n \n" ,binary); 
                }


            }else {
                /* syntax error */
            }
    
        }
    }
    /*  if spec */
    if ((instruction[0]) == 46){
        printf("%s is spec \n",instruction);
        /* 4 handles */

        /* if data */
        if( strcmp(instruction ,".data") ==0 ){
            /* string without ".data" */
            char *data_string = trim(line_with_out_command(orignal_line,strlen(instruction)));
            /* useing tem char for savind the value and temp pointer j */
            char temp[20];
            int j=0;
            /* run on number with out the ".data"*/
            int i;
            for ( i =0; i<strlen(data_string); i++) {
                /* run on the data until comma*/
                if (data_string[i] != 44) {
                    temp[j] = data_string[i];
                    j++;
                /* if mach comma save the number and init the temp var*/
                }if (data_string[i] == 44) {
                    /* save data*/
                    data[dc] = atoi(temp);
                    dc++;
                    /* add to ic */
                    instruction_data[ic] = atoi(temp);
                    ic++; 
                    update_pointers();
                    /* init temp var*/
                    char temp[20];
                    j=0;
                }   
                
            }
            /* after finish to analayze the data save the last number or the first one (depond on the comma)*/
            data[dc] = atoi(temp);
            dc++;
            /* add to ic */
            instruction_data[ic] = atoi(temp);
            ic++; 
            update_pointers();
        }

        /* if string */
        if( strcmp(instruction ,".string") ==0 ){
          /* get data without ".string" */
          char *data_string = trim(line_with_out_command(orignal_line,strlen(instruction))); 
          int ascii_code; 
          /* run on the data and insert to data array */ 
          int i;
          for ( i=1;i<strlen(data_string)-1; i++) {
              ascii_code = data_string[i];
              data[dc] = ascii_code;
              dc++;
              /* add to ic */
              instruction_data[ic] = ascii_code;
              ic++; 
              update_pointers();
          }
          /* add in the end of the sting 0 and up dc counter*/
          data[dc] = 0;                    
          dc++;
        /* add to ic */
        instruction_data[ic] = 0;
        ic++; 
        update_pointers();
        }       

        /* if extern */
        if( strcmp(instruction ,".extern") ==0 ){
            char *data_string = trim(line_with_out_command(orignal_line,strlen(instruction))); 
            add_symbole(data_string, 0, "external");
        }       
    }

}


void first_run(FILE *fp) {
    char line[80];
     /* run on evrey line in the file */ 
            while(fgets(line,  MAX_ROW_LENGTH , fp) != NULL) {
                int start_with_symbol_flag = 0;
                /* print line*/ 
                // printf("%s \n",line); 
                /* run on evrey char in line */
                int line_length = strlen(line);
                int j;
                for ( j=0; j< line_length; j++) {
                    /* SYMBOL */ 
                    /*  if there is ":" symbol name*/
                    if ( line[j] == ':') {
                        start_with_symbol_flag =1;
                        char symbol_name[30] = "";
                        char spec[30] = "code";
                        char *ret;

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
                        add_symbole(symbol_name, ic, spec);

                        // char *returned_line =  trim(line_with_out_symbol(line, j+1));
                        // printf("%s \n ",returned_line);
                        // printf("%d \n  ",returned_line[0]);
                        // printf("%s \n",instruction_name(line_with_out_symbol(line, j+1)));
                        


                        check_line(line_with_out_symbol(line, j+1));
                    }
                } if (start_with_symbol_flag == 0 ) {
                    check_line(line);
                }
            }

            // /* print the data array and dc counter*/
            // printf("the data array is: ");
            // int i;
            // for ( i=0; i<dc ;i++) {
            //   printf(" %d ,",data[i]);
            // }printf("\n");
            // printf("the dc is: %d \n",dc);
            
            // /* print the data array and dc counter*/
            // printf("the ic array is: ");
            // for ( i=0; i<ic ;i++) {
            //   printf(" %d ,",instruction_data[i]);
            // }printf("\n");
            // printf("the ic is: %d \n",ic);

            // /* print the label array and pointer */
            // printf("the label_ptl array is: ");
            // for ( i=0; i<label_ptl ;i++) {
            //   printf(" %s ,",label_names[i]);
            // }printf("\n");
            // printf("the label_ptl is: %d \n",label_ptl);
        
}

