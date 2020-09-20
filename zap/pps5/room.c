#include "room.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

struct room* create_room(char *name, char *description)
{
  if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;
	struct room* newRoom = (struct room*) calloc(1, sizeof(struct room));

  char *new_name = calloc(1, strlen(name)+1);
  char *new_desc = calloc(1, strlen(description)+1);

  strcpy(new_name, name);
  strcpy(new_desc, description);

  newRoom->name = new_name;
  newRoom->description = new_desc;
  newRoom->north = NULL;
  newRoom->south = NULL;
  newRoom->east = NULL;
  newRoom->west = NULL;
  return newRoom;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west)
{
  if(room == NULL) return;
  room->north = north;
  room->south = south;
  room->east = east;
  room->west = west; 
}

void show_room(const struct room* room)
{
  struct container *tmp = room->items;

  printf("Nachadzas sa v %s\n", room->name);
  printf("%s\n", room->description);

  printf("Mozne vychody z miestnosti: \n");
  if(room->north != NULL) printf("%s\n", room->north->name);
  if(room->south != NULL) printf("%s\n", room->south->name);
  if(room->east != NULL) printf("%s\n", room->east->name);
  if(room->west != NULL) printf("%s\n", room->west->name);

  printf("V miestnosti sa nachadza: \n");
  while(tmp != NULL){
    printf("%s\n", tmp->item->name);
    tmp = tmp->next;
  }
	
}

void add_item_to_room(struct room* room, struct item* item)
{
  if(room == NULL || item == NULL) return;

  if(room->items == NULL) room->items = create_container(room->items, ITEM, item); 
  else create_container(room->items, ITEM, item);
}

struct item* get_item_from_room(const struct room* room, const char* name)
{
  if(room == NULL || name == NULL || strlen(name) == 0) return NULL;
  return get_from_container_by_name(room->items, name);
}

void delete_item_from_room(struct room* room, struct item* item)
{
  if(room == NULL || item == NULL) return;
  room->items = remove_container(room->items, item);
}

struct room* destroy_room(struct room* room){

    if(room == NULL) return NULL;

    free(room->name);
    free(room->description);
    destroy_containers(room->items);
    free(room);
    return NULL;
}