/**
 * @file PhysicusParticleType.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_PARTICLE_TYPE_H
#define PHYSICUS_PARTICLE_TYPE_H

namespace Physicus {
	enum class ParticleType {
		// 単発
		kSingle,
		// 四角形
		kRectangle,
		// 円
		kCircle,
		// 多角形
		kPolygon,
		// 連結している形状同士では干渉しない矩形の集合体
		kHandWritten,
		// 線
		kLine
	};
}

#endif