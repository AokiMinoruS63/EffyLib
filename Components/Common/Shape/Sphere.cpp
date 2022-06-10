/**
 * @file Sphere.cpp
 * @brief 球体の形状
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "Sphere.h"

// 球を移動させる
Vec3 Sphere::movedBy(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
	return { this->x, this->y, this->z };
}

// 球を移動させる
Vec3 Sphere::movedBy(Vec3 moveValue) {
	return movedBy( moveValue.x, moveValue.y, moveValue.z);
}