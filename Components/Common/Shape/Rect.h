/**
 * @file Rect.h
 * @brief 矩形の形状
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef RECT_H
#define RECT_H

#include "../Type/Vec2.h"
#include "../Type/Color.h"
#include "../ScreenState/BlendMode.h"
#include "../ScreenState/Lerp.h"

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

	/* 初期化 */

	/**
	 * @brief 初期化
	 * 
	 * @param x X座標
	 * @param y Y座標
	 * @param width 幅
	 * @param height 高さ
	 */
	Rect(float x, float y, float width, float height): x(x), y(y), width(width), height(height) {}

	/**
	 * @brief 正方形の場合の初期化
	 * 
	 * @param x X座標
	 * @param y Y座標
	 * @param size 幅と高さ
	 */
	Rect(float x, float y, float size): Rect(x, y, size, size) {}

	/**
	 * @brief 初期化
	 * 
	 * @param pos 座標
	 * @param width 幅
	 * @param height 高さ
	 */
	Rect(Vec2 pos, float width, float height): Rect(pos.x, pos.y, width, height) {}

	/**
	 * @brief 正方形の場合の初期化
	 * 
	 * @param pos 座標
	 * @param size 幅と高さ
	 */
	Rect(Vec2 pos, float size): Rect(pos.x, pos.y, size, size) {}

	/* Getter */

	/**
	 * @brief 半分の幅
	 * 
	 * @return const float 
	 */
	const float halfWidth();

	/**
	 * @brief 半分の高さ　
	 * 
	 * @return const float 
	 */
	const float halfHeight();

	/**
	 * @brief 左上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftTop();

	/**
	 * @brief 上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 top();

	/**
	 * @brief 右上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 rightTop();

	/**
	 * @brief 左座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 left();

	/**
	 * @brief 中心座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 center();

	/**
	 * @brief 右座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 right();

	/**
	 * @brief 左下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftBottom();

	/**
	 * @brief 下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 bottom();

	/**
	 * @brief 右下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 rightBottom();

	/**
	 * @brief 相対的な左上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftTopRelative();

	/**
	 * @brief 相対的な上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 topRelative();

	/**
	 * @brief 相対的な右上座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 rightTopRelative();

	/**
	 * @brief 相対的な左座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftRelative();

	/**
	 * @brief 相対的な中心座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 centerRelative();

	/**
	 * @brief 相対的な右座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 rightRelative();

	/**
	 * @brief 相対的な左下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 leftBottomRelative();

	/**
	 * @brief 相対的な下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 bottomRelative();

	/**
	 * @brief 相対的な右下座標
	 * 
	 * @return Vec2 
	 */
	const Vec2 rightBottomRelative();

	// MARK: - 関数

	/**
	 * @brief 矩形の中に座標が含まれているかチェックする
	 * 
	 * @param x X座標
	 * @param y Y座標
	 * @return true 
	 * @return false 
	 */
	bool isContain(float x, float y);

	/**
	 * @brief 矩形の中に座標が含まれているかチェックする
	 * 
	 * @param vec ２次元座標
	 * @return true 
	 * @return false 
	 */
	bool isContain(Vec2 vec);

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param x 移動させるX座標
	 * @param y 移動させるY座標
	 * @return Vec2 移動した座標
	 */
	Vec2 movedBy(float x, float y);

	/**
	 * @brief 図形を移動させる
	 * 
	 * @param vec 
	 * @return Vec2 
	 */
	Vec2 movedBy(Vec2 vec);

	/**
	 * @brief 描画
	 * 
	 * @param color 色
	 * @param radian 角度
	 * @param edgeOnly 輪郭のみの描画なら**true**
	 * @param blend ブレンドモード
	 * @param lerp 線形補完
	 * @return int 
	 */
	int draw(int color = Color::kWhite, float radian = 0.0, bool edgeOnly = false, BlendMode::Property blend = BlendMode::Property { BlendMode::kNoBlend, 0 }, Lerp lerp = Lerp::kNearest);	
};

#endif