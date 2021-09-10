/**
 * @file SpriteTimelineItem.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief モーションの基準点
 * @version 0.1
 * @date 2021-08-30
 * 
 * @copyright Copyright (c) 2021
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
int startType;
// モーションの終了時の補完タイプ
int endType;
}sprite_timeline_item_t;

#endif