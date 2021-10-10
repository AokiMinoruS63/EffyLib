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


MainContent::MainContent() {
	SetGraphMode(1136, 852, 32);
    if (DxLib_Init() == -1) {
		return ;
    }
	touchMgr_ = new TouchMgr();
	bmFontMgr_ = new BMFontMgr();
	world_ = new PhysicusWorld(b2Vec2(0, 10.0));
	bmFontMgr_->load("GameFont_Blue");
	bmFontMgr_->load("GameFont_Orange");
	bmFontMgr_->load("GameFont_White");
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
	touchMgr_->calc();
	// タッチを物理演算に適用
	world_->touchCalc(touchMgr_->get(), Physicus::Type::LinksBoard);

	// タッチ画像描画
	{	
		touch_t touch = touchMgr_->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? Color::yellow : Color::red;
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
