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
#include <string>

namespace Physicus {
	class Particle {
		// MARK: - 定数

		public:
		// ガウスぼかしを行わないグループ
		static const int kNoGaussGroup = 0;

		// MARK: - 変数

		private:
		// パーティクルのアクセス用のハンドル
		int handle_;
		// パーティクルの管理クラス
		b2ParticleSystem* particle_system_;
		// パーティクル
		b2ParticleGroup* particle_;
		// 演算を行うワールド
		b2World* world_;
		// タッチの軌跡
		std::vector<b2Vec2> locus_;
		// 拡大率
		float world_scale_;
		// 設定
		ParticleSetting setting_;
		
		// MARK: - コンストラクタ・デストラクタ

		public:

		Particle(int handle, touch_t touch, b2ParticleSystem* particle_system, b2World* world, float scale, ParticleSetting setting);
		~Particle();

		// MARK: - Getter, Setter

		/**
		 * @brief ハンドルを取得する
		 * 
		 * @return int 
		 */
		int getHandle();

		/**
		 * @brief グループを取得する
		 * 
		 * @return int 
		 */
		int getGroup();

		/**
		 * @brief パーティクルのタイプを取得する
		 * 
		 * @return Physicus::ParticleType 
		 */
		Physicus::ParticleType getType();

		/**
		 * @brief パーティクルのタイプを設定する
		 * 
		 * @param type 
		 */
		void setType(Physicus::ParticleType type);

		/**
		 * @brief パーティクルの設定を取得する
		 * 
		 * @return ParticleSetting 
		 */
		ParticleSetting getSetting();

		/**
		 * @brief パーティクルの設定をセットする
		 * 
		 * @param setting 
		 */
		void setSetting(ParticleSetting setting);

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