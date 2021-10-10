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
	const static int kWhite = GetColor(255, 255, 255);
	const static int kBlack = GetColor(0, 0, 0);
	const static int kRed = GetColor(255, 0, 0);
	const static int kGreen = GetColor(0, 255, 0);
	const static int kBlue = GetColor(0, 0, 255);
	const static int kYellow = GetColor(255, 255, 0);
	const static int kPurple = GetColor(0, 255, 255);
}

#endif