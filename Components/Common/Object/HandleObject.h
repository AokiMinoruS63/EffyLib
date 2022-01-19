/**
 * @file HandleObject.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief O(1)するためのオブジェクト
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HANDLE_OBJECT_H
#define HANDLE_OBJECT_H

#include "DeleterBase.h"
#include "../Type/ReturnType.h"
#include <vector>

template<class T>
class HandleObject: public DeleterBase {

	// MARK: - メンバ変数

	private:

	// データの実体が入ったテーブル
	std::vector<T*> entity_table_;

	// MARK: - コンストラクタ・デストラクタ

	protected:

	/**
	 * @brief コンストラクタ
	 * 
	 */
	HandleObject() {
		// 配列０番目にはNULLをセットする
		entity_table_.push_back(NULL);
	}

	/**
	 * @brief デストラクタ
	 * 
	 */
	virtual ~HandleObject() {
		for(auto& itr: entity_table_) {
			if(itr != NULL) {
				// 要素を削除してNULL代入
				delete itr;
				itr = NULL;
			}
		}
	}

	// MARK: - 関数

	protected:

	/**
	 * @brief データを取得する
	 * 
	 * @param handle 
	 * @return T* 
	 */
	T* getDataFromHash(int handle) {
		if(handle < 1 || handle >= entity_table_.size()) {
			return NULL;
		}
		return entity_table_.at(handle);
	}

	/**
	 * @brief 現在のハンドルを取得する
	 * 
	 * @return int 
	 */
	int getHandle() {
		return entity_table_.size();
	}

	/**
	 * @brief データをセットする
	 * 
	 * @param data 
	 * @return int ハンドル
	 */
	int setHashData(T* data) {
		entity_table_.push_back(data);
		return entity_table_.size();
	}

	/**
	 * @brief ハッシュデータを削除する
	 * 
	 * @param handle 
	 * @return int 
	 */
	int removeHashData(int handle) {
		if(handle <= 0 || handle >= entity_table_.size()) {
			return kErrorCode;
		}
		delete entity_table_.at(handle);
		entity_table_.at(handle) = NULL;
		return kSuccessCode;
	}
};

#endif