/**
 * @file LifeObject.h
 * @brief カウントを保持するオブジェクト
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef LIFE_OBJECT_H
#define LIFE_OBJECT_H

#include "../../Utility/DxLibWrap.h"

class LifeObject {
	// MARK: - 変数

	private:

	// 生成されてからのフレーム数
	LONG count_;
	// 寿命を設定するなら**true**
	bool life_destroy_enable_;
	// 寿命を終えていたら**true**
	bool is_life_end_;
	// 寿命のフレーム
	LONG life_span_;
	// 残り寿命のフレーム
	LONG remaining_life_;

	// MARK: - 初期化

	protected:

	/**
	 * @brief フレームを寿命に持つオブジェクトを初期化する
	 * 
	 */
	void lifeObjectInit();

	// MARK: - 関数

	public:

	/**
	 * @brief フレーム数による寿命があるなら**true**
	 * 
	 * @return true 
	 * @return false 
	 */
	bool getLifeDestroyEnable();

	/**
	 * @brief フレーム数による寿命を設定する
	 * 
	 * @param life_destroy_enable 
	 */
	void setLifeDestroyEnable(bool life_destroy_enable);

	/**
	 * @brief フレーム数による寿命を終えていたら**true**
	 * 
	 * @return true 
	 * @return false 
	 */
	bool getLifeEnd();

	/**
	 * @brief フレーム数による寿命を設定する
	 * 
	 * @param life_span 
	 */
	void setLifeSpan(LONG life_span);

	/**
	 * @brief 生成されてからのフレーム数を取得する
	 * 
	 * @return LONG 
	 */
	LONG getCount();

	/**
	 * @brief 生成されてからのフレーム数をセットする
	 * 
	 * @param count 
	 */
	void setCount(LONG count);

	/**
	 * @brief 残り寿命のフレームの取得
	 * 
	 * @return LONG 
	 */
	LONG getRemainingLife();

	/**
	 * @brief カウントを進める
	 * 
	 */
	void timeCalc();
};

#endif