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
	// 最小値
	static const float kMin = 0.0;
	// 4分の1
	static const float kQuarter = 0.25;
	// 中間値
	static const float kHalf = 0.5;
	// 4分の3
	static const float kThreeQuarters = 0.75;
	// 最大値
	static const float kMax = 1.0;

	namespace Angle {
		// 左上角度
		static const float kLeftTop = DX_PI_F / 3.0;
		// 上角度
		static const float kTop = DX_PI_F / 2.0;
		// 右上角度
		static const float kRightTop = DX_PI_F * 2.0 / 3.0;
		// 左角度
		static const float kLeft = 0.0;
		// 右角度
		static const float kRight = DX_PI_F;
		// 左下角度
		static const float kLeftBottom = -DX_PI_F / 3.0;
		// 下角度
		static const float kBottom = -DX_PI_F / 2.0;
		// 右下角度
		static const float kRightBottom = -DX_PI_F * 2.0  / 3.0;

		// 0度
		static const float kZeroDegree = 0.0;
		// 90度
		static const float kNinetyDegree = DX_PI_F * 0.5;
		// 180度
		static const float kOneEightyDegree = DX_PI_F;
		// 270度
		static const float kTwoSeventyDegree = DX_PI_F * 1.5;
		// 360度
		static const float kThreeSixtyDegree = DX_PI_F * 2.0;

		/**
		 * @brief レートから角度への変換
		 * 
		 * @param rate 1.0が最大
		 * @return float 角度(radian)
		 */
		static float fromRate(float rate) {
			return rate * DX_PI_F * 2.0;
		}
	}

	// ベジェ曲線に使用する円の方向
	namespace BezieCircle {
		// 左上
		const float kLeftUp = kMin;
		// 右上
		const float kRightUp = kQuarter;
		// 右下
		const float kRightBottom = kHalf;
		// 左下
		const float kLeftBottom = kThreeQuarters;

		// ベジェの制御点が４つの時に使用する円の係数
		static const float kBezieCircleRate = 0.55228;

		// 円のベジェ曲線における進行率を取得する
		static float bezieRate(float t) {
			if(t < Float::kQuarter) {
				return t * 4.0;
			} else if (t < Float::kHalf) {
				return (t - Float::kQuarter) * 4.0;
			} else if (t < Float::kThreeQuarters) {
				return (t - Float::kHalf) * 4.0;
			} else {
				return (t - Float::kThreeQuarters) * 4.0;
			}
		}

		// 円のベジェ曲線における適用後の回転角度を取得する
		static float plusAngle(float t) {
			if(t < Float::kQuarter) {
				return Angle::kZeroDegree;
			} else if (t < Float::kHalf) {
				return Angle::kNinetyDegree;
			} else if (t < Float::kThreeQuarters) {
				return Angle::kOneEightyDegree;
			} else {
				return Angle::kTwoSeventyDegree;
			}
		}
	};

	/**
	 * @brief 合算値を返す
	 * 
	 * @param vec 
	 * @return float 
	 */
	static float total(std::vector<float> vec) {
		float num = 0;
		for(auto &itr: vec) {
			num += itr;
		}
		return num;
	}

	/**
	 * @brief 長さの等しい節における進行率と進行回数を全体の進行率からセットする
	 * 
	 * @param loopNum 現在何番目の節を進行しているか
	 * @param lastAdvance 進行している最後の節の進行率
	 * @param totalAdvance 全体の進行率。0.0〜1.0
	 * @param size 節の個数
	 */
	static void setAdvance(int& separateNum, float& lastAdvance, float totalAdvance, int size) {
		const float advance = totalAdvance * (float)size;
		separateNum = (int)advance;
		lastAdvance = totalAdvance == kMax ? kMax : fmodf(advance, 1.0 );
	}

	/**
	 * @brief 長さの違う節における進行率と進行回数を全体の進行率からセットする
	 * 
	 * @param separateNum 現在何番目の節を進行しているか
	 * @param lastAdvance 進行している最後の節の進行率
	 * @param sections 節の長さの配列
	 * @param totalAdvance 全体の進行率。0.0〜1.0
	 */
	static void setAdvance(int& separateNum, float& lastAdvance, std::vector<float> sections, float totalAdvance) {
		const float totalLimit = total(sections);
		totalAdvance *= totalLimit;
		separateNum = 0;
		lastAdvance = 0.0;
		for(auto& itr: sections) {
			if(itr > totalAdvance) {
				lastAdvance = totalAdvance / itr;
				break;
			}
			totalAdvance -= itr;
			separateNum++;
		}
	}

	/**
	 * @brief ２つのfloatの間の進行度に応じた値を返す
	 * 
	 * @param s 始点
	 * @param g 終点
	 * @param rate 
	 * @return float 
	 */
	static float between(float s, float g, float rate) {
		return s + (g - s) * rate;
	}

	/**
	 * @brief 2つのfloatの中間地点を返す
	 * 
	 * @param s 始点
	 * @param g 終点
	 * @return float 
	 */
	static float halfWay(float s, float g) {
		return between(s, g, kHalf);
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
		if(angleA < DX_PI_F * -kHalf && angleB > DX_PI_F * kHalf) {
			angleA += DX_PI_F * 2.0;
		} else if(angleB < DX_PI_F * -kHalf && angleA > DX_PI_F * kHalf) {
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
		t = clamp(t, kMin, kMax);
		const float tt = (kMax - t);
		return value[0] * tt * tt + value[1] * 2.0 * t * tt +  value[2] * t * t;
	}

	/**
	 * @brief 4つの制御点のベジェの計算を行う
	 * 
	 * @param value 
	 * @param t 
	 * @return float 
	 */
	static float bezieFourValue(const float value[4], float t) {
		t = clamp(t, kMin, kMax);
		const float tt = (kMax - t);
		return value[0] * tt * tt * tt + value[1] * 3 * t * tt * tt + value[2] * 3 * t * t * tt + value[3] * t * t * t;
	}

	/**
	 * @brief ２つの値を交換する
	 * 
	 * @param val1 
	 * @param val2 
	 */
	static void swap(float* val1, float* val2) {
		const float tmp = *val1;
		*val1 = *val2;
		*val2 = tmp;
	}

	/**
	 * @brief ２つの値の内小さい方を返す
	 * 
	 * @param num1 
	 * @param num2 
	 * @return float 
	 */
	static float smaller(float num1, float num2) {
		if(num1 < num2) {
			return num1;
		}
		return num2;
	}
}

#endif