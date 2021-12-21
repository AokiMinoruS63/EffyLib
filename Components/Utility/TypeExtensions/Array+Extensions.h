/**
 * @file Array+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ARRAY_EXTENSION_H
#define ARRAY_EXTENSION_H

#include <vector>

namespace Array {
	// 配列の未指定を表す定数
	static const int kUnspecified = -1;

	/**
	 * @brief Arrayからstd::vectorへの変換
	 * 
	 * @tparam T 
	 * @param array 
	 * @param size 
	 * @return std::vector<T>* 
	 */
	template <typename T>
	inline std::vector<T> toVector(T* array, int size) {
		std::vector<T> vec;
		for(int i = 0; i < size; i++) {
			vec.push_back(array[i]);
		}
		return vec;
	}

	/**
	 * @brief std::vectorの内容を配列に代入する
	 * 
	 * @tparam T 
	 * @param array 配列
	 */
	template <typename T>
	inline void fromVector(std::vector<T> vec, T* array) {
		for(int i = 0; i < vec.size(); i++) {
			array[i] = vec.at(i);
		}
	}
}

#endif