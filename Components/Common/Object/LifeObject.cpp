/**
 * @file LifeObject.cpp
 * @brief カウントを保持するオブジェクト
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "LifeObject.h"

// 生成されてからのフレーム数を取得する
LONG LifeObject::getCount() {
	return count_;
}

// 生成されてからのフレーム数をセットする
void LifeObject::setCount(LONG count) {
	count_ = count;
}

// フレームを寿命に持つオブジェクトを初期化する
void LifeObject::lifeObjectInit() {
	count_ = 0;
	life_destroy_enable_ = false;
	is_life_end_ = false;
	life_span_ = 0;
	remaining_life_ = 0;
}

// フレーム数による寿命があるなら**true**
bool LifeObject::getLifeDestroyEnable() {
	return life_destroy_enable_;
}

// フレーム数による寿命を設定する
void LifeObject::setLifeDestroyEnable(bool life_destroy_enable) {
	life_destroy_enable_ = life_destroy_enable;
}

// フレーム数による寿命を終えていたら**true**
bool LifeObject::getLifeEnd() {
	return is_life_end_;
}

// フレーム数による寿命を設定する
void LifeObject::setLifeSpan(LONG life_span) {
	life_span_ = life_span;
}

// 残り寿命のフレームの取得
LONG LifeObject::getRemainingLife() {
	return remaining_life_;
}

// カウントを進める
void LifeObject::timeCalc() {
	count_++;
	if(!life_destroy_enable_) {
		return;
	}
	if(life_span_ < count_) {
		is_life_end_ = true;
	}
	remaining_life_ = life_span_ - count_;
}