/**
 * @file DxLibWrap.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "DxLibWrap.h"
#include <vector>
#include "TypeExtensions.h"
#include <stdarg.h>
#ifdef EMSCRIPTEN
#include "../../DxLibForHTML5/include/DxLib.h"
#else
#include <DxLib.h>
#endif

// バイナリをバッファに丸ごと読み込む
void* loadToBuffer(const char* filePath) {
    void *buffer;
    int fileHandle;
    long fileSize;

     // ファイルのサイズを得る
    fileSize = FileRead_size( filePath ) ;
    // ファイルを格納するメモリ領域の確保
    buffer = malloc( fileSize ) ;
    
    // ファイルを読み込む
    fileHandle = FileRead_open( filePath ) ;
    // ファイルを丸ごとメモリに読み込む
    FileRead_read( buffer, fileSize, fileHandle ) ;
    // ファイルを閉じる
    FileRead_close( fileHandle ) ;
    return std::move(buffer);
}

// マウスカーソルの位置を取得する
int getMousePoint(int *x_buf, int *y_buf) {
    int returnNum = GetMousePoint(x_buf, y_buf);
    #ifdef EMSCRIPTEN
    setBrowserGeneralPos(x_buf, y_buf);
    #else
    #endif
    setScreenPosToLocal(x_buf, y_buf);
    return returnNum;
}

// タッチされている箇所の情報を取得する
int getTouchInput(int input_no, int *position_x, int *position_y, int global_pos, int *id, int *device) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(position_x, position_y);
    return GetTouchInput(input_no, position_x, position_y, id, device);
}
	
// ミリ秒単位の精度を持つカウンタの現在値を得る
int getNowCount() {
	return GetNowCount();
}

// １秒を1.0fとした時のカウンタの現在地を得る
float getNowCountFloat() {
	return ((float)getNowCount()) * 0.001;
}

// 明るさを取得する
int getDrawBright(Color::Color* color) {
	return GetDrawBright(&color->red, &color->green, &color->blue);
}

// 明るさを設定する
int setDrawBright(Color::Color color) {
	return SetDrawBright(color.red, color.green, color.blue);
}

// 明るさを設定する
int setDrawBright(int color) {
	Color::Color col;
	getColor2(color, &col);
	return SetDrawBright(col.red, col.green, col.blue);
}

// ブレンドモードを取得する
int getDrawBlendMode(BlendMode::Property* blend) {
	return GetDrawBlendMode(&blend->mode, &blend->prm);
}

// ブレンドモードをセットする
int setDrawBlendMode(int mode, int prm) {
	return SetDrawBlendMode(mode, prm);
}

// ブレンドモードをセットする
int setDrawBlendMode(BlendMode::Property blend) {
	return SetDrawBlendMode(blend.mode, blend.prm);
}

// スクリーンの幅、高さ、深度を取得する
ScreenState::Frame getScreenState() {
	ScreenState::Frame state;
	GetScreenState(&state.width, &state.height, &state.depth);
	return state;
}

// 画像の幅を返す
float getImageWidth(int graph_handle) {
	int width = -1, height = -1;
	GetGraphSize(graph_handle, &width, &height);
	return (float)width;
}

// 画像の高さを返す
float getImageHeight(int graph_handle) {
	int width = -1, height = -1;
	GetGraphSize(graph_handle, &width, &height);
	return (float)height;
}

// 描画対象にできるグラフィックを作成する
int makeScreen(int width, int height, int use_alpha_channel) {
	return MakeScreen(width, height, use_alpha_channel);
}

/**
 * @brief スクリーン・画像にフィルターを施す
 * 
 * @param graph_handle フィルタをかける画像・スクリーン
 * @param dest_gr_handle 出力先の画像・スクリーン
 * @param filter_type フィルタのタイプ
 * @param output アウトプットをするなら TRUE(1)
 * @param va 可変調引数
 * @return int 
 */
int graphFilterCommon(int graph_handle, int dest_gr_handle, int filter_type, int output, va_list va) {
	// インナーマクロ
	#define SET va_arg( va, int )
	#define FILTER(...) output == FALSE ? GraphFilter(graph_handle, filter_type , __VA_ARGS__) : GraphFilterBlt(graph_handle, dest_gr_handle, filter_type, __VA_ARGS__)
	#define FILTER_EMP output == FALSE ? GraphFilter(graph_handle, filter_type) : GraphFilterBlt(graph_handle, dest_gr_handle, filter_type)
	int return_num = kErrorCode;

	switch(filter_type) {
		// モノトーンフィルタ
		case GraphEffect::kMono:
		{
			int cb = SET;
			int cr = SET;
			return_num = FILTER(cb, cr);
		}
		break;
		// ガウスフィルタ
		case GraphEffect::kGauss:
		{
			int pixel_width = SET;
			int prm = SET;
			return_num = FILTER(pixel_width, prm);
		}
		break;
		// 縮小フィルタ
		case GraphEffect::kDownScale:
		{
			int div_num = SET;
			return_num = FILTER(div_num);
		}
		break;
		// 明るさクリップフィルタ
		case GraphEffect::kBrightClip:
		{
			int cmp_type = SET;
			int cmp_param = SET;
			int clip_fill_flag = SET;
			int clip_fill_color = SET;
			int clip_fill_alpha = SET;
			return_num = FILTER(cmp_type, cmp_param, clip_fill_flag, clip_fill_color, clip_fill_alpha);
		}
		break;
		// 指定の明るさ領域を拡大するフィルタ
		case GraphEffect::kBrightScale:
		{
			int min_bright = SET;
			int max_bright = SET;
			return_num = FILTER(min_bright, max_bright);
		}
		break;
		// 色相・彩度・明度フィルタ
		case GraphEffect::kHSB:
		{
			int hue_type = SET;
			int hue = SET;
			int saturation = SET;
			int bright = SET;
			return_num = FILTER(hue_type, hue, saturation, bright);
		}
		break;
		// 階調の反転フィルタ
		case GraphEffect::kInvert:
			return_num = FILTER_EMP;
		break;
		// レベル補正フィルタ
		case GraphEffect::kLevel:
		{
			int min = SET;
			int max = SET;
			int gamma = SET;
			int after_min = SET;
			int after_max = SET;
			return_num = FILTER(min, max, gamma, after_min, after_max);
		}
		break;
		// ２階調化フィルタ
		case GraphEffect::kTwoColor:
		{
			int threshold = SET;
			int low_color = SET;
			int low_alpha = SET;
			int high_color = SET;
			int high_alpha = SET;
			return_num = FILTER(threshold, low_color, low_alpha, high_color, high_alpha);
		}
		break;
		// グラデーションマップフィルタ
		case GraphEffect::kGradientMap:
		{
			int map_gr_handle = SET;
			int reverse = SET;
			return_num = FILTER(map_gr_handle, reverse);
		}
		break;
		// 色の置換
		case GraphEffect::kReplacement:
		{
			int target_r = SET;
			int target_g = SET;
			int target_b = SET;
			int target_a = SET;
			int r = SET;
			int g = SET;
			int b = SET;
			int a = SET;
			return_num = FILTER(target_r, target_g, target_b, target_a, r, g, b, a);
		}
		break;
		// 通常のアルファチャンネル付き画像を乗算済みアルファ画像に変換するフィルタ
		case GraphEffect::kPremulAlpha:
			return_num = FILTER_EMP;
		break;
		// 乗算済みα画像を通常のアルファチャンネル付き画像に変換するフィルタ
		case GraphEffect::kInterpAlpha:
			return_num = FILTER_EMP;
		break;
		// YUVカラーをRGBカラーに変換するフィルタ
		case GraphEffect::kYuvToRgb:
			return_num = FILTER_EMP;
		break;
		// YUVカラーをRGBカラーに変換するフィルタ( UV成分が Y成分の半分・又は４分の１( 横・縦片方若しくは両方 )の解像度しかない場合用 )
		case GraphEffect::kY2uv1ToRgb:
		{
			int uv_gr_handle = SET;
			return_num = FILTER(uv_gr_handle);
		}
		break;
		// YUVカラーをRGBカラーに変換するフィルタ( 且つ右側半分のRの値をアルファ値として扱う )
		case GraphEffect::kYuvToRgbRra:
			return_num = FILTER_EMP;
		break;
		// YUVカラーをRGBカラーに変換するフィルタ( UV成分が Y成分の半分・又は４分の１( 横・縦片方若しくは両方 )の解像度しかない場合用 )( 且つ右側半分のRの値をアルファ値として扱う )
		case GraphEffect::kY2uv1ToRgbRra:
		{
			int uv_gr_handle = SET;
			return_num = FILTER(uv_gr_handle);
		}
		break;
		// バイキュービックを使用した拡大・縮小フィルタ
		case GraphEffect::kBicubicScale:
		{
			int dest_size_x = SET;
			int des_size_y = SET;
			return_num = FILTER(dest_size_x, des_size_y);
		}
		break;
		// Lanczos-3を使用した拡大・縮小フィルタ
		case GraphEffect::kLanczos3Scale:
		{
			int dest_size_x = SET;
			int des_size_y = SET;
			return_num = FILTER(dest_size_x, des_size_y);
		}
		break;
		// 明るさクリップフィルタ(乗算済みアルファ画像用)
		// kPmaBrightClip = DX_GRAPH_FILTER_PMA_BRIGHT_CLIP,
		// 指定の明るさ領域を拡大するフィルタ(乗算済みアルファ画像用)
		// kPmaBrightScale = DX_GRAPH_FILTER_PMA_BRIGHT_SCALE,
		// 色相・彩度・明度フィルタ(乗算済みアルファ画像用)
		// kPmaHsb = DX_GRAPH_FILTER_PMA_HSB,
		// 階調の反転フィルタ(乗算済みアルファ画像用)
		// kPmaInvert = DX_GRAPH_FILTER_PMA_INVERT,
		// レベル補正フィルタ(乗算済みアルファ画像用)
		// kPmaLevel = DX_GRAPH_FILTER_PMA_LEVEL,
		// ２階調化フィルタ(乗算済みアルファ画像用)
		// kPmaTwoColor = DX_GRAPH_FILTER_PMA_TWO_COLOR,
		// グラデーションマップフィルタ(乗算済みアルファ画像用)
		// kPmaGradientMap = DX_GRAPH_FILTER_PMA_GRADIENT_MAP,
		// 色の置換(乗算済みアルファ画像用)
		// kPmaReplacement = DX_GRAPH_FILTER_PMA_REPLACEMENT,
		default:
		break;
	}

	#undef SET
	#undef FILTER
	#undef FILTER_EMP
	return return_num;
}

// スクリーン・画像にフィルターを施す
int graphFilter(int graph_handle, int filter_type, ...) {
	int return_num = kErrorCode;
	va_list va;
	va_start(va, filter_type);

	return_num = graphFilterCommon(graph_handle, FALSE, filter_type, FALSE, va);
	va_end(va);
	return return_num;
}

// スクリーン・画像にフィルターを施し、出力先の画像又はスクリーンに出力する
int graphFilterBlt(int graph_handle, int dest_gr_handle, int filter_type, ...) {
	int return_num = kErrorCode;
	va_list va;
	va_start(va, filter_type);

	return_num = graphFilterCommon(graph_handle, dest_gr_handle, filter_type, TRUE, va);
	va_end(va);
	return return_num;
}

// 線形補完を取得する
Lerp getDrawMode() {
	const int mode = GetDrawMode();
	switch(mode) {
		case Lerp::kNearest: return Lerp::kNearest;
		case Lerp::kBilinear: return Lerp::kBilinear;
		case Lerp::kAnisotropic: return Lerp::kAnisotropic;
		default: return Lerp::kOther;
	}
	return Lerp::kOther;
}

// 線形補完を設定する
int setDrawMode(Lerp draw_mode) {
	return SetDrawMode(draw_mode);
}

// 描画を行なっているスクリーンを取得する
int getDrawScreen() {
	return GetDrawScreen();
}

// 描画を行うスクリーンをセットする
int setDrawScreen(int screen) {
	return SetDrawScreen(screen);
}

// 描画を行うスクリーンをバッファスクリーンにする
int setDrawScreenBack() {
	return SetDrawScreen(ScreenState::kBack);
}

// 現在描画を行なっているスクリーンをクリアする
int clearDrawScreen() {
	return ClearDrawScreen();
}

// 裏画面を表画面に反映する
int screenFrip() {
	return ScreenFlip();
}

// RGBから色を取得する
int getColor(int red, int green, int blue) {
	return GetColor(red, green, blue);
}

// 色をintからRGBに変換する
int getColor2(unsigned int color, Color::Color* color_buf) {
	return GetColor2(color, &color_buf->red, &color_buf->green, &color_buf->blue);
}

// 線を描画
int drawLine( int x1 , int y1 , int x2 , int y2 , unsigned int color, int global_pos, int thickness) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawLine(x1, y1, x2, y2, color, thickness);
}

// 線を描画(アンチエイリアス付き)
int drawLineAA( int x1 , int y1 , int x2 , int y2 , unsigned int color, int global_pos, int thickness) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawLineAA(x1, y1, x2, y2, color, thickness);
}

// 四角形を描画
int drawBox(int x1 , int y1 , int x2 , int y2 , unsigned int color , int fill_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawBox(x1, y1, x2, y2, color, fill_flag);
}

// 四角形を描画
int drawBox(Rect rect, unsigned int color , int fill_flag, int global_pos) {
	const Vec2 leftTop = rect.leftTop();
	const Vec2 rightBottom = rect.rightBottom();
	return drawBox((int)leftTop.x, (int)leftTop.y, (int)rightBottom.x, (int)rightBottom.y, color, fill_flag, global_pos);
}

// 頂点座標を全て指定した矩形を描画
int drawQuadrangle(Vec2* vertices, unsigned int color, int fill_flag, int global_pos) {
	if(global_pos == FALSE) {
		for(int i = 0; i < 4; i++) {
			setScreenPosToGlobal(&vertices[i].x, &vertices[i].y);
		}
	}
	return DrawQuadrangle(
		vertices[0].x, 
		vertices[0].y, 
		vertices[1].x, 
		vertices[1].y, 
		vertices[2].x, 
		vertices[2].y, 
		vertices[3].x, 
		vertices[3].y, 
		color, 
		fill_flag
		);
}

// 頂点座標を全て指定した矩形を描画(アンチエイリアス付き)
int drawQuadrangleAA(Vec2* vertices, unsigned int color, int fill_flag, int global_pos) {
	if(global_pos == FALSE) {
		for(int i = 0; i < 4; i++) {
			setScreenPosToGlobal(&vertices[i].x, &vertices[i].y);
		}
	}
	return DrawQuadrangleAA(
		vertices[0].x, 
		vertices[0].y, 
		vertices[1].x, 
		vertices[1].y, 
		vertices[2].x, 
		vertices[2].y, 
		vertices[3].x, 
		vertices[3].y, 
		color, 
		fill_flag
		);
}

// 四角形を描画(アンチエイリアス付き)
int drawBoxAA(float x1 , float y1 , float x2 , float y2 , unsigned int color , int fill_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawBoxAA(x1, y1, x2, y2, color, fill_flag);
}

// 四角形を描画(アンチエイリアス付き)
int drawBoxAA(Rect rect, unsigned int color, int fill_flag, int global_pos) {
	const Vec2 leftTop = rect.leftTop();
	const Vec2 rightBottom = rect.rightBottom();
	return drawBoxAA(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y, color, fill_flag, global_pos);
}

// 円の描画
int drawCircle(int x, int y, int r, unsigned int color, int global_pos, int fill_flag, int line_chickness) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawCircle(x, y, r, color, fill_flag, line_chickness);
}

// 円の描画
int drawCircle(Circle circle, unsigned int color, int global_pos, int fill_flag, int line_chickness) {
	return drawCircle(circle.x, circle.y, circle.radius, color, global_pos, fill_flag, line_chickness);
}

// 円の描画(アンチエイリアス付き)
int drawCircleAA(float x, float y, float r, int posnum, unsigned int color, int global_pos, int fill_flag, int line_chickness) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawCircleAA(x, y, r, color, fill_flag, line_chickness);
}

// 円の描画(アンチエイリアス付き)
int drawCircleAA(Vec2 center, float r, int posnum, unsigned int color, int global_pos, int fill_flag, int line_chickness) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&center.x, &center.y);
    return drawCircleAA(center.x, center.y, r, posnum, color, global_pos, fill_flag, line_chickness);
}

// 円の描画(アンチエイリアス付き)
int drawCircleAA(Circle circle, int posnum, unsigned int color, int global_pos, int fill_flag, int line_chickness) {
	return drawCircleAA(circle.x, circle.y, circle.radius, posnum, color, global_pos, fill_flag, line_chickness);
}

// 楕円を描く
int drawOval( int x , int y , int rx , int ry , unsigned int color , int fill_flag, int global_pos, int line_chickness ) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawOval(x, y, rx, ry, color, fill_flag, line_chickness);
}

// 楕円を描く(アンチエイリアス付き)
int drawOvalAA( int x , int y , int rx , int ry , unsigned int color , int fill_flag, int global_pos, int line_chickness ) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawOvalAA(x, y, rx, ry, color, fill_flag, line_chickness);
}

// 三角形の描画
int drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color , int fill_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
    }
    return DrawTriangle(x1, y1, x2, y2, x3, y3, color, fill_flag);
}

// 三角形の描画(アンチエイリアス効果付き)
int drawTriangleAA( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color , int fill_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
    }
    return DrawTriangleAA(x1, y1, x2, y2, x3, y3, color, fill_flag);
}

// 点を描画する
int drawPixel( int x , int y , unsigned int color, int global_pos) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawPixel(x, y, color);
}

// 指定点の色を取得
unsigned int getPixel( int x , int y, int global_pos) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return GetPixel(x, y);
}

// メモリに読みこんだグラフィックの描画
int drawGraph( int x, int y, int graph_handle, int trans_flag, int global_pos) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawGraph(x, y, graph_handle, trans_flag);
}

// メモリに読みこんだグラフィックのＬＲ反転描画
int drawTurnGraph( int x, int y, int graph_handle, int trans_flag, int global_pos) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawTurnGraph(x, y, graph_handle, trans_flag);
}

// メモリに読みこんだグラフィックの拡大縮小描画
int drawExtendGraph( int x1, int y1, int x2, int y2, int graph_handle , int trans_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawExtendGraph(x1, y1, x2, y2, graph_handle, trans_flag);
} 

 // メモリに読みこんだグラフィックの回転描画
int drawRotaGraph( int x, int y, double ext_rate, double angle, int graph_handle , int trans_flag , int global_pos, int reverce_x_flag, int reverce_y_flag ) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph(x, y, ext_rate, angle, graph_handle, trans_flag, reverce_x_flag, reverce_y_flag);
}

// メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
int drawRotaGraph2( int x, int y, int cx, int cy, double ext_rate, double angle, int graph_handle, int trans_flag, int global_pos, int reverce_x_flag, int reverce_y_flag) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph2(x, y, cx, cy, ext_rate, angle, graph_handle, trans_flag, reverce_x_flag, reverce_y_flag);
}

// メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
int drawRotaGraph3(int x, int y, int cx, int cy, double ext_rate_x, double ext_rate_y, double angle, int graph_handle, int trans_flag, int global_pos, int reverce_x_flag, int reverce_y_flag) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph3(x, y, cx, cy, ext_rate_x, ext_rate_y, angle, graph_handle, trans_flag, reverce_x_flag, reverce_y_flag);
}

// メモリに読みこんだグラフィックの自由変形描画
int drawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int graph_handle , int trans_flag, int global_pos) {
    if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
        setScreenPosToGlobal(&x4, &y4);
    }
    return DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, graph_handle, trans_flag);
}

// メモリに読みこんだグラフィックの自由変形描画
int drawModiGraph( Vec2 leftUp, Vec2 rightUp, Vec2 rightBottom, Vec2 leftBottom, int graph_handle , int trans_flag, int global_pos) {
    return drawModiGraph((int)leftUp.x, (int)leftUp.y, (int)rightUp.x, (int)rightUp.y, (int)rightBottom.x, (int)rightBottom.y, (int)leftBottom.x, (int)leftBottom.y, graph_handle, trans_flag, global_pos);
}

// メモリに読みこんだグラフィックの自由変形描画
int drawModiGraph( std::vector<Vec2> vec, int graph_handle , int trans_flag, int global_pos) {
	if(vec.size() < 4) {
		return kErrorCode;
	}
	return drawModiGraph(vec.at(0), vec.at(1), vec.at(2), vec.at(3), graph_handle, trans_flag, global_pos);
}

// メモリに読みこんだグラフィックの自由変形描画(float)
int drawModiGraphF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int graph_handle , int trans_flag, int global_pos) {
	if (global_pos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
        setScreenPosToGlobal(&x4, &y4);
    }
    return DrawModiGraphF(x1, y1, x2, y2, x3, y3, x4, y4, graph_handle, trans_flag);
}

// メモリに読みこんだグラフィックの自由変形描画(float,引数がVec2)
int drawModiGraphF( Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4, int graph_handle , int trans_flag, int global_pos) {
	return drawModiGraphF(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, pos4.x, pos4.y, graph_handle, trans_flag, global_pos);
}

// 画像を連続して描画する時の画像ハンドルを返す
int nextImageIndex(std::vector<int> images, int now_index, bool loop, bool edge_draw) {
	const int countMin = edge_draw || IsEmpty(images) ? 0 : 1;
	const int countMax = Int::clamp(edge_draw ? images.size() - 1 : images.size() - 2, 0, images.size());
	int index;
	// 初期値
	if(now_index == Array::kUnspecified) {
		index = loop ? countMin : countMax;
	} else {
		index = Int::clamp(now_index, countMin, countMax);
		if(loop) {
			index++;
			if(index > countMax) {
				index = countMin;
			}
		} else {
			index--;
			if(index < 0) {
				return -1;
			}
		}
	}
	return index;
}

// ベジェ曲線の次の進行率を返す
float nextBezieAdvance(float now_advance, float roughness, bool loop, bool init) {
	roughness = Float::clamp(roughness, 0.0, 1.0);
	if(init) {
		return loop ? 0.0 : 1.0 - roughness;
	}
	float t = loop ? now_advance + roughness : now_advance - roughness ;
	return Float::clamp(t, 0.0, 1.0);
}

// 制御点が３つのベジェ曲線を画像で描画する
int drawBezie(Vec2 left[3], Vec2 right[3], float roughness, std::vector<int> images, bool loop, bool edge_draw, int first_index, float advance, int global_pos) {
	if(advance == Float::kMin) {
		return first_index;
	}
	float t = nextBezieAdvance(0.0, roughness, loop, true);
	const int imgCountMin = edge_draw || images.size() < 2 ? 0 : 1;
	const int imgCountMax = Int::clamp(edge_draw ? images.size() - 1 : images.size() - 2, 0, images.size());
	int imgIndex = first_index == Array::kUnspecified ? nextImageIndex(images, Array::kUnspecified, loop, edge_draw) : first_index;
	float next;
	bool end = false;
	// 左の始点、終点、右の始点、終点
	Vec2 so, si, go, gi;
	roughness = Float::clamp(roughness, 0.0, 1.0);
	next = loop ? Float::clamp(t + roughness, 0.0, 1.0) : 1.0;
	if(advance < next) {
		next = advance;
	}
	while(!end) {
		so = B2Vec2::bezieValue(left, t);
		si = B2Vec2::bezieValue(right, t);
		go = B2Vec2::bezieValue(left, next);
		gi = B2Vec2::bezieValue(right, next);
		
		drawModiGraphF(so, si, gi, go, images.at(imgIndex), TRUE, global_pos);
		// 次の画像ハンドルを決める
		imgIndex = nextImageIndex(images, imgIndex, loop, edge_draw);
		// 根本まで来ていたら描画しない
		if(!loop && imgIndex < imgCountMin) {
			break;
		}
		// 最後まで描画したら終了する
		if(t <= 0.0 - Float::kMinima || next >= 1.0 + Float::kMinima) {
			end = true;
		}
		// 進行率を決める
		t = nextBezieAdvance(t, roughness, loop);
		next = nextBezieAdvance(t, roughness, loop);
		if(advance < t) {
			return imgIndex;
		} else if(advance < next) {
			next = advance;
		}
	}
	return imgIndex;
}

// グラフィックの指定矩形部分のみを描画
int drawRectGraph( int dest_x, int dest_y, int scr_x, int scr_y, int width, int height, 
                    int graph_handle, int trans_flag, int global_pos, 
                    int reverce_x_flag, int reverce_y_flag ) {
    if (global_pos == FALSE)
        setScreenPosToGlobal(&dest_x, &dest_y);
    return DrawRectGraph(dest_x, dest_y, scr_x, scr_y, width, height, graph_handle, trans_flag, reverce_x_flag, reverce_y_flag);
}

// ポリゴンから２D画像を描画します
int drawPolygon2D(DxLib::VERTEX2D *vertex_array, int polygon_num, int graph_handle, int trans_flag, int global_pos) {
    if (global_pos == FALSE) {
        int x, y;
        float fx, fy;
        for(int i=0;i<polygon_num*3;i++) {
            x = (int)vertex_array[i].pos.x;
            y = (int)vertex_array[i].pos.y;
            fx = vertex_array[i].pos.x - (float)x;
            fy = vertex_array[i].pos.y - (float)y;
            setScreenPosToGlobal(&x, &y);
            vertex_array[i].pos = VGet(((float)x) + fx, ((float)y) + fy, 0.0);

        }
    }
    return DrawPolygon2D(vertex_array, polygon_num, graph_handle, trans_flag);
}

// メモリに読み込んだ画像を消去する
int deleteGraph(int graph_handle) {
	return DeleteGraph(graph_handle);
}