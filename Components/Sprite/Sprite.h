/**
 * @file Sprite.h
 * @brief スプライトクラス。描画とトランジションや動き、寿命などの計算管理を行う
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

// 現状スプライトで実装するなら、描画メソッド以外にイージング処理などを行いたい
// イージング処理なども自動で計算すると楽。３０秒でイージングで１０％まで縮小など
// つまり、タイムラインが必要
// しかし、タイムラインは可変式である必要がある
// 通常のアニメーションと違い、動的に生成する必要がある。よって、過去のタイムラインは残す必要がないかもしれない。
// イージング処理はstd::vectorの中にタイムラインをスタックとして積んでいく。
// 古くなったら捨てる
// １つのvector型にスタックとして積んでいく関係上、enumでタイプを設定した方が適当だろう。

// スプライトはグローバル座標とローカル座標が存在する
// 基本情報がタイムラインとして必要

#ifndef SPRITE_H
#define SPRITE_H

#include "../Utility/DxLibWrap.h"
#include "SpriteTimeline.h"
#include "SpriteParameters.h"
#include "SpriteCommon.h"
#include "SpriteType.h"

/*
#ifdef EMSCRIPTEN

#include "../../DxLibForHTML5/include/DxLib.h"
#else
#include <DxLib.h>
#endif
*/

// 相互参照
class PhysicsWorld;

class Sprite {
	private:
	/* 共通情報 */
	sprite_common_t common_;

	/* 基本情報 */

	// グローバルのタイムライン
	sprite_timeline_t global_timeline_;
	// グローバルの現在のパラメータ
	sprite_parameters_t global_;
	// ローカルのタイムライン
	sprite_timeline_t local_timeline_;
	// ローカルの現在のパラメータ
	sprite_parameters_t local_;

	// MARK: function

	/**
	 * @brief タイムラインの初期化
	 * 
	 * @param line 
	 */
	void timelineInit(sprite_timeline_t *line);
	
	/**
	 * @brief パラメータの初期化
	 * 
	 * @param parameter 
	 */
	void parametersInit(sprite_parameters_t *parameter);

	public:

	const sprite_common_t defaultCommon = {
		/* img_handle*/	-1,
		/* su 		 */	0.0,
		/* sv 		 */	0.0,
		/* gu 		 */	1.0,
		/* gv 		 */	1.0,
		/* offset_u  */	0.5,
		/* offset_v  */	0.5,
		/* end_frame */	0,
		/* frame 	 */	0,
		/* loop 	 */	true,
		/* stop 	 */	false,
		/* edge_rate */ 0
	};

	Sprite();
	~Sprite();

	/**
	 * @brief 計算処理を行う
	 * 
	 */
	void calc();

	/*
	float x();
	float y();
	float scale();
	float colorR();
	float colorG();
	float colorB();
	float colorA();
	//COLOR_U8 color;
	float angle();
	float rotateU();
	float rotateV();
	float beforeScaleX();
	float beforeScaleY();
	float afterScaleX();
	float afterScaleY();
	*/
	/*
	void getPos(float *x, float *y);
	float getScale();
	void getColor(float *r, float *g, float *b, float *a);
	float getAngle();
	void getRotateUV(float *u, float *v);
	void getBeforeScale(float *beforeScaleX, float *beforeScaleY);
	void getAfterScale(float *afterScaleX, float *afterScaleY);

	void setPos(float x, float y);
	void setScale(float scale);
	void setColor(float r, float g, float b, float a);
	void setAngle(float angle);
	void setRotateUV(float u, float v);
	void setBeforeScale(float beforeScaleX, float beforeScaleY);
	void setAfterScale(float afterScaleX, float afterScaleY);
	*/

	/*
	BMFont_t bm, int id, float x, float y, float scale = 1.0f, int GlobalPos = FALSE, COLOR_U8 color = GetColorU8(255,255,255,255),
	float angle = 0, float rotateU = 0.5f,float rotateV = 0.5f, float beforeScaleX = 1.0f,float beforeScaleY = 1.0f, 
	float afterScaleX = 1.0f,float afterScaleY = 1.0f
	*/
};

#endif