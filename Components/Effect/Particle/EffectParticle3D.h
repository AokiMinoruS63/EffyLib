/**
 * @file EffectParticle3D.h
 * @brief エフェクト用のパーティクル構造体
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef EFFECT_PARTICLE_H
#define EFFECT_PARTICLE_H

#include "EffectParticleBase.h"
#include "../../Common/Type/Vec3.h"
#include "../../OpenSource/PerlinNoise/PerlinNoise.h"
#include "../../Utility/DxLibWrap.h"

namespace Effect {
	// エフェクト用のパーティクル
	class Particle3D: public ParticleBase {
		/* 変数 */

		// 座標
		Vec3 pos_;
		// 動きの強さ
		Vec3 velocity_;

		/* コンストラクタ・デストラクタ */

		public:

		/**
		 * @brief コンストラクタ
		 * 
		 * @param pos 初期座標
		 * @param radian_min 半径の乱数の最小値
		 * @param radian_max 半径の乱数の最大値
		 * @param life_time 生存秒数
		 * @param image 画像ハンドル
		 */
		Particle3D(Vec3 pos, float radian_min = 2.0, float radian_max = 5.0, float life_time = 2.0, int image = -1);

		/**
		 * @brief デストラクタ
		 * 
		 */
		~Particle3D();

		/* 関数 */

		public:

		/**
		 * @brief 処理を行う
		 * 
		 */
		void run();

		/**
		 * @brief カールノイズによる移動
		 * 
		 * @param noise パーリンノイズ
		 */
		virtual void movedByCurlNoise(PerlinNoise& noise);

		/**
		 * @brief 描画
		 * 
		 */
		virtual void draw();
	};
}

#endif