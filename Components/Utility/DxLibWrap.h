/**
 * @file DxLibWrap.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief DxLibのラッピング関数群。パーティションとオートスケーリングのズレを解消するため座標取得系と描画系をラッピングしている
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
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

#ifdef EMSCRIPTEN
#include "../../DxLibForHTML5/include/DxLib.h"
#include "ScreenSizeGenerator.h"
#else
#include <DxLib.h>
#endif
#include <cstdlib>
#include <utility>
#include "../OpenSource/Box2D/box2d/box2d.h"

/* 読み込み、マウス、タッチ系 */

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
 * @param XBuf 取得する現在のマウスのX座標
 * @param YBuf 取得する現在のマウスのY座標
 * @return int 0: 成功、-1: エラー発生
 */
int getMousePoint(int *XBuf, int *YBuf);

/**
 * @brief 	タッチされている箇所の情報を取得する
 * 
 * @param InputNo タッチされている箇所の番号
 * @param PositionX タッチされている箇所のX座標を保存するint型変数のアドレス
 * @param PositionY タッチされている箇所のY座標を保存するint型変数のアドレス
 * @param ID タッチされている箇所のIDを保存するint型変数のアドレス
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param Device タッチされているデバイス番号を保存するint型変数のアドレス
 * @return int 0: 成功、-1: エラー発生
 */
int getTouchInput(int InputNo, int *PositionX, int *PositionY, 
                    int GlobalPos = FALSE, int *ID = (int *)0, int *Device = (int *)0);

/* 図形描画 */

/**
 * @brief 線の描画
 * 
 * @param x1 描画する線の起点X座標
 * @param y1 描画する線の起点Y座標
 * @param x2 描画する線の終点X座標
 * @param y2 描画する線の終点Y座標
 * @param Color 描く線の色
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param Thickness 線の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawLine( int x1 , int y1 , int x2 , int y2 , unsigned int Color, int GlobalPos = FALSE, int Thickness = 1);

/**
 * @brief 線の描画(アンチエイリアス付き)
 * 
 * @param x1 描画する線の起点X座標
 * @param y1 描画する線の起点Y座標
 * @param x2 描画する線の終点X座標
 * @param y2 描画する線の終点Y座標
 * @param Color 描く線の色
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param Thickness 線の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawLineAA( int x1 , int y1 , int x2 , int y2 , unsigned int Color, int GlobalPos = FALSE, int Thickness = 1);

/**
 * @brief 四角形を描画
 * 
 * @param x1 描画する四角形の左上の頂点X座標
 * @param y1 描画する四角形の左上の頂点Y座標
 * @param x2 描画する四角形の右下＋１の頂点X座標
 * @param y2 描画する四角形の右下＋１の頂点Y座標
 * @param Color 描画する四角形の色
 * @param FillFlag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBox(int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag, int GlobalPos = FALSE);

/**
 * @brief 四角形を描画(アンチエイリアス付き)
 * 
 * @param x1 描画する四角形の左上の頂点X座標
 * @param y1 描画する四角形の左上の頂点Y座標
 * @param x2 描画する四角形の右下＋１の頂点X座標
 * @param y2 描画する四角形の右下＋１の頂点Y座標
 * @param Color 描画する四角形の色
 * @param FillFlag 四角の中身を塗りつぶすか、のフラグ。TRUEで塗り
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawBoxAA(int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag, int GlobalPos = FALSE);

/**
 * @brief 円の描画
 * 
 * @param x 描く円の中心X座標
 * @param y 描く円の中心Y座標
 * @param r 描く円の半径
 * @param Color 円の色
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param FillFlag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param LineChickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircle(int x, int y, int r, unsigned int Color, int GlobalPos = FALSE, int FillFlag = TRUE, int LineChickness = 1);

/**
 * @brief 円の描画(アンチエイリアス付き)
 * 
 * @param x 描く円の中心X座標
 * @param y 描く円の中心Y座標
 * @param r 描く円の半径
 * @param Color 円の色
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param FillFlag TRUE(1の意)で円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param LineChickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawCircleAA(int x, int y, int r, unsigned int Color, int GlobalPos = FALSE, int FillFlag = TRUE, 
                    int LineChickness = 1);

/**
 * @brief 楕円を描く
 * 
 * @param x 描く楕円の中心X座標
 * @param y 描く楕円の中心Y座標
 * @param rx 描く楕円のＸ軸に対する半径
 * @param ry 描く楕円のＹ軸に対する半径
 * @param Color 楕円の色
 * @param FillFlag TRUE(1の意)で楕円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param LineChickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawOval( int x , int y , int rx , int ry , unsigned int Color , int FillFlag, 
                int GlobalPos = FALSE, int LineChickness = 1 );

/**
 * @brief 楕円を描く(アンチエイリアス付き)
 * 
 * @param x 描く楕円の中心X座標
 * @param y 描く楕円の中心Y座標
 * @param rx 描く楕円のＸ軸に対する半径
 * @param ry 描く楕円のＹ軸に対する半径
 * @param Color 楕円の色
 * @param FillFlag TRUE(1の意)で楕円の中身も塗りつぶし、FALSE(0の意)で輪郭のみ
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param LineChickness 縁の太さ
 * @return int 0: 成功、-1: エラー発生
 */
int drawOvalAA( int x , int y , int rx , int ry , unsigned int Color , int FillFlag, int GlobalPos = FALSE, int LineChickness = 1 );

/**
 * @brief 三角形の描画
 * 
 * @param x1 三角形を描く３つの座標
 * @param y1 三角形を描く３つの座標
 * @param x2 三角形を描く３つの座標
 * @param y2 三角形を描く３つの座標
 * @param x3 三角形を描く３つの座標
 * @param y3 三角形を描く３つの座標
 * @param Color 描画に使う色
 * @param FillFlag 三角形の中身を塗りつぶすかフラグ (TRUE:塗りつぶす FALSE:塗りつぶさない)
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color , int FillFlag, int GlobalPos = FALSE) ;

/**
 * @brief 点を描画する
 * 
 * @param x 点を描画するX座標
 * @param y 点を描画するY座標
 * @param Color 描画する点の色
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawPixel( int x , int y , unsigned int Color, int GlobalPos = FALSE) ;

/**
 * @brief 指定点の色を取得
 * 
 * @param x 色を取得する点のX座標
 * @param y 色を取得する点のY座標
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return unsigned int 指定点の色コード
 */
unsigned int getPixel( int x , int y, int GlobalPos = FALSE);


/* 画像描画 */

/**
 * @brief メモリに読みこんだグラフィックの描画
 * 
 * @param x グラフィックを描画する領域の左上頂点のX座標
 * @param y グラフィックを描画する領域の左上頂点のY座標
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawGraph( int x, int y, int GrHandle, int TransFlag, int GlobalPos = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックのＬＲ反転描画
 * 
 * @param x 描画する反転した画像の左上頂点のX座標
 * @param y 描画する反転した画像の左上頂点のY座標
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawTurnGraph( int x, int y, int GrHandle, int TransFlag, int GlobalPos = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックの拡大縮小描画
 * 
 * @param x1 グラフィックを描画する矩形の左上頂点のX座標
 * @param y1 グラフィックを描画する矩形の左上頂点のY座標
 * @param x2 グラフィックを描画する矩形の右下頂点＋１のX座標
 * @param y2 グラフィックを描画する矩形の右下頂点＋１のY座標
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag, int GlobalPos = FALSE ) ;


/**
 * @brief メモリに読みこんだグラフィックの回転描画
 * 
 * @param x グラフィックを描画する領域の中心X座標
 * @param y グラフィックを描画する領域の中心Y座標
 * @param ExtRate 拡大率（１.０で等倍）
 * @param Angle 描画角度（ラジアン指定）
 * @param GrHandle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param TurnFlag 画像の左右反転を行うか、のフラグ(FALSEで普通に描画 TRUEで反転)
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param ReverceXFlag X反転フラグ
 * @param ReverceYFlag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag,
                     int GlobalPos = FALSE, int ReverceXFlag = FALSE, int ReverceYFlag = FALSE ) ;

/**
 * @brief メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
 * 
 * @param x 画像を回転描画する画面上の中心X座標
 * @param y 画像を回転描画する画面上の中心Y座標
 * @param cx 画像を回転描画する画像上の中心X座標
 * @param cy 画像を回転描画する画像上の中心Y座標
 * @param ExtRate 拡大率（１.０で等倍）
 * @param Angle 描画角度（ラジアン指定）
 * @param GrHandle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param TurnFlag 画像の左右反転を行うか、のフラグ(FALSEで普通に描画 TRUEで反転)
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param ReverceXFlag X反転フラグ
 * @param ReverceYFlag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag,
                     int TurnFlag, int GlobalPos = FALSE, int ReverceXFlag = FALSE, int ReverceYFlag = FALSE) ;

/**
 * @brief メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
 * 
 * @param x 画像を回転描画する画面上の中心X座標
 * @param y 画像を回転描画する画面上の中心Y座標
 * @param cx 画像を回転描画する画像上の中心X座標
 * @param cy 画像を回転描画する画像上の中心Y座標
 * @param ExtRateX 横方向の拡大率（１.０で等倍）
 * @param ExtRateY 縦方向の拡大率（１.０で等倍）
 * @param Angle 描画角度（ラジアン指定）
 * @param GrHandle 描画するグラフィックの識別番号（グラフィックハンドル）
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param TurnFlag 画像の左右反転を行うか、のフラグ(FALSEで普通に描画 TRUEで反転)
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param ReverceXFlag X反転フラグ
 * @param ReverceYFlag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRotaGraph3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, 
                    int GrHandle, int TransFlag, int TurnFlag, int GlobalPos = FALSE, 
                    int ReverceXFlag = FALSE, int ReverceYFlag = FALSE) ;

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
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, 
                    int GrHandle , int TransFlag, int GlobalPos = FALSE);

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
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraphF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, 
                    int GrHandle , int TransFlag, int GlobalPos = FALSE);

/**
 * @brief メモリに読みこんだグラフィックの自由変形描画
 * 
 * @param pos1 
 * @param pos2 
 * @param pos3 
 * @param pos4 
 * @param GrHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawModiGraphF( b2Vec2 pos1, b2Vec2 pos2, b2Vec2 pos3, b2Vec2 pos4, 
					int GrHandle , int TransFlag, int GlobalPos = FALSE);

/**
 * @brief 画像を連続して描画する時の画像ハンドルを返す
 * 
 * @param images 
 * @param nowIndex 
 * @param loop 
 * @param edgeDraw 
 * @return int imageHandle
 */
int nextImageIndex(std::vector<int> images, int nowIndex, bool loop, bool edgeDraw);

/**
 * @brief ベジェ曲線の次の進行率を返す
 * 
 * @param nowAdvance 現在の進行率
 * @param roughness どれだけ進行率動かすか
 * @param loop ループなら**true**
 * @param init 
 * @return float 
 */
float nextBezieAdvance(float nowAdvance, float roughness, bool loop, bool init = false);

/**
 * @brief 制御点が３つのベジェ曲線を画像で描画する
 * 
 * @param left 左側の制御点
 * @param right 右側の制御点
 * @param roughness 粒度（1.0が最大）
 * @param images 描画に使用する画像
 * @param loop ループさせるなら**true**
 * @param edgeDraw imagesの最初の画像と最後の画像を使用しないなら**true**
 * @param firstIndex 最初のインデックス
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 終了後のインデックス
 */
int drawBezie(b2Vec2 left[3], b2Vec2 right[3], float roughness, std::vector<int> images, bool loop, bool edgeDraw, int firstIndex, int GlobalPos = FALSE);

/**
 * @brief グラフィックの指定矩形部分のみを描画
 * 
 * @param DestX グラフィックを描画するX座標
 * @param DestY グラフィックを描画するY座標
 * @param SrcX 描画するグラフィック上の描画したい矩形の左上X座標
 * @param SrcY 描画するグラフィック上の描画したい矩形の左上Y座標
 * @param Width 描画するグラフィックの幅
 * @param Height 描画するグラフィックの高さ
 * @param GraphHandle 描画するグラフィックのハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param TurnFlag 画像反転処理の有無(TRUE：有効　FALSE：無効)
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @param ReverceXFlag X反転フラグ
 * @param ReverceYFlag Y反転フラグ
 * @return int 0: 成功、-1: エラー発生
 */
int drawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, 
                    int GraphHandle, int TransFlag, int TurnFlag, int GlobalPos = FALSE, 
                    int ReverceXFlag = FALSE, int ReverceYFlag = FALSE ) ;

/**
 * @brief ポリゴンから２D画像を描画します
 * 
 * @param VertexArray ポリゴンの頂点情報配列（３の倍数はあることになる）
 * @param PolygonNum ポリゴン（三角形）の個数
 * @param GrHandle 画像ハンドル
 * @param TransFlag 画像の透明度を有効にするかどうか( TRUE：有効にする　FALSE：無効にする )
 * @param GlobalPos パーティションを考慮したグローバル座標で描画するか、のフラグ。TRUEでグローバル座標描画
 * @return int 0: 成功、-1: エラー発生
 */
int drawPolygon2D(DxLib::VERTEX2D* VertexArray, int PolygonNum, int GrHandle, int TransFlag, int GlobalPos = FALSE);

#endif