#include "track.h"
#include <stdlib.h>
#include <string.h>

struct track* create_track(const char* title, int duration)
{
    if(strlen(title) < 1 || strlen(title) > 100 || duration < 1) return NULL;

    struct track* newtrack = (struct track*) calloc(1, sizeof(struct track));

    char *new_title = calloc(1, strlen(title)+1);
    strcpy(new_title, title);

    newtrack->title = new_title;
    newtrack->duration = duration;

    return newtrack;
}

void free_track(struct track* track)
{
    free(track->title);
    track->duration = 0;
    free(track);
}
