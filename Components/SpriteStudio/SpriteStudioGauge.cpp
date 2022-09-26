/**
 * @file SpriteStudioGauge.cpp
 * @brief つまみの無いSpriteStidioを使用したゲージクラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudio.h"
#include "SpriteStudioGauge.h"
#include "../Utility/TypeExtensions.h"

using namespace SpriteStudio;

// コンストラクタ
Gauge::Gauge(
	std::string path, 
	std::string ssae_meter, 
	std::string ssae_frame, 
	std::string ssae_frame_back, 
	std::string ssae_mask, 
	float x, 
	float y, 
	float default_value
	) {

	_handle_meter = SpriteStudio::Player::add(path);
	_handle_frame = SpriteStudio::Player::add(path);
	_handle_frame_back = SpriteStudio::Player::add(path);
	_handle_mask = SpriteStudio::Player::add(path);
	SpriteStudio::Player::setScale(_handle_meter, 1.0);
	SpriteStudio::Player::setScale(_handle_frame, 1.0);
	SpriteStudio::Player::setScale(_handle_frame_back, 1.0);
	SpriteStudio::Player::setScale(_handle_mask, 1.0);
	SpriteStudio::Player::setPosition(_handle_meter, x, y);
	SpriteStudio::Player::setPosition(_handle_frame, x, y);
	SpriteStudio::Player::setPosition(_handle_frame_back, x, y);
	_value = default_value;
	_is_draw_update = false;

	// アニメーションを再生する
	auto meter_anime = Player::getAnimeNameList(_handle_meter, ssae_meter);
	auto frame_anime = Player::getAnimeNameList(_handle_frame, ssae_frame);
	auto frame_back_anime = Player::getAnimeNameList(_handle_frame_back, ssae_frame_back);
	auto mask_anime = Player::getAnimeNameList(_handle_mask, ssae_mask);

	SpriteStudio::Player::play(_handle_meter, meter_anime.front());
	SpriteStudio::Player::play(_handle_frame, frame_anime.front());
	SpriteStudio::Player::play(_handle_frame_back, frame_back_anime.front());

	const float max_frame = (float)SpriteStudio::Player::getMaxFrame(_handle_meter);
	const int frame_no = default_value == Float::kMin ? 0 : (int)(default_value * max_frame);

	// ゲージを現在の値に適用する
	SpriteStudio::Player::setFrameNo(_handle_meter, frame_no);
	// マスクは0フレーム固定
	// SpriteStudio::Player::setFrameNo(_handle_mask, frame_no);
	
	// 描画用のフレームを作成する
	initFrame(_handle_frame, x, y);
	setState(UIState::kActive);
	_is_draw_update = true;

	if (updateMotionCheck()) {
		_always_update = true;
	}

	// マスクスクリーンを作成する
	if (IsEmpty(mask_anime)) {
		return;
	}
	ScreenStateResume resume;
	Rect frame = getFrame();
	SpriteStudio::Player::setPosition(_handle_mask, frame.halfWidth(), frame.halfHeight());
	SpriteStudio::Player::play(_handle_mask, mask_anime.front());
}

// デストラクタ
Gauge::~Gauge() {
	SpriteStudio::Player::remove(_handle_meter);
	SpriteStudio::Player::remove(_handle_frame);
	SpriteStudio::Player::remove(_handle_frame_back);
	SpriteStudio::Player::remove(_handle_mask);
	removeScreen();
}

// ゲージの値（0.0 ~ 1.0）を取得する
float Gauge::getValue() {
	return _value;
}

// ゲージの値（0.0 ~ 1.0）をセットする
void Gauge::setValue(float value) {
	_value = value;
	// TODO: メーターを更新する
	const int now_frame = SpriteStudio::Player::getFrameNo(_handle_meter);
	const int max_frame = SpriteStudio::Player::getMaxFrame(_handle_meter) - 1;
	int next_frame;
	if (value < 0.0) {
		next_frame = 0;
	} else if (value > 1.0) {
		next_frame = max_frame;
	} else {
		next_frame = (int)(((float)max_frame) * value);
	}

	// 現在のフレームと変更後のフレームが同じならば処理しない
	if (now_frame == next_frame) {
		return;
	}
	// メーターとマスクのフレームを更新する
	SpriteStudio::Player::setFrameNo(_handle_meter, next_frame);
	SpriteStudio::Player::apply(_handle_meter);
	// マスクは更新しない
	// SpriteStudio::Player::setFrameNo(_handle_mask, next_frame);
	// SpriteStudio::Player::apply(_handle_mask);
	// 画面を更新する
	_is_draw_update = true;
}

// 毎フレーム描画更新するかどうかのフラグを取得する
bool Gauge::getAlwaysUpdateFlag() {
	return _always_update;
}

// 毎フレーム描画更新するかどうかのフラグをセットする
void Gauge::setAlwaysUpdateFlag(bool flag) {
	// 何もアニメーションをしないなら処理を行わない
	if (!updateMotionCheck() ) {
		return;
	}
	_always_update = flag;
	// フレームを０に戻す
	SpriteStudio::Player::setFrameNo(_handle_frame, 0);
	SpriteStudio::Player::apply(_handle_frame);
	SpriteStudio::Player::setFrameNo(_handle_frame_back, 0);
	SpriteStudio::Player::apply(_handle_frame_back);
}

// 描画以外のゲージの更新処理を行う
void Gauge::run(float dt) {
	// StateがkInvisibleなら処理しない
	const UIState state = getState();
	if (state == UIState::kInvisible) {
		return;
	}
	// メーター以外はアニメーションを更新する
	if (_always_update) {
		updateMotion(_handle_frame, dt);
		updateMotion(_handle_frame_back, dt);
	}
}

// ゲージを描画する
int Gauge::draw() {
	// StateがkInvisibleなら描画しない
	if(getState() == UIState::kInvisible) {
		return kSuccessCode;
	}

	if (preRender() == kErrorCode) {
		return kErrorCode;
	}
	return drawCommon();
}

// ゲージをスクリーンに描画する
int Gauge::preRender() {
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

	// DrawAreaで左端を描画しないようにする
	if (SpriteStudio::Player::isAnimation(_handle_meter)) {
		setDrawArea(1, 1, (int)frame.width - 1, (int)frame.height - 1);
		SpriteStudio::Player::draw(_handle_meter);
		setDrawAreaFull();
	}
	// 減算描画して描画範囲を限定する
	SpriteStudio::Player::draw(_handle_mask);

	// 前景フレーム描画
	SpriteStudio::Player::draw(_handle_frame);

	_is_draw_update = false;
	return preRenderEnd();
}

// 描画を更新するアニメーションが存在するかを返す
bool Gauge::updateMotionCheck() {
	return isMotion(_handle_frame) == TRUE || isMotion(_handle_frame_back)  == TRUE;
}

// 座標をセットする
int Gauge::setPosition(float x, float y) {
	// 座標設定
	SpriteStudio::Player::setPosition(_handle_meter, x, y);
	SpriteStudio::Player::setPosition(_handle_frame, x, y);
	SpriteStudio::Player::setPosition(_handle_frame_back, x, y);
	SpriteStudio::Player::setPosition(_handle_mask, x, y);
	// アニメーション中の動きに適用
	SpriteStudio::Player::apply(_handle_meter);
	SpriteStudio::Player::apply(_handle_frame);
	SpriteStudio::Player::apply(_handle_frame_back);
	SpriteStudio::Player::apply(_handle_mask);
	return kSuccessCode;
}
