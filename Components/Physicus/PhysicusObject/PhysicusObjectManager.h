/**
 * @file PhysicusObjectManager.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief オブジェクト管理クラス
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_MANAGER_H
#define PHYSICUS_OBJECT_MANAGER_H

#include "../Common/PhysicusManagerCommon.h"
#include "PhysicusObject.h"

class PhysicusObjectManager: public PhysicusManagerCommon {
	// MARK: 変数
	private:

	// 物理演算を行うボディ配列
	std::vector<Physicus::Object *> objects_;
	// 現在生成・操作を行なっているオブジェクト
	Physicus::Object* current_;
	// オブジェクトの設定
	Physicus::ObjectSetting current_setting_;
	// 数珠繋ぎにする距離
	float tie_loop_range_;

	// MARK: - コンストラクタ・デストラクタ

	public:

	/**
	 * @brief コンストラクタ
	 * 
	 * @param world 物理演算を行うワールド
	 * @param scale ワールドの拡大率
	 * @param alive_area オブジェクトが生存可能なエリア
	 * @param tie_loop_range 数珠繋ぎにする距離
	 */
	PhysicusObjectManager(b2World* world, float scale, Physicus::Frame alive_area, float tie_loop_range = Physicus::Constant::LinksBoardObject::kTieLoopRange);

	/**
	 * @brief デストラクタ
	 * 
	 */
	~PhysicusObjectManager();

	// MARK: 関数
	private:

	/**
	 * @brief オブジェクトの追加
	 * 
	 * @param object 
	 * @return 生成したインスタンスのポインタ
	 */
	Physicus::Object* addObject(Physicus::Object* object);

	/**
	 * @brief オブジェクトの追加
	 * 
	 * @param touch 
	 * @param type 
	 * @param world 
	 * @param scale 
	 * @param setting 
	 * @return Physicus::Object* 
	 */
	Physicus::Object* addObject(touch_t touch, Physicus::ObjectType type, b2World* world, float scale, Physicus::ObjectSetting setting);

	/**
	 * @brief オブジェクトの削除
	 * 
	 * @param remove_list 削除するオブジェクトのリスト
	 */
	void removeObjects(std::vector<Physicus::Object*> remove_list);

	public:

	/**
	 * @brief 線で出来た矩形の即時生成
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @param body_type ボディタイプ
	 * @return int 生成したオブジェクトのハンドル
	 */
	int makeRectangleLine(b2Vec2 start, b2Vec2 end, b2BodyType body_type = b2_staticBody);

	/**
	 * @brief 全てのオブジェクトの描画進行率を設定する
	 * 
	 * @param advance 
	 */
	void setDrawAdvanceAll(float advance);

	// MARK: - 計算

	/**
	 * @brief 時間を進める
	 * 
	 */
	void timeCalc();
	
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
	 * @brief オブジェクト又はパーティクルを描画する
	 * 
	 */
	virtual void draw();

	/**
	 * @brief 現在生成しているオブジェクト又はパーティクルを描画する
	 * 
	 */
	virtual void drawEditing();

	/**
	 * @brief オブジェクト又はパーティクルのフレームを描画する
	 * 
	 */
	virtual void drawDebugFrame();

	/**
	 * @brief 現在生成しているオブジェクト又はパーティクルのフレームを描画する
	 * 
	 */
	virtual void drawEditingDebugFrame();
};

#endif