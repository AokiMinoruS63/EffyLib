/**
 * @file HashObject.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief O(1)するためのオブジェクト
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>

class HashObject {
	private:

	/**
	 * @brief ハッシュテーブル
	 * 
	 */
	std::vector<void*> hash_table_;

	protected:

	/**
	 * @brief ハッシュ値をセットする
	 * 
	 */
	void hashInit();

	/**
	 * @brief データを取得する
	 * 
	 * @param handle 
	 * @return void* 
	 */
	void* getDataFromHash(int handle);

	/**
	 * @brief 現在のハンドルを取得する
	 * 
	 * @return int 
	 */
	int getHandle();

	/**
	 * @brief データをセットする
	 * 
	 * @param data 
	 * @return int ハンドル
	 */
	int setHashData(void* data);
};
