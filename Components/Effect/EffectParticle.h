/**
 * @file EffectParticle.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief エフェクト用のパーティクル構造体
 * @version 0.1
 * @date 2021-12-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EFFECT_PARTICLE_H
#define EFFECT_PARTICLE_H

#include "../Common/Vec3.h"
#include "../Common/Random.h"
#include "../Utility/DxLibWrap.h"

namespace Effect {
	// エフェクト用のパーティクル
	struct Particle3D {
		// 座標
		Vec3 pos;
		// 動きの強さ
		Vec3 velocity;
		// 生成した時間
		LONG start_time;
		// 半径
		float radius;
		// 重さ
		float weight;
		// 間隔
		float offset;
		// 生存時間
		float life_time;
	};

	/**
	 * @brief 初期化
	 * 
	 * @param start_time 生成した時間
	 * @param pos 座標
	 * @return Particle 
	 */
	static Particle3D init(LONG start_time, Vec3 pos) {
		Particle3D particle = Particle3D();
		
		particle.pos = randomVec3(Sphere(10.0));
		particle.velocity = (randomVec3(1.0) + randomVec3(Sphere(0.3))) * 20.0;
		particle.start_time = start_time;
		particle.radius = randomFloat(1.0, 5.0);
		particle.weight = randomFloat();
		particle.offset = randomFloat();
		particle.life_time = 120.0;

		return particle;
	}
}

#endif