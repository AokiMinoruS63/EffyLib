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
#include "Frame/PhysicusWorldFrame.h"

// 相互参照
class Sprite;

class PhysicusWorld {
	// MARK: - 変数

	private:
	// 物理演算を行うワールド
	b2World* world_;
	// ワールドの拡大率
	float world_scale_;
	// 物理演算を行うSprite配列
	std::vector<Sprite *> sprites_;
	// 物理演算を行うボディ配列
	std::vector<Physicus::Object *> objects_;
	// 現在生成・操作を行なっているボディ
	Physicus::Object* current_;
	// オブジェクトが生存できるエリア
	Physicus::Frame alive_area_;
	// 数珠繋ぎにする距離
	float tie_loop_range_;

	// MARK: - コンストラクタ・デストラクタ

	public:

	/**
	 * @brief 演算ワールドクラスのコンストラクタ
	 * 
	 * @param gravity 重力
	 * @param scale ワールドの拡大率
	 * @param alive_area オブジェクトが生存可能なエリア
	 */
	PhysicusWorld(b2Vec2 gravity, float scale, Physicus::Frame alive_area, float tie_loop_range = Physicus::Constant::LinksBoardObject::kTieLoopRange);

	/**
	 * @brief 演算ワールドクラスのデストラクタ
	 * 
	 */
	~PhysicusWorld();

	// MARK: - 関数

	public:

	/**
	 * @brief 時間を進める
	 * 
	 */
	void timeCalc();

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
	 * @param line_width 
	 * @return true オブジェクトが生成
	 * @return false オブジェクトが未生成
	 */
	bool touchCalc(touch_t touch, Physicus::Type type, float line_width = Physicus::Object::kDefaultLineWidth);

	/**
	 * @brief オブジェクトを描画する
	 * 
	 */
	void draw();

	/**
	 * @brief オブジェクトのフレームを描画する
	 * 
	 */
	void drawDebugFrame();
};

#endif