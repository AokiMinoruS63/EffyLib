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
	SetGraphMode(getScreenWidthWithPartition(), getScreenHeightWithPartition(), 32);
    if (DxLib_Init() == -1) {
		return ;
    }
	touchMgr_ = new TouchMgr();
	bmFontMgr_ = new BMFontMgr();
	world_ = new PhysicusWorld(b2Vec2(0, 10.0), 0.1);
	bmFontMgr_->load("GameFont_Blue");
	bmFontMgr_->load("GameFont_Orange");
	bmFontMgr_->load("GameFont_White");
	

    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);
}

MainContent::~MainContent() {
	
}

void MainContent::run() {
	ClearDrawScreen();

	// タッチ計算
	touchMgr_->calc();
	// タッチを物理演算に適用
	world_->touchCalc(touchMgr_->get(), Physicus::Type::kLinksBoard);

	// タッチ画像描画
	{	
		touch_t touch = touchMgr_->get();
		int CircleColor = ( touch.status != TouchStatus::kNoTouch && touch.status != TouchStatus::kJustRelease) ? Color::kYellow : Color::kRed;
		drawCircle(touch.x, touch.y, 5, CircleColor);
	}

	ScreenFlip();
}
