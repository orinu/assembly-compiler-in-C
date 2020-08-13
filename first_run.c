#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "utils.h"
#include "first_run.h"



struct bits
{
    unsigned int are : 3;
    unsigned int funct : 5;
    unsigned int r_des : 3;
    unsigned int ad_des : 2;
    unsigned int r_src : 3;
    unsigned int ad_src : 2;
    unsigned int opcode : 6;
} binary;

void first_run(FILE *fp)
{
    char line[MAX_ROW_LENGTH];
    /* run on every line in the file */
    while (fgets(line, MAX_ROW_LENGTH, fp) != NULL)
    {
        line_number++;
        /* send to check_line after handel symbol*/
        int start_with_symbol_flag = 0;
        /* run on evrey char in line */
        int line_length = strlen(line);
        int j;
        for (j = 0; j < line_length; j++)
        {
            /* SYMBOL */
            /*  if there is ":" symbol name*/
            if (line[j] == ':')
            {
                /* err if isn't space after ":" */
                if (!isspace(line[j + 1]))
                {
                    err_flag = 1;
                    printf("In line %d: \t\t expect to have space after \":\". \n", line_number);
                }
                start_with_symbol_flag = 1;
                char symbol_name[30] = "";
                char spec[30] = "code";
                char *ret;
                /* get the name of the symbol*/
                strncpy(symbol_name, line, j);
                /* looking for ".data"*/
                ret = strstr(line, ".data");
                if (ret != NULL)
                {
                    strcpy(spec, "data");
                }
                /* looking for ".string"*/
                ret = strstr(line, ".string");
                if (ret != NULL)
                {
                    strcpy(spec, "data");
                }
                /* add symbol to the symbol table */
                add_symbole(symbol_name, ic, spec);
                check_line(line_with_out_symbol(line, j + 1));
            }
        }
        /* no symbol send to check line  */
        if (start_with_symbol_flag == 0)
        {
            check_line(line);
        }
    }
}

/* check line function*/
const void check_line(const char *line)
{
    /* init binary data */
    init_binary_struct();
    /* memory save of the hole line */
    char *orignal_line = malloc(MAX_ROW_LENGTH * sizeof(char));
    strcpy(orignal_line, trim(line));

    /* memory save of the instruction line */
    char *instruction = malloc(MAX_ROW_LENGTH * sizeof(char));
    instruction = trim(instruction_name(line));

    int i;
    int space_line = 0;
    /* check if line is space line */
    for (i = 0; i < strlen(line); i++)
    {
        if (!isspace(line[i]))
        {
            space_line = 1;
        }
    }

    /*  if command */
    if (islower(instruction[0]) > 0)
    {
        if (check_if_command_exist(instruction) == 0)
        {
            /* err - cmmand not exist */
            err_flag = 1;
            printf("In line %d: \t\t \"%s\" command not exist. \n", line_number, instruction);
        }
        else
        {
            /* inesrt to the binary command the opcode, funct and are */
            binary.opcode = get_opcode_number(instruction);
            binary.funct = get_funct_number(instruction);
            binary.are = 4;

            /* calculate how many opareted there are in the line */
            int operated_number = get_operated_number(orignal_line, instruction);
            /* compare line operate with the command operate */
            /* error - operate not equal */
            if (check_operated_number(instruction, operated_number) == 0)
            {
                err_flag = 1;
                printf("In line %d: \t\t the operator number of \"%s\" is not ligal. \n", line_number, instruction);
            }
            /* operate line equal to command operate*/
            if (check_operated_number(instruction, operated_number) == 1)
            {
                /* src adress and src register is 0 cuz one oprate */
                binary.ad_src = 0;
                binary.r_src = 0;
                char *operated_name = get_operated_names(trim(line_with_out_command(orignal_line, strlen(instruction))), operated_number);

                /* handale oprate number of 0 */
                if (operated_number == 0)
                {
                    /* inesrt zero to binary code */
                    zero_oprated();
                    /* insert the binary value to instruction data */
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    /* up the i counter*/
                    ICF++;
                    update_pointers();
                }
                /* handale oprate number of 1 */
                else if (operated_number == 1)
                {
                    /* handle des operate  */
                    des_handle(operated_name);
                    /* insert the binary value to instruction data */
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    /* up the i counter*/
                    ICF++;
                    update_pointers();
                }
                /* handle 2 operate */
                else if (operated_number == 2)
                {
                    char *first_operat = malloc(MAX_ROW_LENGTH * sizeof(char));
                    char *sec_operat = malloc(MAX_ROW_LENGTH * sizeof(char));
                    int i = 0;
                    int j = 0;
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

                    /* insert binary code after analyze */
                    src_handle(first_operat);
                    des_handle(sec_operat);
                    /* insert the binary value to instruction data */
                    int *k = &binary;
                    instruction_data[ic] = *k;
                    ic++;
                    /* up the i counter*/
                    ICF++;
                    update_pointers();
                }
            }
        }
    }
    /*  if spec */
    else if ((instruction[0]) == 46)
    {
        /* 4 handles */

        /* if data */
        if (strcmp(instruction, ".data") == 0)
        {
            int i;
            /* string without ".data" */
            char *data_string = trim(line_with_out_command(orignal_line, strlen(instruction)));
            /* search for data syntax err */
            data_err(data_string);
            /* useing temp char for savind the value */
            char temp[MAX_ROW_LENGTH];
            int j = 0;
            for (i = 0; i < strlen(data_string); i++)
            {
                /* search for comma */
                if (data_string[i] != 44)
                {
                    temp[j] = data_string[i];
                    j++;
                }
                if (data_string[i] == 44)
                {
                    /* save data*/
                    data[dc] = atoi(temp);
                    dc++;
                    /* add to ic */
                    instruction_data[ic] = atoi(temp);
                    ic++;
                    /* up the d counter*/
                    IDF++;
                    update_pointers();
                    /* init temp var*/
                    char temp[20];
                    j = 0;
                }
            }
            /* save the last number or the first one (depond on the comma) */
            data[dc] = atoi(temp);
            dc++;
            /* add to ic */
            instruction_data[ic] = atoi(temp);
            ic++;
            /* up the d counter*/
            IDF++;
            update_pointers();
        }

        /* if string */
        if (strcmp(instruction, ".string") == 0)
        {
            /* get data without ".string" */
            char *data_string = trim(line_with_out_command(orignal_line, strlen(instruction)));
            int ascii_code;
            int i;
            int quotation_number = 0;
            /* check for err - .string syntax */
            for (i = 0; i < strlen(data_string); i++)
            {
                if (data_string[i] == 34)
                {
                    quotation_number++;
                }
            }
            if (quotation_number != 2)
            {
                err_flag = 1;
                printf("In line %d: \t\t string syntax error. \n", line_number, instruction);
                return;
            }

            /* insert into data array */
            for (i = 1; i < strlen(data_string) - 1; i++)
            {
                ascii_code = data_string[i];
                data[dc] = ascii_code;
                dc++;
                /* add to ic */
                instruction_data[ic] = ascii_code;
                ic++;
                /* up the d counter*/
                IDF++;
                update_pointers();
            }
            /* add in the end of the string 0 */
            data[dc] = 0;
            dc++;
            /* add to ic */
            instruction_data[ic] = 0;
            ic++;
            /* up the d counter*/
            IDF++;
            update_pointers();
        }

        /* if extern */
        if (strcmp(instruction, ".extern") == 0)
        {
            char *data_string = trim(line_with_out_command(orignal_line, strlen(instruction)));
            add_symbole(data_string, 0, "external");
        }
    }
    /* if space_line continue */
    else if (space_line == 0) {}
    /* unrecognized line */
    else
    {
        err_flag = 1;
        printf("In line %d: \t\t unrecognized syntax error. \n", line_number);
    }
}

/* init data */
void init_binary_struct()
{
    binary.are = 0;
    binary.funct = 0;
    binary.r_des = 0;
    binary.ad_des = 0;
    binary.r_src = 0;
    binary.ad_src = 0;
    binary.opcode = 0;
}

/* insert 0 to zero operate*/
void zero_oprated()
{
    binary.r_des = 0;
    binary.ad_des = 0;
    binary.r_src = 0;
    binary.ad_src = 0;
}

void des_handle(char *operated_name)
{
    /*  if immediate */
    if (operated_name[0] == 35)
    {
        /* if err in lea */
        if (!(binary.opcode == 1 || binary.opcode == 13))
        {
            err_flag = 1;
            printf("In line %d:\t\t that command not allowed immediate in the des operated. \n", line_number);
        }
        /* get number of immediate*/
        char number_of_imm[MAX_ROW_LENGTH];
        int i;
        for (i = 0; i < strlen(operated_name); i++)
        {
            number_of_imm[i] = operated_name[i + 1];
        }
        /* insert the binary part of command */
        binary.ad_des = 0;
        binary.r_des = 0;

        /* insert the immediate value to the ic array */
        int immadte = atoi(number_of_imm) << 3;
        immadte = immadte ^ 4;
        /* save */
        instruction_data[ic_temp] = immadte;
        ic_temp++;
        /* up the i counter*/
        ICF++;
    }
    /*  if register */
    else if (check_if_rgister(operated_name) == 1)
    {
        /* err - rgister is not alow in opcode 9 */
        if (binary.opcode == 9)
        {
            err_flag = 1;
            printf("In line %d:\t\t the command not allowed to use rgister in the des operated. \n", line_number);
        }
        binary.ad_des = 3;
        binary.r_des = get_rgister_number(operated_name);
    }
    /* if label */
    else
    {
        binary.r_des = 0;
        instruction_data[ic_temp] = LABEL_FLAG;
        ic_temp++;
        /* up the i counter*/
        ICF++;
        /* add to label array */
        label_names[label_ptl] = operated_name;
        label_ptl++;
        /* check if &*/
        if (operated_name[0] == 38)
        {
            binary.ad_des = 2;
        }
        else
        {
            binary.ad_des = 1;
        }
    }
}

void src_handle(char *operated_name)
{
    /*  if immediate # */
    if (operated_name[0] == 35)
    {
        /* if err - lea cant get src immediate */
        if (binary.opcode == 4)
        {
            err_flag = 1;
            printf("In line %d:\t\t the command lea not allowed immediate in the src operated. \n", line_number);
        }
        /* get number of immediate*/
        char number_of_imm[MAX_ROW_LENGTH];
        int i;
        for (i = 0; i < strlen(operated_name); i++)
        {
            number_of_imm[i] = operated_name[i + 1];
        }
        binary.ad_src = 0;
        binary.r_src = 0;
        /* insert the immediate value to the ic array*/
        int immadte = atoi(number_of_imm) << 3;
        immadte = immadte ^ 4;
        /* save */
        instruction_data[ic_temp] = immadte;
        ic_temp++;
        /* up the i counter*/
        ICF++;
    }
    /*  if register */
    else if (check_if_rgister(operated_name) == 1)
    {
        /* if err - lea cant get src register */
        if (binary.opcode == 4)
        {
            err_flag = 1;
            printf("In line %d:\t\t the command lea not allowed register in the src operated. \n", line_number);
        }
        binary.ad_src = 3;
        binary.r_src = get_rgister_number(operated_name);
    }
    /* if label */
    else
    {
        binary.r_src = 0;
        instruction_data[ic_temp] = LABEL_FLAG;
        ic_temp++;
        /* up the i counter*/
        ICF++;
        /* add to label array */
        label_names[label_ptl] = operated_name;
        label_ptl++;
        /* check if &*/
        if (operated_name[0] == 38)
        {
            binary.ad_src = 2;
        }
        else
        {
            binary.ad_src = 1;
        }
    }
}

/* data syntax err */
void data_err(char *data_string)
{
    int i = 0;
    if ((!isdigit(data_string[0]) && !(data_string[0] == 45)) || !isdigit(data_string[strlen(data_string) - 1]))
    {
        err_flag = 1;
        printf("In line %d: \t\t data syntax error. \n", line_number);
    }
    /*   */
    for (i = 0; i < strlen(data_string); i++)
    {
        /* two comma in a row or - and no digit after*/
        if (((data_string[i] == 44) && (data_string[i + 1] == 44)) || ((data_string[i] == 45) && !isdigit(data_string[i + 1])))
        {
            err_flag = 1;
            printf("In line %d: \t\t data syntax error. \n", line_number);
        }
        /* not digit or comma or - */
        if (!(isdigit(data_string[i]) || data_string[i] == 44 || data_string[i] == 45 || isspace(data_string[i])))
        {
            err_flag = 1;
            printf("In line %d: \t\t data syntax error. \n", line_number);
        }
        if ((i != 0) && (data_string[i] == 45) && !((data_string[i - 1] == 44) || isspace(data_string[i - 1])))
        {
            err_flag = 1;
            printf("In line %d: \t\t data syntax error. \n", line_number);
        }
    }
}
