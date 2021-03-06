/**
 * @file ScreenState+Extensions.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SCREEN_STATE_EXTENSION_H
#define SCREEN_STATE_EXTENSION_H

#include "../DxLibWrap.h"

namespace ScreenState {

	// スクリーン
	enum Screen {
		// スクリーンバッファ
		kBack = DX_SCREEN_BACK,
		// 描画用のスクリーン(チラつくため基本直接描画はしない)
		kFront = DX_SCREEN_FRONT
	};

	// フレーム
	struct Frame {
		// 幅
		int width;
		// 高さ
		int height;
		// 深度
		int depth;

		/**
		 * @brief 拡大率を適用したフレームを返す
		 * 
		 * @param scale 
		 * @return Frame 
		 */
		Frame toScale(float scale) {
			return Frame { (int)(((float)this->width) * scale), (int)(((float)this->height) * scale), this->depth};
		}

		/**
		 * @brief 拡大率を適用したフレームを返す
		 * 
		 * @param separateNum 分割数
		 * @return Frame 
		 */
		Frame toScale(int separateNum) {
			return this->toScale(1.0f / ((float)separateNum));
		}
	};
}

#endif