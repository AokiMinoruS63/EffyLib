/**
 * @file ScreenSizeGenerator.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 画面サイズの調整やパーティションの調整を行う
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
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

/* ブラウザ限定処理 */
#ifdef EMSCRIPTEN
// ブラウザの座標をセットする（ローカル・グローバル共通処理のため）
void setBrowserGeneralPos(int *x, int *y);

#endif
#endif