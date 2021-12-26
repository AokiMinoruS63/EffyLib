/**
 * @file Circle.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 円の形状
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Vec2.h"

// 円の図形
struct Circle {
	// 中心X座標
	float x;
	// 中心Y座標
	float y;
	// 半径
	float radius;

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param x 移動させるX座標
	 * @param y 移動させるY座標
	 * @return Vec2 移動後の座標
	 */
	Vec2 movedBy(float x, float y) {
		this->x += x;
		this->y += y;
		Vec2 vec = Vec2();
		vec.x = this->x;
		vec.y = this->y;
		return vec;
	}

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param vec 
	 * @return Vec2 移動後の座標
	 */
	Vec2 movedBy(Vec2 vec) {
		return movedBy(vec.x, vec.y);
	}
};

#endif