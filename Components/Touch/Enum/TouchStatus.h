/**
 * @file TouchStatus.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief タッチ情報のステータス一覧
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
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