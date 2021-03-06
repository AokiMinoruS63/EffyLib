/**
 * @file TouchMgr.h
 * @brief タッチ操作
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef TOUCH_MGR_H
#define TOUCH_MGR_H

#include "TouchData.h"
#include "Enum/TouchStatus.h"
#include "../Utility/DxLibWrap.h"

class TouchMgr {
    private:
    /* 定数 */

    // タッチログを何フレーム保存するか
    static const int kTouchLogMax = 60;
	// 何フレームまで押し続ければリピートになるか
	static const int kTouchRepeatTime = 20;
    // 何フレーム目までに２回タップすればダブルタップになるか
    static const int kDoubleTapInterval = 5;

    /* 変数 */
    // タッチ情報
    touch_t touch_;

    /* コンストラクタ・デストラクタ */
    public:
    TouchMgr();
    ~TouchMgr();

    /* 関数 */

    // タッチ・座標ログを取っておく
    void updateLog();
    // タッチしているか、座標はどこかの判定
    void calc();
    // ローカルタッチ情報を返す
    touch_t get();
    // ワールドタッチ情報を返す
    touch_t getGlobalTouch();
};

#endif