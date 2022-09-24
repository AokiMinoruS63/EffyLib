/**
 * @file SpriteStudioSlider.h
 * @brief SpriteStudioのスライダー
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_STUDIO_SLIDER_H
#define SPRITE_STUDIO_SLIDER_H

#include "SpriteStudioUI.h"
#include "../UI/UIAnimeState.h"
#include "../Touch/TouchData.h"

namespace SpriteStudio {
	/**
	 * @brief SpriteStudioのスライダー
	 * 
	 */
	class Slider: public UICommon {

		// MARK: - 変数
		private:

		// 一部のみ描画するメーター部分のss::Playerハンドル
		int _handle_meter;
		// 枠のハンドル
		int _handle_frame;
		// 枠の背景のハンドル
		int _handle_frame_back;
		// つまみのハンドル
		int _handle_thumb;
		// メーターの値。0.0〜1.0
		float _value;
		// メーターの始点
		Vec2 _start;
		// メーターの終点
		Vec2 _end;
		// つまみをドラッグ中なら**true**
		bool _dragging = false;
		// つまみ操作以外にも毎フレーム描画更新するなら**true**
		bool _always_update = false;

		public:

		// MARK: - コンストラクタ・デストラクタ

		/**
		 * @brief コンストラクタ
		 * 
		 * @param path ssbpファイル名
		 * @param ssae_meter メーター部分のssae名
		 * @param ssae_frame フレーム部分のssae名
		 * @param ssae_frame_back フレーム背景部分のssae名
		 * @param ssae_thumb つまみ部分のssae名
		 * @param x X座標
		 * @param y Y座標
		 * @param default_value メーターの初期値
		 */
		Slider(std::string path, std::string ssae_meter, std::string ssae_frame, std::string ssae_frame_back, std::string ssae_thumb, float x, float y, float default_value);

		~Slider();

		/**
		 * @brief スライダーの値（0.0 ~ 1.0）を取得する
		 * 
		 * @return float 
		 */
		float getValue();

		/**
		 * @brief スライダーの値（0.0 ~ 1.0）をセットする
		 * 
		 * @param value 
		 */
		void setValue(float value);

		/**
		 * @brief 毎フレーム描画更新するかどうかのフラグを取得する
		 * 
		 * @return true 
		 * @return false 
		 */
		bool getAlwaysUpdateFlag();

		/**
		 * @brief 毎フレーム描画更新するかどうかのフラグをセットする
		 * 
		 * @param flag 
		 */
		void setAlwaysUpdateFlag(bool flag);

		/**
		 * @brief スライダーを走らせる
		 * 
		 * @param touch タッチ情報
		 * @param dt 経過時間（ミリ秒）
		 */
		void run(touch_t touch, float dt);

		/**
		 * @brief スライダーを描画する
		 * 
		 * @return int 
		 */
		int draw();

		private:

		/**
		 * @brief 描画する
		 * 
		 * @return int 
		 */
		int preRender();

		// MARK: - override

		public:

		/**
		 * @brief 座標をセットする
		 * 
		 * @param x 
		 * @param y 
		 * @return int 
		 */
		virtual int setPosition(float x, float y);

	};
}

#endif
