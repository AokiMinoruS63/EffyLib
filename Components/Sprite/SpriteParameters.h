/**
 * @file SpriteParameters.h
 * @brief スプライトのパラメータ
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_PARAMETERS_H
#define SPRITE_PARAMETERS_H

/* 現在のパラメータ */
typedef struct {
	/* 基本情報 */
	float x;
	float y;
	float scale;
	float color_r;
	float color_g;
	float color_b;
	float color_a;
	//COLOR_U8 color;
	float angle;
	float rotate_u;
	float rotate_v;
	float before_scale_x;
	float before_scale_y;
	float after_scale_x;
	float after_scale_y;
}sprite_parameters_t;

#endif