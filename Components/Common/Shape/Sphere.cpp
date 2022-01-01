/**
 * @file Sphere.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 球体の形状
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
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