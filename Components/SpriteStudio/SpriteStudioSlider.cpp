/**
 * @file SpriteStudioSlider.cpp
 * @brief SpriteStudioのスライダー
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudio.h"
#include "SpriteStudioSlider.h"
#include "../Utility/TypeExtensions.h"

using namespace SpriteStudio;

/**
 * @brief パーツの情報を取得する
 * 
 * @param handle 取得するハンドル
 * @param result 情報
 * @param frame_no 取得するフレーム(現在のものなら-1)
 * @return int 成功すればkSuccessCode, 失敗すればkErrorCode
 */
int getPartResult(int handle, SpriteStudioResult& result, int frame_no) {
	if (SpriteStudio::Player::getPartState(handle, result, 1, frame_no) == kErrorCode) {
		if (SpriteStudio::Player::getPartState(handle, result, 0, frame_no) == kErrorCode) {
			return kErrorCode;
		}
	}
	return kSuccessCode;
}

/**
 * @brief モーションが存在するアニメなら**true**
 * 
 * @param handle アニメハンドル
 * @return int kErrorCode・・・存在しない、0 = FALSE, 1 = TRUE
 */
int isMotion(int handle) {
	// ハンドルが存在しなければ**false**
	if (handle <= 0) {
		return kErrorCode; 
	}
	return SpriteStudio::Player::isNoMotion(handle) ? FALSE : TRUE;
}

Slider::Slider(
	std::string path, 
	std::string ssae_meter, 
	std::string ssae_frame, 
	std::string ssae_frame_back,
	std::string ssae_thumb, 
	float x, 
	float y, 
	float default_value
	) {
	_handle_meter = SpriteStudio::Player::add(path);
	_handle_frame = SpriteStudio::Player::add(path);
	_handle_frame_back = SpriteStudio::Player::add(path);
	_handle_thumb = SpriteStudio::Player::add(path);
	SpriteStudio::Player::setScale(_handle_meter, 1.0);
	SpriteStudio::Player::setScale(_handle_frame, 1.0);
	SpriteStudio::Player::setScale(_handle_frame_back, 1.0);
	SpriteStudio::Player::setScale(_handle_thumb, 1.0);
	SpriteStudio::Player::setPosition(_handle_meter, x, y);
	SpriteStudio::Player::setPosition(_handle_frame, x, y);
	SpriteStudio::Player::setPosition(_handle_frame_back, x, y);
	SpriteStudio::Player::setPosition(_handle_thumb, x, y);
	_value = default_value;
	_is_draw_update = false;

	// アニメーションを再生する
	auto meter_anime = Player::getAnimeNameList(_handle_meter, ssae_meter);
	auto frame_anime = Player::getAnimeNameList(_handle_frame, ssae_frame);
	auto frame_back_anime = Player::getAnimeNameList(_handle_frame_back, ssae_frame_back);
	auto thumb_anime = Player::getAnimeNameList(_handle_thumb, ssae_thumb);

	SpriteStudio::Player::play(_handle_meter, meter_anime.front());
	SpriteStudio::Player::play(_handle_frame, frame_anime.front());
	SpriteStudio::Player::play(_handle_frame_back, frame_back_anime.front());
	SpriteStudio::Player::play(_handle_thumb, thumb_anime.front());
	const float max_frame = (float)SpriteStudio::Player::getMaxFrame(_handle_thumb);
	const int frame_no = default_value == Float::kMin ? 0 : (int)(default_value * max_frame);
	// DrawArea関数を使用するために、最初のフレームの座標と最後のフレームの座標を取得しておく
	SpriteStudioResult result;
	// 始点取得
	getPartResult(_handle_thumb, result, 0);
	_start = Vec2(result.x, result.y);
	// 終点取得
	getPartResult(_handle_thumb, result, max_frame - 1);
	_end = Vec2(result.x, result.y);
	// つまみ部分を現在の値に戻す
	SpriteStudio::Player::setFrameNo(_handle_thumb, frame_no);
	
	// 描画用のフレームを作成する
	initFrame(_handle_thumb, x, y);
	setState(UIState::kActive);
	_is_draw_update = true;

	if (isMotion(_handle_frame) == TRUE || isMotion(_handle_frame_back)  == TRUE || isMotion(_handle_meter)  == TRUE ) {
		_always_update = true;
	}
}

Slider::~Slider() {
	SpriteStudio::Player::remove(_handle_meter);
	SpriteStudio::Player::remove(_handle_frame);
	SpriteStudio::Player::remove(_handle_frame_back);
	SpriteStudio::Player::remove(_handle_thumb);
	removeScreen();
}

// スライダーの値（0.0 ~ 1.0）を取得する
float Slider::getValue() {
	return _value;
}

// スライダーの値（0.0 ~ 1.0）をセットする
void Slider::setValue(float value) {
	_value = value;
	// 画面を更新する
	_is_draw_update = true;
}

// 毎フレーム描画更新するかどうかのフラグを取得する
bool Slider::getAlwaysUpdateFlag() {
	return _always_update;
}

// 毎フレーム描画更新するかどうかのフラグをセットする
void Slider::setAlwaysUpdateFlag(bool flag) {
	// 何もアニメーションをしないなら処理を行わない
	if (isMotion(_handle_frame) != TRUE || isMotion(_handle_frame_back)  != TRUE || isMotion(_handle_meter)  != TRUE ) {
		return;
	}
	_always_update = flag;
	// フレームを０に戻す
	SpriteStudio::Player::setFrameNo(_handle_frame, 0);
	SpriteStudio::Player::apply(_handle_frame);
	SpriteStudio::Player::setFrameNo(_handle_frame_back, 0);
	SpriteStudio::Player::apply(_handle_frame_back);
	SpriteStudio::Player::setFrameNo(_handle_meter, 0);
	SpriteStudio::Player::apply(_handle_meter);
}

/**
 * @brief モーションを更新する
 * 
 * @param handle ハンドル
 * @param dt 進行時間
 */
void updateMotion(int handle, float dt) {
	SpriteStudio::Player::update(handle, dt);
	if(SpriteStudio::Player::isEndFrame(handle) && !SpriteStudio::Player::isNoMotion(handle)) {
		SpriteStudio::Player::setFrameNo(handle, 0);
	}
}

void Slider::run(touch_t touch, float dt) {
	// StateがkInvisibleなら処理しない
	const UIState state = getState();
	if (state == UIState::kInvisible) {
		_dragging = false;
		return;
	}
	// つまみ以外はアニメーションを更新する
	if (_always_update) {
		updateMotion(_handle_meter, dt);
		updateMotion(_handle_frame, dt);
		updateMotion(_handle_frame_back, dt);
	}
	// つまみの計算
	// kActiveでなければ処理しない
	if (state != UIState::kActive) {
		_dragging = false;
		return;
	}
	// 判定処理
	SpriteStudioResult result, result2;
	Vec2 start = _start;
	Vec2 end = _end;
	if (getPartResult(_handle_thumb, result, -1) == kErrorCode) {
		return;
	}
	if (SpriteStudio::Player::getPartState(getLinkedPlayerHandle(), result2, getLinkedPartName().c_str()) == kSuccessCode) {
		result.x += result2.x;
		result.y += getScreenHeight() - result2.y;
		start.x += result2.x;
		start.y += getScreenHeight() - result2.y;
		end.x += result2.x;
		end.y += getScreenHeight() - result2.y;
	}

	// サイズから判定をする
	Rect rect = Rect(result.x, result.y, result.size_X, result.size_Y);
	// 前のフレームでエリアインしているなら**true**
	const bool current_area_in = rect.isContain(touch.x, touch.y) && touch.input_log[0];
	const bool last_area_in = rect.isContain(touch.pos_log_x[1], touch.pos_log_y[1]) && touch.input_log[1];
	if (!_dragging) {
		if (!current_area_in) {
			return;
		}
		_dragging = true;
	} else if (touch.status == TouchStatus::kNoTouch) {
		_dragging = false;
		return;
	}

	// 含まれていないなら何もしない
	if (!touch.input_log[0] && !last_area_in) {
		return;
	}
	const int now_frame = SpriteStudio::Player::getFrameNo(_handle_thumb);
	int next_frame;
	const int max_frame = SpriteStudio::Player::getMaxFrame(_handle_thumb) - 1;
	float rate;
	if (touch.x < (int)start.x) {
		next_frame = 0;
		rate = 0.0;
	} else if (touch.x > (int)end.x) {
		next_frame = max_frame;
		rate = 1.0;
	} else {
		rate = ((float)touch.x - start.x) / (end.x - start.x);
		next_frame = (int)(((float)max_frame) * rate);
	}
	if (now_frame == next_frame) {
		return;
	}
	setValue(rate);
	SpriteStudio::Player::setFrameNo(_handle_thumb, next_frame);
	_is_draw_update = true;
	runAction();
}

// スライダーを描画する
int Slider::draw() {
	// StateがkInvisibleなら描画しない
	if(getState() == UIState::kInvisible) {
		return kSuccessCode;
	}

	if (preRender() == kErrorCode) {
		return kErrorCode;
	}
	return drawCommon();
}

// 描画する
int Slider::preRender() {
	if (!_is_draw_update && !_always_update) {
		return kSuccessCode;
	}
	if(preRenderInit() == kErrorCode) {
		return kErrorCode;
	}
	Rect frame = getFrame();

	// スクリーン上の座標に変更する
	setPosition(frame.halfWidth(), frame.halfHeight());
	// 描画実行
	clearDrawScreen();
	SpriteStudio::Player::draw(_handle_frame_back);
	// ゲージ分のみ描画
	SpriteStudioResult result;
	getPartResult(_handle_thumb, result, -1);
	setDrawArea(0, 0, (int)result.x, (int)frame.height);
	SpriteStudio::Player::draw(_handle_meter);
	setDrawAreaFull();
	SpriteStudio::Player::draw(_handle_frame);
	SpriteStudio::Player::draw(_handle_thumb);
	setPosition(frame.x, frame.y);
	_is_draw_update = false;
	return preRenderEnd();
}

int Slider::setPosition(float x, float y) {
	// 座標設定
	SpriteStudio::Player::setPosition(_handle_meter, x, y);
	SpriteStudio::Player::setPosition(_handle_frame, x, y);
	SpriteStudio::Player::setPosition(_handle_frame_back, x, y);
	SpriteStudio::Player::setPosition(_handle_thumb, x, y);
	// アニメーション中の動きに適用
	SpriteStudio::Player::apply(_handle_meter);
	SpriteStudio::Player::apply(_handle_frame);
	SpriteStudio::Player::apply(_handle_frame_back);
	SpriteStudio::Player::apply(_handle_thumb);
	return kSuccessCode;
}
