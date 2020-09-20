#include "world.h"
#include "room.h"
#include "container.h"
#include <stdlib.h>
#include <string.h>

struct container* create_world()
{
    struct room* first = create_room("Zaciatok sveta", "Cesta 10000 krokov zacina prvym padom");
    struct container* new_world = create_container(NULL, ROOM, first);

    struct room* home = create_room("start", "Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.");
    struct room* garden = create_room("zahradka", "Kvetinky sama zlen.");
    struct room* kitchen = create_room("kuchna", "Coska tu fajne vona");
    struct room* bedroom = create_room("izba", "Joj vyvetraj sebe. Smrad tu mas");
    struct room* bridge = create_room("most", "Pekny vyhlad na vodu. Abo na ryby.");
    struct room* road = create_room("cesta", "Nachadzas sa na R1.");
    struct room* cave = create_room("jaskyna", "Jak si sa sem vlatne dostal.");
    struct room* mountain = create_room("hory", "Tatry Vysoke abo Nizke. Neznam uz.");
    struct room* old_building = create_room("stara budova", "Taka stara ze tu citic esci komunizmus.");
    struct room* tower = create_room("veza", "Ci pana skoro jak eifelovka.");
    struct room* bar = create_room("bar", "Som mal znac ze ten vychodnar tu skonci.");
    struct room* strip_club = create_room("strip", "Najdzi sebe frajirku uz to s tebu plano.");
    struct room* tuke = create_room("skola", "Najlepsa skola pod slunkom.");
    struct room* bus_station = create_room("autobus", "Zas si zdzigany az nemozes soferovac.");
    struct room* river = create_room("rieka", "Pome na ryby.");
    struct room* dormitory = create_room("intraky", "Som cul ze neska chodbovica.");
    
    struct item* key = create_item("ZLATY KLUC", "Zlaty kluc pravdepodobne od zlatej zamky. Su na nom viditelne vyryte pismena AB", MOVABLE | USABLE );
    struct item* beer = create_item("Pivko", "To moje palivo", MOVABLE | USABLE );
    struct item* guitar = create_item("Gitara", "Ta sebe zahrame naj nam neni smutno", MOVABLE | USABLE );
    struct item* lamp = create_item("Lampa", "Sa zide do tej jaskyni", MOVABLE | USABLE );
    struct item* movie = create_item("Film", "Idzeme kuknuc Votrelca i tak neni co robic", MOVABLE | USABLE );
    
    add_room_to_world(new_world, first);
    add_room_to_world(new_world, home);
    add_room_to_world(new_world, garden);
    add_room_to_world(new_world, kitchen);
    add_room_to_world(new_world, bedroom);
    add_room_to_world(new_world, bridge);
    add_room_to_world(new_world, road);
    add_room_to_world(new_world, cave);
    add_room_to_world(new_world, mountain);
    add_room_to_world(new_world, old_building);
    add_room_to_world(new_world, tower);
    add_room_to_world(new_world, bar);
    add_room_to_world(new_world, strip_club);
    add_room_to_world(new_world, tuke);
    add_room_to_world(new_world, bus_station);
    add_room_to_world(new_world, river);
    add_room_to_world(new_world, dormitory);

    add_item_to_room(first, key);
    add_item_to_room(first, guitar);
    add_item_to_room(first, lamp);
    add_item_to_room(first, movie);
    add_item_to_room(first, beer);

    return new_world;
}

struct container* add_room_to_world(struct container* world, struct room* room)
{
    if(room == NULL) return NULL;
    if((get_from_container_by_name(world, room->name) != NULL)) return NULL;

    if(world == NULL){
        world = create_container(NULL, ROOM, room);
        return world;
    }
    return create_container(world, ROOM, room); 
}


struct room* get_room(struct container* world, char* name)
{
    if(name == NULL || world == NULL || strlen(name) == 0) return NULL;
	return get_from_container_by_name(world, name);
}