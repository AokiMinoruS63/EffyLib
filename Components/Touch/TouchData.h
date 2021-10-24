/**
 * @file TouchData.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief タッチ構造体
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
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