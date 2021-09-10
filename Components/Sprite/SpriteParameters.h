/**
 * @file SpriteParameters.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief スプライトのパラメータ
 * @version 0.1
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2021
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
	float colorR;
	float colorG;
	float colorB;
	float colorA;
	//COLOR_U8 color;
	float angle;
	float rotateU;
	float rotateV;
	float beforeScaleX;
	float beforeScaleY;
	float afterScaleX;
	float afterScaleY;
}sprite_parameters_t;

#endif