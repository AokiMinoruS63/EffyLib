/**
 * @file ComponentAssets.cpp
 * @brief ライブラリ固有のコンポーネントアセット
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
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