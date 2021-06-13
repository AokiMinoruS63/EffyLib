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
    TouchStatus status;
    int x, y;
    std::vector<bool> inputLog;
    std::vector<int>posLogX;
    std::vector<int>posLogY;
    bool doubleTap;
}touch_t;

#endif