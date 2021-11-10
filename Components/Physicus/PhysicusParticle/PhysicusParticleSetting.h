/**
 * @file PhysicusParticleSetting.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_PARTICLE_SETTING_H
#define PHYSICUS_PARTICLE_SETTING_H

#include "../../OpenSource/Box2D/Box2D.h"
#include "PhysicusParticleType.h"

namespace Physicus {
	struct ParticleSetting {
		// タイプ
		ParticleType type;
		// 設定
		b2ParticleSystemDef setting;
		// 線の色
		int color;
		// エリアアウトしても生存するなら**true**
		bool area_out_alive;
		// 角の尖り具合(1.0でそのまま、０で辺の中心から次の辺の中心までベジェ曲線で描画する)
		float sharpness;
		// ベジェの補完をどれだけ行うかの係数(0に近いほど多く行う。1が最大)
		float roughness;
	};
}

#endif