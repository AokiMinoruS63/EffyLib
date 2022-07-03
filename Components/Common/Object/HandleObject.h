/**
 * @file HandleObject.h
 * @brief O(1)するためのオブジェクト
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
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
	 * @brief データを取得する
	 * 
	 * @param handle アクセス用のハンドル
	 * @return T* データ
	 */
	T* getHashData(int handle) {
		return entity_table_.at(handle);
	}


	/**
	 * @brief データをセットする
	 * 
	 * @param data 
	 * @return int ハンドル
	 */
	int setHashData(T* data) {
		entity_table_.push_back(data);
		return entity_table_.size() - 1;
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