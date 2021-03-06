/**
 * @file Sphere.h
 * @brief 球体の形状
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "../Type/Vec3.h"

struct Sphere {
	// X座標
	float x;
	// Y座標
	float y;
	// Z座標
	float z;
	// 半径
	float radius;

	/**
	 * @brief 座標と半径を設定した初期化
	 * 
	 * @param x 
	 * @param y 
	 * @param z 
	 * @param radius 
	 */
	Sphere(float x, float y, float z, float radius): x(x), y(y), z(z), radius(radius) {}

	/**
	 * @brief 半径のみの初期化
	 * 
	 * @param radius 半径
	 */
	Sphere(float radius): Sphere(0.0f, 0.0f, 0.0f, radius) {}

	/**
	 * @brief 座標と半径を設定した初期化
	 * 
	 * @param position 座標
	 * @param radius 半径
	 */
	Sphere(Vec3 position, float radius): Sphere(position.x, position.y, position.z, radius) {}

	/**
	 * @brief 球を移動させる
	 * 
	 * @param x X軸の移動量
	 * @param y Y軸の移動量
	 * @param z Z軸の移動量
	 * @return Vec3 移動後の座標
	 */
	Vec3 movedBy(float x, float y, float z);

	/**
	 * @brief 球を移動させる
	 * 
	 * @param moveValue 移動量
	 * @return Vec3 移動後の座標
	 */
	Vec3 movedBy(Vec3 moveValue);
};

#endif