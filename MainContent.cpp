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
	world_ = new PhysicusWorld(b2Vec2(0, 10.0), 0.1, {b2Vec2(0, 0), b2Vec2(getScreenWidth(), getScreenHeight())});
	bmFontMgr_->load("GameFont_Blue");
	bmFontMgr_->load("GameFont_Orange");
	bmFontMgr_->load("GameFont_White");

	auto setting = world_->getParticleSetting();
	int money = ComponentAssets::shared()->getImages().icons.at(0);
	int jewery = ComponentAssets::shared()->getImages().icons.at(1);
	int images[30];
	for(int i = 0; i < 30; i++) {
		if(i % 5 == 0) {
			images[i] = jewery;
		} else {
			images[i] = money;
		}
	}
	setting.setImages(images, 30);
	world_->setParticleSetting(setting);
	

    ChangeFont("07LogoTypeGothic7.ttf");
	setDrawScreen(ScreenState::kBack);
}

MainContent::~MainContent() {
	
}

void MainContent::run() {
	clearDrawScreen();

	// タッチ計算
	touchMgr_->calc();
	// パーティクルのタイプをシングルに
	world_->setParticleType(Physicus::ParticleType::kSingle);
	// オブジェクトのタイプを手描き線に先行
	//world_->setObjectType(Physicus::ObjectType::kHandWritten);
	// 操作内容をパーティクル生成に変更
	world_->setControlType(Physicus::ControlType::kParticleCreate);
	// タッチを物理演算に適用
	world_->touchCalc(touchMgr_->get());
	// 時間を進める
	world_->timeCalc();

	// タッチ画像描画
	{	
		touch_t touch = touchMgr_->get();
		int CircleColor = ( touch.status != TouchStatus::kNoTouch && touch.status != TouchStatus::kJustRelease) ? Color::kYellow : Color::kRed;
		drawCircle(touch.x, touch.y, 5, CircleColor);
	}
	// オブジェクトの描画
	world_->draw();
	// ボーンの描画
	//world_->drawDebugFrame();

	ScreenFlip();
}
