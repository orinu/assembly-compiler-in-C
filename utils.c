#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "data.h"

/* return line with no starting symbol*/
char *line_with_out_symbol(char *line, int ptl)
{
    char *new_line = malloc(MAX_ROW_LENGTH * sizeof(char));
    int i;
    int j;
    for (i = ptl, j = 0; i < strlen(line); i++, j++)
    {
        new_line[j] = line[i];
    }
    return new_line;
}

/* return line with no starting command */
char *line_with_out_command(char *line, int ptl)
{
    char *line_with_out_command = malloc(MAX_ROW_LENGTH * sizeof(char));
    int i;
    int j;
    for (i = ptl, j = 0; i < strlen(line); i++, j++)
    {
        line_with_out_command[j] = line[i];
    }
    return line_with_out_command;
}

/* trim function */
char *trim(char *line)
{
    char *line_with_out_spaces = malloc(MAX_ROW_LENGTH * sizeof(char));
    int j;

    int start = 0;
    int end = strlen(line) - 1;

    if (!line)
        return NULL;
    if (!*line)
        return line;

    while (isspace(line[start]))
    {
        start++;
    }
    while (isspace(line[end]))
    {
        end--;
    }
    for (j = 0; start < end + 1; start++, j++)
    {
        line_with_out_spaces[j] = line[start];
    }
    return line_with_out_spaces;
}

/* get instruction name */
char *instruction_name(char *line)
{
    char *command_name;
    command_name = strtok(line, " ");
    return command_name;
}

/* check how many oprated there are */
int get_operated_number(char *line, char *command_name)
{
    int comma_counter = 0;
    int i;
    for (i = 0; i < strlen(line) - 1; i++)
    {
        if (line[i] == 44)
        {
            comma_counter++;
        }
    }
    if (comma_counter == 0)
    {
        if (trim(line_with_out_command(line, strlen(command_name)))[0])
        {
            /* return 1 operated  if there is char is not space */
            return 1;
            /* return 0 operated if there is no char */
        }
        return 0;
        /* return 1 + comma's number operated */
    }
    return comma_counter + 1;
}

/*  get operate names */
char *get_operated_names(char *line, int operated_number)
{
    char *operated_names_values = malloc(MAX_ROW_LENGTH * sizeof(char));
    /* return operate name for 1 operate */
    if (operated_number == 1)
    {
        return line;
        /* return operate name for 2 operate */
    }
    else if (operated_number == 2)
    {
        char *operated_names;
        /* cut the two operate */
        operated_names = strtok(line, ",");
        while (operated_names != NULL)
        {
            strcat(operated_names_values, operated_names);
            strcat(operated_names_values, " ");
            operated_names = strtok(NULL, ",");
        }
        return operated_names_values;
    }
    return "";
}

/* return symbol name without & */
char *symbol_name_without_choko(char *name)
{
    char *name_without = malloc(MAX_ROW_LENGTH * sizeof(char));
    int i;
    for (i = 0; i < strlen(name); i++)
    {
        name_without[i] = name[i + 1];
    }
    return name_without;
}