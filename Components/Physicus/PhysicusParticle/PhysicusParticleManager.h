/**
 * @file PhysicusParticleManager.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief パーティクル管理クラス
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_PARTICLE_MANAGER_H
#define PHYSICUS_PARTICLE_MANAGER_H

#include "../Common/PhysicusManagerCommon.h"
#include "PhysicusParticle.h"
#include "../../Effect/EffectScreen.h"
#include "../../Effect/LiquidEffect.h"

class PhysicusParticleManager: public PhysicusManagerCommon, HandleObject<Physicus::Particle> {
	// MARK: 変数
	private:

	// 物理演算を行うボディ配列
	std::vector<Physicus::Particle *> particles_;
	// 現在生成・操作を行なっているオブジェクト
	Physicus::Particle* current_;
	// パーティクルの生成クラス
	b2ParticleSystem* system_;
	// パーティクルの設定
	Physicus::ParticleSetting current_setting_;
	// 液体エフェクトのスクリーン
	std::vector<Effect::Liquid *> screen_;

	// MARK: - コンストラクタ・デストラクタ

	public:

	/**
	 * @brief コンストラクタ
	 * 
	 * @param world 物理演算を行うワールド
	 * @param scale ワールドの拡大率
	 * @param alive_area オブジェクトが生存可能なエリア
	 */
	PhysicusParticleManager(b2World* world, float scale, Physicus::Frame alive_area);

	/**
	 * @brief デストラクタ
	 * 
	 */
	~PhysicusParticleManager();

	// MARK: 関数

	// MARK: Getter, Setter

	private:

	/**
	 * @brief パーティクルを取得する
	 * 
	 * @param handle 
	 * @return Physicus::Particle* 
	 */
	Physicus::Particle* getParticle(int handle);

	public:

	/**
	 * @brief パーティクルのタイプを取得する
	 * 
	 * @param handle パーティクルハンドル
	 * @return Physicus::ParticleType 
	 */
	Physicus::ParticleType getType(int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルのタイプを設定する
	 * 
	 * @param type 
	 * @param handle パーティクルハンドル
	 */
	void setType(Physicus::ParticleType type, int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルの設定を取得する
	 * 
	 * @param handle パーティクルハンドル
	 * @return ParticleSetting 
	 */
	Physicus::ParticleSetting getSetting(int handle = PhysicusParticleManager::kCurrentHandle);

	/**
	 * @brief パーティクルの設定を設定する
	 * 
	 * @param setting 設定
	 * @param handle パーティクルハンドル
	 */
	void setSetting(Physicus::ParticleSetting setting, int handle = PhysicusParticleManager::kCurrentHandle);

	private:

	/**
	 * @brief パーティクルの追加
	 * 
	 * @param particle 
	 * @return 生成したインスタンスのポインタ
	 */
	Physicus::Particle* addParticle(Physicus::Particle* particle);

	/**
	 * @brief パーティクルの追加
	 * 
	 * @param touch 
	 * @param setting 
	 * @return Physicus::Object* 
	 */
	Physicus::Particle* addParticle(touch_t touch, Physicus::ParticleSetting setting);

	/**
	 * @brief パーティクルを削除する
	 * 
	 * @param remove_list 削除するパーティクルのリスト
	 */
	void removeParticles(std::vector<Physicus::Particle*> remove_list);

	public:
	
	/**
	 * @brief シングルパーティクルの即時生成
	 * 
	 * @param position 
	 * @param setting 
	 * @return int 
	 */
	int makeParticleSingle(b2Vec2 position, Physicus::ParticleSetting setting);

	/**
	 * @brief パーティクル用のスクリーンを生成する
	 * 
	 * @param setting エフェクトの設定
	 */
	void makeScreen(Effect::LiquidSetting setting);

	/**
	 * @brief 時間を進める
	 * 
	 */
	void timeCalc();

	public:
	
	// MARK: 再定義

	/**
	 * @brief フレームアウトしているかチェックする
	 * 
	 */
	virtual void checkFrameOut();

	/**
	 * @brief 寿命がフレーム数を超えているかチェックする
	 * 
	 */
	virtual void checkLifeEnd();

	/**
	 * @brief タッチによってオブジェクト又はパーティクルを生成する
	 * 
	 * @param touch タッチ情報
	 * @return int 生成されたハンドル。生成されなければ**NULL**を返す
	 */
	virtual int touchCreate(touch_t touch);

	/**
	 * @brief パーティクルを描画する
	 * 
	 */
	virtual void draw();

	/**
	 * @brief 現在生成しているパーティクルを描画する
	 * 
	 */
	virtual void drawEditing();

	/**
	 * @brief パーティクルのフレームを描画する
	 * 
	 */
	virtual void drawDebugFrame();

	/**
	 * @brief 現在生成しているパーティクルのフレームを描画する
	 * 
	 */
	virtual void drawEditingDebugFrame();
};

#endif