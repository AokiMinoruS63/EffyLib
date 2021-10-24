/**
 * @file ComponentAssets.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief コンポーネントのアセット
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ComponentAssets.h"

// コンストラクタ。アセットの読み込みを行う
ComponentAssets::ComponentAssets() {
	images_ = Components::Images::init();
}

// デストラクタ。アセットの解放を行う
ComponentAssets::~ComponentAssets() {}

/**
 * @brief 画像コンポーネントアセットの取得
 * 
 * @return Images 
 */
Images ComponentAssets::getImages() {
	return images_;
}

/**
 * @brief フォントコンポーネントアセットの取得
 * 
 * @return Fonts 
 */
Fonts ComponentAssets::getFonts() {
	return fonts_;
}