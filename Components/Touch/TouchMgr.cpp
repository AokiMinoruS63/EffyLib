#include "TouchMgr.h"

/**
 * @brief コンストラクタ。ログを初期化し、スクリーンサイズクラスのインスタンスを生成する
 * 
 */
TouchMgr::TouchMgr() {
    // vector初期化
    int i = 0;
    for(int i=0;i<kTouchLogMax;i++) {
        touch_.input_log.push_back(false);
        touch_.pos_log_x.push_back(0);
        touch_.pos_log_y.push_back(0);
    }
}

/**
 * @brief 処理は特になし
 * 
 */
TouchMgr::~TouchMgr() {

}

/**
 * @brief タップ情報のログを更新する
 * 
 */
void TouchMgr::updateLog() {
    for (int i = kTouchLogMax - 1; i > 0; i--)
    {
        touch_.input_log[i] = touch_.input_log[i - 1];
        touch_.pos_log_x[i] = touch_.pos_log_x[i - 1];
        touch_.pos_log_y[i] = touch_.pos_log_y[i - 1];
    }
}

/**
 * @brief タップ情報の取得・更新・タップ座標はローカル座標に変換される
 * 
 * 
 */
void TouchMgr::calc() {
    
    /* 座標・タップ情報取得 */
    #ifdef EMSCRIPTEN
    getMousePoint(&touch_.x, &touch_.y);
    touch_.input_log[0] = GetMouseInput()& MOUSE_INPUT_LEFT ? true:false;
    #else
    if (GetTouchInputNum() > 0)
    {
        GetTouchInput(0, &touch.x, &touch.y, NULL, NULL);
        touch.input_log[0] = true;
    }
    else
    {
        touch.input_log[0] = false;
    }
    #endif

    // ログ・タップステータス初期化
    touch_.pos_log_x[0] = touch_.x;
    touch_.pos_log_y[0] = touch_.y;
    touch_.status = TouchStatus::kNoTouch;
    touch_.double_tap = false;
	touch_.beginIndex = 0;

    // タップステータス更新
    if (touch_.input_log[0] == true && touch_.input_log[1] == false)touch_.status = TouchStatus::kJustTouch;// 押した瞬間
    else if (touch_.input_log[0] == false && touch_.input_log[1] == true)touch_.status = TouchStatus::kJustRelease;// 離した瞬間
    else if (touch_.input_log[0] == true && touch_.input_log[1] == true) //キーリピート処理 
    {
        touch_.status = TouchStatus::kRepeating;
        for (int i = 2; i < kTouchRepeatTime; i++)
        {
            if (touch_.input_log[i] == false) { 
				touch_.status = TouchStatus::kNotRepeating;
				 break; 
			}
        }
    }
	// タッチ開始が何フレーム前か調査
	if(touch_.status != TouchStatus::kNoTouch) {
		for (int i = 2; i < kTouchLogMax; i++)
		{
			if (touch_.input_log[i] == false) { 
				touch_.beginIndex = i - 1;
					break; 
			}
		}
	}
    // ダブルタップ更新 
    for (int i = 2; i < kDoubleTapInterval; i++)
    {
        if (!touch_.input_log[i])continue;
        touch_.double_tap = true;
        break;
    } 

    // ログ更新
    updateLog();
}

/**
 * @brief ローカル座標を返す
 * 
 * @return touch_t 現在のローカル座標のタップ情報
 */
touch_t TouchMgr::get() {
    return touch_;
}

/**
 * @brief パーティションを考慮したグローバルタップ情報を返す
 * 
 * @return touch_t 現在のパーティションを考慮したタップ情報を返す
 */
touch_t TouchMgr::getGlobalTouch() {
    touch_t globalTouch = touch_;
    #ifdef EMSCRIPTEN
    setScreenPosToGlobal(&globalTouch.x, &globalTouch.y);
    #else
    // Android,iOSは変換して返す
    screenSizeGenerator->setScreenPosToGlobal(&globalTouch.x,&globalTouch.y);
    for(int i=0;i<kTouchLogMax;i++) {
        screenSizeGenerator->setScreenPosToGlobal(&globalTouch.pos_log_x[i]],&globalTouch.pos_log_y[i]);
    }
    #endif
    return touch_;
}