/**
 * @file SpriteStudioUI.cpp
 * @brief SpriteStudioで作成されたUI共通
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudioUI.h"
#include "SpriteStudio.h"
#include "../Common/Type/ReturnType.h"
#include "../Common/Constant/MathConstant.h"

using namespace SpriteStudio;

// フレームを初期化する
int UICommon::initFrame(int handle, float x, float y) {
	int width, height;
	if (Player::getFrameSize(handle, &width, &height) == kErrorCode) {
		return kErrorCode;
	}
	// スクリーン作成
	this->makeScreen(width, height);
	// 座標、フレームサイズを設定する
	setFrame(Rect(x, y, (float)width, (float)height));
	return kSuccessCode;
}

// 現在の描画エリアの座標を設定する
int UICommon::setFramePotision(float x, float y) {
	_frame.x = x;
	_frame.y = y;
	return kSuccessCode;
}

// 現在の描画エリアを取得する
Rect UICommon::getFrame() {
	return _frame;
}

// 現在の描画エリアを設定する
int UICommon::setFrame(Rect frame) {
	_frame = frame;
	return kSuccessCode;
}

// 領域に入っているかの反応を返す
UIAreaState UICommon::getAreaState(touch_t touch) {
	// 判定を行わない状態なら処理しない
	if(_state != UIState::kActive) {
		return UIAreaState::kNoTouch;
	}
	// 座標を移動用にとっておく
	const Rect tmp_rect = _frame;

	// リンクしているss::Playerがあるならば、そこと連動させる
	SpriteStudioResult result;
	if(SpriteStudio::Player::getPartState(_linked_handle, result, _linked_part_name.c_str()) == kSuccessCode) {
		_frame.x += result.x;
		_frame.y += getScreenHeight() - result.y;
		_frame.width *= result.scaleX;
		_frame.height *= result.scaleY;
	}
	// 現在エリアインしているなら**true**
	const bool current_area_in = _frame.isContain(touch.x, touch.y);
	// 前のフレームでエリアインしているなら**true**
	const bool last_area_in = _frame.isContain(touch.pos_log_x[1], touch.pos_log_y[1]);
	// 座標を元に戻す
	_frame = tmp_rect;

	// 前も今もタッチしていない
	if(!touch.isLastTouch() && !touch.isCurrentTouch()) {
		#ifdef __ANDROID__
		return UIAreaState::kNoTouch;
		#elif __APPLE__
		return UIAreaState::kNoTouch;
		#else
		return current_area_in ? UIAreaState::kAreaIn : UIAreaState::kNoTouch;
		#endif
	} else if (!touch.isLastTouch() && touch.isCurrentTouch()) {
		// 前のフレームはタッチせず、今のフレームでタッチ
		// 今エリアインならタップ開始を返す
		if (current_area_in) {
			return UIAreaState::kJustTap;
		} else {
			return UIAreaState::kNoTouch;
		}
	} else if (touch.isLastTouch() && touch.isCurrentTouch()) {
		// 前も今もタッチしている
		if (current_area_in) {
			if (!last_area_in) {
				return UIAreaState::kJustAreaIn;
			} else {
				// リピート判定を行う
				if (touch.pos_log_x.size() <= _repeat_frame) {
					return UIAreaState::kAreaIn;
				}
				for(int i = 2; i < _repeat_frame; i++) {
					if (!_frame.isContain(touch.pos_log_x[i], touch.pos_log_y[i])) {
						return UIAreaState::kAreaIn;
					}
				}
				return UIAreaState::kAreaInRepeat;
			}
		} else {
			// 前フレームイン、今フレームアウト
			if (last_area_in) {
				return UIAreaState::kJustAreaOut;
			} else {
				return UIAreaState::kNoTouch;
			}
		}
	} else {
		// 前はタッチ、今はリリース
		return current_area_in ? UIAreaState::kJustRelease : UIAreaState::kNoTouch;
	}
	return UIAreaState::kNoTouch;
}

// 削除フラグを取得する
bool UICommon::getDeleteFlag() {
	return _is_waiting_deletion;
}

// 削除フラグを設定する
void UICommon::setDeleteFlag(bool is_delete) {
	_is_waiting_deletion = is_delete;
}

// UIの状態を取得する
UIState UICommon::getState() {
	return _state;
}

// UIの状態を設定する
void UICommon::setState(UIState state) {
	_state = state;
}

// アニメーションの状態を取得する
UIAnimeState UICommon::getAnimeState() {
	return _anime_state;
}

// アニメーションの状態を設定する
void UICommon::setAnimeState(UIAnimeState anime_state) {
	_anime_state = anime_state;
}

// リンク先のSpriteStudioPlayerハンドルを取得する
int UICommon::getLinkedPlayerHandle() {
	return _linked_handle;
}

// リンク先のSpriteStudioPlayerハンドルを設定する
void UICommon::setLinkedPlayerHandle(int handle) {
	_linked_handle = handle;
}

// リンク先のSpriteStudioPlayerのパーツ名を取得する
std::string UICommon::getLinkedPartName() {
	return _linked_part_name;
}

// リンク先のSpriteStudioPlayerのパーツ名を設定する
void UICommon::setLinkedPartName(std::string part_name) {
	_linked_part_name = part_name;
}

// アニメーションの再生カウントを取得する
int UICommon::getAnimationCount() {
	return _animation_count;
}

// アニメーションの再生カウントを設定する
void UICommon::setAnimationCount(int animation_count) {
	_animation_count = animation_count;
}

// リピート時間を取得する
int UICommon::getRepeatFrame() {
	return _repeat_frame;
}

// リピート時間をセットする
void UICommon::setRepeatFrame(int frame) {
	_repeat_frame = frame;
}

// UIを動かした時の処理を設定する
void UICommon::setAction(std::function<void()> action) {
	_action = action;
}

// 描画準備
int UICommon::preRenderInit() {
	if(_screen == NULL) {
		return kErrorCode;
	}
	_screen_resume.saveScreen();
	_screen_resume.saveScreenState();
	_screen_resume.initScreenState();
	setDrawScreen(_screen);
	return kSuccessCode;
}

// 描画後の後始末
int UICommon::preRenderEnd() {
	if(getDrawScreen() != _screen) {
		return kErrorCode;
	}
	_screen_resume.loadScreen();
	_screen_resume.loadScreenState();
	return kSuccessCode;
}

// preRender済のスクリーンを使用した共通描画処理
int UICommon::drawCommon() {
	Rect frame = getFrame();
	// リンクしているssPlayerの拡大率、アルファ値、角度を設定する
	float scale_x = 1.0;
	float scale_y = 1.0;
	float radian = 0.0;
	float alpha = 1.0;
	int blend_mode = BlendMode::kNoBlend;
	const int linked_handle = getLinkedPlayerHandle();
	ScreenStateResume resume;
	SpriteStudioResult result;
	if(SpriteStudio::Player::getPartState(linked_handle, result, getLinkedPartName().c_str()) == kSuccessCode) {
		frame.x = result.x;
		frame.y = getScreenHeight() - result.y;
		scale_x = result.scaleX;
		scale_y = result.scaleY;
		const char* root_part_name = SpriteStudio::Player::getPartName(linked_handle, 0);
		// Rootの拡大率適用
		if (getLinkedPartName() != root_part_name) {
			SpriteStudioResult result2;
			SpriteStudio::Player::getPartState(linked_handle, result2, SpriteStudio::Player::getPartName(linked_handle, 0));
			scale_x *= result2.scaleX;
			scale_y *= result2.scaleY;
		}
		// 親の拡大率適用
		const char* parent_name = SpriteStudio::Player::getPartName(linked_handle, result.parent_index);
		if (getLinkedPartName() != parent_name && getLinkedPartName() != root_part_name) {
			SpriteStudioResult result2;
			SpriteStudio::Player::getPartState(linked_handle, result2, parent_name);
			scale_x *= result2.scaleX;
			scale_y *= result2.scaleY;
		}
		alpha = ((float)result.opacity) * 255.0;
		blend_mode = result.colorBlendType;
		radian = result.rotationZ * (1.0 / 360.0) * kPiFloat;
	}
	if(blend_mode != BlendMode::kNoBlend) {
		resume.saveBlend();
		setDrawBlendMode(blend_mode, alpha);
	}
	int returnValue = drawRotaGraph3(frame.x, frame.y, frame.halfWidth(), frame.halfHeight(), scale_x, scale_y, radian, getScreen(), TRUE);
	if(blend_mode != BlendMode::kNoBlend) {
		resume.loadScreenState();
	}
	if(blend_mode != BlendMode::kNoBlend) {
		resume.loadBlend();
	}
	return returnValue;
}

// UIを動かした時の処理を実行する
int UICommon::runAction() {
	if(_action == NULL) {
		return kErrorCode;
	}
	_action();
	return kSuccessCode;
}

// スクリーンが存在すれば**true**
bool UICommon::isScreen() {
	return _screen != NULL;
}

// 描画スクリーンを生成する
int UICommon::makeScreen(int width, int height) {
	_screen = MakeScreen((int)width, (int)height, TRUE);
	return _screen == kErrorCode ? kErrorCode : kSuccessCode;
}

// スクリーンを開放する
int UICommon::removeScreen() {
	if(_screen == NULL) {
		return kErrorCode;
	}
	DeleteGraph(_screen);
	_screen = NULL;
	return kSuccessCode;
}

// スクリーンの取得
int UICommon::getScreen() {
	return _screen == NULL ? kErrorCode : _screen;
}

// 座標を取得する
int UICommon::getPosition(float *x, float *y) {
	printfDx("ERROR: 継承されずに\"UICommon::getPosition\"関数が呼ばれました。\n");
	return kErrorCode;
}

// 座標をセットする
int UICommon::setPosition(float x, float y) {
	printfDx("ERROR: 継承されずに\"UICommon::setPosition\"関数が呼ばれました。\n");
	return kErrorCode;
}

// ボタンを描画・判定共に行う状態にする
int UICommon::setActived() {
	printfDx("ERROR: 継承されずに\"UICommon::setDisabled\"関数が呼ばれました。\n");
	return kErrorCode;
}

// ボタンを描画は行うが、判定は行わない状態にする
int UICommon::setUnresponsive() {
	printfDx("ERROR: 継承されずに\"UICommon::setUnresponsive\"関数が呼ばれました。\n");
	return kErrorCode;
}

// ボタンを使用できない事を示す描画を行い、判定は行わない状態にする
int UICommon::setDisabled() {
	printfDx("ERROR: 継承されずに\"UICommon::setDisabled\"関数が呼ばれました。\n");
	return kErrorCode;
}

// ボタンを描画も判定も行わない状態にする
int UICommon::setInvisible() {
	printfDx("ERROR: 継承されずに\"UICommon::setInvisible\"関数が呼ばれました。\n");
	return kErrorCode;
}
