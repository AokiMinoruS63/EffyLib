/**
 * @file SpriteType.h
 * @brief スプライトの種類
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_TYPE_H
#define SPRITE_TYPE_H

enum class SpriteType {
	// 縁のみを描画するスプライト
    kStroke,
	// 塗りつぶしを行うスプライト
	kFill,
	// SpriteStudio5のスプライト
	kSpriteStudio5,
	// Spineで出来たスプライト
	kSpine
};

#endif