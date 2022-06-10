/**
 * @file RandomEngine.h
 * @brief 乱数生成機
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef RANDOM_ENGINE_H
#define RANDOM_ENGINE_H

#include <random>

class RandomEngine {
	// MARK: - 変数

	private:
	// 乱数シード生成
	std::random_device rnd;
	public:
	// 乱数生成器
	std::mt19937 mt;

	// MARK: - コンストラクタ、デストラクタ

	private:

	/**
	 * @brief 乱数生成
	 * 
	 */
	RandomEngine();

	/**
	 * @brief デストラクタ
	 * 
	 */
	~RandomEngine();

	public:

	// MARK: - シングルトン

	/**
	 * @brief シングルトン
	 * 
	 * @return RandomEngine* 
	 */
	static RandomEngine* shared() {
		static RandomEngine instance;
		return &instance;
	}

	// MARK: - シードの初期化

	/**
	 * @brief 乱数シードの初期化
	 * 
	 */
	void setSeed();

	/**
	 * @brief 乱数シードの初期化
	 * 
	 * @param seed 
	 */
	void setSeed(std::uint32_t seed);

	// MARK: - 乱数の生成

	/**
	 * @brief ランダムな0から1のint型の値を返す
	 * 
	 * @return int 
	 */
	int randomInt();

	/**
	 * @brief ランダムな0からmaxのint型の値を返す
	 * 
	 * @param max 
	 * @return int 
	 */
	int randomInt(int max);

	/**
	 * @brief ランダムなminからmaxのint型の値を返す
	 * 
	 * @param min 
	 * @param max 
	 * @return int 
	 */
	int randomInt(int min, int max);

	/**
	 * @brief ランダムな0.0から1.0のfloat型の値を返す
	 * 
	 * @return float 
	 */
	float randomFloat();

	/**
	 * @brief ランダムな0.0からmaxのfloat型の値を返す
	 * 
	 * @param max 
	 * @return float 
	 */
	float randomFloat(float max);

	/**
	 * @brief ランダムなminからmaxのfloat型の値を返す
	 * 
	 * @param min 
	 * @param max 
	 * @return float 
	 */
	float randomFloat(float min, float max);

	/**
	 * @brief ランダムな0.0から1.0のdouble型の値を返す
	 * 
	 * @return double 
	 */
	double randomDouble();

	/**
	 * @brief ランダムな0.0からmaxのdouble型の値を返す
	 * 
	 * @param max 
	 * @return double 
	 */
	double randomDouble(double max);

	/**
	 * @brief ランダムなminからmaxのdouble型の値を返す
	 * 
	 * @param min 
	 * @param max 
	 * @return double 
	 */
	double randomDouble(double min, double max);
};
#endif