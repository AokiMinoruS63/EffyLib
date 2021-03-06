/**
 * @file Vec3.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

struct Vec3 {
	float x;
	float y;
	float z;

	/**
	 * @brief 初期化
	 * 
	 * @param x 
	 * @param y 
	 * @param z 
	 */
	Vec3(float x, float y, float z): x(x), y(y), z(z){}

	/**
	 * @brief 初期化
	 * 
	 */
	Vec3(): Vec3(0.0f, 0.0f, 0.0f) {}

	/**
	 * @brief 初期化
	 * 
	 * @param x 
	 * @param y 
	 * @param z 
	 */
	Vec3(int x, int y, int z): Vec3((float)x, (float)y, (float)z) {}

	/* 関数 */

	/**
	 * @brief ベクトルを正規化する
	 *  
	 */
	void norm() {
		float value = std::sqrtf( x * x + y * y + z * z );
		if(value > 0) {
			value = 1 / value;
		}
		x = x * value;
		y = y * value;
		z = z * value;
	}
};

/* 演算 */

/**
 * @brief Vec3それぞれにfloat型を足す
 * 
 * @param v 
 * @param f 
 * @return Vec3 
 */
inline Vec3 operator + (const Vec3& v, float f) {
	return { v.x + f, v.y + f, v.z + f };
}

inline Vec3 operator + (float f, const Vec3& v) {
	return { v.x + f, v.y + f, v.z + f };
}

inline void operator += (Vec3& v, float f) {
	v.x += f;
	v.y += f;
	v.z += f;
}

/**
 * @brief Vec3それぞれをfloat型で引く
 * 
 * @param v 
 * @param f 
 * @return b2Vec2 
 */
inline Vec3 operator - (const Vec3& v, float f) {
	return { v.x - f, v.y - f, v.z - f };
}

inline Vec3 operator - (float f, const Vec3& v) {
	return { v.x - f, v.y - f, v.z - f };
}

/**
 * @brief Vec3それぞれにfloat型をかける
 * 
 * @param v 
 * @param f 
 * @return b2Vec2 
 */
inline Vec3 operator * (const Vec3& v, float f) {
	return { v.x * f, v.y * f, v.z * f };
}

inline Vec3 operator * (float f, const Vec3& v) {
	return { v.x * f, v.y * f, v.z * f };
}

/**
 * @brief Vec3それぞれにfloat型を割る
 * 
 * @param v 
 * @param f 
 * @return Vec3 
 */
inline Vec3 operator / (const Vec3& v, float f) {
	return { v.x / f, v.y / f, v.z / f };
}

inline Vec3 operator / (float f, const Vec3& v) {
	return { v.x / f, v.y / f, v.z / f };
}

/**
 * @brief Vec3同士で足す
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator + (const Vec3& v1, const Vec3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

/**
 * @brief Vec3同士で足して代入する
 * 
 * @param v1 左辺
 * @param v2 右辺
 */
inline void operator += (Vec3& v1, const Vec3& v2) {
	v1 = v1 + v2;
}

/**
 * @brief Vec3からVec3を引く
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator - (const Vec3& v1, const Vec3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

/**
 * @brief Vec3からVec3を引いて代入する
 * 
 * @param v1 左辺
 * @param v2 右辺
 */
inline void operator -= (Vec3& v1, const Vec3& v2) {
	v1 = v1 - v2;
}

/**
 * @brief Vec3同士をかける
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator * (const Vec3& v1, const Vec3& v2) {
	return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

/**
 * @brief Vec3同士で掛け算して代入する
 * 
 * @param v1 左辺
 * @param v2 右辺
 */
inline void operator *= (Vec3& v1, const Vec3& v2) {
	v1 = v1 * v2;
}

/**
 * @brief Vec3からVec3を割る
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator / (const Vec3& v1, const Vec3& v2) {
	return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}

/**
 * @brief Vec3からVec3を割って代入する
 * 
 * @param v1 左辺
 * @param v2 右辺
 */
inline void operator /= (Vec3& v1, const Vec3& v2) {
	v1 = v1 / v2;
}

#endif
