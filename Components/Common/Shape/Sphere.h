/**
 * @file Sphere.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 球体の形状
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "../Vec3.h"

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
	 * @brief 半径のみの初期化
	 * 
	 * @param radius 半径
	 */
	Sphere(float radius) {
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
		this->radius = radius;
	}

	/**
	 * @brief 座標と半径を設定した初期化
	 * 
	 * @param x 
	 * @param y 
	 * @param z 
	 * @param radius 
	 */
	Sphere(float x, float y, float z, float radius) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->radius = radius;
	}

	/**
	 * @brief 座標と半径を設定した初期化
	 * 
	 * @param position 座標
	 * @param radius 半径
	 */
	Sphere(Vec3 position, float radius) {
		this->x = position.x;
		this->y = position.y;
		this->z = position.z;
		this->radius = radius;
	}

	/**
	 * @brief 球を移動させる
	 * 
	 * @param x X軸の移動量
	 * @param y Y軸の移動量
	 * @param z Z軸の移動量
	 * @return Vec3 移動後の座標
	 */
	Vec3 movedBy(float x, float y, float z) {
		this->x += x;
		this->y += y;
		this->z += z;
		return { this->x, this->y, this->z };
	}

	/**
	 * @brief 球を移動させる
	 * 
	 * @param moveValue 移動量
	 * @return Vec3 移動後の座標
	 */
	Vec3 movedBy(Vec3 moveValue) {
		return movedBy( moveValue.x, moveValue.y, moveValue.z);
	}
};

#endif