#include "backpack.h"
#include "item.h"
#include "container.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <stdio.h>


struct backpack* create_backpack(const int capacity)
{
  struct backpack* new_backpack = (struct backpack*) calloc(1, sizeof(struct backpack));
  new_backpack->capacity = capacity;
  new_backpack->items = NULL;
  new_backpack->size = 0;
  return new_backpack;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item)
{
  if(backpack == NULL || item == NULL || backpack->size >= backpack->capacity) return false;
  backpack->size += 1;
  
  if(backpack->items == NULL) backpack->items = create_container(backpack->items, ITEM, item); 
  else create_container(backpack->items, ITEM, item);

  return true;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name)
{
  if(backpack == NULL || name == NULL || strlen(name) == 0) return NULL;
	return get_from_container_by_name(backpack->items, name);
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item)
{
  if(backpack== NULL || item == NULL) return;
  backpack->items = remove_container(backpack->items, item);
  backpack->size -= 1;
}

struct backpack* destroy_backpack(struct backpack* backpack)
{
  backpack->capacity = 0;
  backpack->items = NULL;
  backpack->size = 0;
  free(backpack);
  return NULL;
}