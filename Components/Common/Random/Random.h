/**
 * @file Random.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RANDOM_H
#define RANDOM_H

#include "RandomEngine.h"
#include "../Type/Vec2.h"
#include "../Type/Vec3.h"
#include "../Constant/MathConstant.h"
#include "../Shape/Circle.h"
#include "../Shape/Rect.h"
#include "../Shape/Sphere.h"
#include <cmath>

/**
 * @brief 乱数シードの初期化
 * 
 */
inline void setRandomSeed() {
	RandomEngine::shared()->setSeed();
}

/**
 * @brief 乱数シードの初期化
 * 
 * @param seed 乱数シード
 */
inline void setRandomSeed(std::uint32_t seed) {
	RandomEngine::shared()->setSeed(seed);
}

/**
 * @brief ランダムな0から1のint型の値を返す
 * 
 * @return int 
 */
inline int randomInt() {
	return RandomEngine::shared()->randomInt();
}

/**
 * @brief ランダムな0からmaxのint型の値を返す
 * 
 * @param max 
 * @return int 
 */
inline int randomInt(int max) {
	return RandomEngine::shared()->randomInt(max);
}

/**
 * @brief ランダムなminからmaxのint型の値を返す
 * 
 * @param min 
 * @param max 
 * @return int 
 */
inline int randomInt(int min, int max) {
	return RandomEngine::shared()->randomInt(min, max);
}

/**
 * @brief ランダムな0.0から1.0のfloat型の値を返す
 * 
 * @return float 
 */
inline float randomFloat() {
	return RandomEngine::shared()->randomFloat();
}

/**
 * @brief ランダムな0.0からmaxのfloat型の値を返す
 * 
 * @param max 
 * @return float 
 */
inline float randomFloat(float max) {
	return RandomEngine::shared()->randomFloat(max);
}

/**
 * @brief ランダムなminからmaxのfloat型の値を返す
 * 
 * @param min 
 * @param max 
 * @return float 
 */
inline float randomFloat(float min, float max) {
	return RandomEngine::shared()->randomFloat(min, max);
}

/**
 * @brief ランダムな0.0から1.0のdouble型の値を返す
 * 
 * @return double 
 */
inline double randomDouble() {
	return RandomEngine::shared()->randomDouble();
}

/**
 * @brief ランダムな0.0からmaxのdouble型の値を返す
 * 
 * @param max 
 * @return double 
 */
inline double randomDouble(double max) {
	return RandomEngine::shared()->randomDouble(max);
}

/**
 * @brief ランダムなminからmaxのdouble型の値を返す
 * 
 * @param min 
 * @param max 
 * @return double 
 */
inline double randomDouble(double min, double max) {
	return RandomEngine::shared()->randomDouble(min, max);
}

/**
 * @brief ランダムな２次元単位ベクトルの取得
 * 
 * @return Vec2 
 */
inline Vec2 randomVec2() {
	const double theta = randomFloat(kTwoPiFloat);
	return { (float)std::cos(theta), (float)std::sin(theta) };
}

/**
 * @brief ランダムな２次元単位ベクトルを等倍したベクトルの取得
 * 
 * @param length 倍率
 * @return Vec2 倍化させたベクトル
 */
inline Vec2 randomVec2(float length) {
	const Vec2 vec = randomVec2();
	return { vec.x * length, vec.y * length };
}

/**
 * @brief 最小値と最大値からランダムな座標を返す
 * 
 * @param min 最小値の座標
 * @param max 最大値の座標
 * @return Vec2 
 */
inline Vec2 randomVec2(Vec2 min, Vec2 max) {
	Vec2 vec;
	vec.x = randomFloat(min.x, max.x);
	vec.y = randomFloat(min.y, max.y);
	return vec;
}

/**
 * @brief 0から最大値までランダムな座標を返す
 * 
 * @param xMax X座標の最大値
 * @param yMax Y座標の最大値
 * @return Vec2 
 */
inline Vec2 randomVec2(float xMax, float yMax) {
	Vec2 vec = Vec2();
	vec.x = randomFloat(0.0f, xMax);
	vec.y = randomFloat(0.0f, yMax);
	return vec;
}

/**
 * @brief 円を半径からランダムな場所に移動させる
 * 
 * @param circle 移動させる円
 * @return Vec2 移動後の座標
 */
inline Vec2 randomVec2(Circle& circle) {
	const float r = sqrt(randomFloat()) * circle.radius;
	const double theta = randomFloat(kTwoPiFloat);
	return circle.movedBy((float)std::cos(theta) * r, (float)std::sin(theta) * r);
}

/**
 * @brief 矩形を幅・高さの範囲でランダムな場所に移動させる
 * 
 * @param rect 移動させる矩形
 * @return Vec2 移動後の座標
 */
inline Vec2 randomVec2(Rect& rect) {
	Vec2 vec;
	const Vec2 leftTop = rect.leftTop();
	const Vec2 rightBottom = rect.rightBottom();
	vec.x = randomFloat(leftTop.x, rightBottom.x);
	vec.y = randomFloat(leftTop.y, rightBottom.y);
	return rect.movedBy(vec);
}

/**
 * @brief ランダムな３次元単位ベクトルを返す
 * 
 * @return Vec3 
 */
inline Vec3 randomVec3() {
	const float theta = randomFloat(kPiFloat);
	const float phi = randomFloat(kTwoPi);
	const float s = std::sin(theta);
	return { s * std::cos(phi), s * std::sin(phi), std::cos(theta) };
}

/**
 * @brief ランダムな３次元単位ベクトルを等倍したベクトルの取得
 * 
 * @param length 
 * @return Vec3 
 */
inline Vec3 randomVec3(float length) {
	auto vec = randomVec3();
	return { vec.x * length, vec.y * length, vec.z * length };
}

/**
 * @brief 0から最大値までランダムな座標を返す
 * 
 * @param max 最大値
 * @return Vec3 
 */
inline Vec3 randomVec3(Vec3 max) {
	Vec3 vec;
	vec.x = randomFloat(0.0f, max.x);
	vec.y = randomFloat(0.0f, max.y);
	vec.z = randomFloat(0.0f, max.z);
	return vec;
}

/**
 * @brief 最小値と最大値からランダムな座標を返す
 * 
 * @param min 最小値
 * @param max 最大値
 * @return Vec3 
 */
inline Vec3 randomVec3(Vec3 min, Vec3 max) {
	Vec3 vec;
	vec.x = randomFloat(min.x, max.x);
	vec.y = randomFloat(min.y, max.y);
	vec.z = randomFloat(min.z, max.z);
	return vec;
}

/**
 * @brief 0から最大値までランダムな座標を返す
 * 
 * @param xMax X座標の最大値
 * @param yMax Y座標の最大値
 * @param zMax Z座標の最大値
 * @return Vec3 
 */
inline Vec3 randomVec3(float xMax, float yMax, float zMax) {
	Vec3 vec;
	vec.x = randomFloat(0.0f, xMax);
	vec.y = randomFloat(0.0f, yMax);
	vec.z = randomFloat(0.0f, zMax);
	return vec;
}

/**
 * @brief 球を半径からランダムな場所に移動させる
 * 
 * @param sphere 移動させる球体
 * @return Vec3 移動後の座標
 */
inline Vec3 randomVec3(Sphere sphere) {
	const Vec3 vec = randomVec3(sphere.radius);
	return sphere.movedBy(vec);
}

#endif