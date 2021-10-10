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
	const static int white = GetColor(255, 255, 255);
	const static int black = GetColor(0, 0, 0);
	const static int red = GetColor(255, 0, 0);
	const static int green = GetColor(0, 255, 0);
	const static int blue = GetColor(0, 0, 255);
	const static int yellow = GetColor(255, 255, 0);
	const static int purple = GetColor(0, 255, 255);
}

#endif