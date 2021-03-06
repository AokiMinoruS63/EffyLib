/**
 * @file SpriteTimeline.h
 * @brief スプライトの座標などタイムラインに表示する情報
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
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
	std::vector<sprite_timeline_item_t> color_r;
	std::vector<sprite_timeline_item_t> color_g;
	std::vector<sprite_timeline_item_t> color_b;
	std::vector<sprite_timeline_item_t> color_a;
	//COLOR_U8 color;
	std::vector<sprite_timeline_item_t> angle;
	std::vector<sprite_timeline_item_t> rotate_u;
	std::vector<sprite_timeline_item_t> rotate_v;
	std::vector<sprite_timeline_item_t> before_scale_x;
	std::vector<sprite_timeline_item_t> before_scale_y;
	std::vector<sprite_timeline_item_t> after_scale_x;
	std::vector<sprite_timeline_item_t> after_scale_y;
}sprite_timeline_t;

#endif