#include "ScreenSizeGenerator.h"
#include "GetBrowserSize.h"

/**
 * @brief パーティションを入れない幅を返す
 * 
 * @return int パーティションを除いた画面の幅
 */

/* 定数 */

// パーティションを入れない幅（ローカル幅）
static const int SCREEN_WIDTH = 1136;
// パーティションを入れない高さ(ローカル高さ)
static const int SCREEN_HEIGHT = 852;

#ifdef EMSCRIPTEN
// ブラウザのパーティションの幅
static const int BROWSER_PERTISION_WIDTH = 0;
// ブラウザのパーティションの片面の幅
static const int BROWSER_PERTISION_WIDTH_HALF = 0;

// 伸び縮みしているブラウザの幅の現在の比率を返す
float getBrowserCanvasWidthRate();
// 伸び縮みしているブラウザの高さの現在の比率を返す
float getBrowserCanvasHeightRate();

#endif

int getScreenWidth() {
    return SCREEN_WIDTH;
}

/**
 * @brief パーティションを入れない高さを返す
 * 
 * @return int パーティションを除いた画面の高さ
 */
int getScreenHeight() {
    return SCREEN_HEIGHT;
}

/**
 * @brief パーティションを入れた幅を返す
 * 
 * @return int パーティションを入れた画面の幅
 */
int getScreenWidthWithPartition() {
    #ifdef EMSCRIPTEN
    return SCREEN_WIDTH + BROWSER_PERTISION_WIDTH;
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
    return SCREEN_WIDTH;
}

/**
 * @brief パーティションを入れた高さを返す
 * 
 * @return int パーティションを入れた画面の高さ
 */
int getScreenHeightWithPartition() {
    #ifdef EMSCRIPTEN
    // Emscriptenにはパーティションはない
    return SCREEN_HEIGHT;
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
    return SCREEN_HEIGHT;
}

// パーティションの入ったグローバルポジションからローカルポジションへの変換
void setScreenPosToLocal(int *x, int *y) {
    #ifdef EMSCRIPTEN
    // 幅のパーティション分減算
    *x -= BROWSER_PERTISION_WIDTH_HALF;
    // ブラウザの伸び縮みの計算
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
}

// ローカルポジションからパーティションの入ったグローバルポジションへの変換
void setScreenPosToGlobal(int *x, int *y) {
    #ifdef EMSCRIPTEN
    // 幅のパーティションのみ加算
    *x += BROWSER_PERTISION_WIDTH_HALF;
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
}

#ifdef EMSCRIPTEN
/**
 * @brief 伸び縮みしているブラウザの幅の現在の比率を返す
 * 
 * @return float １.０が最大
 */
float getBrowserCanvasWidthRate() {
    return ((float)getScreenWidthWithPartition()) / ((float)getBrowserCanvasWidthEM());
}

/**
 * @brief 伸び縮みしているブラウザの高さの現在の比率を返す
 * 
 * @return float １.０が最大
 */
float getBrowserCanvasHeightRate() {
    return ((float)getScreenHeightWithPartition()) / ((float)getBrowserCanvasHeightEM());
}

/**
 * @brief ブラウザの座標をセットする（ローカル・グローバル共通処理のため）
 * 
 * @param x 伸び縮み適用後のX座標
 * @param y 伸び縮み適用後のY座標
 */
void setBrowserGeneralPos(int *x, int *y) {
    float Rate = isBrowserLandscapeEM()==1 ?
    getBrowserCanvasWidthRate() :
    getBrowserCanvasHeightRate();

    *x = (int)(((float)*x)*Rate);
    *y = (int)(((float)*y)*Rate);
}
#endif