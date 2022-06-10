/**
 * @file PhysicusConstant.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_CONSTANT_H
#define PHYSICUS_CONSTANT_H

namespace Physicus {
	namespace Constant {
		/**
		 * @brief オブジェクト共通の定数
		 * 
		 */
		namespace Object {
			// 線のデフォルトの幅
			constexpr static float kDefaultLineWidth = 10.0;
			// ベジェ曲線の補完係数の初期値(0に近いほど多く行う)
			constexpr static float kBezieRoughness = 0.2;
			// 円のベジェ曲線の補完係数の初期値(0に近いほど多く行う)
			constexpr static float kBezieCircleRoughness = 0.05;
			// デフォルトの角の尖り具合。０に近づくほど丸くなる。1.0で最大で直角になる
			constexpr static float kDefaultSharpness = 0.5;
		}
		/**
		 * @brief 数珠繋ぎのオブジェクトの定数
		 * 
		 */
		namespace LinksBoardObject {
			// 数珠繋ぎにする距離
			constexpr float kTieLoopRange = 5.0;
		}
	}
}

#endif