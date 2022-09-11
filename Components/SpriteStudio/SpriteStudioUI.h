/**
 * @file SpriteStudioUI.h
 * @brief SpriteStudioで作成されたUI共通
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_STUDIO_UI_H
#define SPRITE_STUDIO_UI_H

#include <string>
#include <functional>
#include "../UI/UIAnimeState.h"
#include "../UI/UIState.h"
#include "../UI/UIAreaState.h"
#include "../Touch/TouchData.h"
#include "../Common/Shape/Rect.h"
#include "../Common/ScreenState/ScreenStateResume.h"

namespace SpriteStudio {
	class UICommon {

		// MARK: - 変数

		private:

		// 削除待ちの状態なら**true**
		bool _is_waiting_deletion;
		// UIの状態
		UIState _state;
		// アニメーションの状態
		UIAnimeState _anime_state;
		// UI描画に使用するスクリーン
		int _screen = NULL;
		// アニメーション用のカウント
		int _animation_count;
		// SpriteStudioリンク用のアクセスハンドル。座標、スケール、透過率をリンクする
		int _linked_handle;
		// リンク先のアニメーション名
		std::string _linked_animation_name;
		// 条件を成立した時に行うコールバック関数
		std::function<void()> _action;
		// 矩形変数
		Rect _frame = Rect(0, 0, 0, 0);
		// 加算アニメーション用のカウント
		int _add_count;
		// スクリーン再起用のパラメータ
		ScreenStateResume _screen_resume;
		// リピートに要するフレーム
		int _repeat_frame = 0;

		protected:

		bool _is_draw_update;

		// MARK: - 関数

		// MARK: - Getter, Setter

		protected:

		/**
		 * @brief 現在の描画エリアの座標を設定する
		 * 
		 * @param x 
		 * @param y 
		 * @return int 
		 */
		int setFramePotision(float x, float y);

		/**
		 * @brief 現在の描画エリアを取得する
		 * 
		 * @return Rect 
		 */
		Rect getFrame();

		/**
		 * @brief 現在の描画エリアを設定する
		 * 
		 * @param frame 描画範囲
		 * @return int 失敗：kErrorCode, 成功kSuccessCode
		 */
		int setFrame(Rect frame);

		public:

		/**
		 * @brief 領域に入っているかの反応を返す
		 * 
		 * @param touch タッチ情報
		 * @return UIAreaState タップ状態
		 */
		UIAreaState getAreaState(touch_t touch);

		/**
		 * @brief 削除フラグを取得する
		 * 
		 * @return true 
		 * @return false 
		 */
		bool getDeleteFlag();

		/**
		 * @brief 削除フラグを設定する
		 * 
		 * @param is_delete 
		 */
		void setDeleteFlag(bool is_delete);

		/**
		 * @brief UIの状態を取得する
		 * 
		 * @return UIState 
		 */
		UIState getState();

		/**
		 * @brief UIの状態を設定する
		 * 
		 * @param state 
		 */
		void setState(UIState state);

		/**
		 * @brief アニメーションの状態を取得する
		 * 
		 * @return UIAnimeState 
		 */
		UIAnimeState getAnimeState();

		/**
		 * @brief アニメーションの状態を設定する
		 * 
		 * @param anime_state 
		 */
		void setAnimeState(UIAnimeState anime_state);

		/**
		 * @brief リンク先のSpriteStudioPlayerハンドルを取得する
		 * 
		 * @return int 
		 */
		int getLinkedPlayerHandle();

		/**
		 * @brief リンク先のSpriteStudioPlayerハンドルを設定する
		 * 
		 * @param handle 
		 */
		void setLinkedPlayerHandle(int handle);

		/**
		 * @brief リンク先のSpriteStudioPlayerの再生中のアニメーション名を取得する
		 * 
		 * @return std::string 
		 */
		std::string getLinkedAnimationName();

		/**
		 * @brief リンク先のSpriteStudioPlayerの再生中のアニメーションを設定する
		 * 
		 * @param motion_name 
		 */
		void setLinkedAnimationName(std::string animation_name);

		/**
		 * @brief アニメーションの再生カウントを取得する
		 * 
		 * @return int 
		 */
		int getAnimationCount();

		/**
		 * @brief アニメーションの再生カウントを設定する
		 * 
		 * @param animation_count 
		 */
		void setAnimationCount(int animation_count);

		/**
		 * @brief リピート時間を取得する
		 * 
		 * @return int 
		 */
		int getRepeatFrame();

		/**
		 * @brief リピート時間をセットする
		 * 
		 * @param frame 
		 */
		void setRepeatFrame(int frame);

		/**
		 * @brief UIを動かした時の処理を設定する
		 * 
		 * @param action 
		 */
		void setAction(std::function<void()> action);

		// MARK: - 実行処理

		protected:

		/**
		 * @brief 描画準備
		 * 
		 * @return int 
		 */
		int preRenderInit();

		/**
		 * @brief 描画後の後始末
		 * 
		 * @return int 
		 */
		int preRenderEnd();

		public:

		/**
		 * @brief UIを動かした時の処理を実行する
		 * 
		 * @return int 
		 */
		int runAction();

		/**
		 * @brief スクリーンが存在すれば**true**
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isScreen();

		/**
		 * @brief 描画スクリーンを生成する
		 * 
		 * @param width スクリーンの幅
		 * @param height スクリーンの高さ
		 * @return int 
		 */
		int makeScreen(int width, int height);

		/**
		 * @brief スクリーンを開放する
		 * 
		 * @return int 
		 */
		int removeScreen();

		/**
		 * @brief スクリーンの取得
		 * 
		 * @return int 
		 */
		int getScreen();

		// MARK: - override

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