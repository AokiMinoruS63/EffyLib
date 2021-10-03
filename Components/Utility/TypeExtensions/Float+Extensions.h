/**
 * @file FloatExtensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief float型のextension
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLOAT_EXTENSION_H
#define FLOAT_EXTENSION_H

namespace Float {
	/**
	 * @brief 2つのfloatの中間地点を返す
	 * 
	 * @param s 始点
	 * @param g 終点
	 * @return float 
	 */
	float halfWay(float s, float g) {
		return s + (g - s) * 0.5;
	}

	/**
	 * @brief ２つの数値の差を返す
	 * 
	 * @param s 
	 * @param g 
	 * @return float 
	 */
	float distance(float s, float g) {
		return g - s < 0 ? s - g : g - s;
	}

	/**
	 * @brief 絶対値を返す
	 * 
	 * @param value 
	 * @return float 
	 */
	float absolute(float value) {
		return value < 0 ? -value : value;
	}
}

#endif