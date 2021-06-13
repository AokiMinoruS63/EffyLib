/* 
 * File:   Main
 * Author: nokotan
 *
 * Created on 2020/01/30, 0:57
 * 
 * DxLibToHTML5雛形ファイル
 */

#include "DxLib.h"
#include "Components/Touch/TouchMgr.h"
#ifdef EMSCRIPTEN
#  include <emscripten.h>
#endif

static bool shouldExit = false;
TouchMgr *touchMgr;
void mainLoop() {
	if (ProcessMessage() == -1) {
		shouldExit = true;
	}

	ClearDrawScreen();

	{
		touchMgr->calc();
		//int MouseX, MouseY;
		touch_t touch = touchMgr->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

		DrawCircle(touch.x, touch.y, 64, CircleColor);
	}

	{
		int StringColor = CheckHitKey(KEY_INPUT_SPACE) ? GetColor(0, 255, 0) : GetColor(255, 255, 255);
		DrawString(3, 3, "Hello DxLib on HTML5!", StringColor);
		DrawLine(1513,0,1513,1136,GetColor(255,0,0),2);
		/*
		std::string c = "鳥";//"鼻";// 鳥 40165(9CE5)//u8"\u9F3B";// 鼻 40763
		char c2[] = u8"\u9CE5";//u8"\u9F3B";
		int byte = std::strlen("鳥");//std::strlen("鼻");//std::strlen("鼻");// 3byte
		//std::string str = "a";
		LONG num = (LONG)(c.c_str());// 
		//鼻=10891024 鳥=10891008
		DrawFormatString(3,30,GetColor(255,255,255),"char c1: %s c2: %s num %ld byte %d", c.c_str(), c2, utf8_to_int(c.c_str()), byte);
		// 区 点 JIS  SJIS EUC  UTF-8  UTF-16 字
		// 36 27 443B 92B9 C4BB E9B3A5 9CE5   鳥
		// 41 01 4921 9540 C9A1 E9BCBB 9F3B   鼻
		hoge->intputNum(3);
		printfDx("\n\ntestNum %d", hoge->outputNum());
		*/
		
	}

	ScreenFlip();
}


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main () {
#endif
	SetGraphMode(1514, 1136, 32);

    if (DxLib_Init() == -1) {
		return -1;
    }
	touchMgr = new TouchMgr();
    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(mainLoop, 0, 1);	
#else
    while (!shouldExit) {
		mainLoop();
    }
    
    DxLib_End();
 #endif

    return 0;
}