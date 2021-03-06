/**
 * @file Color.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef COLOR_H
#define COLOR_H

#ifdef EMSCRIPTEN
#include "../../../DxLibForHTML5/include/DxLib.h"
#else
#include <DxLib.h>
#endif

namespace Color {
	static const int kWhite = GetColor(255, 255, 255);
	static const int kBlack = GetColor(0, 0, 0);
	static const int kRed = GetColor(255, 0, 0);
	static const int kGreen = GetColor(0, 255, 0);
	static const int kBlue = GetColor(0, 0, 255);
	static const int kYellow = GetColor(255, 255, 0);
	static const int kPurple = GetColor(0, 255, 255);

	static const int kLightBlue = GetColor(157, 204, 224);
	static const int kNigelleBlue = GetColor(0, 133, 201);
	static const int kOrange = GetColor(255, 165, 0);
	static const int kDeepOrange = GetColor(255, 102, 51);
	/**
	 * @brief 色
	 * 
	 */
	struct Color {
		// 赤
		int red;
		// 緑
		int green;
		// 青
		int blue;

		/**
		 * @brief 初期化
		 * 
		 * @param red 
		 * @param green 
		 * @param blue 
		 */
		Color(int red, int green, int blue): red(red), green(green), blue(blue) {}

		/**
		 * @brief 初期化
		 * 
		 */
		Color(): Color(255, 255, 255) {}
	};
}

#endif