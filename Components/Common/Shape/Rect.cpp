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

/**
 * @brief 半分の幅
 * 
 * @return const float 
 */
const float Rect::halfWidth() {
	return width * 0.5f;
}

/**
 * @brief 半分の高さ　
 * 
 * @return const float 
 */
const float Rect::halfHeight() {
	return height * 0.5f;
}

/**
 * @brief 左上座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::leftTop() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y - height * 0.5;
	return vec;
}

/**
 * @brief 上座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::top() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y - height * 0.5;
	return vec;
}

/**
 * @brief 右上座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::rightTop() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y - height * 0.5;
	return vec;
}

/**
 * @brief 左座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::left() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y;
	return vec;
}

/**
 * @brief 中心座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::center() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y;
	return vec;
}

/**
 * @brief 右座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::right() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y;
	return vec;
}

/**
 * @brief 左下座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::leftBottom() {
	Vec2 vec = Vec2();
	vec.x = x - width * 0.5;
	vec.y = y + height * 0.5;
	return vec;
}

/**
 * @brief 下座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::bottom() {
	Vec2 vec = Vec2();
	vec.x = x;
	vec.y = y + height * 0.5;
	return vec;
}

/**
 * @brief 右下座標
 * 
 * @return Vec2 
 */
const Vec2 Rect::rightBottom() {
	Vec2 vec = Vec2();
	vec.x = x + width * 0.5;
	vec.y = y + height * 0.5;
	return vec;
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