/**
 * @file TouchMgr.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief タッチ操作を行うコンポーネント
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TOUCH_MGR_H
#define TOUCH_MGR_H

#include "TouchData.h"
#include "Enum/TouchStatus.h"
#include "../Utility/ScreenSizeGenerator.h"
#include "../../DxLibForHTML5/include/DxLib.h"

class TouchMgr {
    private:
    /* 定数 */

    // タッチログを何フレーム保存するか
    const static int TOUCH_LOG_MAX = 60;
    // 何フレーム目までに２回タップすればダブルタップになるか
    const static int DOUBLE_TAP_INTERVAL = 5;

    /* 変数 */
    // タッチ情報
    touch_t touch;

    /* インスタンス */
    ScreenSizeGenerator *screenSizeGenerator;

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