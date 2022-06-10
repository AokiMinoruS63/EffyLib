/**
 * @file Circle.cpp
 * @brief 円の形状
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "Circle.h"
#include "../ScreenState/ScreenStateResume.h"

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

// 描画
int Circle::draw(int color, bool edgeOnly, BlendMode::Property blend, Lerp lerp) {
	ScreenStateResume state = ScreenStateResume();
	state.saveScreenState();
	setDrawBlendMode(blend);
	setDrawMode(lerp);
	const int x = this->x;
	const int y = this->y;
	const int r = this->radius;
	const int returnNum = drawCircle(x, y, r, color, FALSE, !edgeOnly);
	state.loadScreenState();
	return returnNum;
}