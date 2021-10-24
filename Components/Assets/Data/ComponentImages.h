/**
 * @file ComponentImages.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef COMPONENT_IMAGES_H
#define COMPONENT_IMAGES_H

#include <vector>
#include "../../Utility/DxLibWrap.h"
#include "../../Utility/TypeExtensions/Array+Extensions.h"

namespace Components {
	struct Images {
		// クレヨンの画像
		std::vector<int> brush_crayon;

		/* 初期化関数 */

		/**
		 * @brief 画像コンポーネントの初期化
		 * 
		 * @return Images 
		 */
		static Images init() {
			int crayon_images[3];
			LoadDivGraph("Components/Texture/crayon.png", 3, 1, 3, 128, 128, crayon_images);
			return { Array::toVector(crayon_images, 3) };
		}
	};
}

#endif