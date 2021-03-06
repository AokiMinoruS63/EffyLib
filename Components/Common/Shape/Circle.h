/**
 * @file Circle.h
 * @brief 円の形状
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Type/Vec2.h"
#include "../Type/Color.h"
#include "../ScreenState/BlendMode.h"
#include "../ScreenState/Lerp.h"

// 円の図形
struct Circle {
	// 中心X座標
	float x;
	// 中心Y座標
	float y;
	// 半径
	float radius;

	/**
	 * @brief 初期化
	 * 
	 * @param x X座標
	 * @param y Y座標
	 * @param radius 半径
	 */
	Circle(float x, float y, float radius): x(x), y(y), radius(radius) {}

	/**
	 * @brief 初期化
	 * 
	 * @param pos 座標
	 * @param radius 半径
	 */
	Circle(Vec2 pos, float radius): Circle(pos.x, pos.y, radius) {}

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param x 移動させるX座標
	 * @param y 移動させるY座標
	 * @return Vec2 移動後の座標
	 */
	Vec2 movedBy(float x, float y);

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param vec 
	 * @return Vec2 移動後の座標
	 */
	Vec2 movedBy(Vec2 vec);

	/**
	 * @brief 描画
	 * 
	 * @param color 色
	 * @param edgeOnly 輪郭のみの描画なら**true**
	 * @param blend ブレンドモード
	 * @param lerp 線形補完
	 * @return int 
	 */
	int draw(int color = Color::kWhite, bool edgeOnly = false, BlendMode::Property blend = BlendMode::Property { BlendMode::kNoBlend, 0 }, Lerp lerp = Lerp::kNearest);	
};

#endif
