/**
 * @file ScreenStateResume.h
 * @brief スクリーン情報を一時的に保存するための構造体
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SCREEN_STATE_RESUME_H
#define SCREEN_STATE_RESUME_H

#include "../../Utility/DxLibWrap.h"

struct ScreenStateResume {
	// 保存時のスクリーン
	int screen;
	// バッファとして保存している明るさ情報
	Color::Color buf_bright;

	// バッファとして保存しているブレンド情報
	BlendMode::Property buf_blend;

	// バッファとして保存している線形補完情報
	Lerp lerp;

	// 初期化
	ScreenStateResume(): buf_bright(Color::Color { 255, 255, 255 }), buf_blend(BlendMode::Property { BlendMode::kNoBlend, 0 }), lerp(Lerp::kNearest) {}

	// MARK: - 画面の明るさ情報、ブレンド情報の読み込み・保存

	/**
	 * @brief アクティブなスクリーンの読み込み
	 * 
	 * @return int 
	 */
	int loadScreen();

	/**
	 * @brief 再起用のスクリーンの保存
	 * 
	 * @return int 
	 */
	int saveScreen();

	/**
	 * @brief 明るさ情報の読み込み
	 * 
	 * @return int 
	 */
	int loadBright();

	/**
	 * @brief 明るさ情報の保存
	 * 
	 * @return int 
	 */
	int saveBright();

	/**
	 * @brief ブレンド情報の読み込み
	 * 
	 * @return int 
	 */
	int loadBlend();

	/**
	 * @brief ブレンド情報の保存
	 * 
	 * @return int 
	 */
	int saveBlend();

	/**
	 * @brief 線形補完情報の読み込み
	 * 
	 * @return int 
	 */
	int loadLerp();

	/**
	 * @brief 線形補完情報の保存
	 * 
	 * @return int 
	 */
	int saveLerp();

	/**
	 * @brief スクリーン情報のバッファからの読み込み
	 * 
	 * @param screen_load スクリーンもロードするなら**true**
	 * @return int 
	 */
	int loadScreenState(bool screen_load = false);

	/**
	 * @brief スクリーン情報のバッファへの保存
	 * 
	 * @param screen_save スクリーンもセーブするなら**true**
	 * @return int 
	 */
	int saveScreenState(bool screen_save = false);

	// MARK: - スクリーン画面の初期化

	/**
	 * @brief スクリーン情報の初期化
	 * 
	 * @return int 
	 */
	int initScreenState();
};

#endif
