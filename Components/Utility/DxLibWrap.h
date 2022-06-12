/**
 * @file DxLibWrap.h
 * @brief DxLibのラッピング関数群。パーティションとオートスケーリングのズレを解消するため座標取得系と描画系をラッピングしている
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

// 画像描画・座標関係はDxライブラリのものを使うとズレるので専用のものを用意する
// DXライブラリの座標系は左上でそのオフセット値は変更する必要はないにしても
// 縦長の端末などでパーティションを入れる場合があるため、それと分ける必要がある


// 使ってはいけない関数

// GetMousePoint　・・・パディング、ブラウザのオートスケーリングのため座標がズレるため。
// Draw〜         ・・・文字・画像含め描画系全部この関数を使用してはいけない！
// String系     　・・・ビットマップフォントを使用するため、デバッグ以外で使用してはいけない！

#ifndef DXLIB_WRAPPING_H
#define DXLIB_WRAPPING_H

#include <cstdlib>
#include <utility>
#include "../OpenSource/Box2D/Box2D.h"
#include "../Common/Type/Color.h"
#include "../Common/ScreenState/BlendMode.h"
#include "../Common/ScreenState/Lerp.h"
#include "TypeExtensions/ScreenState+Extensions.h"
#include <stdarg.h>
#include "../Common/Type/Vec2.h"
#include "../Common/Type/ReturnType.h"
#include "../Common/Shape/Rect.h"
#include "../Common/Shape/Circle.h"

#ifdef EMSCRIPTEN
#include "ScreenSizeGenerator.h"
#endif

// MARK - 読み込み、マウス、タッチ系

/**
 * @brief バイナリをバッファに丸ごと読み込む
 * 
 * @param filePath 
 * @return void* 読み込んだバッファを返す
 */
void* loadToBuffer(const char* filePath);

/**
 * @brief マウスカーソルの位置を取得する
 * 
 * @param x_buf 取得する現在のマウスのX座標
 * @param y_buf 取得する現在のマウスのY座標
 * @return int 0: 成功、-1: エラー発生
 */
int getMousePoint(int *x_buf, int *y_buf);

/**
 * @brief 	タッチされている箇所の情報を取得する
 * 
 * @param input_no タッチされている箇所の番号
 * @param position_x タッチされている箇所のX座標を保存するint型変数のアドレス
 * @param position_y タッチされている箇所のY座標を保存するint型変数のアドレス
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param id タッチされている箇所のIDを保存するint型変数のアドレス
 * @param device タッチされているデバイス番号を保存するint型変数のアドレス
 * @return int 0: 成功、-1: エラー発生
 */
int getTouchInput(int input_no, int *position_x, int *position_y, 
                    int global_pos = FALSE, int *id = (int *)0, int *device = (int *)0);

/**
 * @brief ミリ秒単位の精度を持つカウンタの現在値を得る
 * 
 * @return int 端末が起動してからの経過時間（ミリ秒）
 */
int getNowCount();

/**
 * @brief １秒を1.0fとした時のカウンタの現在地を得る
 * 
 * @return float 
 */
float getNowCountFloat();

// MARK -  色・スクリーン関係

/**
 * @brief 明るさを取得する
 * 
 * @param color 
 * @return int 0: 成功、-1: エラー発生
 */
int getDrawBright(Color::Color* color);

/**
 * @brief 明るさを設定する
 * 
 * @param color 
 * @return int 
 */
int setDrawBright(Color::Color color);

/**
 * @brief 明るさを設定する
 * 
 * @param color 
 * @return int 
 */
int setDrawBright(int color);

/**
 * @brief ブレンドモードを取得する
 * 
 * @param blend 
 * @return int 
 */
int getDrawBlendMode(BlendMode::Property* blend);

/**
 * @brief ブレンドモードをセットする
 * 
 * @param mode 
 * @param prm 
 * @return int 
 */
int setDrawBlendMode(int mode, int prm);

/**
 * @brief ブレンドモードをセットする
 * 
 * @param blend 
 * @return int 
 */
int setDrawBlendMode(BlendMode::Property blend);

/**
 * @brief スクリーンの幅、高さ、深度を取得する
 * 
 * @return ScreenState 
 */
ScreenState::Frame getScreenState();

/**
 * @brief 画像の幅を返す
 * 
 * @param graph_handle 
 * @return float 
 */
float getImageWidth(int graph_handle);

/**
 * @brief 画像の高さを返す
 * 
 * @param graph_handle 
 * @return int 
 */
float getImageHeight(int graph_handle);

/**
 * @brief 描画対象にできるグラフィックを作成する
 * 
 * @param width 作成するグラフィックの幅
 * @param height 作成するグラフィックの高さ
 * @param use_alpha_channel 作成するグラフィックにアルファチャンネルを付けるかどうか(TRUE: 付ける FALSE: 付けない)
 * @return int int 0: 成功、-1: エラー発生
 */
int makeScreen(int width, int height, int use_alpha_channel = FALSE);

/**
 * @brief スクリーン・画像にフィルターを施す
 * 
 * @param graph_handle 
 * @param filter_type 
 * @param ... 
 * @return int 
 */
int graphFilter(int graph_handle, int filter_type, ...);

/**
 * @brief スクリーン・画像にフィルターを施し、出力先の画像又はスクリーンに出力する
 * 
 * @param graph_handle フィルタを施す画像・スクリーン
 * @param dest_gr_handle 出力先の画像・スクリーン
 * @param filter_type フィルターのタイプ
 * @param ... 
 * @return int 
 */
int graphFilterBlt(int graph_handle, int dest_gr_handle, int filter_type, ...);

/**
 * @brief 線形補完を取得する
 * 
 * @return Lerp 
 */
Lerp getDrawMode();

/**
 * @brief 線形補完を設定する
 * 
 * @param drawMode 
 * @return int 
 */
int setDrawMode(Lerp draw_mode);

/**
 * @brief 描画を行なっているスクリーンを取得する
 * 
 * @return int 
 */
int getDrawScreen();

/**
 * @brief 描画を行うスクリーンをセットする
 * 
 * @param screen 
 * @return int 
 */
int setDrawScreen(int screen);

/**
 * @brief 描画を行うスクリーンをバッファスクリーンにする
 * 
 * @return int 
 */
int setDrawScreenBack();

/**
 * @brief 現在描画を行なっているスクリーンをクリアする
 * 
 * @return int 
 */
int clearDrawScreen();

/**
 * @brief 裏画面を表画面に反映する
 * 
 * @return int 
 */
int screenFrip();

/**
 * @brief RGBから色を取得する
 * 
 * @param red 
 * @param green 
 * @param blue 
 * @return int 
 */
int getColor(int red, int green, int blue);

/**
 * @brief 色をintからRGBに変換する
 * 
 * @param color 
 * @param color_buf 
 * @return int 
 */
int getColor2(unsigned int color, Color::Color* color_buf);

// MARK -  図形描画

/**
 * @brief 線の描画
 * 
 * @param x1 描画する線の起点X座標
 * @param y1 描画する線の起点Y座標
 * @param x2 描画する線の終点X座標
 * @param y2 描画する線の終点Y座標
 * @param color 描く線の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param thickness 線の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawLine( int x1 , int y1 , int x2 , int y2 , unsigned int color, int global_pos = FALSE, int thickness = 1);

/**
 * @brief 線の描画(アンチエイリアス付き)
 * 
 * @param x1 描画する線の起点X座標
 * @param y1 描画する線の起点Y座標
 * @param x2 描画する線の終点X座標
 * @param y2 描画する線の終点Y座標
 * @param color 描く線の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param thickness 線の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawLineAA( int x1 , int y1 , int x2 , int y2 , unsigned int color, int global_pos = FALSE, int thickness = 1);

/**
 * @brief 四角形を描画
 * 
 * @param x1 描画する四角形の左上の頂点X座標
 * @param y1 描画する四角形の左上の頂点Y座標
 * @param x2 描画する四角形の右下＋１の頂点X座標
 * @param y2 描画する四角形の右下＋１の頂点Y座標
 * @param color 描画する四角形の色
 * @param fill_flag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBox(int x1 , int y1 , int x2 , int y2 , unsigned int color , int fill_flag, int global_pos = FALSE);

/**
 * @brief 四角形の描画
 * 
 * @param rect 四角形の形状
 * @param color 描画する四角形の色
 * @param fill_flag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBox(Rect rect, unsigned int color , int fill_flag, int global_pos = FALSE);

/**
 * @brief 四角形を描画(アンチエイリアス付き)
 * 
 * @param x1 描画する四角形の左上の頂点X座標
 * @param y1 描画する四角形の左上の頂点Y座標
 * @param x2 描画する四角形の右下＋１の頂点X座標
 * @param y2 描画する四角形の右下＋１の頂点Y座標
 * @param color 描画する四角形の色
 * @param fill_flag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBoxAA(float x1 , float y1 , float x2 , float y2 , unsigned int color , int fill_flag, int global_pos = FALSE);

/**
 * @brief 頂点座標を全て指定した矩形を描画
 * 
 * @param vertices 頂点４つ（左上、右上、右下、左下）
 * @param color 色
 * @param fill_flag 塗りつぶすなら**true**
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawQuadrangle(Vec2* vertices, unsigned int color, int fill_flag, int global_pos = FALSE);

/**
 * @brief 頂点座標を全て指定した矩形を描画(アンチエイリアス付き)
 * 
 * @param vertices 頂点４つ（左上、右上、右下、左下）
 * @param color 色
 * @param fill_flag 塗りつぶすなら**true**
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawQuadrangleAA(Vec2* vertices, unsigned int color, int fill_flag, int global_pos = FALSE);

/**
 * @brief 四角形を描画(アンチエイリアス付き)
 * 
 * @param rect 四角形の形状
 * @param color 描画する四角形の色
 * @param fill_flag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBoxAA(Rect rect, unsigned int color, int fill_flag, int global_pos = FALSE);

/**
 * @brief 円の描画
 * 
 * @param x 描く円の中心X座標
 * @param y 描く円の中心Y座標
 * @param r 描く円の半径
 * @param color 円の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param fill_flag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircle(int x, int y, int r, unsigned int color, int global_pos = FALSE, int fill_flag = TRUE, int line_chickness = 1);

/**
 * @brief 円の描画
 * 
 * @param circle 円の形状
 * @param color 円の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param fill_flag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircle(Circle circle, unsigned int color, int global_pos = FALSE, int fill_flag = TRUE, int line_chickness = 1);

/**
 * @brief 円の描画(アンチエイリアス付き)
 * 
 * @param x 描く円の中心X座標
 * @param y 描く円の中心Y座標
 * @param r 描く円の半径
 * @param posnum 円を形成する頂点の数
 * @param color 円の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param fill_flag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircleAA(float x, float y, float r, int posnum, unsigned int color, int global_pos = FALSE, int fill_flag = TRUE, 
                    int line_chickness = 1);

/**
 * @brief 円の描画(アンチエイリアス付き)
 * 
 * @param center 描く円の中心座標
 * @param r 描く円の半径
 * @param posnum 円を形成する頂点の数
 * @param color 円の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param fill_flag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircleAA(Vec2 center, float r, int posnum, unsigned int color, int global_pos = FALSE, int fill_flag = TRUE, 
                    int line_chickness = 1);

/**
 * @brief 円の描画(アンチエイリアス付き)
 * 
 * @param circle 円の形状
 * @param posnum 円を形成する頂点の数
 * @param color 円の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param fill_flag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircleAA(Circle circle, int posnum, unsigned int color, int global_pos = FALSE, int fill_flag = TRUE, 
                    int line_chickness = 1);

/**
 * @brief 楕円を描く
 * 
 * @param x 描く楕円の中心X座標
 * @param y 描く楕円の中心Y座標
 * @param rx 描く楕円のＸ軸に対する半径
 * @param ry 描く楕円のＹ軸に対する半径
 * @param color 楕円の色
 * @param fill_flag TRUE(1の意)で楕円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawOval( int x , int y , int rx , int ry , unsigned int color , int fill_flag, 
                int global_pos = FALSE, int line_chickness = 1 );

/**
 * @brief 楕円を描く(アンチエイリアス付き)
 * 
 * @param x 描く楕円の中心X座標
 * @param y 描く楕円の中心Y座標
 * @param rx 描く楕円のＸ軸に対する半径
 * @param ry 描く楕円のＹ軸に対する半径
 * @param color 楕円の色
 * @param fill_flag TRUE(1の意)で楕円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param line_chickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawOvalAA( int x , int y , int rx , int ry , unsigned int color , int fill_flag, int global_pos = FALSE, int line_chickness = 1 );

/**
 * @brief 三角形の描画
 * 
 * @param x1 三角形を描く３つの座標
 * @param y1 三角形を描く３つの座標
 * @param x2 三角形を描く３つの座標
 * @param y2 三角形を描く３つの座標
 * @param x3 三角形を描く３つの座標
 * @param y3 三角形を描く３つの座標
 * @param color 描画に使う色
 * @param fill_flag 三角形の中身を塗りつぶすかフラグ (TRUE:塗りつぶす FALSE:塗りつぶさない)
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color , int fill_flag, int global_pos = FALSE) ;

/**
 * @brief 点を描画する
 * 
 * @param x 点を描画するX座標
 * @param y 点を描画するY座標
 * @param color 描画する点の色
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawPixel( int x , int y , unsigned int color, int global_pos = FALSE) ;

/**
 * @brief 指定点の色を取得
 * 
 * @param x 色を取得する点のX座標
 * @param y 色を取得する点のY座標
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return unsigned int 指定点の色コード
 */
unsigned int getPixel( int x , int y, int global_pos = FALSE);


// MARK -  画像描画

/**
 * @brief メモリに読みこんだグラフィックの描画
 * 
 * @param x グラフィックを描画する領域の左上頂点のX座標
 * @param y グラフィックを描画する領域の左上頂点のY座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawGraph( int x, int y, int graph_handle, int trans_flag, int global_pos = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックのＬＲ反転描画
 * 
 * @param x 描画する反転した画像の左上頂点のX座標
 * @param y 描画する反転した画像の左上頂点のY座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawTurnGraph( int x, int y, int graph_handle, int trans_flag, int global_pos = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックの拡大縮小描画
 * 
 * @param x1 グラフィックを描画する矩形の左上頂点のX座標
 * @param y1 グラフィックを描画する矩形の左上頂点のY座標
 * @param x2 グラフィックを描画する矩形の右下頂点＋１のX座標
 * @param y2 グラフィックを描画する矩形の右下頂点＋１のY座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawExtendGraph( int x1, int y1, int x2, int y2, int graph_handle , int trans_flag, int global_pos = FALSE ) ;


/**
 * @brief メモリに読みこんだグラフィックの回転描画
 * 
 * @param x グラフィックを描画する領域の中心X座標
 * @param y グラフィックを描画する領域の中心Y座標
 * @param ext_rate 拡大率（１.０で等倍）
 * @param angle 描画角度（ラジアン指定）
 * @param graph_handle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param reverce_x_flag X反転フラグ
 * @param reverce_y_flag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph( int x, int y, double ext_rate, double angle, int graph_handle , int trans_flag ,
                     int global_pos = FALSE, int reverce_x_flag = FALSE, int reverce_y_flag = FALSE ) ;

/**
 * @brief メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
 * 
 * @param x 画像を回転描画する画面上の中心X座標
 * @param y 画像を回転描画する画面上の中心Y座標
 * @param cx 画像を回転描画する画像上の中心X座標
 * @param cy 画像を回転描画する画像上の中心Y座標
 * @param ext_rate 拡大率（１.０で等倍）
 * @param angle 描画角度（ラジアン指定）
 * @param graph_handle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param reverce_x_flag X反転フラグ
 * @param reverce_y_flag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph2( int x, int y, int cx, int cy, double ext_rate, double angle, int graph_handle, int trans_flag,
                     int global_pos = FALSE, int reverce_x_flag = FALSE, int reverce_y_flag = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
 * 
 * @param x 画像を回転描画する画面上の中心X座標
 * @param y 画像を回転描画する画面上の中心Y座標
 * @param cx 画像を回転描画する画像上の中心X座標
 * @param cy 画像を回転描画する画像上の中心Y座標
 * @param ext_rate_x 横方向の拡大率（１.０で等倍）
 * @param ext_rate_y 縦方向の拡大率（１.０で等倍）
 * @param angle 描画角度（ラジアン指定）
 * @param graph_handle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param reverce_x_flag X反転フラグ
 * @param reverce_y_flag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph3(int x, int y, int cx, int cy, double ext_rate_x, double ext_rate_y, double angle, 
                    int graph_handle, int trans_flag, int global_pos = FALSE, 
                    int reverce_x_flag = FALSE, int reverce_y_flag = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param x1 左上の頂点のX座標
 * @param y1 左上の頂点のY座標
 * @param x2 右上の頂点のX座標
 * @param y2 右上の頂点のY座標
 * @param x3 右下の頂点のX座標
 * @param y3 右下の頂点のY座標
 * @param x4 左下の頂点のX座標
 * @param y4 左下の頂点のY座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, 
                    int graph_handle , int trans_flag, int global_pos = FALSE);

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param leftUp 左上の座標
 * @param rightUp 右上の座標
 * @param rightBottom 右下の座標
 * @param leftBottom 左下の座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraph( Vec2 leftUp, Vec2 rightUp, Vec2 rightBottom, Vec2 leftBottom,
                    int graph_handle , int trans_flag, int global_pos = FALSE);

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param vec 座標vector（左上、右上、右下、左下）
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraph( std::vector<Vec2> vec,
                    int graph_handle , int trans_flag, int global_pos = FALSE);

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param x1 左上の頂点のX座標
 * @param y1 左上の頂点のY座標
 * @param x2 右上の頂点のX座標
 * @param y2 右上の頂点のY座標
 * @param x3 右下の頂点のX座標
 * @param y3 右下の頂点のY座標
 * @param x4 左下の頂点のX座標
 * @param y4 左下の頂点のY座標
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraphF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, 
                    int graph_handle , int trans_flag, int global_pos = FALSE);

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param pos1 
 * @param pos2 
 * @param pos3 
 * @param pos4 
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraphF( Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4, 
					int graph_handle , int trans_flag, int global_pos = FALSE);

/**
 * @brief 画像を連続して描画する時の画像ハンドルを返す
 * 
 * @param images 
 * @param now_index 
 * @param loop 
 * @param edge_draw 
 * @return int image_handle
 */
int nextImageIndex(std::vector<int> images, int now_index, bool loop, bool edge_draw);

/**
 * @brief ベジェ曲線の次の進行率を返す
 * 
 * @param now_advance 現在の進行率
 * @param roughness どれだけ進行率動かすか
 * @param loop ループなら**true**
 * @param init 
 * @return float 
 */
float nextBezieAdvance(float now_advance, float roughness, bool loop, bool init = false);

/**
 * @brief 制御点が３つのベジェ曲線を画像で描画する
 * 
 * @param left 左側の制御点
 * @param right 右側の制御点
 * @param roughness 粒度（1.0が最大）
 * @param images 描画に使用する画像
 * @param loop ループさせるなら**true**
 * @param edge_draw imagesの最初の画像と最後の画像を使用しないなら**true**
 * @param first_index 最初のインデックス
 * @param advance どこまで描画するか
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 終了後のインデックス
 */
int drawBezie(Vec2 left[3], Vec2 right[3], float roughness, std::vector<int> images, bool loop, bool edge_draw, int first_index, float advance = 1.0, int global_pos = FALSE);

/**
 * @brief グラフィックの指定矩形部分のみを描画
 * 
 * @param dest_x グラフィックを描画するX座標
 * @param dest_y グラフィックを描画するY座標
 * @param scr_x 描画するグラフィック上の描画したい矩形の左上X座標
 * @param scr_y 描画するグラフィック上の描画したい矩形の左上Y座標
 * @param width 描画するグラフィックの幅
 * @param height 描画するグラフィックの高さ
 * @param graph_handle 描画するグラフィックのハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param reverce_x_flag X反転フラグ
 * @param reverce_y_flag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRectGraph( int dest_x, int dest_y, int scr_x, int scr_y, int width, int height, 
                    int graph_handle, int trans_flag, int global_pos = FALSE, 
                    int reverce_x_flag = FALSE, int reverce_y_flag = FALSE ) ;

/**
 * @brief ポリゴンから２D画像を描画します
 * 
 * @param vertex_array ポリゴンの頂点情報配列（３の倍数はあることになる）
 * @param polygon_num ポリゴン（三角形）の個数
 * @param graph_handle 画像ハンドル
 * @param trans_flag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param global_pos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawPolygon2D(DxLib::VERTEX2D* vertex_array, int polygon_num, int graph_handle, int trans_flag, int global_pos = FALSE);

/**
 * @brief メモリに読み込んだ画像を消去する
 * 
 * @param graph_handle 消去する画像
 * @return int 0: 成功、-1: エラー発生
 */
int deleteGraph(int graph_handle);
#endif