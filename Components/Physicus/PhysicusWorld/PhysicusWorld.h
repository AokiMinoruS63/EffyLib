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
#include "../PhysicusParticle/PhysicusParticle.h"
#include "Frame/PhysicusWorldFrame.h"
#include "PhysicusControlType.h"
#include "../../Effect/EffectScreen.h"
#include "../../Effect/LiquidEffect.h"

class PhysicusWorld {
	// MARK: - 変数

	private:
	// オブジェクトのハンドルのカウンタ
	int object_handle_counter_;
	// パーティクルのハンドルのカウンタ
	int particle_handle_counter_;
	// 物理演算を行うワールド
	b2World* world_;
	// ワールドの拡大率
	float world_scale_;
	// 物理演算を行うボディ配列
	std::vector<Physicus::Object *> objects_;
	// 現在生成・操作を行なっているオブジェクト
	Physicus::Object* current_object_;
	// パーティクルの生成クラス
	b2ParticleSystem* particle_system_;
	// 現在生成・操作を行なっているパーティクル
	Physicus::Particle* current_particle_;
	// 物理演算を行うParticle配列
	std::vector<Physicus::Particle *> particles_;
	// オブジェクトの設定
	Physicus::ObjectSetting current_object_setting_;
	// パーティクルの設定
	Physicus::ParticleSetting current_particle_setting_;
	// オブジェクト・パーティクルが生存できるエリア
	Physicus::Frame alive_area_;
	// 数珠繋ぎにする距離
	float tie_loop_range_;
	// 液体エフェクトのスクリーン
	std::vector<Effect::Liquid *> screen_;

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

	// MARK: - Getter, Setter

	/**
	 * @brief オブジェクトのタイプを取得する
	 * 
	 * @return Physicus::ObjectType 
	 */
	Physicus::ObjectType getObjectType();

	/**
	 * @brief オブジェクトのタイプを設定する
	 * 
	 * @param type 
	 */
	void setObjectType(Physicus::ObjectType type);

	/**
	 * @brief パーティクルのタイプを取得する
	 * 
	 * @return Physicus::ParticleType 
	 */
	Physicus::ParticleType getParticleType();

	/**
	 * @brief パーティクルのタイプを設定する
	 * 
	 * @param type 
	 */
	void setParticleType(Physicus::ParticleType type);

	/**
	 * @brief パーティクルの設定を取得する
	 * 
	 * @return ParticleSetting 
	 */
	Physicus::ParticleSetting getParticleSetting();

	/**
	 * @brief パーティクルの設定を設定する
	 * 
	 * @param setting 
	 */
	void setParticleSetting(Physicus::ParticleSetting setting);

	// MARK: - プレビュー

	void makePreviewData();

	// MARK: - 関数

	private: 

	/**
	 * @brief オブジェクトのハンドルのカウンタを進める
	 * 
	 */
	void addObjectHandleCounter();

	/**
	 * @brief パーティクルのハンドルのカウンタを進める
	 * 
	 */
	void addParticleHandleCounter();

	public:

	/**
	 * @brief タッチによってオブジェクトを生成する
	 * 
	 * @param touch タッチ情報
	 * @return int 生成されたオブジェクトハンドル
	 */
	int touchObjectCreate(touch_t touch);

	/**
	 * @brief タッチによってパーティクルを生成する
	 * 
	 * @param touch タッチ情報
	 * @return int 生成されたパーティクルハンドル。生成されなければ**NULL**を返す
	 */
	int touchParticleCreate(touch_t touch);

	/**
	 * @brief パーティクル用のスクリーンを生成する
	 * 
	 * @param setting エフェクトの設定
	 */
	void makeParticleScreen(Effect::LiquidSetting setting);

	public:

	/**
	 * @brief 矩形の即時作成
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @param body_type ボディタイプ
	 * @return int 生成したオブジェクトのハンドル
	 */
	int makeRectangle(b2Vec2 start, b2Vec2 end, b2BodyType body_type = b2_staticBody);

	/**
	 * @brief パーティクルの即時作成
	 * 
	 * @param position 生成座標
	 * @param setting パーティクルの設定
	 * @return int 生成したパーティクルのハンドル
	 */
	int makeParticle(b2Vec2 position, Physicus::ParticleSetting setting);

	/**
	 * @brief 時間を進める
	 * 
	 */
	void timeCalc();

	/**
	 * @brief オブジェクトとパーティクルを描画する
	 * 
	 */
	void draw();

	/**
	 * @brief オブジェクトとパーティクルのフレームを描画する
	 * 
	 */
	void drawDebugFrame();
};

#endif