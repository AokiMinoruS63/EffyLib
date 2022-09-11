/**
 * @file TouchData.h
 * @brief タッチ構造体
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef TOUCH_DATA_H
#define TOUCH_DATA_H

#include <vector>
#include "Enum/TouchStatus.h"

/**
 * @brief タッチ情報
 * 
 */
struct touch_t {
	// タッチの状態
    TouchStatus status;
	// 座標
    int x, y;
	// タッチ履歴
    std::vector<bool> input_log;
	// X座標履歴
    std::vector<int>pos_log_x;
	// Y座標履歴
    std::vector<int>pos_log_y;
	// ダブルタップしているなら**true**
    bool double_tap;
	// タッチを開始したインデックス
	int beginIndex;

	/**
	 * @brief 前のフレームでタッチしているなら**true**
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isLastTouch() {
		return status == TouchStatus::kNotRepeating || status == TouchStatus::kRepeating || status == TouchStatus::kJustRelease;
	}

	/**
	 * @brief 現在タッチしているなら**true**
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isCurrentTouch() {
		return status != TouchStatus::kJustRelease && status != TouchStatus::kNoTouch;
	}
};

#endif