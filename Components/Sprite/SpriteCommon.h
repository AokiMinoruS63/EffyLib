/**
 * @file SpriteCommon.h
 * @brief スプライトのローカル、グローバル問わない共通情報
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_COMMON_H
#define SPRITE_COMMON_H

typedef struct {
	/* 画像のマップ、ハンドル */
	int img_handle;
	// テクスチャの座標
	float su, sv, gu, gv;
	// 描画・回転の中心となるオフセット値
	float offset_u, offset_v;
	// 総フレーム数
	int end_frame;
	// 現在のフレーム
	int frame;
	// ループするなら**true**
	bool loop;
	// ストップしているなら**true**
	bool stop;
	// カーブの尖り具合(0〜1.0。0で半分からカーブ、１で先端)
	float edge_rate;
}sprite_common_t;

#endif