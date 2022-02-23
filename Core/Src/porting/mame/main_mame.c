#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "rom_manager.h"

#include "gw_lcd.h"
#include "gw_linker.h"
#include "common.h"
#include "appid.h"

#include "mame.h"

void InitCheat(void){}
void StopCheat(void){}
int cheat_menu(struct osd_bitmap *bitmap, int selection){}
void DoCheat(void){}

void hs_open( const char *name ){}
void hs_init( void ){}
void hs_update( void ){}
void hs_close( void ){}

void profiler_start(void){}
void profiler_stop(void){}
void profiler_mark(int type){}
void profiler_show(struct osd_bitmap *bitmap){}

/*
struct GfxElement *builduifont(void){}
void pick_uifont_colors(void);void displaytext(struct osd_bitmap *bitmap,const struct DisplayText *dt,int erase,int update_screen){}
void ui_text(struct osd_bitmap *bitmap,const char *buf,int x,int y){}
void ui_drawbox(struct osd_bitmap *bitmap,int leftx,int topy,int width,int height){}
void ui_displaymessagewindow(struct osd_bitmap *bitmap,const char *text){}
void ui_displaymenu(struct osd_bitmap *bitmap,const char **items,const char **subitems,char *flag,int selected,int arrowize_subitem){}
int showcopyright(struct osd_bitmap *bitmap){}
int showgamewarnings(struct osd_bitmap *bitmap){}
void set_ui_visarea (int xmin, int ymin, int xmax, int ymax){}
void init_user_interface(void){}
int handle_user_interface(struct osd_bitmap *bitmap){}
int onscrd_active(void){}
int setup_active(void){}
void CLIB_DECL usrintf_showmessage(const char *text,...){}
void CLIB_DECL usrintf_showmessage_secs(int seconds, const char *text,...){}

int uistring_init (void *language_file){}
void uistring_shutdown (void){}
*/

void app_main_mame(uint8_t load_state)
{
    printf("MAME Load: %s\n", ACTIVE_FILE->name);
    
    odroid_system_init(APPID_MAME, 48000);
    // Init Sound
    memset(audiobuffer_dma, 0, sizeof(audiobuffer_dma));
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *)audiobuffer_dma, (2 * 48000)/60 );
    printf("Sound initialized\n");


    run_game(0);
}
