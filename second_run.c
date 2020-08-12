#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ROW_LENGTH 80


#include "second_run.h"



void second_run(FILE *fp) {
    char line[80];
     while(fgets(line,  MAX_ROW_LENGTH , fp) != NULL) {
       /* memory save of the hole line */
       char *orignal_line = malloc(80*sizeof(char));
       strcpy(orignal_line, trim(line));
       /* memory save of the instruction line */
       char *instruction = malloc(80*sizeof(char));
       instruction= trim(instruction_name(line));

       /* if entry */ 
       if( strcmp(instruction ,".entry") ==0 ){
        /* anlyze the data after ".entry" */
        char *data_string = trim(line_with_out_command(orignal_line,strlen(instruction)));
        /* insert 1 to entry falg  */
        symbole_entry_flag(data_string);
        }
   
        }
        /* define var for label value in sec run*/
        int j;
        int ic_label_value[200];
        int ic_label_value_ptr = 0;

        for ( j=0; j<label_ptl ;j++) {
          int value; 
          int are;
          char *new_name;
          /* handle adress delta of &LABAL */
          if (label_names[j][0] == 38) {
            /* label name with & */
            new_name = symbol_name_without_choko(label_names[j]);
            /* get the postion of the original label and the use of the label */
            int src_position = get_symbol_value(new_name);
            int labal_position = got_orignal_ic(j+1);
            /* calculate the distance*/
            value = src_position - labal_position ;
            /* determine the ARE bits*/
            are = 4;

          /* if label with out & */
          }else {
            /* get the adress of the label */
            value = get_symbol_value(label_names[j]) ;
            /* if external the ARE bit is 1 */
            if (check_if_external(label_names[j]) == 1) {
              /* got_orignal_ic go to the original commnd therefore need to add 1  */
              int labal_position = got_orignal_ic(j+1) +1  ;
              are = 1;
              printf("%s is eternal the value is  %07d\n",label_names[j],labal_position);
              external[external_ptl] = label_names[j];
              external[external_ptl+1] =labal_position;
              external_ptl += 2;
            /* if not external determine ARE bits to 2 and add 100 to value*/
            }else if (check_if_external(label_names[j]) == 0) {
              are = 2;
              value += IC;
            }
          }
          /* shift left the value and mask the ARE */ 
          value = value<<3;
          value = value^are;

          /* insert the value to the array of label value*/
          ic_label_value[ic_label_value_ptr] = value;
          ic_label_value_ptr++;
    }
            /* print the ic_label_value */
            printf("the ic_label_value array is: ");
            int k;
            for ( k=0; k<ic_label_value_ptr ;k++) {
              printf(" %d ,",ic_label_value[k]);
            }printf("\n");
            printf("the ic_label_value_ptr is: %d \n",ic_label_value_ptr);

        /* insert the label value from the ic_label_value to ic instruction_data */
        ic_label_value_ptr =0;    
        for (j=0;j<ic;j++){
        if (instruction_data[j] == -999898) {
            instruction_data[j] = ic_label_value[ic_label_value_ptr];
            ic_label_value_ptr++;
        }
    }



  

            
            


                    /* */
        //   printf("the line is: %s \n",label_names[j]);
        //   printf("the value is: %d \n",value);
        //   printf("the value in hex is: %06x \n",value);

                /* print the data array and dc counter*/
            printf("the data array is: ");
            int i;
            for ( i=0; i<dc ;i++) {
              printf(" %d ,",data[i]);
            }printf("\n");
            printf("the dc is: %d \n",dc);

            /* the ps.op output */
            printf("the hex array is: \n");
            printf("the ICF is: %d . the IDF is: %d \n", ICF, IDF);
            for ( i=0; i<ic ;i++) {
            printf("the ic value is: %07d ,the value in hex is: %06x \n",i+IC,instruction_data[i]);
            }printf("\n");
            printf("the dc is: %d \n",dc);

            /* the ps.ent output */
            printf("the ps.ent \n");
            for ( i=0; i<label_entry_ptl ;i++) {
            printf("%s    %07d \n", label_entres[i], get_symbol_value(label_entres[i])+IC  );
            }printf("\n");
            
            /* the ps.ext output */
            printf("the ps.ext \n");
            for ( i=0; i<external_ptl ;i++) {
            printf("%s    %07d \n", external[i]  ,external[i+1] +IC );
            i++;
            }printf("\n");
            
            /* print the data array and dc counter*/
            printf("the ic array is: ");
            for ( i=0; i<ic ;i++) {
              printf(" %d ,",instruction_data[i]);
            }printf("\n");
            printf("the ic is: %d \n",ic);

            /* print the label name array and pointer */
            printf("the label_ptl array is: ");
            for ( i=0; i<label_ptl ;i++) {
            printf(" %s ,",label_names[i]);
            }printf("\n");
            printf("the label_ptl is: %d \n",label_ptl);

            /* print the label entry array and pointer */
            printf("the label_ptl array is: ");
            for ( i=0; i<label_entry_ptl ;i++) {
            printf(" %s ,",label_entres[i]);
            }printf("\n");
            printf("the label_ptl is: %d \n",label_entry_ptl);
}


void make_files(char *file_name) {
    /* first file */
    char* filename = malloc(strlen(file_name));
    strcat(filename,file_name);
    strcat(filename,".ob");

    FILE *fd;
    if (!(fd = fopen(filename,"w"))) {
        fprintf(stderr,"cannot open file \n");
        exit(0);
    }else {
            fprintf(fd,"%d  \t\t %d \n", ICF, IDF);
            int i;
            for ( i=0; i<ic ;i++) {
                if (instruction_data[i] >=0 ){
                    fprintf(fd,"%07d \t%06x \n",i+IC,instruction_data[i]);
                } else {
                      char tmp[100];
                      int s = sprintf(tmp, "%x", instruction_data[i]);
                      fprintf(fd,"%07d     %.6s\n",i+IC, tmp + s - 6 );
                }
            }
    }
    free(filename);
    
    /* second file */
    filename = malloc(strlen(file_name));
    strcat(filename,file_name);
    strcat(filename,".ext");

    if (!(fd = fopen(filename,"w"))) {
        fprintf(stderr,"cannot open file \n");
        exit(0);
    }else { 
        int i;
        for ( i=0; i<external_ptl ;i++) {
        fprintf(fd,"%s    %07d \n", external[i]  ,external[i+1] +IC );
        i++;
        }
    }
    free(filename);

    /* third file */
    filename = malloc(strlen(file_name));
    strcat(filename,file_name);
    strcat(filename,".ent");

    if (!(fd = fopen(filename,"w"))) {
        fprintf(stderr,"cannot open file \n");
        exit(0);
    }else { 
        int i;
        for ( i=0; i<label_entry_ptl ;i++) {
            fprintf(fd,"%s    %07d \n", label_entres[i], get_symbol_value(label_entres[i])+IC);
         }
        }
}