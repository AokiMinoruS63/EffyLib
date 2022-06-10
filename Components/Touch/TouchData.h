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

typedef struct {
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
}touch_t;

#endif