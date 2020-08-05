#include <stdio.h>
#include "calc_fun.h"
#include "calc_top.h"
#include "calc_res.h"

int main(void) {

	videoSetMode(MODE_4_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);


    consoleInit(0,0, BgType_Text4bpp, BgSize_T_256x256, 3,0, true, true);
    printf("\x1b[18;1H");

    int bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 5,0);
    decompress(calc_resBitmap, bgGetGfxPtr(bg),  LZ77Vram);
    memcpy(BG_PALETTE, calc_resPal, sizeof(short)*256);

    bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    decompress(calc_topBitmap, BG_GFX_SUB,  LZ77Vram);
    memcpy(BG_PALETTE_SUB, calc_topPal, sizeof(short)*256);

	while(1) {
        CheckTouch();
		swiWaitForVBlank();
	}
	return 0;
}
