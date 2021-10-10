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
#include "../PhysicusObject/PhysicusObject.h"

// 相互参照
class Sprite;

class PhysicusWorld {
	/* 変数 */

	private:
	b2World* world_;
	// 物理演算を行うSprite配列
	std::vector<Sprite *> sprites_;
	// 物理演算を行うボディ配列
	std::vector<Physicus::Object> objects_;
	// 現在生成・操作を行なっているボディ
	Physicus::Object* current_;

	/* コンストラクタ・デストラクタ */
	public:
	PhysicusWorld(b2Vec2 gravity);
	~PhysicusWorld();

	/* 関数 */

	public:

	/**
	 * @brief スプライトに物理演算を適用する
	 * 
	 * @param sprite 適用するスプライト
	 */
	void applySprite(Sprite* sprite);

	/**
	 * @brief タッチによるオブジェクトの干渉（生成も含む）
	 * 
	 * @param touch 
	 * @param type 
	 */
	void touchCalc(touch_t touch, Physicus::Type type);
};

#endif