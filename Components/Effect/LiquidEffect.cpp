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

// デフォルトの初期化
Liquid Liquid::init(EffectScreen* screen) {
	return Liquid(screen, 1, Color::kBlue, Color::kWhite, 1400, 800);
}

// コンストラクタ
Liquid::Liquid(EffectScreen* screen, int group, int fill_color, int edge_color, int fill_gauss_rate, int edge_gauss_rate, int fill_finish_gauss_rate, int edge_finish_gauss_rate) {
	group_ = group;
	Frame frame =  getScreenState();
	effect_screen_ = screen;
	current_screen_ = 0;
	render_screen_[0] = -1;
	render_screen_[1] = -1;
	render_screen_[0] = MakeScreen(frame.width, frame.height);
	render_screen_[1] = MakeScreen(frame.width, frame.height);

	fill_color_ = fill_color;
	edge_color_ = edge_color;
	fill_gauss_rate_ = fill_gauss_rate;
	edge_gauss_rate_ = edge_gauss_rate;
	fill_finish_gauss_rate_ = fill_finish_gauss_rate;
	edge_finish_gauss_rate_ = edge_finish_gauss_rate;
}

// デストラクタ
Liquid::~Liquid() {
	//DeleteGraph(edge_screen_);
	//DeleteGraph(fill_screen_);
}

// グループを取得する
int Liquid::getGroup() {
	return group_;
}

// 描画準備
void Liquid::preRender() {
	SetDrawScreen(render_screen_[current_screen_]);
	ClearDrawScreen();
}

// 描画
void Liquid::postRender() {
	Color::Color fill_color, edge_color;
	int edge_screen = effect_screen_->getEdgeScreen();
	int fill_screen = effect_screen_->getFillScreen();
	int gauss_screen = effect_screen_->getGaussScreen();
	Frame frame = getScreenState();
	Frame smallFrame = frame.toScale(EffectScreen::kGaussRatio);
	effect_screen_->saveScreenState();
	getColor2(fill_color_, &fill_color);
	getColor2(edge_color_, &edge_color);
	setDrawScreen(fill_screen);
	setDrawMode(kBilinear);
	setDrawBlendMode(BlendMode::kAlpha, 230);
	drawExtendGraph(0, 0, smallFrame.width, smallFrame.height, render_screen_[current_screen_], FALSE);
	setDrawMode(kNearest);

	setDrawBlendMode(BlendMode::kNoBlend, 0);
	setDrawScreenBack();
	GraphFilter(fill_screen, Filter::kGauss, 16, fill_gauss_rate_ );
	GraphFilter(fill_screen, Filter::kTwoColor, 20, Color::kBlack, 0, Color::kWhite, 255);
	GraphFilterBlt(fill_screen, edge_screen, Filter::kGauss, 16, edge_gauss_rate_);
	GraphFilter(edge_screen, Filter::kTwoColor, 20,  Color::kBlack, 0, Color::kWhite, 255);

	setDrawScreen(edge_screen);
	int beforeBlendMode, beforeBlendPrm;
	BlendMode::Property beforeBlend, subBlend = BlendMode::init(BlendMode::kSub, BlendMode::kMax);
	getDrawBlendMode(&beforeBlend);
	setDrawBlendMode(subBlend);
	drawExtendGraph(0, 0, smallFrame.width, smallFrame.height, fill_screen, TRUE);
	setDrawBlendMode(beforeBlend);
	setDrawScreenBack();

	if(fill_finish_gauss_rate_ > 0) {
		GraphFilter(fill_screen, Filter::kGauss, 16, fill_finish_gauss_rate_ );
	}
	if(edge_finish_gauss_rate_ > 0) {
		GraphFilter(edge_screen, Filter::kGauss, 16, edge_finish_gauss_rate_ );
	}
	setDrawMode(kBilinear);
	setDrawBright(fill_color);
	drawExtendGraph(0, 0, frame.width, frame.height, fill_screen, TRUE);
	setDrawBright(edge_color);
	setDrawBlendMode(BlendMode::kAdd, 255);
	drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
	// ガウスをしたらもう一度描画する
	if(edge_finish_gauss_rate_ > 0 ) {
		drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
		drawExtendGraph(0, 0, frame.width, frame.height, edge_screen, TRUE);
	}
	effect_screen_->loadScreenState();
	current_screen_ = 1 - current_screen_;
}