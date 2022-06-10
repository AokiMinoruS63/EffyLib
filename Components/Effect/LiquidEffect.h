/**
 * @file LiquidEffect.h
 * @brief 流体エフェクト
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef LIQUID_EFFECT_H
#define LIQUID_EFFECT_H

#include "LiquidSetting.h"

class EffectScreen;

namespace Effect {
	class Liquid {
		// MARK: - 変数

		private:
		LONG cnt_;
		// 現在のスクリーン
		int current_screen_;
		// 描画準備用のスクリーン
		int render_screen_[2];
		// 共用で使用される描画用のスクリーン
		EffectScreen* effect_screen_;
		// 設定
		LiquidSetting setting_;

		// MARK: - コンストラクタ・デストラクタ

		public:

		/**
		 * @brief コンストラクタ
		 * 
		 * @param setting セッティング
		 */
		Liquid(LiquidSetting setting);

		/**
		 * @brief Destroy the Liquid object
		 * 
		 */
		~Liquid();

		// MARK: Getter, Setter

		/**
		 * @brief スクリーンのグループを取得する
		 * 
		 * @return int 
		 */
		int getGroup();

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