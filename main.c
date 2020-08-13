#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h"
#include "utils.h"
#include "first_run.h"
#include "second_run.h"


int main(int argc, char *argv[]){
    FILE *fp;
    int i;

    init_data();
  
    for( i = 1; i < argc; i++)
    {    
        /* merage file name with .as */ 
        char* filename = malloc(strlen(argv[i])+4);
        strcpy(filename,argv[i]);
        strcat(filename,".as");

        /*  open file */
        fp = fopen(filename, "r");
        if(fp != NULL) { 
            printf("reading file name %s \n \n" , filename);
            /* trsfer file to first run */
            first_run(fp);
            rewind(fp);
            second_run(fp);
            /* if there is no err make the output files */
            if (err_flag == 0) {
              char* filename_without_extension = malloc(strlen(argv[i])+4);
              strcpy(filename_without_extension,argv[i]);
              make_files(filename_without_extension );  
              free(fp);
            }
            /* if there are err*/
            else {
                printf("\n \n \nfix the error and try again s\n");
            }
            
        }else 
        {
            printf("cannot open the file \n");
        }
	return 0;
 }
 return 0;
}
