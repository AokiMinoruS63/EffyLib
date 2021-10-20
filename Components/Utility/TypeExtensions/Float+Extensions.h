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

#include "../../Utility/DxLibWrap.h"

namespace Float {

	// floatの極小値
	static const float kMinima = FLT_MIN;

	/**
	 * @brief 2つのfloatの中間地点を返す
	 * 
	 * @param s 始点
	 * @param g 終点
	 * @return float 
	 */
	static float halfWay(float s, float g) {
		return s + (g - s) * 0.5;
	}

	/**
	 * @brief ２つの数値の差を返す
	 * 
	 * @param s 
	 * @param g 
	 * @return float 
	 */
	static float distance(float s, float g) {
		return g - s < 0 ? s - g : g - s;
	}

	/**
	 * @brief 絶対値を返す
	 * 
	 * @param value 
	 * @return float 
	 */
	static float absolute(float value) {
		return value < 0 ? -value : value;
	}

	/**
	 * @brief ２つの角度の差を返す。角度はラジアン（右から時計周りに -PI　〜　PI）
	 * 
	 * @param angleA 
	 * @param angleB 
	 * @return float 
	 */
	static float angleDifference(float angleA, float angleB) {
		if(angleA < DX_PI_F * -0.5 && angleB > DX_PI_F * 0.5) {
			angleA += DX_PI_F * 2.0;
		} else if(angleB < DX_PI_F * -0.5 && angleA > DX_PI_F * 0.5) {
			angleB += DX_PI_F * 2.0;
		}
		float dif = angleB - angleA;
		if(dif < 0) {
			dif *= -1;
		}
		return dif;
	}

	/**
	 * @brief 値に最小値と最大値を設定する
	 * 
	 * @param num 適用する値
	 * @param min 最小値
	 * @param max 最大値
	 * @return float 適用した値
	 */
	static float clamp(float num, float min, float max) {
		num = num > max ? max : num;
		num = num < min ? min : num;
		return num;
	}

	/**
	 * @brief ３つの制御値のベジェの計算を行う
	 * 
	 * @param value 
	 * @param t 
	 * @return float 
	 */
	static float bezieValue(const float value[3], float t) {
		t = clamp(t, 0.0, 1.0);
		const float tt = (1.0 - t);
		return value[0] * tt * tt + value[1] * 2.0 * t * tt +  value[2] * t * t;
	}
}

#endif