/**
 * @file ComponentAssets.h
 * @brief ライブラリ固有のコンポーネント
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef COMPONENT_ASSETS_H
#define COMPONENT_ASSETS_H

#include "Data/ComponentFonts.h"
#include "Data/ComponentImages.h"

using namespace Components;

class ComponentAssets {
	private:

	/* 変数 */

	// 画像アセット
	Images images_;
	// フォントアセット
	Fonts fonts_;


	/* コンストラクタ・デストラクタ */

	/**
	 * @brief コンストラクタ。アセットの読み込みを行う
	 * 
	 */
	ComponentAssets();

	/**
	 * @brief デストラクタ。アセットの解放を行う
	 * 
	 */
	~ComponentAssets();
	
	public:

	/**
	 * @brief シングルトン
	 * 
	 * @return ComponentAssets* 
	 */
	static ComponentAssets* shared() {
		static ComponentAssets instance;
		return &instance;
	}

	/* Getter, Setter */

	/**
	 * @brief 画像コンポーネントアセットの取得
	 * 
	 * @return Images 
	 */
	Images getImages();

	/**
	 * @brief フォントコンポーネントアセットの取得
	 * 
	 * @return Fonts 
	 */
	Fonts getFonts();
};

#endif