/**
 * @file ScreenStateResume.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "ScreenStateResume.h"

// アクティブなスクリーンの読み込み
int ScreenStateResume::loadScreen() {
	if(screen != getDrawScreen()) {
		return setDrawScreen(screen);
	}
	return 0;
}

// 再起用のスクリーンの保存
int ScreenStateResume::saveScreen() {
	screen = getDrawScreen();
	return screen;
}

// 明るさ情報の読み込み
int ScreenStateResume::loadBright() {
	return setDrawBright(buf_bright);
}

// 明るさ情報の保存
int ScreenStateResume::saveBright() {
	return getDrawBright(&buf_bright);
}

// ブレンド情報の読み込み
int ScreenStateResume::loadBlend() {
	return setDrawBlendMode(buf_blend);
}

// ブレンド情報の保存
int ScreenStateResume::saveBlend() {
	return getDrawBlendMode(&buf_blend);
}

// 線形補完情報の読み込み
int ScreenStateResume::loadLerp() {
	return setDrawMode(lerp);
}

// 線形補完情報の保存
int ScreenStateResume::saveLerp() {
	lerp = getDrawMode();
	return lerp;
}

// ブレンド情報の読み込み
int ScreenStateResume::loadScreenState(bool screen_load) {
	const int check = screen_load ? loadScreen() : kSuccessCode;
	if( check					 == kErrorCode ||
		loadBright() 			 == kErrorCode || 
		loadBlend() 			 == kErrorCode || 
		loadLerp() 				 == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}

// ブレンド情報の保存
int ScreenStateResume::saveScreenState(bool screen_save) {
	const int check = screen_save ? saveScreen() : kSuccessCode;
	if( check					 == kErrorCode ||
		saveBright() 			 == kErrorCode || 
		saveBlend() 			 == kErrorCode || 
		saveLerp()				 == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}
