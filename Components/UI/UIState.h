/**
 * @file UIState.h
 * @brief UIの状態
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef UI_STATE_H
#define UI_STATE_H

/**
 * @brief UIの状態
 * 
 */
enum class UIState {
	// 描画・判定共に行う
	kActive,
	// 描画は行うが、判定は行わない
	kUnresponsive,
	// 使用できない事を示す描画を行い、判定は行わない
	kDisable,
	// 描画も判定も行わない
	kInvisible
};

#endif