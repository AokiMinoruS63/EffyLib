/**
 * @file SpriteTimeLine.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief スプライトの座標などタイムラインに表示する情報
 * @version 0.1
 * @date 2021-08-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPRITE_TIMELINE_H
#define SPRITE_TIMELINE_H

#include "SpriteTimelineItem.h"
#include <vector>

/* モーションの基準点 */
typedef struct {
	/* 基本情報 */
	std::vector<sprite_timeline_item_t> x;
	std::vector<sprite_timeline_item_t> y;
	std::vector<sprite_timeline_item_t> scale;
	std::vector<sprite_timeline_item_t> colorR;
	std::vector<sprite_timeline_item_t> colorG;
	std::vector<sprite_timeline_item_t> colorB;
	std::vector<sprite_timeline_item_t> colorA;
	//COLOR_U8 color;
	std::vector<sprite_timeline_item_t> angle;
	std::vector<sprite_timeline_item_t> rotateU;
	std::vector<sprite_timeline_item_t> rotateV;
	std::vector<sprite_timeline_item_t> beforeScaleX;
	std::vector<sprite_timeline_item_t> beforeScaleY;
	std::vector<sprite_timeline_item_t> afterScaleX;
	std::vector<sprite_timeline_item_t> afterScaleY;
}sprite_timeline_t;

#endif