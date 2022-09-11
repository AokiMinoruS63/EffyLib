/**
 * @file SpriteStudioButton.h
 * @brief SpriteStudioで動くボタン
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_STUDIO_BUTTON_H
#define SPRITE_STUDIO_BUTTON_H

#include "SpriteStudioUI.h"
#include "../UI/UIAnimeState.h"
#include "../Touch/TouchData.h"


namespace SpriteStudio {
	/**
	 * @brief SpriteStudio用のボタン
	 * 
	 */
	class Button: public UICommon {

		// MARK: - 変数

		// SpriteStudioのハンドル
		int _handle;
		// ssae名.
		std::string _ssae_name;
		// アニメーション名リスト
		std::vector<std::string> _anime_list;
		// 再生中のアニメ
		UIAnimeState _play_animation;

		// MARK: - コンストラクタ・デストラクタ

		public:

		/**
		 * @brief コンストラクタ
		 * 
		 * @param path ファイルパス＋ssbpファイル名
		 * @param ssae_name ssaeファイルネーム
		 * @param fadein_animation フェードインアニメーションを行うなら**true**
		 * @param x X座標
		 * @param y Y座標
		 */
		Button(std::string path, std::string ssae_name, bool fadein_animation, float x, float y);

		/**
		 * @brief デストラクタ
		 * 
		 */
		~Button();

		/**
		 * @brief ボタンを走らせる
		 * 
		 * @param touch タッチ情報
		 * @param dt 経過時間（ミリ秒）
		 */
		void run(touch_t touch, float dt);

		/**
		 * @brief ボタンを描画する
		 * 
		 * @return int 
		 */
		int draw();

		/**
		 * @brief アニメーションを変更する
		 * 
		 * @param animation アニメーション
		 * @return int 
		 */
		int changeAnimation(UIAnimeState animation);

		/**
		 * @brief ボタンを通常アニメーションにする
		 * 
		 * @return int 
		 */
		int setNormalAnimation();

		/**
		 * @brief 描画する
		 * 
		 * @return int 
		 */
		int preRender();

		// MARK: - private

		private:

		/**
		 * @brief アニメーションを再生する
		 * 
		 * @param anime_index アニメーションのインデックス
		 * @param loop ループするなら**TRUE**
		 * @param start_frame_no 開始するフレーム
		 * @return int 
		 */
		int play(UIAnimeState anime_index, int loop = TRUE, int start_frame_no = 0);

		// MARK: - override

		public:

		/**
		 * @brief 座標を取得する
		 * 
		 * @param x 
		 * @param y 
		 * @return int 
		 */
		virtual int getPosition(float *x, float *y);

		/**
		 * @brief 座標をセットする
		 * 
		 * @param x 
		 * @param y 
		 * @return int 
		 */
		virtual int setPosition(float x, float y);

		/**
		 * @brief ボタンを描画・判定共に行う状態にする
		 * 
		 * @return int 
		 */
		virtual int setActived();

		/**
		 * @brief ボタンを描画は行うが、判定は行わない状態にする
		 * 
		 * @return int 
		 */
		virtual int setUnresponsive();

		/**
		 * @brief ボタンを使用できない事を示す描画を行い、判定は行わない状態にする
		 * 
		 * @return int 
		 */
		virtual int setDisabled();

		/**
		 * @brief ボタンを描画も判定も行わない状態にする
		 * 
		 * @return int 
		 */
		virtual int setInvisible();
	};
}

#endif
