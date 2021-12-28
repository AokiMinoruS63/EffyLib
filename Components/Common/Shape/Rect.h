/**
 * @file Rect.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 矩形の形状
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RECT_H
#define RECT_H

#include "../Vec2.h"

// 矩形
struct Rect {
	// 中心X座標
	float x;
	// 中心Y座標
	float y;
	// 幅
	float width;
	// 高さ
	float height;

	/**
	 * @brief 半分の幅
	 * 
	 * @return const float 
	 */
	const float halfWidth() {
		return width * 0.5f;
	}

	/**
	 * @brief 半分の高さ　
	 * 
	 * @return const float 
	 */
	const float halfHeight() {
		return height * 0.5f;
	}

	/**
	 * @brief 左上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftTop() {
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
	const Vec2 top() {
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
	const Vec2 rightTop() {
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
	const Vec2 left() {
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
	const Vec2 center() {
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
	const Vec2 right() {
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
	const Vec2 leftBottom() {
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
	const Vec2 bottom() {
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
	const Vec2 rightBottom() {
		Vec2 vec = Vec2();
		vec.x = x + width * 0.5;
		vec.y = y + height * 0.5;
		return vec;
	}

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param x 移動させるX座標
	 * @param y 移動させるY座標
	 * @return Vec2 移動した座標
	 */
	Vec2 movedBy(float x, float y) {
		this->x += x;
		this->y += y;
		Vec2 vec;
		vec.x = x;
		vec.y = y;
		return vec;
	}

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param vec 
	 * @return Vec2 
	 */
	Vec2 movedBy(Vec2 vec) {
		return movedBy(vec.x, vec.y);
	}
};

#endif