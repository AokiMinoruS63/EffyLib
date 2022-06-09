/**
 * @file EffectParticleBase.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief エフェクトのパーティクルのベースクラス
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EFFECT_PARTICLE_BASE_H
#define EFFECT_PARTICLE_BASE_H

#include "../../OpenSource/PerlinNoise/PerlinNoise.h"
#include "../../Utility/DxLibWrap.h"

namespace Effect {
	class ParticleBase {
		public:
		ParticleBase(){};
		~ParticleBase(){};


		/* 変数 */

		protected:

		// 座標(座標系が種類によって違うため、サブクラスにて定義)
		//Vec3 pos;
		// 動きの強さ(座標系が種類によって違うため、サブクラスにて定義)
		//Vec3 velocity;

		// 生成した時間(秒数)
		float start_time_;
		// 半径
		float radius_;
		// 重さ
		float weight_;
		// 間隔
		float offset_;
		// 画像を使用する場合
		int image_;
		// 生存時間
		float life_time_;
		// 寿命が尽きていたら**true**
		bool is_life_end_;

		private:
		// 経過時間
		float delta_time_;
		// 前のフレームの時間
		float last_time_;

		/* 関数 */

		protected:

		/**
		 * @brief 変数の初期化
		 * 
		 * @param radian_min 半径の乱数の最小値
		 * @param radian_max 半径の乱数の最大値
		 * @param life_time 生存秒数
		 * @param image 画像ハンドル
		 */
		void initBase(float radian_min = 1.0, float radian_max = 5.0, float life_time = 2.0, int image = -1);

		/**
		 * @brief 経過時間を取得する
		 * 
		 * @return float 
		 */
		float getDeltaTime();

		/**
		 * @brief 経過時間をセットする
		 * 
		 */
		void calcDeltaTime();

		public:

		/**
		 * @brief 寿命を終えているかチェックする
		 * 
		 * @return true 寿命が終えていたら**true**
		 * @return false 
		 */
		bool lifeCheck();

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