/**
 * @file MainContent.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "MainContent.h"
#include <math.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

TouchMgr *touchMgr;


MainContent::MainContent() {
	SetGraphMode(1136, 852, 32);
    if (DxLib_Init() == -1) {
		return ;
    }
	touchMgr = new TouchMgr();
	bmFontMgr = new BMFontMgr();
	bmFontMgr->load("GameFont_Blue");
	bmFontMgr->load("GameFont_Orange");
	bmFontMgr->load("GameFont_White");
	//test = new box2DTest();
	

    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);
	//Sprite *spr = new Sprite();
	//Sprite *spr = new Sprite();
	//spr->setColor(255,255,255,255);
	//b2Vec2 gravity(0.0f, -10.0f);
	//b2World world(gravity);
}

MainContent::~MainContent() {
	
}

void MainContent::run() {
	ClearDrawScreen();

	// box2Dテスト
	//test->calc();
	//test->draw();

	// タッチ計算
	touchMgr->calc();

	// タッチ画像描画
	{	
		touch_t touch = touchMgr->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);
		//drawCircle(touch.x, touch.y, 64, CircleColor);

		if (touch.status == TouchStatus::JustTouch) {
			//test->create(touch.x * 0.1, touch.y * 0.1);
			//test->createCar(touch.x, touch.y);
			//test->createChainPolygon(touch.x, touch.y);
		}
		//test->createHandWritten(touch, 10.0);
	}

	ScreenFlip();
}
