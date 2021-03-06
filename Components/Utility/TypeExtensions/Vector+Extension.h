/**
 * @file Vector+Extension.h
 * @brief std::vectorのextension
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef VECTOR_EXTENSION_H
#define VECTOR_EXTENSION_H

#include <vector>

namespace Vector {
	// TODO: remove, 

	/**
	 * @brief vectorが空なら**true**
	 * 
	 * @param vec std::vector
	 * @return true 
	 * @return false 
	 */
	template <typename T>
	inline bool isEmpty(std::vector<T> vec) {
		return vec.empty();
	}

	/**
	 * @brief std::vectorの最初の要素を返す
	 * 
	 * @param vec 
	 * @return 最初の要素
	 */
	/*
	template <typename T>
	T& first(std::vector<T> vec) {
		return vec.begin();
	}
	*/

	/**
	 * @brief std::vectorの末尾の要素を返す
	 * 
	 * @param vec 
	 * @return T* 
	 */
	/*
	template <typename T>
	T& last(std::vector<T> vec) {
		return vec.back();
	}
	*/

	/**
	 * @brief std::vectorに要素を追加する
	 * 
	 * @param vec 
	 * @param t 
	 */
	template <typename T>
	void append(std::vector<T> vec, const T& t) {
		vec.push_back(t);
	}

	// TODO: remove

	/**
	 * @brief 全ての要素を削除する
	 * 
	 * @param vec 
	 */
	template <typename T>
	void removeAll(std::vector<T> vec) {
		vec.clear();
	}
}

#endif