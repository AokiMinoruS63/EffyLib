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
#include "../ScreenStateResume.h"

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