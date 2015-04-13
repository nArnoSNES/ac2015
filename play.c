/*---------------------------------------------------------------------------------

	AC2015 - play()
		-- n_Arno

---------------------------------------------------------------------------------*/
#include <snes.h>

extern char gfxpsrite, gfxpsrite_end;
extern char palsprite, palsprite_end;
extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;
extern char mapcol, mapcol_end;

extern char gfxpsrite2, gfxpsrite2_end;
extern char palsprite2, palsprite2_end;
extern char patterns2, patterns2_end;
extern char palette2, palette2_end;
extern char map2, map2_end;
extern char mapcol2, mapcol2_end;

extern char snesfont;

u16 getCollisionTile(u16 x, u16 y) {
    	// Check all four corner of the sprite (16px) to avoid clipping (all must be Zero for ok)
	u16 *ptrMapUL = (u16 *) &mapcol + (y>>3)*32 + (x>>3);
    	u16 *ptrMapUR = (u16 *) &mapcol + (y>>3)*32 + ((x+16)>>3);
    	u16 *ptrMapDL = (u16 *) &mapcol + ((y+16)>>3)*32 + (x>>3);
	u16 *ptrMapDR = (u16 *) &mapcol + ((y+16)>>3)*32 + ((x+16)>>3);
	return (*ptrMapUL+*ptrMapUR+*ptrMapDL+*ptrMapDR);
}

u16 getCollisionTile2(u16 x, u16 y) {
    	// Check all four corner of the sprite (16px) to avoid clipping (all must be Zero for ok)
	u16 *ptrMapUL = (u16 *) &mapcol2 + (y>>3)*32 + (x>>3);
    	u16 *ptrMapUR = (u16 *) &mapcol2 + (y>>3)*32 + ((x+16)>>3);
    	u16 *ptrMapDL = (u16 *) &mapcol2 + ((y+16)>>3)*32 + (x>>3);
	u16 *ptrMapDR = (u16 *) &mapcol2 + ((y+16)>>3)*32 + ((x+16)>>3);
	return (*ptrMapUL+*ptrMapUR+*ptrMapDL+*ptrMapDR);
}

#define ANIM_SPEED 3 // 3 VBL before update
#define FRAMES_PER_ANIMATION 3 // 3 sprites per direction

//---------------------------------------------------------------------
// The Player sprite
//---------------------------------------------------------------------
typedef struct
{
    	short x, y;
	int gfx_frame;
	int state;
	int anim_frame;
	int flipx;
} Player;

//---------------------------------------------------------------------
// The state of the sprite (which way it is walking)
//---------------------------------------------------------------------
enum SpriteState {W_DOWN = 0, W_UP = 1, W_RIGHT = 2,  W_LEFT = 2};

//---------------------------------------------------------------------
// Screen dimentions
//---------------------------------------------------------------------
enum {SCREEN_TOP = 0, SCREEN_BOTTOM = 224, SCREEN_LEFT = 1, SCREEN_RIGHT = 256};

char sprTiles[9]={0,2,4, 6,8,10, 12,14,32};  // Remember that sprites are interleave with 128 pix width,

//---------------------------------------------------------------------------------
Player play1(Player playerCur) {
    	Player player = playerCur;
	unsigned short pad0,i;

	bgInitTileSet(0, &patterns, &palette, 0, (&patterns_end - &patterns), (&palette_end - &palette), BG_16COLORS, 0x4000);

	// Copy Map to VRAM
    	bgInitMapSet(0, &map, (&map_end - &map),SC_32x32, 0x3000);

	// Now Put in 16 color mode and disable unused BG
    	setMode(BG_MODE1,0); bgSetDisable(1);  bgSetDisable(2);
	
	// Init Sprites gfx and palette with default size of 16x16
	oamInitGfxSet(&gfxpsrite, (&gfxpsrite_end-&gfxpsrite), &palsprite, (&palsprite_end-&palsprite), 0, 0x6000, OBJ_SIZE16);

	// Define sprites parameters
	oamSet(0,  player.x, player.y, 0, 0, 0, 0, 0); 
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
	oamSetVisible(0,OBJ_SHOW);
	
	// Wait VBL 'and update sprites too ;-) )
	WaitForVBlank();

	// init timer for anim speed
	int stimer = 0;

	// Wait for Start
	pad0 = padsCurrent(0);
	while(pad0 != KEY_R) {
		// Refresh pad values in VBL and Get current #0 pad
		pad0 = padsCurrent(0);    
	    
		if (pad0) {
		    	// Update sprite with current pad
			if(pad0 & KEY_UP) {
			    	if(player.y >= SCREEN_TOP & getCollisionTile(player.x, player.y-2) == 0) player.y--;
				player.state = W_UP;
				player.flipx = 0;
			}
			if(pad0 & KEY_LEFT) {
			    	if(player.x >= SCREEN_LEFT & getCollisionTile(player.x-2, player.y) == 0) player.x--;
				player.state = W_LEFT;
				player.flipx = 1;
			}
			if(pad0 & KEY_RIGHT) {
			    	if((player.x+16) <= SCREEN_RIGHT & getCollisionTile(player.x+2, player.y) == 0) player.x++;
				player.state = W_LEFT;
				player.flipx = 0;
			}
			if(pad0 & KEY_DOWN) {
			    	if((player.y+16) <= SCREEN_BOTTOM & getCollisionTile(player.x, player.y+2) == 0) player.y++;
				player.state = W_DOWN;
				player.flipx = 0;
			}
		    	stimer++;
		    	if (stimer>ANIM_SPEED) {
			stimer = 0;
			player.anim_frame++;
			if(player.anim_frame >= FRAMES_PER_ANIMATION) player.anim_frame = 0;
			}
		}
		
		// Now, get current sprite in current animation
		player.gfx_frame = sprTiles[player.anim_frame + player.state*FRAMES_PER_ANIMATION ];
		oamSet(0,  player.x, player.y, 3, player.flipx, 0, player.gfx_frame, 0);
		
		// Wait VBL 'and update sprites too ;-) )
		WaitForVBlank();
	}
	return player;
}

Player play2(Player playerCur) {
    	Player player = playerCur;
	unsigned short pad0,i;

	bgInitTileSet(0, &patterns2, &palette2, 0, (&patterns2_end - &patterns2), (&palette2_end - &palette2), BG_16COLORS, 0x4000);

	// Copy Map to VRAM
    	bgInitMapSet(0, &map2, (&map2_end - &map2),SC_32x32, 0x3000);

	// Now Put in 16 color mode and disable unused BG
    	setMode(BG_MODE1,0); bgSetDisable(1);  bgSetDisable(2);
	
	// Init Sprites gfx and palette with default size of 16x16
	oamInitGfxSet(&gfxpsrite2, (&gfxpsrite2_end-&gfxpsrite2), &palsprite2, (&palsprite2_end-&palsprite2), 0, 0x6000, OBJ_SIZE16);

	// Define sprites parameters
	oamSet(0,  player.x, player.y, 0, 0, 0, 0, 0); 
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
	oamSetVisible(0,OBJ_SHOW);
	
	// Wait VBL 'and update sprites too ;-) )
	WaitForVBlank();

	// init timer for anim speed
	int stimer = 0;

	// Wait for Start
	pad0 = padsCurrent(0);
	while(pad0 != KEY_L) {
		// Refresh pad values in VBL and Get current #0 pad
		pad0 = padsCurrent(0);    
	    
		if (pad0) {
		    	// Update sprite with current pad
			if(pad0 & KEY_UP) {
			    	if(player.y >= SCREEN_TOP & getCollisionTile2(player.x, player.y-2) == 0) player.y--;
				player.state = W_UP;
				player.flipx = 0;
			}
			if(pad0 & KEY_LEFT) {
			    	if(player.x >= SCREEN_LEFT & getCollisionTile2(player.x-2, player.y) == 0) player.x--;
				player.state = W_LEFT;
				player.flipx = 1;
			}
			if(pad0 & KEY_RIGHT) {
			    	if((player.x+16) <= SCREEN_RIGHT & getCollisionTile2(player.x+2, player.y) == 0) player.x++;
				player.state = W_LEFT;
				player.flipx = 0;
			}
			if(pad0 & KEY_DOWN) {
			    	if((player.y+16) <= SCREEN_BOTTOM & getCollisionTile2(player.x, player.y+2) == 0) player.y++;
				player.state = W_DOWN;
				player.flipx = 0;
			}
		    	stimer++;
		    	if (stimer>ANIM_SPEED) {
			stimer = 0;
			player.anim_frame++;
			if(player.anim_frame >= FRAMES_PER_ANIMATION) player.anim_frame = 0;
			}
		}
		
		// Now, get current sprite in current animation
		player.gfx_frame = sprTiles[player.anim_frame + player.state*FRAMES_PER_ANIMATION ];
		oamSet(0,  player.x, player.y, 3, player.flipx, 0, player.gfx_frame, 0);
		
		// Wait VBL 'and update sprites too ;-) )
		WaitForVBlank();
	}
	return player;
}

void play(int choix) {
    int sw = choix;
    Player player1 = {30,30};
    Player player2 = {30,30};
    while (1) {
    	if (sw == 0) {
	    Player result = play1(player1);
	    player1 = result;
	    sw = 2;
	} else {
	    Player result = play2(player2);
	    player2 = result;
	    sw = 0;
    	}
	WaitForVBlank();
    }
}