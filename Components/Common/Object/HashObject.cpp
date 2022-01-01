/**
 * @file HashObject.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief O(1)するためのオブジェクト
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "HashObject.h"

// ハッシュ値をセットする
void HashObject::hashInit() {
	// 配列０番目にはNULLをセットする
	hash_table_.push_back(NULL);
}

// ハンドルを取得する
void* HashObject::getDataFromHash(int handle) {
	if(handle < 1 || handle >= hash_table_.size()) {
		return NULL;
	}
	return hash_table_.at(handle);
}

// 現在のハンドルを取得する
int HashObject::getHandle() {
	return hash_table_.size();
}

// データをセットする
int HashObject::setHashData(void* data) {
	hash_table_.push_back(data);
	return hash_table_.size();
}