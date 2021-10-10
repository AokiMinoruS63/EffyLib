#include "TouchMgr.h"

/**
 * @brief コンストラクタ。ログを初期化し、スクリーンサイズクラスのインスタンスを生成する
 * 
 */
TouchMgr::TouchMgr() {
    // vector初期化
    int i = 0;
    for(int i=0;i<TOUCH_LOG_MAX;i++) {
        touch_.inputLog.push_back(false);
        touch_.posLogX.push_back(0);
        touch_.posLogY.push_back(0);
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
    for (int i = TOUCH_LOG_MAX - 1; i > 0; i--)
    {
        touch_.inputLog[i] = touch_.inputLog[i - 1];
        touch_.posLogX[i] = touch_.posLogX[i - 1];
        touch_.posLogY[i] = touch_.posLogY[i - 1];
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
    touch_.inputLog[0] = GetMouseInput()& MOUSE_INPUT_LEFT ? true:false;
    #else
    if (GetTouchInputNum() > 0)
    {
        GetTouchInput(0, &touch.x, &touch.y, NULL, NULL);
        touch.inputLog[0] = true;
    }
    else
    {
        touch.inputLog[0] = false;
    }
    #endif

    // ログ・タップステータス初期化
    touch_.posLogX[0] = touch_.x;
    touch_.posLogY[0] = touch_.y;
    touch_.status = TouchStatus::NoTouch;
    touch_.doubleTap = false;
	touch_.beginIndex = 0;

    // タップステータス更新
    if (touch_.inputLog[0] == true && touch_.inputLog[1] == false)touch_.status = TouchStatus::JustTouch;// 押した瞬間
    else if (touch_.inputLog[0] == false && touch_.inputLog[1] == true)touch_.status = TouchStatus::JustRelease;// 離した瞬間
    else if (touch_.inputLog[0] == true && touch_.inputLog[1] == true) //キーリピート処理 
    {
        touch_.status = TouchStatus::Repeating;
        for (int i = 2; i < TOUCH_REPEAT_TIME; i++)
        {
            if (touch_.inputLog[i] == false) { 
				touch_.status = TouchStatus::NotRepeating;
				 break; 
			}
        }
    }
	// タッチ開始が何フレーム前か調査
	if(touch_.status != TouchStatus::NoTouch) {
		for (int i = 2; i < TOUCH_LOG_MAX; i++)
		{
			if (touch_.inputLog[i] == false) { 
				touch_.beginIndex = i - 1;
					break; 
			}
		}
	}
    // ダブルタップ更新 
    for (int i = 2; i < DOUBLE_TAP_INTERVAL; i++)
    {
        if (!touch_.inputLog[i])continue;
        touch_.doubleTap = true;
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
    for(int i=0;i<TOUCH_LOG_MAX;i++) {
        screenSizeGenerator->setScreenPosToGlobal(&globalTouch.posLogX[i]],&globalTouch.posLogY[i]);
    }
    #endif
    return touch_;
}