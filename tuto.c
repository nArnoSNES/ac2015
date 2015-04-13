/*---------------------------------------------------------------------------------

	AC2015 - tuto()
		-- n_Arno

---------------------------------------------------------------------------------*/
#include <snes.h>

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
void tuto(void) {
	unsigned short pad0;
	char sz[16];

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
	consoleDrawText(2,2, "{__________________________}");
	consoleDrawText(2,3, "|                          |");
	consoleDrawText(2,4, "|  Time Fighters - AC2015  |");
	consoleDrawText(2,5, "|                          |");
	consoleDrawText(2,6, "|  Help the two strangers  |");
	consoleDrawText(2,7, "|   linked through time    |");
	consoleDrawText(2,8, "| fight against the chaos. |");
	consoleDrawText(2,9, "|                          |");
	consoleDrawText(2,10,"|  Kill foes in your time  |");
	consoleDrawText(2,11,"|  and send their weapons  |");
	consoleDrawText(2,12,"|   to your partner.       |");
	consoleDrawText(2,13,"|                          |");
	consoleDrawText(2,14,"| Switch of player to help |");
	consoleDrawText(2,15,"|     them when needed.    |");
	consoleDrawText(2,16,"|                          |");
	consoleDrawText(2,17,"|  A: Interact with item   |");
    	consoleDrawText(2,18,"|  L: Swith to past        |");
	consoleDrawText(2,19,"|  R: Swith to future      |");
	consoleDrawText(2,20,"|  B: Strike enemy         |");
	consoleDrawText(2,21,"|                          |");
    	consoleDrawText(2,22,"|   2015/nArno - AC/RGC    |");
	consoleDrawText(2,23,"|  Built on a Raspberry Pi |");
	consoleDrawText(2,24,"|  PVSNESLIB - OpenGameArt |");
	consoleDrawText(2,25,"^__________________________~");

	// First VBL
	WaitForVBlank();
	
	
	// Wait for start
	pad0 = padsCurrent(0);
	while(pad0 != KEY_START) {
	    	pad0 = padsCurrent(0);
		WaitForVBlank();
	}
}
