/**
 * @file BloomEffect.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ブルームエフェクト用のスクリーン
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BLOOM_EFFECT_H
#define BLOOM_EFFECT_H

#include "../Common/ScreenState/ScreenStateResume.h"

namespace Effect {
	// ブルームエフェクト用のクラス
	class Bloom {

		// MARK: - 変数
		private:

		// 明るさのクリップの境界値
		int bright_clip_value_;

		// メインで使用するスクリーン
		int current_screen_;
		// 明るさクリップで使用するスクリーン
		int bright_screen_;

		// 4分の1の大きさのガウス用のスクリーン
		int gauss_screen_a4_;
		// 8分の1の大きさのガウス用のスクリーン
		int gauss_screen_a8_;
		// 16分の1の大きさのガウス用のスクリーン
		int gauss_screen_a16_;

		// 明るさ、ブレンド、線形補完情報を一時的に記憶している構造体
		ScreenStateResume screen_state_;

		// MARK: - コンストラクタ・デストラクタ

		public:

		/**
		 * @brief コンストラクタ
		 * 
		 * @param bright_clip_value ブルームを始める明るさの境界値
		 */
		Bloom(int bright_clip_value);

		/**
		 * @brief デストラクタ
		 * 
		 */
		~Bloom();

		// MARK: 描画

		/**
		 * @brief 描画準備
		 * 
		 */
		void preRender();

		/**
		 * @brief 描画処理
		 * 
		 */
		void postRender();
	};
}

#endif