#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "gdt/gdt.h"
#include "io/printf.h"
#include "idt/idt.h"
#include "io/keyboard.h"
#include "memory/malloc.h"
#include "memory/paging.h"
#include "pit/pit.h"
#include "music/songplayer.h"




struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();
extern uint32_t end;


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    initGdt();
    initIdt();
    init_kernel_memory(&end);
    init_paging();
   
    

    initKeyboard();
    mafiaPrint("Wadiyatalkinabeet\n");
    mafiaPrint("\n");

    
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    print_memory_layout();

    mafiaPrint("Trying to play sound...");
    while (1)
    {
        play_sound(440);         // A4 (audible tone)
        sleep_interrupt(1000);   // 1 second
        stop_sound();
    }
    
    

    return kernel_main(); 

}