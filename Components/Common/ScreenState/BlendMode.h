/**
 * @file BlendMode.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BLENDMODE_H
#define BLENDMODE_H

#ifdef EMSCRIPTEN
#include "../../../DxLibForHTML5/include/DxLib.h"
#else
#include <DxLib.h>
#endif

namespace BlendMode {
	static const int kMin = 0;
	static const int kMax = 255;
	enum Mode {
		// ノーブレンド（デフォルト）
		kNoBlend = DX_BLENDMODE_NOBLEND,
		// αブレンド
		kAlpha = DX_BLENDMODE_ALPHA,
		// 加算ブレンド
		kAdd = DX_BLENDMODE_ADD,
		// 減算ブレンド
		kSub = DX_BLENDMODE_SUB,
		// 乗算ブレンド
		kMura = DX_BLENDMODE_MULA,
		// 反転ブレンド
		kInvsrc = DX_BLENDMODE_INVSRC,
		// 乗算済みα用の加算ブレンド
		kPmaAdd = DX_BLENDMODE_PMA_ADD,
		// 乗算済みα用の減算ブレンド
		kPmaSub = DX_BLENDMODE_PMA_SUB,
		// 乗算済みα用の反転ブレンド
		kPmaInvsrc = DX_BLENDMODE_PMA_INVSRC
	};
	
	// ブレンドの設定
	struct Property {
		// ブレンドモードの種類
		int mode;
		// ブレンドモードの強さ
		int prm;
	};

	/**
	 * @brief 初期化
	 * 
	 * @param mode ブレンドモード
	 * @param prm パラメータ(0〜255)
	 * @return Property 
	 */
	inline Property init(Mode mode = kNoBlend, int prm = kMin) {
		return Property { mode, prm };
	}

	/**
	 * @brief 初期化
	 * 
	 * @param mode ブレンドモード
	 * @param rate パラメータ(0.0〜1.0)
	 * @return Property 
	 */
	inline Property init(Mode mode = Mode::kNoBlend, float rate = 0.0) {
		return Property { mode, (int)(rate * 255.0) };
	}
}

#endif