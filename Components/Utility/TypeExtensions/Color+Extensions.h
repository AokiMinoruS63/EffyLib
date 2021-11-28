/**
 * @file Color+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef COLOR_EXTENSION_H
#define COLOR_EXTENSION_H

#include "../../../DxLibForHTML5/include/DxLib.h"

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
	};
}

#endif