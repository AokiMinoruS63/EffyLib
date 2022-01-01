/**
 * @file Lerp.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 線形補完のenum
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LERP_H
#define LERP_H

#ifdef EMSCRIPTEN
#include "../../DxLibForHTML5/include/DxLib.h"
#else
#include "DxLib.h"
#endif

// 線形補完情報
enum Lerp {
	// ネアレストネイバー法で描画(デフォルト)
	kNearest = DX_DRAWMODE_NEAREST,
	// バイリニア法
	kBilinear = DX_DRAWMODE_BILINEAR,
	// 異方性フィルタリング法
	kAnisotropic = DX_DRAWMODE_ANISOTROPIC,
	// それ以外
	kOther = DX_DRAWMODE_OTHER,
	// 描画モードの数
	kNum = DX_DRAWMODE_NUM
};

#endif
