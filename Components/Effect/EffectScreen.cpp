/**
 * @file EffectScreen.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../Utility/DxLibWrap.h"
#include "EffectScreen.h"

/**
 * @brief エフェクトスクリーンの生成
 * 
 */
EffectScreen::EffectScreen() {
	ScreenState::Frame state = getScreenState();
	state.width /= kGaussRatio;
	state.height /= kGaussRatio;
	edge_screen_ = -1;
	fill_screen_ = -1;
	edge_screen_ = MakeScreen(state.width, state.height, TRUE);
	fill_screen_ = MakeScreen(state.width, state.height, TRUE);
	gauss_screen_ = MakeScreen(state.width, state.height, TRUE);
}

/**
 * @brief エフェクトスクリーンの削除
 * 
 */
EffectScreen::~EffectScreen() {
	DeleteGraph(edge_screen_);
	DeleteGraph(fill_screen_);
	DeleteGraph(gauss_screen_);
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

// 明るさ情報の読み込み
int EffectScreen::loadBright() {
	return setDrawBright(buf_bright_);
}

// 明るさ情報の保存
int EffectScreen::saveBright() {
	return getDrawBright(&buf_bright_);
}

// ブレンド情報の読み込み
int EffectScreen::loadBlend() {
	return setDrawBlendMode(buf_blend_);
}

// ブレンド情報の保存
int EffectScreen::saveBlend() {
	return getDrawBlendMode(&buf_blend_);
}

// 線形補完情報の読み込み
int EffectScreen::loadLinerInterPolation() {
	return setDrawMode(liner_inter_polation_);
}

// 線形補完情報の保存
int EffectScreen::saveLinerInterPolation() {
	liner_inter_polation_ = getDrawMode();
	return liner_inter_polation_;
}

// ブレンド情報の読み込み
int EffectScreen::loadScreenState() {
	if( loadBright() 			 == kErrorCode || 
		loadBlend() 			 == kErrorCode || 
		loadLinerInterPolation() == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}

// ブレンド情報の保存
int EffectScreen::saveScreenState() {
	if( saveBright() 			 == kErrorCode || 
		saveBlend() 			 == kErrorCode || 
		saveLinerInterPolation() == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}