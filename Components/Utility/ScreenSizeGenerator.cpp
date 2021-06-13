#include "ScreenSizeGenerator.h"
#include "GetBrowserSize.h"

/**
 * @brief パーティションを入れない幅を返す
 * 
 * @return int パーティションを除いた画面の幅
 */
int ScreenSizeGenerator::getWidth() {
    return SCREEN_WIDTH;
}

/**
 * @brief パーティションを入れない高さを返す
 * 
 * @return int パーティションを除いた画面の高さ
 */
int ScreenSizeGenerator::getHeight() {
    return SCREEN_HEIGHT;
}

/**
 * @brief パーティションを入れた幅を返す
 * 
 * @return int パーティションを入れた画面の幅
 */
int ScreenSizeGenerator::getWidthWithPartition() {
    #ifdef EMSCRIPTEN
    // Emscriptenにはパーティションはない
    return SCREEN_WIDTH;
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
int ScreenSizeGenerator::getHeightWithPartition() {
    #ifdef EMSCRIPTEN
    // Emscriptenにはパーティションはない
    return SCREEN_HEIGHT;
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
    return SCREEN_HEIGHT;
}

// パーティションの入ったグローバルポジションからローカルポジションへの変換
void ScreenSizeGenerator::setPositionToLocal(int *x, int *y) {
    #ifdef EMSCRIPTEN
    // Emscriptenにはパーティションはないのでブラウザの伸び縮みのみ計算
    setBrowserGeneralPos(x,y);
    #else
    // TODO: Android,iOSはパーティションがある場合がある
    #endif
}
// ローカルポジションからパーティションの入ったグローバルポジションへの変換
void ScreenSizeGenerator::setPositionToGlobal(int *x, int *y) {
    #ifdef EMSCRIPTEN
    // Emscriptenにはパーティションはないのでブラウザの伸び縮みのみ計算
    setBrowserGeneralPos(x,y);
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
float ScreenSizeGenerator::getBrowserCanvasWidthRate() {
    return ((float)getWidthWithPartition()) / ((float)getBrowserCanvasWidthEM());
}

/**
 * @brief 伸び縮みしているブラウザの高さの現在の比率を返す
 * 
 * @return float １.０が最大
 */
float ScreenSizeGenerator::getBrowserCanvasHeightRate() {
    return ((float)getHeightWithPartition()) / ((float)getBrowserCanvasHeightEM());
}

/**
 * @brief ブラウザの座標をセットする（ローカル・グローバル共通処理のため）
 * 
 * @param x 伸び縮み適用後のX座標
 * @param y 伸び縮み適用後のY座標
 */
void ScreenSizeGenerator::setBrowserGeneralPos(int *x, int *y) {
    float Rate = isBrowserLandscapeEM()==1 ?
    getBrowserCanvasWidthRate() :
    getBrowserCanvasHeightRate();

    *x = (int)(((float)*x)*Rate);
    *y = (int)(((float)*y)*Rate);
}
#endif