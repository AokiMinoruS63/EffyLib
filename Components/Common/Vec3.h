/**
 * @file Vec3.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ３軸のベクトル構造体
 * @version 0.1
 * @date 2021-12-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef VEC3_H
#define VEC3_H

struct Vec3 {
	float x;
	float y;
	float z;
};

/**
 * @brief Vec3それぞれにfloat型を足す
 * 
 * @param v 
 * @param f 
 * @return Vec3 
 */
inline Vec3 operator + (const Vec3& v, float f)
{
	return { v.x + f, v.y + f, v.z + f };
}

/**
 * @brief Vec3それぞれをfloat型で引く
 * 
 * @param v 
 * @param f 
 * @return b2Vec2 
 */
inline Vec3 operator - (const Vec3& v, float f)
{
	return { v.x - f, v.y - f, v.z - f };
}

/**
 * @brief Vec3それぞれにfloat型をかける
 * 
 * @param v 
 * @param f 
 * @return b2Vec2 
 */
inline Vec3 operator * (const Vec3& v, float f)
{
	return { v.x * f, v.y * f, v.z * f };
}

/**
 * @brief Vec3それぞれにfloat型を割る
 * 
 * @param v 
 * @param f 
 * @return Vec3 
 */
inline Vec3 operator / (const Vec3& v, float f)
{
	return { v.x / f, v.y / f, v.z / f };
}

/**
 * @brief Vec3同士で足す
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator + (const Vec3& v1, const Vec3& v2)
{
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

/**
 * @brief Vec3からVec3を引く
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator - (const Vec3& v1, const Vec3& v2)
{
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

/**
 * @brief Vec3同士をかける
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator * (const Vec3& v1, const Vec3& v2)
{
	return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

/**
 * @brief Vec3からVec3を割る
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
inline Vec3 operator / (const Vec3& v1, const Vec3& v2)
{
	return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}

#endif