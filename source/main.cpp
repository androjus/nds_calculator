#include <nds.h>
#include <stdio.h>
#include <string>
#include "calc_top.h"
#include "calc_res.h"
using namespace std;
PrintConsole topScreen;
string action;
bool isPressed = false;
string button_list[4][4]{
{
    "7", "8", "9", "*"
},
{
    "4", "5", "6", "/"
},
{
    "1", "2", "3", "-"
},
{
    "0", "DEL", "=", "+"
}
};

int button_mapping[4][4][4]={
    0,0,62,46,    65,0,127,46,    129,0,191,46,    192,0,255,46,
    0,49,62,94,   65,49,127,94,   129,49,191,94,   192,49,255,94,
    0,97,62,142,  65,97,127,142,  129,97,191,142,  192,97,255,142,
    0,145,62,191, 65,145,127,191, 129,145,191,191, 192,145,255,191
};

void Clear(){
    consoleClear();
    printf("\x1b[18;1H");
    action="";
}
void onClicks(string chars){
    if(chars == "DEL"){
        Clear();
        return;
    }
    else{
        if(chars == "="){
            printf("%s", chars.c_str());
        }
        else{
            printf("%s", chars.c_str());
        }
    }
}

void CheckTouch()
{
	touchPosition touch;
	touchRead (&touch);
	if(touch.py == 0 && touch.px == 0){
        isPressed = false;
        return;
	}
	for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            if(touch.px>button_mapping[i][j][0] && touch.px<button_mapping[i][j][2] && touch.py>button_mapping[i][j][1] && touch.py<button_mapping[i][j][3]){
                if(isPressed == false){
                    onClicks(button_list[i][j]);
                }
                isPressed = true;
                return;
        }
	}}
	return;
}
int main(void) {

	videoSetMode(MODE_4_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);


    consoleInit(0,0, BgType_Text4bpp, BgSize_T_256x256, 3,0, true, true);
    printf("\x1b[18;1H");

    int bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 5,0);
    decompress(calc_resBitmap, bgGetGfxPtr(bg),  LZ77Vram);
    dmaCopy(calc_resPal, BG_PALETTE, sizeof(short)*256);

    bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    decompress(calc_topBitmap, BG_GFX_SUB,  LZ77Vram);
    memcpy(BG_PALETTE_SUB, calc_topPal, sizeof(short)*256);

	while(1) {
        CheckTouch();
		swiWaitForVBlank();
	}
	return 0;
}
