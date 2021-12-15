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
#include "../PhysicusObject/PhysicusObjectManager.h"
#include "../PhysicusParticle/PhysicusParticleManager.h"
#include "Frame/PhysicusWorldFrame.h"

class PhysicusWorld {
	// MARK: - 変数

	private:
	// オブジェクト管理クラス
	PhysicusObjectManager* objects_;
	// パーティクル管理クラス
	PhysicusParticleManager* particles_;
	// 物理演算を行うワールド
	b2World* world_;
	// ワールドの拡大率
	float world_scale_;
	// 静止させるなら**true**
	bool stop_;

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
	 * @brief パーティクルのタイプを取得する
	 * 
	 * @param handle パーティクルハンドル
	 * @return Physicus::ParticleType 
	 */
	Physicus::ParticleType getParticleType(int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルのタイプを設定する
	 * 
	 * @param type 
	 * @param handle パーティクルハンドル
	 */
	void setParticleType(Physicus::ParticleType type, int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルの設定を取得する
	 * 
	 * @param handle パーティクルハンドル
	 * @return ParticleSetting 
	 */
	Physicus::ParticleSetting getParticleSetting(int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルの設定を設定する
	 * 
	 * @param setting 設定
	 * @param handle パーティクルハンドル
	 */
	void setParticleSetting(Physicus::ParticleSetting setting, int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief オブジェクトのスプライトのタイプを取得する
	 * 
	 * @param handle オブジェクトハンドル
	 * @return SpriteType 
	 */
	SpriteType getObjectSpriteType(int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief オブジェクトのスプライトのタイプを設定する
	 * 
	 * @param sprite_type 
	 * @param handle オブジェクトハンドル
	 */
	void setObjectSpriteType(SpriteType sprite_type, int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief 全てのオブジェクトの描画進行率を設定する
	 * 
	 * @param advance 
	 */
	void setObjectsDrawAdvanceAll(float advance);

	/**
	 * @brief 演算を静止させているかを取得する
	 * 
	 * @return true 
	 * @return false 
	 */
	bool getStop();

	/**
	 * @brief 演算の静止状態をセットする
	 * 
	 * @param stop 
	 */
	void setStop(bool stop);

	// MARK: - プレビュー

	void makePreviewData();

	// MARK: - 関数

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
	 * @brief 縁取りした矩形の即時生成
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @param body_type ボディタイプ
	 * @return int 生成したオブジェクトのハンドル
	 */
	int makeRectangleStroke(b2Vec2 start, b2Vec2 end, b2BodyType body_type = b2_staticBody);

	/**
	 * @brief 塗りつぶし矩形の即時生成
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @param body_type ボディタイプ
	 * @return int 生成したオブジェクトのハンドル
	 */
	int makeRectangleFill(b2Vec2 start, b2Vec2 end, b2BodyType body_type = b2_staticBody);

	/**
	 * @brief シングルパーティクルの即時生成
	 * 
	 * @param position 生成座標
	 * @param setting パーティクルの設定
	 * @return int 生成したパーティクルのハンドル
	 */
	int makeParticleSingle(b2Vec2 position, Physicus::ParticleSetting setting);

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