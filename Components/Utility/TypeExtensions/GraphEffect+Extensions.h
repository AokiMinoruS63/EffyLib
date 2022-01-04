/**
 * @file GraphEffect+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../DxLibWrap.h"

namespace GraphEffect {
	enum Filter {
		// モノトーンフィルタ
		kMono = DX_GRAPH_FILTER_MONO,
		// ガウスフィルタ
		kGauss = DX_GRAPH_FILTER_GAUSS,
		// 縮小フィルタ
		kDownScale = DX_GRAPH_FILTER_DOWN_SCALE,
		// 明るさクリップフィルタ
		kBrightClip = DX_GRAPH_FILTER_BRIGHT_CLIP,
		// 指定の明るさ領域を拡大するフィルタ
		kBrightScale = DX_GRAPH_FILTER_BRIGHT_SCALE,
		// 色相・彩度・明度フィルタ
		kHSB = DX_GRAPH_FILTER_HSB,
		// 階調の反転フィルタ
		kInvert = DX_GRAPH_FILTER_INVERT,
		// レベル補正フィルタ
		kLevel = DX_GRAPH_FILTER_LEVEL,
		// ２階調化フィルタ
		kTwoColor = DX_GRAPH_FILTER_TWO_COLOR,
		// グラデーションマップフィルタ
		kGradientMap = DX_GRAPH_FILTER_GRADIENT_MAP,
		// 色の置換
		kReplacement = DX_GRAPH_FILTER_REPLACEMENT,
		// 通常のアルファチャンネル付き画像を乗算済みアルファ画像に変換するフィルタ
		kPremulAlpha = DX_GRAPH_FILTER_PREMUL_ALPHA,
		// 乗算済みα画像を通常のアルファチャンネル付き画像に変換するフィルタ
		kInterpAlpha = DX_GRAPH_FILTER_INTERP_ALPHA,
		// YUVカラーをRGBカラーに変換するフィルタ
		kYuvToRgb = DX_GRAPH_FILTER_YUV_TO_RGB,
		// YUVカラーをRGBカラーに変換するフィルタ( UV成分が Y成分の半分・又は４分の１( 横・縦片方若しくは両方 )の解像度しかない場合用 )
		kY2uv1ToRgb = DX_GRAPH_FILTER_Y2UV1_TO_RGB,
		// YUVカラーをRGBカラーに変換するフィルタ( 且つ右側半分のRの値をアルファ値として扱う )
		kYuvToRgbRra = DX_GRAPH_FILTER_YUV_TO_RGB_RRA,
		// YUVカラーをRGBカラーに変換するフィルタ( UV成分が Y成分の半分・又は４分の１( 横・縦片方若しくは両方 )の解像度しかない場合用 )( 且つ右側半分のRの値をアルファ値として扱う )
		kY2uv1ToRgbRra = DX_GRAPH_FILTER_Y2UV1_TO_RGB_RRA,
		// バイキュービックを使用した拡大・縮小フィルタ
		kBicubicScale = DX_GRAPH_FILTER_BICUBIC_SCALE,
		// Lanczos-3を使用した拡大・縮小フィルタ
		kLanczos3Scale = DX_GRAPH_FILTER_LANCZOS3_SCALE,
		// 明るさクリップフィルタ(乗算済みアルファ画像用)
		kPmaBrightClip = DX_GRAPH_FILTER_PMA_BRIGHT_CLIP,
		// 指定の明るさ領域を拡大するフィルタ(乗算済みアルファ画像用)
		kPmaBrightScale = DX_GRAPH_FILTER_PMA_BRIGHT_SCALE,
		// 色相・彩度・明度フィルタ(乗算済みアルファ画像用)
		kPmaHsb = DX_GRAPH_FILTER_PMA_HSB,
		// 階調の反転フィルタ(乗算済みアルファ画像用)
		kPmaInvert = DX_GRAPH_FILTER_PMA_INVERT,
		// レベル補正フィルタ(乗算済みアルファ画像用)
		kPmaLevel = DX_GRAPH_FILTER_PMA_LEVEL,
		// ２階調化フィルタ(乗算済みアルファ画像用)
		kPmaTwoColor = DX_GRAPH_FILTER_PMA_TWO_COLOR,
		// グラデーションマップフィルタ(乗算済みアルファ画像用)
		kPmaGradientMap = DX_GRAPH_FILTER_PMA_GRADIENT_MAP,
		// 色の置換(乗算済みアルファ画像用)
		kPmaReplacement = DX_GRAPH_FILTER_PMA_REPLACEMENT,
		// フィルタの総数
		kMax = DX_GRAPH_FILTER_NUM
	};

	enum Type {
		// FALSE
		kCmpNever = DX_CMP_NEVER,
		// Src <  Dest		DrawAlpha <  TestParam
		kCmpLess = DX_CMP_LESS,
		// Src == Dest		DrawAlpha == TestParam
		kCmpEqual = DX_CMP_EQUAL,
		// Src <= Dest		DrawAlpha <= TestParam
		kCmpLessQual = DX_CMP_LESSEQUAL,
		// Src >  Dest		DrawAlpha >  TestParam
		kCmpGreater = DX_CMP_GREATER,
		// Src != Dest		DrawAlpha != TestParam
		kCmpNoteQual = DX_CMP_NOTEQUAL,
		// Src >= Dest		DrawAlpha >= TestParam
		kCmpGreaterQual = DX_CMP_GREATEREQUAL,
		// TRUE
		kCmpAlways = DX_CMP_ALWAYS,
		// ( DX_CMP_LESSEQUAL )
		kZcmpDefault = DX_ZCMP_DEFAULT,
		// ( DX_CMP_GREATEREQUAL )
		kZcmpReverse = DX_ZCMP_REVERSE
	};
}