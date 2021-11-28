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
	// 操作の種類
	Physicus::ControlType control_type_;
	// エフェクト用の共用で使用するスクリーン
	EffectScreen* effect_screen_;
	// 液体エフェクトのスクリーン
	std::vector<Effect::Liquid> screen_;

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
	 * @brief 操作の種類を取得する
	 * 
	 * @return Physicus::ControlType 
	 */
	Physicus::ControlType getControlType();

	/**
	 * @brief 操作の種類を設定する
	 * 
	 * @param type 
	 */
	void setControlType(Physicus::ControlType type);

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

	// MARK: - プレビュー

	void makePreviewData();

	// MARK: - 関数

	/**
	 * @brief タッチによってオブジェクトを生成する
	 * 
	 * @param touch タッチ情報
	 * @return true オブジェクトが生成されるなら**true**
	 * @return false 
	 */
	bool touchObjectCreate(touch_t touch);

	/**
	 * @brief タッチによってパーティクルを生成する
	 * 
	 * @param touch タッチ情報
	 * @return true パーティクルが生成されるなら**true**
	 * @return false 
	 */
	bool touchParticleCreate(touch_t touch);

	/**
	 * @brief パーティクル用のスクリーンを生成する
	 * 
	 * @param group 描画用のスクリーンのグループ
	 * @param fill_color 塗りつぶし色
	 * @param edge_color 線の色
	 */
	void makeParticleScreen(int group, int fill_color, int edge_color);

	public:

	/**
	 * @brief 矩形の即時作成
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @param body_type ボディタイプ
	 */
	void makeRectangle(b2Vec2 start, b2Vec2 end, b2BodyType body_type = b2_staticBody);

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
	 * @return true オブジェクトが生成
	 * @return false オブジェクトが未生成
	 */
	bool touchCalc(touch_t touch);

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