#include "songplayer.h"

// Define a cool melody
Note music_1[] = {
    {440, 200}, {0, 50}, {440, 200}, {0, 50},
    {523, 300}, {0, 50}, {659, 300}, {0, 50},
    {440, 400}, {0, 200}, {440, 200}, {392, 200},
    {349, 200}, {330, 400}, {0, 300}
};

size_t music_1_length = sizeof(music_1) / sizeof(Note);
