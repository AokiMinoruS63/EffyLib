/**
 * @file SpriteCommon.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief スプライトのローカル、グローバル問わない共通情報
 * @version 0.1
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPRITE_COMMON_H
#define SPRITE_COMMON_H

typedef struct {
	/* 画像のマップ、ハンドル */
	int imgHandle;
	// テクスチャの座標
	float su,sv,gu,gv;
	// 描画・回転の中心となるオフセット値
	float offsetU,offsetV;
	// 総フレーム数
	int endFrame;
	// 現在のフレーム
	int frame;
	// ループするなら**true**
	bool loop;
	// ストップしているなら**true**
	bool stop;
}sprite_common_t;

#endif