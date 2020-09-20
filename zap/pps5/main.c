#include "container.h"
#include "room.h"
#include "world.h"
#include "backpack.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  struct container* world = create_world();
  get_room(world, "start");
  struct container* container = create_container(world, ROOM, NULL);
  get_from_container_by_name(container, "name");
	create_game();
  struct room* dormitory = create_room("intraky", "Som cul ze neska chodbovica.");
  show_room(dormitory);
  set_exits_from_room(dormitory, NULL, NULL, NULL, NULL);
  add_room_to_world(world, dormitory);

  struct command* help = create_command("POMOC", "Zobrazi zoznam vsetkych prikazov", "(POMOC)", 1);
  destroy_command(help);

  struct item* key = create_item("ZLATY KLUC", "Zlaty kluc pravdepodobne od zlatej zamky. Su na nom viditelne vyryte pismena AB", MOVABLE | USABLE );
  add_item_to_room(dormitory, key);
  get_item_from_room(dormitory, "zlaty kluc");
  delete_item_from_room(dormitory, key);
  
  struct backpack* backpack = create_backpack(5);
  add_item_to_backpack(backpack, key); 
  get_item_from_backpack(backpack, "zlaty kluc");
  delete_item_from_backpack(backpack, key);
  key = destroy_item(key);
  backpack = destroy_backpack(backpack);
  // destroy_world(world);
  destroy_room(dormitory);

 
  return 0;
}