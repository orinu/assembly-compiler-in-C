#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "data.h"
#include "utils.h"
#include "first_run.h"
#include "second_run.h"


int main(int argc, char *argv[]){
    init_data();
    FILE *fp;
  
    int i;
    for( i = 1; i < argc; i++)
    {    
        /* merage file name with .as */ 
        char* filename = malloc(strlen(argv[i])+4);
        strcpy(filename,argv[i]);
        strcat(filename,".as");

        /*  open file */
        fp = fopen(filename, "r");
        if(fp != NULL) { 
            printf("reading file name  %s \n \n" , filename);
            /* trsfer file to first run */
            first_run(fp);
            rewind(fp);
            second_run(fp);

            char* filename_without_extension = malloc(strlen(argv[i])+4);
            strcpy(filename_without_extension,argv[i]);

            make_files(filename_without_extension );  
        }else 
        {
            printf("fuck u all , the file not exit biaaaaatch \n");
        }
	return 0;
 }
}
