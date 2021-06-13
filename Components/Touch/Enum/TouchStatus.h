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
    NoTouch,
    JustTouch,
    NotRepeating,
    Repeating,
    JustRelease
};

#endif