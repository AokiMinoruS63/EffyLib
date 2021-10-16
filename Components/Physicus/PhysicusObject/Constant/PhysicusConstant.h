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
	/**
	 * @brief 物理演算の定数
	 * 
	 */
	namespace Constant {
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