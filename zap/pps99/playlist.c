#include "playlist.h"
#include "track.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct playlist* create_playlist(char* name)
{
    if(strlen(name) < 1 || strlen(name) > 100) return NULL;

    struct playlist* newPlaylist = (struct playlist*) calloc(1, sizeof(struct playlist));

    char *new_name = calloc(1, strlen(name)+1);
    strcpy(new_name, name);

    newPlaylist->name = new_name;
    newPlaylist->duration = 0;
    newPlaylist->size = 0;
    newPlaylist->mode = REPEAT;
    newPlaylist->current = NULL;
    newPlaylist->first = NULL;
    
    return newPlaylist;
}

void append_track_to_playlist(struct playlist *playlist, struct track *track)
{
    if(playlist == NULL || track == NULL) return;

    struct entry* newEntry = (struct entry*) calloc(1, sizeof(struct entry));
    newEntry->track = track;
    newEntry->next = NULL;
    newEntry->prev = NULL;

    if(playlist->current == NULL){
        playlist->current = newEntry;
        return;
    }

    struct entry* tmp = playlist->current;

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    newEntry->prev = tmp;
    tmp->next = newEntry;
}

struct track* play(struct playlist* playlist)
{
    if(playlist == NULL || playlist->current == NULL) return NULL;

    struct track* result = playlist->current->track;
    printf("Playing track: %s from playlist %s\n", result->title, playlist->name);

    if(playlist->current->next != NULL){
        playlist->current = playlist->current->next;
    }else{
        if(playlist->mode == REPEAT) playlist->current = playlist->first;
    }

    return result;
}

struct track* next(struct playlist* playlist)
{
    if(playlist == NULL || playlist->current == NULL) return NULL;

    if(playlist->current->next != NULL){
        playlist->current = playlist->current->next;
    }

    return playlist->current->track;
}

struct track* prev(struct playlist* playlist)
{
    if(playlist == NULL || playlist->current == NULL) return NULL;

    if(playlist->current->prev != NULL){
        playlist->current = playlist->current->prev;
    }

    return playlist->current->track;
}

void change_mode(struct playlist* playlist, enum play_mode mode)
{
    if(playlist == NULL) return;
    if(mode == ONE_SONG || mode == REPEAT || mode == DONT_REPEAT) playlist->mode = mode;
}

void free_playlist(struct playlist* playlist)
{
    struct entry* tmp = playlist->current;

    while(tmp->prev != NULL){
        tmp = tmp->prev;
    }

    while(tmp->next != NULL){
        free_track(tmp->track);
        tmp = tmp->next;
        tmp->prev = NULL;   
    }

    free(playlist);
}