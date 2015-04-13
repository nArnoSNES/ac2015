/*---------------------------------------------------------------------------------

	AC2015 - title()
		-- n_Arno

---------------------------------------------------------------------------------*/
#include <snes.h>

extern char m0, m0_end, p0, p0_end, t0, t0_end;
extern char m1, m1_end, p1, p1_end, t1, t1_end;
extern char m2, m2_end, p2, p2_end, t2, t2_end;
extern char m3, m3_end, p3, p3_end, t3, t3_end;

extern char gfxaclogo, gfxaclogo_end;
extern char palaclogo, palaclogo_end;

extern char soundbrr,soundbrrend;
brrsamples hihisound;

//---------------------------------------------------------------------------------
void title(void) {
    	unsigned char sxbg1=0,sxbg2=0,sxbg3=0, flip=0;
    	unsigned short pad0;

	// Load effect
	spcSetSoundEntry(15, 8, 4, &soundbrrend-&soundbrr, &soundbrr, &hihisound);

    	// Init all BG 
    	bgInitTileSet(0, &t0, &p0, 0, (&t0_end - &t0), 8, BG_4COLORS0, 0x2000);
	bgInitTileSet(1, &t1, &p1, 0, (&t1_end - &t1), 8, BG_4COLORS0, 0x3000);
	bgInitTileSet(2, &t2, &p2, 0, (&t2_end - &t2), 8, BG_4COLORS0, 0x4000);
	bgInitTileSet(3, &t3, &p3, 0, (&t3_end - &t3), 16, BG_4COLORS0, 0x5000);

	// Copy Map to VRAM
	bgInitMapSet(0, &m0, (&m0_end - &m0),SC_32x32, 0x0000);
	bgInitMapSet(1, &m1, (&m1_end - &m1),SC_32x32, 0x0400);
	bgInitMapSet(2, &m2, (&m2_end - &m2),SC_32x32, 0x0800);
	bgInitMapSet(3, &m3, (&m3_end - &m3),SC_32x32, 0x0C00);

	// Init Sprites gfx and palette with default size of 32x32
	oamInitGfxSet(&gfxaclogo, (&gfxaclogo_end-&gfxaclogo), &palaclogo, (&palaclogo_end-&palaclogo), 0, 0x6000, OBJ_SIZE32);

	// Define sprites parmaters
	oamSet(0,  214, 182, 3, 0, 0, 0, 0); // Put sprite in 100,100, with maximum priority 3 from tile entry 0, palette 0
	oamSetEx(0, OBJ_SMALL, OBJ_SHOW);

	// Now Put in 16 color mode and disable other BGs except 1st one
	setMode(BG_MODE0,0);  

	// Wait for Start
	pad0 = padsCurrent(0);
	while(pad0 != KEY_START) {
	    	pad0 = padsCurrent(0);
		// Change scrolling only each 3 frames
		flip++;
		if (flip == 3) {
			flip=0;
			sxbg3++;
			sxbg2+=2;
			sxbg1+=3;
			bgSetScroll(1,sxbg1,0);
			bgSetScroll(2,sxbg2,0);
			bgSetScroll(3,sxbg3,0);
		}
		WaitForVBlank();
	}

	// Play Giggle and wait a few VBlank for to finish SPC processing
	spcPlaySound(0);
	short wait = 0;
	while(wait<40) {
		wait++;
		spcProcess();
		WaitForVBlank();
	}
	
	// Fade Out
	setFadeEffect(FADE_OUT);
	WaitForVBlank();
}