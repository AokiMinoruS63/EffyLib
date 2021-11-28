/**
 * @file LiquidEffect.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIQUID_EFFECT_H
#define LIQUID_EFFECT_H

class EffectScreen;

namespace Effect {
	class Liquid {
		// MARK: - 変数

		private:
		// スクリーンのグループ
		int group_;
		// 現在のスクリーン
		int current_screen_;
		// 描画準備用のスクリーン
		int render_screen_[2];
		// 共用で使用される描画用のスクリーン
		EffectScreen* effect_screen_;
		// 前景のぼかしの強さ
		int fill_gauss_rate_;
		// 背景のぼかしの強さ
		int edge_gauss_rate_;
		// 前景の仕上げのぼかしの強さ
		int fill_finish_gauss_rate_;
		// 背景の仕上げのぼかしの強さ
		int edge_finish_gauss_rate_;
		// 塗りつぶしの色
		int fill_color_;
		// 線の色
		int edge_color_;

		// MARK: - コンストラクタ・デストラクタ

		public:

		/**
		 * @brief Liquid
		 * 
		 * @param fill_screen 塗りつぶし用のスクリーン
		 * @param edge_screen 縁を描画用のスクリーン
		 * @param gauss_screen ガウス用のスクリーン
		 * @return Liquid 
		 */

		/**
		 * @brief 
		 * 
		 * @param screen 
		 * @return Liquid 
		 */
		Liquid init(EffectScreen *screen);

		/**
		 * @brief Construct a new Liquid object
		 * 
		 * @param screen 
		 * @param group スクリーンのグループ
		 * @param front_color 前景色
		 * @param back_color 背景色
		 * @param front_gauss_rate 前景のガウスの強さ
		 * @param back_gauss_rate 背景のガウスの強さ
		 * @param front_finish_gauss_rate 前景の仕上げのぼかしの強さ
		 * @param back_finish_gauss_rate 背景の仕上げのぼかしの強さ
		 */
		Liquid(EffectScreen *screen, int group, int front_color, int back_color, int front_gauss_rate = 700, int back_gauss_rate = 200, int front_finish_gauss_rate = 0, int back_finish_gauss_rate = 0);

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