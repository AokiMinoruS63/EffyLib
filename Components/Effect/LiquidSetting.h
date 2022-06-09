/**
 * @file LiquidSetting.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIQUID_SETTING_H
#define LIQUID_SETTING_H

#include "../Common/Type/Color.h"
#include "../Utility/TypeExtensions/Int+Extensions.h"
#include "math.h"
#include "../Common/Constant/MathConstant.h"

namespace Effect {
	struct LiquidSetting {
		// 描画時のグループ
		int group;
		// 塗りつぶし色
		int fill_color;
		// 境界色
		int edge_color;
		// エフェクトのぼかしをするなら**true**
		bool effect;
		// エフェクトのぼかしの色
		int effect_color;
		// エフェクトのブレンドモード
		int effect_blend_mode;
		// エフェクトのサイクル
		int effect_cycle;
		// エフェクトのパラメータの下限値
		int effect_prm_min;
		// エフェクトのパラメータの上限値
		int effect_prm_max;
		// 塗りつぶしのガウスの強さ
		int fill_gauss_rate;
		// 境界のガウスの強さ
		int edge_gauss_rate;
		// 塗りつぶしの仕上げのガウスの強さ
		int fill_finish_gauss_rate;
		// 境界の仕上げのガウスの強さ
		int edge_finish_gauss_rate;

		/**
		 * @brief 初期化
		 * 
		 * @return LiquidSetting 
		 */
		static LiquidSetting init() {
			auto setting = LiquidSetting();
			setting.group = 1;
			setting.fill_color = Color::kNigelleBlue;
			setting.edge_color = Color::kWhite;
			setting.effect = false;
			setting.effect_color = Color::kDeepOrange;
			setting.effect_cycle = 40;
			setting.effect_prm_min = 100;
			setting.effect_prm_max = 255;
			setting.effect_blend_mode = 0;
			setting.fill_gauss_rate = 700;
			setting.edge_gauss_rate = 200;
			setting.fill_finish_gauss_rate = 0;
			setting.edge_finish_gauss_rate = 0;
			return setting;
		}

		/**
		 * @brief ブレンドモードを設定する
		 * 
		 * @param blend_mode 
		 */
		void setBlendMode(int blend_mode) {
			effect_blend_mode = blend_mode;
		}

		/**
		 * @brief ブレンドモードの強さを返す
		 * 
		 * @param cnt 時間経過の変数
		 * @return int 
		 */
		int blendPrm(LONG cnt) {
			int prm = effect_prm_min + sin(kPiFloat * 2.0f / ((float)effect_cycle) * ((float)(effect_prm_max - effect_prm_min)));
			prm = Int::clamp(prm, 0, 255);
			return prm;
		}
	};
}

#endif