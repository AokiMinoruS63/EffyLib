/**
 * @file EffectScreen.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "../Utility/DxLibWrap.h"
#include "EffectScreen.h"

/**
 * @brief エフェクトスクリーンの生成
 * 
 */
EffectScreen::EffectScreen() {
	screen_state_.saveScreenState();
	ScreenState::Frame state = getScreenState();
	edge_screen_ = -1;
	fill_screen_ = -1;
	edge_screen_ = MakeScreen(state.width, state.height, TRUE);
	fill_screen_ = MakeScreen(state.width, state.height, TRUE);
	state.width /= kGaussRatio;
	state.height /= kGaussRatio;
	gauss_screen_ = MakeScreen(state.width, state.height, TRUE);
}

/**
 * @brief エフェクトスクリーンの削除
 * 
 */
EffectScreen::~EffectScreen() {
	deleteGraph(edge_screen_);
	deleteGraph(fill_screen_);
	deleteGraph(gauss_screen_);
}

// 縁を描画するためのスクリーンの取得
int EffectScreen::getEdgeScreen() {
	return edge_screen_;
}

// 塗りつぶし用のスクリーンの取得
int EffectScreen::getFillScreen() {
	return fill_screen_;
}

// ガウス用のスクリーンの取得
int EffectScreen::getGaussScreen() {
	return gauss_screen_;
}

// スクリーン情報のバッファからの読み込み
int EffectScreen::loadScreenState() {
	return screen_state_.loadScreenState();
}

// スクリーン情報のバッファへの保存
int EffectScreen::saveScreenState() {
	return screen_state_.saveScreenState();
}
