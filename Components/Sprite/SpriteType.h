/**
 * @file SpriteType.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief スプライトの種類
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
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