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

#ifdef EMSCRIPTEN


class ScreenSizeGenerator {
     public:
    /* 定数 */

    // パーティションを入れない幅（ローカル幅）
    static const int SCREEN_WIDTH = 640;
    // パーティションを入れない高さ(ローカル高さ)
    static const int SCREEN_HEIGHT = 1136;

    /* コンストラクタ・デストラクタ */
   

    ScreenSizeGenerator(){}
    ~ScreenSizeGenerator(){}

    // パーティションを入れない幅を返す
    int getWidth();
    // パーティションを入れない高さを返す
    int getHeight();
    // パーティションを入れた幅を返す
    int getWidthWithPartition();
    // パーティションを入れた高さを返す
    int getHeightWithPartition();
    // パーティションの入ったグローバルポジションからローカルポジションへの変換
    void setPositionToLocal(int *x, int *y);
    // ローカルポジションからパーティションの入ったグローバルポジションへの変換
    void setPositionToGlobal(int *x, int *y);

    /* ブラウザ限定処理 */
    #ifdef EMSCRIPTEN
    // ブラウザの座標をセットする（ローカル・グローバル共通処理のため）
    void setBrowserGeneralPos(int *x, int *y);
    private:
    // 伸び縮みしているブラウザの幅の現在の比率を返す
    float getBrowserCanvasWidthRate();
    // 伸び縮みしているブラウザの高さの現在の比率を返す
    float getBrowserCanvasHeightRate();
    #endif
};



#endif
#endif