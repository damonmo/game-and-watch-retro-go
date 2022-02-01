#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "rom_manager.h"

#include "gw_lcd.h"
#include "gw_linker.h"

#include "mame.h"

void InitCheat(void)
{
}

void StopCheat(void)
{
}

int cheat_menu(struct osd_bitmap *bitmap, int selection)
{
}

void DoCheat(void)
{
}

void hs_open( const char *name ){}
void hs_init( void ){}
void hs_update( void ){}
void hs_close( void ){}

void app_main_mame(uint8_t load_state)
{
    int ret;
    printf("MAME Load: %s\n", ACTIVE_FILE->name);
    ret = run_game(0);

    while (1) {
        HAL_Delay(1000);
        printf("Hello!\n");
        __NOP();
    }
}
