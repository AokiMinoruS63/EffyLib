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
#include "../../Utility/TypeExtensions/Color+Extensions.h"
#include "../../Utility/TypeExtensions/Float+Extensions.h"

namespace Physicus {
	struct ParticleSetting {
		// タイプ
		ParticleType type;
		// 設定
		b2ParticleSystemDef setting;
		// 描画用のスクリーンのグループ。0ならぼかし用のスクリーンを生成しない
		int group;
		// 線の色
		int edge_color;
		// 塗りつぶし色
		int fill_color;
		// エリアアウトしても生存するなら**true**
		bool area_out_alive;
		// 角の尖り具合(1.0でそのまま、０で辺の中心から次の辺の中心までベジェ曲線で描画する)
		float sharpness;
		// ベジェの補完をどれだけ行うかの係数(0に近いほど多く行う。1が最大)
		float roughness;
		// ガウスを考慮してどれだけ小さく描くか
		int draw_small_value_x;
		// ガウスを考慮してどれだけ小さく描くか
		int draw_small_value_y;

		static ParticleSetting init() {
			b2ParticleSystemDef setting = b2ParticleSystemDef();
			setting.density = 1.0;
			return ParticleSetting({ ParticleType::kSingle, setting, 1, Color::kWhite, Color::kNigelleBlue, false, Float::kMax, Float::kQuarter, 2, 8});
		}
	};
}

#endif