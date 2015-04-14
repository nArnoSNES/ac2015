/*---------------------------------------------------------------------------------

	AC2015 - main()
		-- n_Arno

---------------------------------------------------------------------------------*/
#include <snes.h>
#include "soundbank.h"
#include "main.h"
extern char __SOUNDBANK__;

//---------------------------------------------------------------------------------
int main(void) {
    	// Initialize sound engine (take some time)
	spcBoot();

    	// Initialize SNES 
	consoleInit();

	// Set give soundbank
	spcSetBank(&__SOUNDBANK__);
	
	// allocate around 10K of sound ram (39 256-byte blocks)
	spcAllocateSoundRegion(39);

	title();
	int choix = -1;
	while (choix != 0 & choix != 2) {
		choix = menu();
		if (choix == 4) {
	    		tuto();
		}
	}
	play(choix);
	
	while(1) {
		WaitForVBlank();
	}
	return 0;
}
