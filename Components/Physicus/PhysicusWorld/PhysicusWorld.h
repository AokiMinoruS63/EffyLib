/**
 * @file PhysicusWorld.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 物理演算の制御を行うワールドのクラス
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_WORLD_H
#define PHYSICUS_WORLD_H

#include <vector>

// 相互参照
class Sprite;

class PhysicusWorld {
	public:
	PhysicusWorld();
	~PhysicusWorld();

	void append(Sprite* sprite);

	// 物理演算を行うSprite配列
	std::vector<Sprite *> sprites;
};

#endif