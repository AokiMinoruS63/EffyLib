/**
 * @file LiquidEffect.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "LiquidEffect.h"
#include "../Utility/DxLibWrap.h"
#include "../Utility/TypeExtensions.h"
#include "EffectScreen.h"

using namespace Effect;
using namespace ScreenState;
using namespace GraphEffect;

// コンストラクタ
Liquid::Liquid(LiquidSetting setting) {
	Frame frame =  getScreenState();
	cnt_ = 0;
	effect_screen_ = new EffectScreen();
	current_screen_ = 0;
	render_screen_[0] = -1;
	render_screen_[1] = -1;
	render_screen_[0] = MakeScreen(frame.width, frame.height);
	render_screen_[1] = MakeScreen(frame.width, frame.height);

	setting_ = setting;
}

// デストラクタ
Liquid::~Liquid() {
	delete effect_screen_;
	for(int i = 0; i < 2; i++) {
		if(render_screen_[i] != -1) {
			deleteGraph(render_screen_[i]);
		}
	}
}

// グループを取得する
int Liquid::getGroup() {
	return setting_.group;
}

// 描画準備
void Liquid::preRender() {
	setDrawScreen(render_screen_[current_screen_]);
	clearDrawScreen();
}

// 描画
void Liquid::postRender() {
	const int edge_screen = effect_screen_->getEdgeScreen();
	const int fill_screen = effect_screen_->getFillScreen();
	const int gauss_screen = effect_screen_->getGaussScreen();
	Frame frame = getScreenState();
	Frame smallFrame = frame.toScale(EffectScreen::kGaussRatio);
	effect_screen_->saveScreenState();
	setDrawScreen(fill_screen);
	setDrawMode(kBilinear);
	setDrawBlendMode(BlendMode::kAlpha, 230);
	drawExtendGraph(0, 0, frame.width, frame.height, render_screen_[current_screen_], FALSE);
	setDrawMode(kNearest);

	setDrawBlendMode(BlendMode::kNoBlend, 0);
	setDrawScreenBack();
	graphFilter(fill_screen, Filter::kGauss, 16, setting_.fill_gauss_rate );
	graphFilter(fill_screen, Filter::kTwoColor, 20, Color::kBlack, 0, Color::kWhite, 255);
	graphFilterBlt(fill_screen, edge_screen, Filter::kGauss, 16, setting_.edge_gauss_rate);
	graphFilter(edge_screen, Filter::kTwoColor, 20,  Color::kBlack, 0, Color::kWhite, 255);
	if(setting_.effect) {
		graphFilterBlt(edge_screen, gauss_screen, Filter::kDownScale, EffectScreen::kGaussRatio);
		graphFilter(gauss_screen, Filter::kGauss, 16, 1400);
		graphFilter(gauss_screen, Filter::kTwoColor, 20,  Color::kBlack, 0, Color::kWhite, 255);
		graphFilter(gauss_screen, Filter::kGauss, 16, 1400);
		graphFilter(gauss_screen, Filter::kTwoColor, 20,  Color::kBlack, 0, Color::kWhite, 255);
		graphFilter(gauss_screen, Filter::kGauss, 16, 5000);
	}

	setDrawScreen(edge_screen);
	int beforeBlendMode, beforeBlendPrm;
	BlendMode::Property beforeBlend, subBlend = BlendMode::init(BlendMode::kSub, BlendMode::kMax);
	getDrawBlendMode(&beforeBlend);
	setDrawBlendMode(subBlend);
	drawGraph(0, 0, fill_screen, TRUE);
	setDrawBlendMode(beforeBlend);
	setDrawScreenBack();

	if(setting_.fill_finish_gauss_rate > 0) {
		graphFilter(fill_screen, Filter::kGauss, 16, setting_.fill_finish_gauss_rate );
	}
	if(setting_.edge_finish_gauss_rate > 0) {
		graphFilter(edge_screen, Filter::kGauss, 16, setting_.edge_finish_gauss_rate );
	}
	setDrawMode(kBilinear);
	if(setting_.effect) {
		cnt_++;
		const int prm = setting_.blendPrm(cnt_);
		setDrawBlendMode(setting_.effect_blend_mode, prm);
		setDrawBright(setting_.effect_color);
		drawExtendGraph(0, 0, frame.width, frame.height, gauss_screen, TRUE);
		setDrawBlendMode(beforeBlend);
	}
	setDrawBright(setting_.fill_color);
	drawExtendGraph(0, 0, frame.width, frame.height, fill_screen, TRUE);
	setDrawBright(setting_.edge_color);
	setDrawBlendMode(BlendMode::kAdd, 255);
	drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
	// ガウスぼかしをならもう一度描画する
	if(setting_.edge_finish_gauss_rate > 0 ) {
		drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
		drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
	}
	effect_screen_->loadScreenState();
	current_screen_ = 1 - current_screen_;
}