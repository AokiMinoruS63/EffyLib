/**
 * @file PhysicusParticle.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_PARTICLE_H
#define PHYSICUS_PARTICLE_H

#include "../../OpenSource/Box2D/Box2D.h"
#include "../../Touch/TouchData.h"
#include "PhysicusParticleSetting.h"
#include <vector>

namespace Physicus {
	class Particle {

		// MARK: - 変数

		// パーティクルの中に入っている子パーティクル
		std::vector<b2ParticleSystem *> particle_;
		// 拡大率
		float world_scale_;
		// 設定
		ParticleSetting setting_;
		
		// MARK: - コンストラクタ・デストラクタ

		public:

		Particle();
		~Particle();

		// MARK: - 生成

		/**
		 * @brief パーティクルの生成
		 * 
		 * @param touch 
		 * @return true パーティクルが生成されたら**true**
		 * @return false 
		 */
		bool generation(touch_t touch);

		// MARK: - 描画

		/**
		 * @brief パーティクルの描画
		 * 
		 */
		void draw();

		/**
		 * @brief 編集中のパーティクルの描画
		 * 
		 */
		void drawEditing();

		/**
		 * @brief パーティクルのフレームの描画
		 * 
		 */
		void drawDebugFrame();

		/**
		 * @brief 編集中のパーティクルのフレームの描画
		 * 
		 */
		void drawEditingDebugFrame();
	};
}

#endif