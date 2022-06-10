/**
 * @file Int+Extensions.h
 * @brief int型のExtension
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef INT_EXTENSION_H
#define INT_EXTENSION_H

namespace Int {
	/**
	 * @brief 最小値と最大値を適用した値を返す
	 * 
	 * @param value 適用する値
	 * @param min 最小値
	 * @param max 最大値
	 * @return int 
	 */
	inline int clamp(int value, int min, int max) {
		value = value < min ? min : value;
		value = value > max ? max : value;
		return value;
	}
}

#endif