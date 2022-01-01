/**
 * @file ScreenStateResume.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief スクリーン情報を一時的に保存するための構造体
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCREEN_STATE_RESUME_H
#define SCREEN_STATE_RESUME_H

#include "../Utility/DxLibWrap.h"

struct ScreenStateResume {
	// バッファとして保存している明るさ情報
	Color::Color buf_bright;

	// バッファとして保存しているブレンド情報
	BlendMode::Property buf_blend;

	// バッファとして保存している線形補完情報
	int liner_inter_polation;

	// MARK: 画面の明るさ情報、ブレンド情報の読み込み・保存

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
	int loadLinerInterPolation();

	/**
	 * @brief 線形補完情報の保存
	 * 
	 * @return int 
	 */
	int saveLinerInterPolation();

	/**
	 * @brief スクリーン情報のバッファからの読み込み
	 * 
	 * @return int 
	 */
	int loadScreenState();

	/**
	 * @brief スクリーン情報のバッファへの保存
	 * 
	 * @return int 
	 */
	int saveScreenState();
};

#endif