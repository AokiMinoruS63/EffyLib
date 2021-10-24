/**
 * @file Int+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief intのExtension
 * @version 0.1
 * @date 2021-10-20
 * 
 * @copyright Copyright (c) 2021
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
	static int clamp(int value, int min, int max) {
		value = value < min ? min : value;
		value = value > max ? max : value;
		return value;
	}
}

#endif