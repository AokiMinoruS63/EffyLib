/**
 * @file SpriteTimelineItem.h
 * @brief モーションの基準点
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_TIMELINE_ITEM_H
#define SPRITE_TIMELINE_ITEM_H

/* モーションの基準点 */
typedef struct {
// 基準点の位置
int frame;
// 所持している数値
float num;
// モーションの開始時の補完タイプ
int start_type;
// モーションの終了時の補完タイプ
int end_type;
}sprite_timeline_item_t;

#endif