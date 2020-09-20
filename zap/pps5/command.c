#include "command.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch)
{
  if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;

  struct command *new_com = (struct command*) calloc(1, sizeof(struct command));

  char *new_name = calloc(1, strlen(name)+1);
  char *new_desc = calloc(1, strlen(description)+1);

  strcpy(new_name, name);
  strcpy(new_desc, description);

  new_com->name = new_name;
  new_com->description = new_desc;

  if(pattern != NULL){
    regex_t regex;
    regcomp(&regex, pattern, 0);
    new_com->preg = regex;
  }
  
  new_com->groups = NULL;
  new_com->nmatch = nmatch;

  return new_com;
}

struct command* destroy_command(struct command* command)
{
  if(command == NULL) return NULL;
  free(command->name);
	free(command->description);
	regfree(&command->preg);
	free(command);
  return NULL;
}