/**
 * @file UIAreaState.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef UI_AREA_STATE_H
#define UI_AREA_STATE_H

/**
 * @brief UIの選択状態
 * 
 */
enum class UIAreaState {
	// タッチしていない
	kNoTouch,
	// タップ開始
	kJustTap,
	// 領域に入った直後
	kJustAreaIn,
	// 領域に入っている
	kAreaIn,
	// 領域に入ってからリピート分経過
	kAreaInRepeat,
	// 領域から離れた直後
	kJustAreaOut,
	// 領域内で離れた直後
	kJustRelease
};

#endif
