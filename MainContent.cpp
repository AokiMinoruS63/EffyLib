/**
 * @file MainContent.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */



#include "MainContent.h"
#include <math.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

//double *buf;

//#include <random>

std::vector<Effect::Particle3D*> effects;
PerlinNoise noise;
Effect::Bloom* bloom;

MainContent::MainContent() {
	/*
	const int width = getScreenWidth();
	const int height = getScreenHeight();
	buf = new double[width * height]();
	PerlinNoise pn;
	unsigned int kk = 0;
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
		double x = (double)j/((double)width);
			double y = (double)i/((double)height);

			// Typical Perlin noise
			double n = pn.noise(10 * x, 10 * y, 0.8);

			// Wood like structure
			n = 20 * pn.noise(x, y, 0.8);
			n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			buf[kk] = floor(255 * n);
			kk++;
		}
	}
	*/
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
	/*
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
	*/
	bloom = new Effect::Bloom(100);
	

    ChangeFont("07LogoTypeGothic7.ttf");
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
	// パーティクルのタイプをシングルに
	//world_->setParticleType(Physicus::ParticleType::kSingle);
	// タッチを物理演算に適用
	//world_->touchParticleCreate(touchMgr_->get());
	world_->touchObjectCreate(touchMgr_->get());

	// 時間を進める
	world_->timeCalc();

	// タッチ画像描画
	{	
		touch_t touch = touchMgr_->get();
		if(touch.status == TouchStatus::kJustTouch) {
			for(int i = 0; i < 100; i++) {
				Effect::Particle3D* ef = new Effect::Particle3D(Vec3(touch.x, touch.y, 0));
				effects.push_back( ef );
			}
		}
		int CircleColor = ( touch.status != TouchStatus::kNoTouch && touch.status != TouchStatus::kJustRelease) ? Color::kYellow : Color::kRed;
		drawCircle(touch.x, touch.y, 5, CircleColor);
	}
	
	// オブジェクトの描画
	world_->draw();
	// ボーンの描画
	//world_->drawDebugFrame();

	/*
	bloom->preRender();
	std::vector<Effect::Particle3D*> remove_list;
	for(auto& itr: effects) {
		itr->run();
		itr->movedByCurlNoise(noise);
		if(itr->lifeCheck()) {
			remove_list.push_back(itr);
		}
		itr->draw();
	}
	auto itr = effects.begin();
	while(itr != effects.end()) {
		const int size = Filter(remove_list, [&remove_list, itr](Effect::Particle3D* item){ return item == (*itr); }).size();
		if(size > 0) {
			itr = effects.erase(itr);
		} else {
			++itr;
		}
	}
	bloom->postRender();
	*/
	/*
	unsigned int kk = 0;
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
			double num = buf[kk];
			int numInt = (int)num;
			DrawPixel(j, i, GetColor(numInt, numInt, numInt));
			//printfDx("num: %d\n", numInt);
			kk++;
		}
	}
	*/

	ScreenFlip();
}
