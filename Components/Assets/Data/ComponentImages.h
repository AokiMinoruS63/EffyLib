/**
 * @file ComponentImages.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
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
		// ゴールドのアイコン、宝石のアイコン
		std::vector<int> icons;

		/* 初期化関数 */

		/**
		 * @brief 画像コンポーネントの初期化
		 * 
		 * @return Images 
		 */
		static Images init() {
			int crayon_images[3];
			std::vector<int> icons;
			LoadDivGraph("Components/Texture/crayon.png", 3, 1, 3, 128, 128, crayon_images);
			icons.push_back( LoadGraph("Components/Texture/gold.png") );
			icons.push_back( LoadGraph("Components/Texture/jewel.png") );
			icons.push_back( LoadGraph("Components/Texture/charcoal.png") );
			return { Array::toVector(crayon_images, 3), icons };
		}
	};
}

#endif