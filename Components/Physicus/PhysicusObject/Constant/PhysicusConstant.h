/**
 * @file PhysicusConstant.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
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