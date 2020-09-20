#include <stdlib.h>
#include "backpack.h"
#include "game.h"
#include "world.h"
#include "room.h"
#include "parser.h"

struct game* create_game()
{
  struct game* game = calloc(1, sizeof(struct game));
  game->state = PLAYING;
  game->parser = create_parser();
  game->world = create_world();
  game->current_room = create_room("zaklad", "Tu zacnes.");
  game->backpack = create_backpack(10);
  return game;
}

// struct game* destroy_game(struct game* game)
// {
//   game->state = PLAYING;
//   game->parser = destroy_parser();
//   game->world = destroy_world();
//   game->current_room = destroy_room("zaklad", "Tu zacnes.");
//   game->backpack = destroy_backpack(10);
//   free(game);
//   return NULL;
// }
