#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "first_run.c"



int main(int argc, char *argv[]){
    init_data();
    FILE *fp;
  

    for(int i = 1; i < argc; i++)
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
           
        }else 
        {
            printf("fuck u all , the file not exit biaaaaatch \n");
        }
    
    // free(filename);


	return 0;
 }
}
