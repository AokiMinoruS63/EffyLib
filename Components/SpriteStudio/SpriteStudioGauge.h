/**
 * @file SpriteStudioGauge.h
 * @brief つまみの無いSpriteStidioを使用したゲージクラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_STUDIO_GAUGE_H
#define SPRITE_STUDIO_GAUGE_H

#include "SpriteStudioUI.h"
#include "../UI/UIAnimeState.h"
#include "../Touch/TouchData.h"

namespace SpriteStudio {
	/**
	 * @brief SpriteStudio用のボタン
	 * 
	 */
	class Gauge: public UICommon {

		// MARK: - 変数
		private:

		// 一部のみ描画するメーター部分のss::Playerハンドル
		int _handle_meter;
		// 枠のハンドル
		int _handle_frame;
		// 枠の背景のハンドル
		int _handle_frame_back;
		// マスクハンドル
		int _handle_mask;
		// メーターの値。0.0〜1.0
		float _value;
		// メーター増減時以外にも毎フレーム描画更新するなら**true**
		bool _always_update = false;

		// MARK: - コンストラクタ・デストラクタ

		public:

		/**
		 * @brief コンストラクタ
		 * 
		 * @param path ssbpファイル名
		 * @param ssae_meter メーター部分のssae名
		 * @param ssae_frame フレーム部分のssae名
		 * @param ssae_frame_back フレーム背景部分のssae名
		 * @param ssae_mask マスク部分のssae名
		 * @param x X座標
		 * @param y Y座標
		 * @param default_value メーターの初期値
		 */
		Gauge(std::string path, std::string ssae_meter, std::string ssae_frame, std::string ssae_frame_back, std::string ssae_mask, float x, float y, float default_value);

		/**
		 * @brief デストラクタ
		 * 
		 */
		~Gauge();

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
		 * @brief 描画以外のゲージの更新処理を行う
		 * 
		 * @param dt 経過時間（ミリ秒）
		 */
		void run(float dt);

		/**
		 * @brief ゲージを描画する
		 * 
		 * @return int 
		 */
		int draw();

		private:

		/**
		 * @brief ゲージをスクリーンに描画する
		 * 
		 * @return int 
		 */
		int preRender();

		/**
		 * @brief 描画を更新するアニメーションが存在するかを返す
		 * 
		 * @return true 
		 * @return false 
		 */
		bool updateMotionCheck();

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
