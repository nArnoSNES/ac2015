/*---------------------------------------------------------------------------------

	AC2015 - menu()
		-- n_Arno

---------------------------------------------------------------------------------*/
#include <snes.h>
#include "soundbank.h"

extern char pattilekawaii, pattilekawaii_end;
extern char maptilekawaii, maptilekawaii_end;
extern char paltilekawaii, paltilekawaii_end;

extern char gfxicon, gfxicon_end;
extern char palicon, palicon_end;

extern char snesfont;

void consoleSetShadowCol(u8 paletteNumber, u16 colorShad) {
	// For 3 color Font
	REG_CGADD = 0x02+(paletteNumber<<4); *CGRAM_PALETTE = colorShad & 0xFF; *CGRAM_PALETTE = colorShad>>8;
}

//---------------------------------------------------------------------------------
int menu(void) {
	short scrX=0, scrY=0;
	unsigned short pad0;
	char sz[16];

	// Load music
	spcLoad(MOD_POLLEN8);

	// Initialize text console with our font
	consoleInitText(0, 1, &snesfont);
	consoleSetTextCol(RGB15(0,0,0),RGB15(31,31,31));
	consoleSetShadowCol(1,RGB15(15,15,15));

	// Load BG
    	bgInitTileSet(1, &pattilekawaii, &paltilekawaii, 0, (&pattilekawaii_end - &pattilekawaii), 16*2, BG_16COLORS, 0x4000);
	bgInitMapSet(1, &maptilekawaii, (&maptilekawaii_end - &maptilekawaii),SC_32x32, 0x2000);
	
	// Now Put in 16 color mode and out text on top of screen
	setMode(BG_MODE1,0);  bgSetDisable(2);
	
	// Write new text
	consoleSetTextCol(RGB15(20,31,20),RGB15(0,0,0));
	consoleSetShadowCol(1,RGB15(5,15,5));
	consoleDrawText(6,8, "{__________________}");
	consoleDrawText(6,9, "|                  |");
	consoleDrawText(6,10,"|   Start Game (P) |");
	consoleDrawText(6,11,"|                  |");
	consoleDrawText(6,12,"|   Start Game (F) |");
	consoleDrawText(6,13,"|                  |");
	consoleDrawText(6,14,"|     Tutorial     |");
	consoleDrawText(6,15,"|                  |");
	consoleDrawText(6,16,"^__________________~");
	//                   "6789012345678901267"  
	
	// Init sprite
	oamInitGfxSet(&gfxicon, (&gfxicon_end-&gfxicon), &palicon, (&palicon_end-&palicon), 0, 0x6000, OBJ_SIZE8);

	int posmenu = 0;
	
	// Define sprites parameters
	oamSet(0, 8*8-1, (10+posmenu)*8-1, 3, 0, 0, 0, 0); 
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
	oamSetVisible(0,OBJ_SHOW);

	// First VBL
	WaitForVBlank();
	
	// Play file from the beginning
	spcPlay(0);
	
	// Wait for start
	pad0 = padsCurrent(0);
	short wait = 0;
	while(pad0 != KEY_START) {
		// Scroll BG		
	    	scrX--;
	    	//scrY++; 
		bgSetScroll(1, scrX,scrY);
		
		// Refresh pad values in VBL and Get current #0 pad
		pad0 = padsCurrent(0);

		if (wait > 0) {
		    wait--;
		} 
		else {
			if (pad0) {
				// Update menu choice with current pad
				if(pad0 & KEY_UP) {
					if (posmenu != 0) { posmenu-=2; wait = 5; }
				}
				if(pad0 & KEY_DOWN) {
					if (posmenu != 4) { posmenu+=2; wait = 5; }
				}
			}
		}
		
		// Update Sprite position based on menu choice.
		oamSet(0, 8*8-1, (10+posmenu)*8-1, 3, 0, 0, 0, 0); 

		// tell SPC to process sound and wait vBlank
		spcProcess();
		WaitForVBlank();
	}
	
	// Fade Out and stop music
	setFadeEffect(FADE_OUT);
	spcStop();
	spcProcess();
	WaitForVBlank();

	// Clean Everything (still dirtya
    	oamSetEx(0, OBJ_SMALL, OBJ_HIDE);
	bgSetDisable(1);

	return posmenu;
}
