#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radat.h"



#define T_INT 1
#define T_STR 2

static int curr_line=1;


void add_prop_int(void *packet, int id, int type, int val)
{
  printf("attribute id=%d type=%d value=%d\n",id,type,val);
}

void add_prop_str(void *packet, int id, int type, char *val)
{
  printf("attribute id=%d type=%d value=%s\n",id,type,val);
}


int read_int(char **buff)
{
  int result = 0;

  while (**buff >= '0' && **buff <= '9')
    {
      result = **buff - '0' + result * 10;
      (*buff)++;
    }
  if (**buff != ' ' && **buff != '\n' && **buff != '\t')
    ERROR("Integer attribute expected!\n");
  return result;
}

char *read_string(char **buff)
{
  int size = 0;
  int backslashes = 0;
  char *str = NULL, *s_str = NULL;

  if (**buff != '"')
    ERROR("String attribute expected!\n");
  /* Skip \" character */
  (*buff)++;

  while (**buff != '\"')
    {
      /* count characters until end */
      if (**buff == '\\') backslashes++;
      (*buff)++;
      size++;
    }

  str = (char *)malloc(size+1-backslashes);
  if (NULL == str)
    ERROR("Unable to allocate buffer of size %d!\n",size+1);
  s_str = str;

  *buff = *buff - size;

  while(size > 0)
    {
      if (**buff == '\\')
	{
	  (*buff)++;
	  continue;
	} else {
	*str = **buff;
	str++;
	(*buff)++;
	size--;
      }
    }
  *str = '\0';
  (*buff)++;
  return s_str;
}

int read_type(char **buff)
{  
  if (0 == strncmp(*buff, "INTEGER", 7))
    {
      *buff = (*buff) + 7;
      return T_INT;
    } 
  else if (0 == strncmp(*buff, "STRING", 6))
    {
      *buff = (*buff) + 6;
      return T_STR;
    }
  else
    ERROR("Unknown attribute type - line: %d!\n", curr_line);

  return -1;
}

void eat_space(char **buff)
{
  while(**buff == ' ' || **buff == '\t')
    (*buff)++;
}

int eat_newline(char **buff)
{
  int count = 0;

  while (**buff == '\n') 
    {
      (*buff)++;
      count++;
    }
  return count;
}

int parse_config(char *f_name) 
{
  FILE *fp = NULL;
  long f_size = 0;
  size_t f_read = 0;
  char *buff = NULL, *s_buff = NULL;
  int id, type;

  fp = fopen(f_name,"r");
  if (NULL == fp)
    ERROR("Unable to open %s file!\nExiting....\n", f_name);

  if (0 != fseek(fp, 0, SEEK_END))
    ERROR("Unable to execute fseek to end of the file\n");

  f_size = ftell(fp);
  
  if (0 != fseek(fp, 0, SEEK_SET))
    ERROR("Unable to execute fseek to start of the file!\n");

  s_buff = buff = (char *)malloc(f_size);
  if (NULL == buff + 1)
    ERROR("Unable to allocate %ld bytes of memory!\n", f_size + 1);

  f_read = fread(buff, 1, f_size, fp);

  if (f_read < f_size)
    ERROR("Error reading file %s!\n", f_name);

  while (buff < (s_buff + f_read))
    {
      id = read_int(&buff);
      eat_space(&buff);
      switch (type = read_type(&buff)) 
	{
	case T_INT :    eat_space(&buff); 
			add_attrib_int(id, (unsigned int)read_int(&buff));
			break;
	case T_STR :    eat_space(&buff);
	                add_attrib_string(id, read_string(&buff));
			break;
	default    : ERROR("Unknown type in config file!\n");
	}
      eat_space(&buff);
      curr_line+= eat_newline(&buff);
    }

  fclose(fp);
  free(s_buff);
  return 0;
}
