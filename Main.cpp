/* 
 * File:   Main
 * Author: nokotan
 *
 * Created on 2020/01/30, 0:57
 * 
 * DxLibToHTML5雛形ファイル
 */

#include <DxLib.h>
#include <math.h>
//#include "Components/Touch/TouchMgr.h"
//#include <hogeClass.h>
#include <Touch/TouchMgr.h>
#include <BMFont/BMFontMgr.h>
#include <utility>
#include <Utility/DxLibWrap.h>
#include <Utility/TypeConversion.h>
#include <Sprite/Sprite.h>
#include <Box2D/box2d/box2d.h>
//#include <Components/hogeClass.h>
#ifdef EMSCRIPTEN
#  include <emscripten.h>
#endif

static bool shouldExit = false;
TouchMgr *touchMgr;
BMFontMgr *bmFontMgr;
const BMFont::bmFont_t *bmFont;


//BMFont::BMFont bmFont;
void mainLoop() {
	if (ProcessMessage() == -1) {
		shouldExit = true;
	}

	ClearDrawScreen();

	{
		touchMgr->calc();
		
	}

	{
		
		// タッチ画像描画
		touch_t touch = touchMgr->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

		drawCircle(touch.x, touch.y, 64, CircleColor);
		
	}

	ScreenFlip();
}


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main () {
#endif

#ifdef EMSCRIPTEN
	SetGraphMode(1136, 852, 32);
#else
	SetGraphMode(852, 1136, 32)
#endif
// Emscriptenは非同期読み込み不可のようなのでそれ以外の時のみ使用する
#ifndef EMSCRIPTEN
	// 非同期読み込みモードオン
	SetUseASyncLoadFlag( TRUE ) ;
#endif
    if (DxLib_Init() == -1) {
		return -1;
    }
	touchMgr = new TouchMgr();
	bmFontMgr = new BMFontMgr();
	bmFontMgr->load("GameFont_Blue");
    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);
	Sprite *spr = new Sprite();
	//Sprite *spr = new Sprite();
	//spr->setColor(255,255,255,255);
	b2Vec2 gravity(0.0f, -10.0f);
	//b2World world(gravity);

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