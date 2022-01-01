/**
 * @file Rect.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 矩形の形状
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Rect.h"
#include "../ScreenState/ScreenStateResume.h"
#include "../../Utility/TypeExtensions/B2Vec2+Extensions.h"

// 半分の幅
const float Rect::halfWidth() {
	return width * 0.5f;
}

// 半分の高さ　
const float Rect::halfHeight() {
	return height * 0.5f;
}

// 左上座標
const Vec2 Rect::leftTop() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y - height * 0.5;
	return vec;
}

// 上座標
const Vec2 Rect::top() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y - height * 0.5;
	return vec;
}

// 右上座標
const Vec2 Rect::rightTop() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y - height * 0.5;
	return vec;
}

// 左座標
const Vec2 Rect::left() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y;
	return vec;
}

// 中心座標
const Vec2 Rect::center() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y;
	return vec;
}

// 右座標
const Vec2 Rect::right() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y;
	return vec;
}

// 左下座標
const Vec2 Rect::leftBottom() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y + height * 0.5;
	return vec;
}

// 下座標
const Vec2 Rect::bottom() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y + height * 0.5;
	return vec;
}

// 右下座標
const Vec2 Rect::rightBottom() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y + height * 0.5;
	return vec;
}

// 相対的な左上座標
const Vec2 Rect::leftTopRelative() {
	return Vec2(-halfWidth(), -halfHeight());
}

// 相対的な上座標
const Vec2 Rect::topRelative() {
	return Vec2(0.0f, -halfHeight());
}

// 相対的な右上座標
const Vec2 Rect::rightTopRelative() {
	return Vec2(halfWidth(), -halfHeight());
}

// 相対的な左座標
const Vec2 Rect::leftRelative() {
	return Vec2(-halfWidth(), 0.0f);
}

// 相対的な中心座標
const Vec2 Rect::centerRelative() {
	return Vec2(0.0f, 0.0f);
}

// 相対的な右座標
const Vec2 Rect::rightRelative() {
	return Vec2(halfWidth(), 0.0f);
}

// 相対的な左下座標
const Vec2 Rect::leftBottomRelative() {
	return Vec2(-halfWidth(), halfHeight());
}

// 相対的な下座標
const Vec2 Rect::bottomRelative() {
	return Vec2(0.0f, halfHeight());
}

// 相対的な右下座標
const Vec2 Rect::rightBottomRelative() {
	return Vec2(halfWidth(), halfHeight());
}

// 図形を移動させる
Vec2 Rect::movedBy(float x, float y) {
	this->x += x;
	this->y += y;
	Vec2 vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

// 図形を移動させる
Vec2 Rect::movedBy(Vec2 vec) {
	return movedBy(vec.x, vec.y);
}

// 描画
int Rect::draw(int color, float radian, bool edgeOnly, BlendMode::Property blend, Lerp lerp) {
	ScreenStateResume state = ScreenStateResume();
	state.saveScreenState();
	setDrawBlendMode(blend);
	setDrawMode(lerp);
	const int x = this->x;
	const int y = this->y;
	Vec2 vertices[4] = {
		B2Vec2::rotate(leftTopRelative(), radian) + Vec2(x, y),
		B2Vec2::rotate(rightTopRelative(), radian) + Vec2(x, y),
		B2Vec2::rotate(rightBottomRelative(), radian) + Vec2(x, y),
		B2Vec2::rotate(leftBottomRelative(), radian) + Vec2(x, y)
	};
	const int returnNum = drawQuadrangle(vertices, color, !edgeOnly);
	state.loadScreenState();
	return returnNum;
}
