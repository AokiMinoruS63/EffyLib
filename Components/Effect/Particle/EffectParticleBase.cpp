/**
 * @file EffectParticleBase.cpp
 * @brief エフェクトのパーティクルのベースクラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "EffectParticleBase.h"
#include "../../Utility/DxLibWrap.h"
#include "../../Common/Random/Random.h"

using namespace Effect;

// 変数の初期化
void ParticleBase::initBase(float radian_min, float radian_max, float life_time, int image) {
	start_time_ = getNowCountFloat();
	last_time_ = start_time_;
	delta_time_ = 0.0f;
	radius_ = randomFloat(radian_min, radian_max);
	weight_ = randomFloat();
	offset_ = randomFloat();
	image_ = image;
	life_time_ = life_time;
	is_life_end_ = false;
}

// 寿命を終えているかチェックする
bool ParticleBase::lifeCheck() {
	if (getNowCountFloat() > start_time_ + life_time_) {
		is_life_end_ = true;
	}
	return is_life_end_;
}

/**
 * @brief 経過時間を取得する
 * 
 * @return float 
 */
float ParticleBase::getDeltaTime() {
	return delta_time_;
}

// 経過時間をセットする
void ParticleBase::calcDeltaTime() {
	const float now_time = getNowCountFloat();
	delta_time_ = now_time - last_time_;
	last_time_ = now_time;
}

// カールノイズによる移動
void ParticleBase::movedByCurlNoise(PerlinNoise& noise) {}

// 描画
void ParticleBase::draw() {}