/**
 * @file Circle.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 円の形状
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Circle.h"

// 図形を移動させる
Vec2 Circle::movedBy(float x, float y) {
	this->x += x;
	this->y += y;
	Vec2 vec;
	vec.x = this->x;
	vec.y = this->y;
	return vec;
}

// 図形を移動させる
Vec2 Circle::movedBy(Vec2 vec) {
	return movedBy(vec.x, vec.y);
}
