/**
 * @file ScreenStateResume.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ScreenStateResume.h"

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
int ScreenStateResume::loadScreenState() {
	if( loadBright() 			 == kErrorCode || 
		loadBlend() 			 == kErrorCode || 
		loadLerp() 				 == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}

// ブレンド情報の保存
int ScreenStateResume::saveScreenState() {
	if( saveBright() 			 == kErrorCode || 
		saveBlend() 			 == kErrorCode || 
		saveLerp()				 == kErrorCode ) {
		return kErrorCode;
	}
	return kSuccessCode;
}
