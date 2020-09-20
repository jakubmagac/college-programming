#include "track.h"
#include "playlist.h"
#include <stdio.h>

int main()
{
    struct track* track = create_track("Za rana za rosy", 240);
    struct playlist* playlist = create_playlist("Soundtracks");
    append_track_to_playlist(playlist, track);
    append_track_to_playlist(playlist, create_track("Outro", 247));
    append_track_to_playlist(playlist, create_track("Midnight City", 242));
    play(playlist);
    next(playlist);
    prev(playlist);
    change_mode(playlist, DONT_REPEAT);
    free_playlist(playlist);
    return 0;
}