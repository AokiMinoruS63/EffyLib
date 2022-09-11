/**
 * @file SpriteStudioButton.cpp
 * @brief SpriteStudioで動くボタン
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudio.h"
#include "SpriteStudioButton.h"
#include "../Common/Type/ReturnType.h"
#include "../Common/Constant/MathConstant.h"
#include <vector>

using namespace SpriteStudio;

// コンストラクタ
Button::Button(std::string path, std::string ssae_name, bool fadein_animation, float x, float y) {
	_handle = Player::add(path);
	_is_draw_update = false;
	_ssae_name = ssae_name;
	if(_handle == kErrorCode) {
		// TODO: プラットフォーム別に対応したエラーコード出力
		printfDx("Failed to create SpriteStudio Button.");
		return;
	}
	// アニメーションを再生する
	_anime_list = Player::getAnimeNameList(_handle, _ssae_name);
	if(_anime_list.size() < 1) {
		// TODO: プラットフォーム別に対応したエラーコード出力
		printfDx("Failed to make SpriteStudio Button's screen.");
		return;
	}
	
	setAnimeState(fadein_animation ? (_anime_list.size() <= (int)UIAnimeState::kFadein ? UIAnimeState::kNormal : UIAnimeState::kFadein) : UIAnimeState::kNormal);

	// サイズを抽出するためにアニメを再生させる
	play(UIAnimeState::kNormal);
	// サイズ抽出。
	int width, height;
	Player::getFrameSize(_handle, &width, &height);
	// スクリーン作成
	this->makeScreen(width, height);
	// 座標、フレームサイズを設定する
	setFrame(Rect(x, y, (float)width, (float)height));
	// フェードインアニメーションを再生するなら変更する
	if(fadein_animation && _anime_list.size() >= (int)UIAnimeState::kFadein) {
		changeAnimation(UIAnimeState::kFadein);
	}
	// 描画更新フラグを立てる
	_is_draw_update = true;
	// スクリーンに描画
	preRender();
}

// デストラクタ
Button::~Button() {
	// スクリーンをメモリから解放する
	removeScreen();
}

// ボタンを走らせる
void Button::run(touch_t touch, float dt) {
	// StateがkInvisibleなら処理しない
	UIState state = getState();
	UIAnimeState anime_state = getAnimeState();
	if (state == UIState::kInvisible) {
		return;
	}
	// 現在のアニメーションフレーム取得
	const int anime_frame = SpriteStudio::Player::getFrameNo(_handle);

	UIAreaState area_state = getAreaState(touch);

	// アニメーションを進める
	SpriteStudio::Player::update(_handle, dt);

	if ((int)anime_state != 0)
	
	if(SpriteStudio::Player::isEndFrame(_handle)) {
		// アニメーション遷移を行う
		if (anime_state == UIAnimeState::kFadein) {
			changeAnimation(UIAnimeState::kNormal);
		} else if (anime_state == UIAnimeState::kEntered) {
			changeAnimation(UIAnimeState::kHover);
		} else if (anime_state == UIAnimeState::kHover) {
			if (area_state == UIAreaState::kJustAreaOut || area_state == UIAreaState::kNoTouch) {
				changeAnimation(UIAnimeState::kExited);
			}
		} else if (anime_state == UIAnimeState::kExited) {
			changeAnimation(UIAnimeState::kNormal);
		} else if(!SpriteStudio::Player::isNoMotion(_handle) && anime_state != UIAnimeState::kFadeout) {
			SpriteStudio::Player::setFrameNo(_handle, 0);
		}
	}

	// 動いていたら再描画
	if (anime_frame != SpriteStudio::Player::getFrameNo(_handle)) {
		_is_draw_update = true;
	}

	// 状態が判定がオンになっていなければこれ以降の処理は作成しない
	if (state != UIState::kActive) {
		return;
	}

	// 標準の時にエリアイン又はタッチされたらkEnterd
	if (anime_state == UIAnimeState::kNormal) {
		if (area_state == UIAreaState::kAreaIn || area_state == UIAreaState::kJustTap) {
			changeAnimation(UIAnimeState::kEntered);
		}
	} else if (anime_state == UIAnimeState::kEntered || anime_state == UIAnimeState::kHover) {
		// ボタンがタップされたらフェードアウト、アクション実行
		if (area_state == UIAreaState::kJustRelease) {
			if (changeAnimation(UIAnimeState::kFadeout) == kErrorCode) {
				changeAnimation(UIAnimeState::kExited);
			}
			runAction();
		} else if (area_state == UIAreaState::kJustAreaOut) {
			// 範囲外になったらリリースアニメーションを出す
			// TODO: anime_state == UIAnimeState::kEnteredの時は進行率を1.0-進行率として代入し直す
			changeAnimation(UIAnimeState::kExited);
		}
	} else if (anime_state == UIAnimeState::kHover && area_state == UIAreaState::kJustAreaOut) {
		// kHoverの時にエリアアウトしたらkExited
		changeAnimation(UIAnimeState::kExited);
	} else if (anime_state == UIAnimeState::kExited && area_state == UIAreaState::kJustAreaIn) {
		// TODO: kExitedの時に再度入ったらkEntered
		// 進行率を1.0-進行率として代入し直す
		changeAnimation(UIAnimeState::kEntered);
	}
}

// ボタンを描画する
int Button::draw() {
	// StateがkInvisibleなら描画しない
	if(getState() == UIState::kInvisible) {
		return kSuccessCode;
	}

	// 描画更新をしていたらスクリーンに表示する
	preRender();
	
	const UIAnimeState anime = getAnimeState();
	int returnValue;
	if(anime == UIAnimeState::kFadein || anime == UIAnimeState::kFadeout) {
		returnValue = SpriteStudio::Player::draw(_handle);
	} else {
		Rect frame = getFrame();
		// TODO: リンクしているssPlayerの拡大率、アルファ値、角度を設定する
		float scale = 1.0;
		float radian = 0.0;
		float alpha = 1.0;
		int blend_mode = BlendMode::kNoBlend;
		const int linked_handle = getLinkedPlayerHandle();
		ScreenStateResume resume;
		SpriteStudioResult result;
		if(SpriteStudio::Player::getPartState(linked_handle, result, getLinkedAnimationName().c_str()) == kSuccessCode) {
			frame.x = result.x;
			frame.y = result.y;
			scale = result.scaleX;
			alpha = ((float)result.opacity) * 255.0;
			blend_mode = result.colorBlendType;
			radian = result.rotationZ * (1.0 / 360.0) * kPiFloat;
		}
		if(blend_mode != BlendMode::kNoBlend) {
			resume.saveBlend();
			setDrawBlendMode(blend_mode, alpha);
		}
		returnValue = drawRotaGraph(frame.x, frame.y, scale, radian, getScreen(), true);
		if(blend_mode != BlendMode::kNoBlend) {
			resume.loadScreenState();
		}
		if(blend_mode != BlendMode::kNoBlend) {
			resume.loadBlend();
		}
	}
	return returnValue;
}

// アニメーションを変更する
int Button::changeAnimation(UIAnimeState animation) {
	if(_anime_list.size() <= (int)animation) {
		return kErrorCode;
	}
	int loop;
	switch (animation) {
		case UIAnimeState::kNormal: loop = TRUE; break;
		case UIAnimeState::kEntered: loop = FALSE; break;
		case UIAnimeState::kHover: loop = TRUE; break;
		case UIAnimeState::kExited: loop = FALSE; break;
		case UIAnimeState::kFadein: loop = FALSE; break;
		case UIAnimeState::kFadeout: loop = FALSE; break;
		default: loop = TRUE;
	}
	// フェードイン、フェードアウトの場合はY座標が中心に来るよう調整する
	bool isPadding = animation == UIAnimeState::kFadein || animation == UIAnimeState::kFadeout;
	if (isPadding) {
		float x, y;
		SpriteStudio::Player::getPosition(_handle, &x, &y);
		auto frame = getFrame();
		// 座標系を合わせる処理を挟む
		SpriteStudio::Player::setPosition(_handle, frame.x, getScreenHeight() - frame.y);
	}
	// 再生する
	play(animation, loop);
	setAnimeState(animation);
	// 描画更新フラグを立てる
	_is_draw_update = true;
	return kSuccessCode;
}

// ボタンの持つスクリーンに描画する
int Button::preRender() {
	if (!_is_draw_update) {
		return kSuccessCode;
	}
	// フェードイン、フェードアウトの場合は事前描画は行わない
	const auto anime = getAnimeState();
	if (anime == UIAnimeState::kFadein || anime == UIAnimeState::kFadeout) {
		return kSuccessCode;
	}
	if(preRenderInit() == kErrorCode) {
		return kErrorCode;
	}
	Rect frame = getFrame();

	// 座標を変えても再生するまで座標の変更が反映されないため、再度再生する
	SpriteStudio::Player::setPosition(_handle, frame.halfWidth(), frame.halfHeight());
	SpriteStudio::Player::apply(_handle);
	// 描画実行
	clearDrawScreen();
	SpriteStudio::Player::draw(_handle);
	SpriteStudio::Player::setPosition(_handle, frame.x, frame.y);
	SpriteStudio::Player::apply(_handle);
	_is_draw_update = false;
	return preRenderEnd();
}

// アニメーションを再生する
int Button::play(UIAnimeState anime_index, int loop, int start_frame_no) {
	_play_animation = anime_index;
	return SpriteStudio::Player::play(_handle, _anime_list.at((int)anime_index), loop == TRUE ? 0 : 1, start_frame_no);
}

// 座標を取得する
int Button::getPosition(float *x, float *y) {
	Rect frame = getFrame();
	*x = frame.x;
	*y = frame.y;
	return kSuccessCode;
}

// 座標をセットする
int Button::setPosition(float x, float y) {
	setFramePotision(x, y);
	return SpriteStudio::Player::setPosition(_handle, x, y);
}

// ボタンを描画・判定共に行う状態にする
int Button::setActived() {
	// Stateを変更する
	setState(UIState::kActive);
	// ボタンが既に活性状態（kDisabledでない）なら何もしないでkSuccessCodeを返す
	if(getAnimeState() != UIAnimeState::kDisabled) {
		return kSuccessCode;
	}
	// ノーマルアニメーションを再生し、失敗したらエラーを返す
	if(changeAnimation(UIAnimeState::kNormal) == kErrorCode) {
		return kErrorCode;
	}
	// 描画更新フラグを立てる
	_is_draw_update = true;
	return kSuccessCode;
}

// ボタンを描画は行うが、判定は行わない状態にする
int Button::setUnresponsive() {
	// Stateを変更する
	setState(UIState::kUnresponsive);
	// ノーマルアニメーションを再生し、失敗したらエラーを返す
	if(changeAnimation(UIAnimeState::kNormal) == kErrorCode) {
		return kErrorCode;
	}
	// 描画更新フラグを立てる
	_is_draw_update = true;
	return kSuccessCode;
}

// ボタンを使用できない事を示す描画を行い、判定は行わない状態にする
int Button::setDisabled() {
	// Stateを変更する
	setState(UIState::kDisable);
	// ボタンが既に非活性なら何もしないでkSuccessCodeを返す
	if(getAnimeState() == UIAnimeState::kDisabled) {
		return kSuccessCode;
	}

	if(_anime_list.size() <= (int)UIAnimeState::kDisabled) {
		return kErrorCode;
	}
	play(UIAnimeState::kDisabled);
	setAnimeState(UIAnimeState::kDisabled);
	// 描画更新フラグを立てる
	_is_draw_update = true;
	return kSuccessCode;
}

// ボタンを描画も判定も行わない状態にする
int Button::setInvisible() {
	// Stateを変更する
	setState(UIState::kInvisible);
	return kSuccessCode;
}
