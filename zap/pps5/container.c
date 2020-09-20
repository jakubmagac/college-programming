#include <stdlib.h>
#include <string.h>
#include <strings.h>  
#include "container.h"

struct container* create_container(struct container* first, enum container_type type, void* entry)
{
  if(entry == NULL || (first != NULL && first->type != type)) return NULL;

	struct container* newCont = (struct container*) calloc(1, sizeof(struct container));
	struct container* tmp = first;

  if(first != NULL){
    while(tmp->next != NULL){
      tmp = tmp->next;
    }
    tmp->next = newCont;
  }

  newCont->next = NULL;
	newCont->type = type;

  switch (type)
  {
  case ROOM:
    newCont->room = (struct room*) entry; break;
  case ITEM:
    newCont->item = (struct item*) entry; break;
  case COMMAND:
    newCont->command = (struct command*) entry; break;
  case TEXT:
    newCont->text = (char*) entry; break;
  default:
    free(newCont);
    return NULL;
    break;
  }

  return newCont;
}

void* get_from_container_by_name(struct container *first, const char *name){
  if(first == NULL || name == NULL || strlen(name) == 0) return NULL;
	struct container* tmp = first;

	while(tmp != NULL){
    if(first->type == ROOM){
      if(strcasecmp(tmp->room->name, name) == 0) return tmp->room;
    } 

    if(first->type == ITEM){
      if(strcasecmp(tmp->item->name, name) == 0) return tmp->item;
    }

    if(first->type == COMMAND){
      if(strcasecmp(tmp->command->name, name) == 0) return tmp->command;
    }

    if(first->type == TEXT){
      if(strcasecmp(tmp->text, name) == 0) return tmp->text;
    }

		tmp = tmp->next;
	}

  return NULL;
}

struct container* remove_container(struct container *first, void *entry)
{
  if(first == NULL) return NULL;
  if(entry == NULL) return first;
  struct container *tmp = first;

  if(tmp->room == entry || tmp->item == entry || tmp->command == entry || tmp->text == entry){
    first = NULL;
    return first;
  }

  while(tmp->next != NULL){
    if(first->type == ROOM){
      if(tmp->next->room == entry){
        tmp->next = NULL;
        break;
      }
    } 

    if(first->type == ITEM){
      if(tmp->next->item == entry){
        tmp->next = NULL;
        break;
      }
    }

    if(first->type == COMMAND){
      if(tmp->next->command == entry){
        tmp->next = NULL;
        break;
      }
    }

    if(first->type == TEXT){
      if(tmp->next->text == entry){
        tmp->next = NULL;
        break;
      }
    }
    tmp = tmp->next;
  }
  return first;
}

struct container* destroy_containers(struct container* first){
	struct container* temporaryFirst;

    while(first != NULL) {
      temporaryFirst = first;
      first = first->next;

      if (temporaryFirst->type == ROOM) destroy_room(temporaryFirst->room);
      if (temporaryFirst->type == ITEM) destroy_item(temporaryFirst->item);
      if (temporaryFirst->type == COMMAND) destroy_command(temporaryFirst->command);
      if (temporaryFirst->type == TEXT) free(temporaryFirst->text);

      free(temporaryFirst);
      temporaryFirst = NULL;
    }
	
	return NULL;
}