/**
 * @file RandomEngine.cpp
 * @brief 乱数生成機
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "RandomEngine.h"

// 乱数生成機
RandomEngine::RandomEngine() {
	mt.seed(rnd());
}

// デストラクタ
RandomEngine::~RandomEngine() {}

// 乱数シードの初期化
void RandomEngine::setSeed() {
	mt.seed(rnd());
}

// 乱数シードの初期化
void RandomEngine::setSeed(std::uint32_t seed) {
	mt.seed(seed);
}

// ランダムな0から1のint型の値を返す
int RandomEngine::randomInt() {
	return randomInt(0, 1);
}

// ランダムな0からmaxのint型の値を返す
int RandomEngine::randomInt(int max) {
	return randomInt(0, max);
}

// ランダムなminからmaxのint型の値を返す
int RandomEngine::randomInt(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}

// ランダムな0.0から1.0のfloat型の値を返す
float RandomEngine::randomFloat() {
	return randomFloat(0.0f, 1.0f);
}

// ランダムな0.0からmaxのfloat型の値を返す
float RandomEngine::randomFloat(float max) {
	return randomFloat(0.0f, max);
}

// ランダムなminからmaxのfloat型の値を返す
float RandomEngine::randomFloat(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(mt);
}

// ランダムな0.0から1.0のdouble型の値を返す
double RandomEngine::randomDouble() {
	return randomDouble(0.0f, 1.0f);
}

// ランダムな0.0からmaxのdouble型の値を返す
double RandomEngine::randomDouble(double max) {
	return randomDouble(0.0f, max);
}

// ランダムなminからmaxのdouble型の値を返す
double RandomEngine::randomDouble(double min, double max) {
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(mt);
}