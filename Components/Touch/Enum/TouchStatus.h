/**
 * @file TouchStatus.h
 * @brief タッチ情報のステータス一覧
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef TOUCH_STATUS_H
#define TOUCH_STATUS_H

enum class TouchStatus {
	// 触っていない状態
    kNoTouch,
	// 触った直後の状態
    kJustTouch,
	// 触っているがリピートまでは行っていない状態
    kNotRepeating,
	// 触っていてリピート中の状態
    kRepeating,
	// 離した直後の状態
    kJustRelease
};

#endif