/**
 * @file BloomEffect.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ブルームエフェクト用のスクリーン
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "BloomEffect.h"
#include "../Utility/DxLibWrap.h"
#include "../Utility/TypeExtensions.h"

using namespace Effect;
using namespace ScreenState;
using namespace GraphEffect;

// コンストラクタ
Bloom::Bloom(int bright_clip_value) {
	bright_clip_value_ = bright_clip_value;
	const Frame frame =  getScreenState();
	const float width = (float)frame.width;
	const float height = (float)frame.height;
	current_screen_ = makeScreen(frame.width, frame.height, TRUE);
	bright_screen_ = makeScreen(frame.width, frame.height, TRUE);
	gauss_screen_a4_ = makeScreen((int)(width * Float::kQuarter), (int)(height * Float::kQuarter));
	gauss_screen_a8_ = makeScreen((int)(width * Float::kOneEight), (int)(height * Float::kOneEight));
	gauss_screen_a16_ = makeScreen((int)(width * Float::kOneSixteen), (int)(height * Float::kOneSixteen));
}

// デストラクタ
Bloom::~Bloom() {
	deleteGraph(current_screen_);
	deleteGraph(bright_screen_);
	deleteGraph(gauss_screen_a4_);
	deleteGraph(gauss_screen_a8_);
	deleteGraph(gauss_screen_a16_);
}

// 描画準備
void Bloom::preRender() {
	screen_state_.saveScreenState(true);
	setDrawScreen(current_screen_);
	clearDrawScreen();
}

// 描画処理
void Bloom::postRender() {
	// スクリーンを開始前のスクリーンに戻す
	setDrawScreen(screen_state_.screen);
	// スクリーンのスクリーンサイズを取得する
	const Frame frame =  getScreenState();
	// 描画結果から高輝度部分のみを抜き出した画像を得る
	graphFilterBlt(current_screen_, bright_screen_, Filter::kBrightClip, Type::kCmpLess, bright_clip_value_, TRUE, Color::kBlack, 255);
	// 高輝度部分を4分の1に縮小した画像を得る
	graphFilterBlt(bright_screen_, gauss_screen_a4_, Filter::kDownScale, 4 ) ;
	// 高輝度部分を8分の1に縮小した画像を得る
	graphFilterBlt(gauss_screen_a4_, gauss_screen_a8_, Filter::kDownScale, 2 ) ;
	// 高輝度部分を16分の1に縮小した画像を得る
	graphFilterBlt(gauss_screen_a8_, gauss_screen_a16_, Filter::kDownScale, 2 ) ;
	// 通常の描画を行う
	drawGraph(0, 0, current_screen_, TRUE);
	// 線形補完
	setDrawMode(Lerp::kBilinear);
	// 描画ブレンドモードを加算にする
	setDrawBlendMode(BlendMode::init(BlendMode::kAdd, 1.0f));
	// 2回描画を行う
	drawExtendGraph(0, 0, frame.width, frame.height, gauss_screen_a16_, FALSE);
	drawExtendGraph(0, 0, frame.width, frame.height, gauss_screen_a16_, FALSE);

	// スクリーンを元に戻す
	screen_state_.loadScreenState(true);
}