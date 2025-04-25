#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "libc/stdint.h"
#include "libc/stddef.h"

// ===== Song and Note Definitions =====

typedef struct {
    uint32_t frequency;    // Frequency in Hz
    uint32_t duration_ms;  // Duration in milliseconds
} Note;

typedef struct {
    Note* notes;
    size_t note_count;
} Song;

// ===== SongPlayer Interface =====

typedef struct {
    void (*play_song)(Song* song);
} SongPlayer;

// ===== API Functions =====

SongPlayer* create_song_player();
void play_song(Song* song); // Internal

// Low-level speaker control
void enable_speaker();
void disable_speaker();
void play_sound(uint32_t frequency);
void stop_sound();

#endif // SONGPLAYER_H
