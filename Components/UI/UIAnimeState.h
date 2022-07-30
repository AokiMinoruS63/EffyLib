/**
 * @file UIAnimeState.h
 * @brief UIのアニメの状態
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef UI_ANIME_STATE_H
#define UI_ANIME_STATE_H

enum class UIAnimeState {
	// 通常(領域に入っていない時)
	kNormal,
	// 指が領域内に入っている
	kEntered,
	// 完全に入りきっている時
	kHover,
	// 離れた時
	kExited,
	// フェードイン
	kFadein,
	// フェードアウト
	kFadeout,
	// 非活性
	kDisabled
};

#endif
