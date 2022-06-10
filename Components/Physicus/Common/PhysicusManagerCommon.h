/**
 * @file PhysicusManagerCommon.h
 * @brief 物理演算のオブジェクト・パーティクルのためのオーバーライド用のクラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_MANAGER_COMMON_H
#define PHYSICUS_MANAGER_COMMON_H

#include "../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include "../../OpenSource/Box2D/Box2D.h"
#include "../../Touch/TouchData.h"
#include "../../Common/Object/HandleObject.h"
#include "PhysicusEvent.h"

class PhysicusManagerCommon {
	// MARK: 定数
	public:

	// 新規生成中のオブジェクト・パーティクルを編集する場合のハンドルは０とする
	static const int kCurrentHandle = 0;

	// MARK: 変数

	protected:
	// 物理演算を行うワールド
	b2World* world_;
	// ワールドの拡大率
	float world_scale_;
	// オブジェクト・パーティクルが生存できるエリア
	Physicus::Frame alive_area_;
	// 所持しているイベント
	std::vector<Physicus::Event*> events;

	// MARK: - 関数

	public:

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