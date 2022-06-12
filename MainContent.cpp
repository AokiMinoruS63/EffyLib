/**
 * @file MainContent.cpp
 * @brief 
 */

#include "MainContent.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

MainContent::MainContent() {
	setGraphMode(getScreenWidthWithPartition(), getScreenHeightWithPartition(), 32);
	if (init() == kErrorCode) {
		return;
	}
	touchMgr_ = new TouchMgr();
	world_ = new PhysicusWorld(b2Vec2(0, 10.0), 0.1, {b2Vec2(0, 0), b2Vec2(getScreenWidth(), getScreenHeight())});

	auto setting = world_->getParticleSetting();

	setDrawScreen(ScreenState::kBack);
	// プレビューデータの作成
	world_->makePreviewData();
}

MainContent::~MainContent() {
	
}

void MainContent::run() {
	const int width = getScreenWidth();
	const int height = getScreenHeight();
	clearDrawScreen();

	// タッチ計算
	touchMgr_->calc();
	// タッチによりオブジェクトを生成
	world_->touchObjectCreate(touchMgr_->get());

	// 時間を進める
	world_->timeCalc();

	// タッチ画像描画
	{	
		touch_t touch = touchMgr_->get();
		int circle_color = ( touch.status != TouchStatus::kNoTouch && touch.status != TouchStatus::kJustRelease) ? Color::kYellow : Color::kRed;
		drawCircle(touch.x, touch.y, 5, circle_color);
	}
	
	// オブジェクトの描画
	world_->draw();

	screenFrip();
}
