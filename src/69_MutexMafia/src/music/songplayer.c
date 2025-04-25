#include "songplayer.h"
#include "../pit/pit.h"
#include "libc/stdio.h"
#include "../memory/malloc.h"
#include "../io/printf.h"
//#include <libc/stdbool.h>
// I/O ports
#define PC_SPEAKER_PORT    0x61
#define PIT_CONTROL_PORT   0x43
#define PIT_CHANNEL2_PORT  0x42

void enable_speaker() {
    uint8_t tmp = inPortB(PC_SPEAKER_PORT);
    outPortB(PC_SPEAKER_PORT, tmp | 0x03);
}

void disable_speaker() {
    uint8_t tmp = inPortB(PC_SPEAKER_PORT);
    outPortB(PC_SPEAKER_PORT, tmp & ~0x03);
}

void play_sound(uint32_t frequency) {
    if (frequency == 0) return;

    uint32_t divisor = 1193180 / frequency;

    outPortB(PIT_CONTROL_PORT, 0xB6);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outPortB(PIT_CHANNEL2_PORT, low);
    outPortB(PIT_CHANNEL2_PORT, high);

    enable_speaker();
}

void stop_sound() {
    uint8_t tmp = inPortB(PC_SPEAKER_PORT);
    outPortB(PC_SPEAKER_PORT, tmp & 0xFC);
}

void play_song(Song* song) {
    enable_speaker();

    for (size_t i = 0; i < song->note_count; i++) {
        Note note = song->notes[i];
        mafiaPrint("Playing note: freq=%d Hz, duration=%d ms\n", note.frequency, note.duration_ms);

        play_sound(note.frequency);
        sleep_interrupt(note.duration_ms);
        stop_sound();

        sleep_interrupt(50); // optional gap
    }

    disable_speaker();
}

SongPlayer* create_song_player() {
    SongPlayer* player = (SongPlayer*)malloc(sizeof(SongPlayer));
    player->play_song = play_song;
    return player;
}
