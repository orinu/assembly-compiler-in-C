#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LENGTH 80

#include "second_run.h"

void second_run(FILE *fp)
{
  char line[80];
  /* line counter */
  line_number = 0;
  while (fgets(line, MAX_ROW_LENGTH, fp) != NULL)
  {
    line_number++;
    /* line */
    char *orignal_line = malloc(80 * sizeof(char));
    strcpy(orignal_line, trim(line));
    /* instruction */
    char *instruction = malloc(80 * sizeof(char));
    instruction = trim(instruction_name(line));

    /* if entry */
    if (strcmp(instruction, ".entry") == 0)
    {
      /* anlyze the data after ".entry" */
      char *data_string = trim(line_with_out_command(orignal_line, strlen(instruction)));
      /* insert 1 to entry falg  */
      symbole_entry_flag(data_string);
    }
  }
  
  int j;
  int ic_label_value[200];
  int ic_label_value_ptr = 0;

  for (j = 0; j < label_ptl; j++)
  {
    int value;
    int are;
    char *new_name;

    /* handle & address */
    if (label_names[j][0] == 38)
    {
      /* label name with & */
      new_name = symbol_name_without_choko(label_names[j]);
      /* err - label name not exist */
      if (check_if_symbol_exist(new_name) == 0)
      {
        err_flag = 1;
        printf("In line %d:\t\t the symbol \"%s\" symbol not exist. \n", line_number, new_name);
      }
      /* original label */
      int src_position = get_symbol_value(new_name);
      int labal_position = got_orignal_ic(j + 1);

      /* check if bne, jmp, jsr - opcode 9 */
      int opcode = instruction_data[labal_position] >> 18;
      if (opcode != 9)
      {
        err_flag = 1;
        printf("In line %d:\t\t the command not allowed to use \"%s\". \n", line_number, label_names[j]);
      }
      /* calculate the distance*/
      value = src_position - labal_position;
      /* determine the ARE bits*/
      are = 4;
    }
    /* if label without & */
    else
    {
      /* err - if label name not exist */
      if (check_if_symbol_exist(label_names[j]) == 0)
      {
        err_flag = 1;
        printf("In line %d:\t\t the symbol \"%s\" symbol not exist. \n", line_number, label_names[j]);
      }
      /* get the address of the label */
      value = get_symbol_value(label_names[j]);
      /* if external - insert to ARE bit 1 */
      if (check_if_external(label_names[j]) == 1)
      {
        /* get orignal ic */
        int labal_position = got_orignal_ic(j + 1) + 1;
        are = 1;
        external[external_ptl] = label_names[j];
        external[external_ptl + 1] = labal_position;
        external_ptl += 2;
      }
      /* if not external determine ARE bits to 2 and add 100 to value*/
      else if (check_if_external(label_names[j]) == 0)
      {
        are = 2;
        value += IC;
      }
    }
    /* shift left the value and mask the ARE */
    value = value << 3;
    value = value ^ are;

    /* insert the value to the array of label value*/
    ic_label_value[ic_label_value_ptr] = value;
    ic_label_value_ptr++;
  }
  /* insert the label value from the ic_label_value to ic instruction_data */
  ic_label_value_ptr = 0;
  for (j = 0; j < ic; j++)
  {
    if (instruction_data[j] == LABEL_FLAG)
    {
      instruction_data[j] = ic_label_value[ic_label_value_ptr];
      ic_label_value_ptr++;
    }
  }
}

void make_files(char *file_name)
{
  /* first file */
  char *filename = malloc(strlen(file_name));
  strcat(filename, file_name);
  strcat(filename, ".ob");

  FILE *fd;
  if (!(fd = fopen(filename, "w")))
  {
    fprintf(stderr, "cannot open file \n");
    exit(0);
  }
  else
  {
    fprintf(fd, "%d  \t\t %d \n", ICF, IDF);
    int i;
    for (i = 0; i < ic; i++)
    {
      if (instruction_data[i] >= 0)
      {
        fprintf(fd, "%07d \t%06x \n", i + IC, instruction_data[i]);
      }
      else
      {
        char tmp[100];
        int s = sprintf(tmp, "%x", instruction_data[i]);
        fprintf(fd, "%07d     %.6s\n", i + IC, tmp + s - 6);
      }
    }
  }
  printf("create file %s\n", filename);
  free(filename);

  /* second file */
  filename = malloc(strlen(file_name));
  strcat(filename, file_name);
  strcat(filename, ".ext");

  if (!(fd = fopen(filename, "w")))
  {
    fprintf(stderr, "cannot open file \n");
    exit(0);
  }
  else
  {
    int i;
    for (i = 0; i < external_ptl; i++)
    {
      fprintf(fd, "%s    %07d \n", external[i], external[i + 1] + IC);
      i++;
    }
  }
  printf("create file %s\n", filename);
  free(filename);

  /* third file */
  filename = malloc(strlen(file_name));
  strcat(filename, file_name);
  strcat(filename, ".ent");

  if (!(fd = fopen(filename, "w")))
  {
    fprintf(stderr, "cannot open file \n");
    exit(0);
  }
  else
  {
    int i;
    for (i = 0; i < label_entry_ptl; i++)
    {
      fprintf(fd, "%s    %07d \n", label_entres[i], get_symbol_value(label_entres[i]) + IC);
    }
    printf("create file %s\n", filename);
  }
}