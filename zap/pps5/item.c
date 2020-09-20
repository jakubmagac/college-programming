#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item* create_item(char* name, char* description, unsigned int properties)
{
  if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;
  struct item* new_item = (struct item*) calloc(1, sizeof(struct item));
 
  new_item->name = name;
  new_item->description = description;
  new_item->properties = properties;

  char *new_name = calloc(1, strlen(name)+1);
  char *new_desc = calloc(1, strlen(description)+1);

  strcpy(new_name, name);
  strcpy(new_desc, description);

  new_item->name = new_name;
  new_item->description = new_desc;

  return new_item;
}

struct item* destroy_item(struct item* item)
{
    if(item == NULL) return NULL;
    free(item->name);
    free(item->description);
    free(item);
    return NULL;
}