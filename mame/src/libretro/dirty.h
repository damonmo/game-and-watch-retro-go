#define MAX_GFX_WIDTH 1600
#define MAX_GFX_HEIGHT 1600
#define DIRTY_H 256 			/* 160 would be enough, but * 256 is faster */
#define DIRTY_V (MAX_GFX_HEIGHT/16)


//gw: assume use_dirty=0 for now
//typedef char dirtygrid[DIRTY_V * DIRTY_H];
typedef char dirtygrid[1];
#define ISDIRTY(x,y) (dirty_new[(y)/16 * DIRTY_H + (x)/16] || dirty_old[(y)/16 * DIRTY_H + (x)/16])
#define MARKDIRTY(x,y) dirty_new[(y)/16 * DIRTY_H + (x)/16] = 1
