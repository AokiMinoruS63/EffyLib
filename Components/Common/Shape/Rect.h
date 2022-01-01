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

	/* 関数 */

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
};

#endif