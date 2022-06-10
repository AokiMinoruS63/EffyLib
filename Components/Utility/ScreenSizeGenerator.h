/**
 * @file ScreenSizeGenerator.h
 * @brief 画面サイズの調整やパーティションの調整を行う
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SCREEN_SIZE_GENERATOR_H
#define SCREEN_SIZE_GENERATOR_H

// パーティションを入れない幅を返す
int getScreenWidth();
// パーティションを入れない高さを返す
int getScreenHeight();
// パーティションを入れた幅を返す
int getScreenWidthWithPartition();
// パーティションを入れた高さを返す
int getScreenHeightWithPartition();
// パーティションの入ったグローバルポジションからローカルポジションへの変換
void setScreenPosToLocal(int *x, int *y);
// ローカルポジションからパーティションの入ったグローバルポジションへの変換
void setScreenPosToGlobal(int *x, int *y);
// ローカルポジションからパーティションの入ったグローバルポジションへの変換(float)
void setScreenPosToGlobal(float *x, float *y);

/* ブラウザ限定処理 */
#ifdef EMSCRIPTEN
// ブラウザの座標をセットする（ローカル・グローバル共通処理のため）
void setBrowserGeneralPos(int *x, int *y);

#endif
#endif