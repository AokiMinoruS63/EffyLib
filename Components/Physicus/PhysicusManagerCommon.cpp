/**
 * @file PhysicusManagerCommon.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 物理演算のオブジェクト・パーティクルのためのオーバーライド用のクラス
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusManagerCommon.h"
#include "../Utility/DxLibWrap.h"

// ハンドルのカウンタを一つ進める
void PhysicusManagerCommon::addHandleCounter() {
	handle_counter_++;
}

// フレームアウトしているかチェックする
void PhysicusManagerCommon::checkFrameOut() {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::checkFrameOut\"関数が呼ばれました。\n");
}

// タッチによってオブジェクト又はパーティクルを生成する
int PhysicusManagerCommon::touchCreate(touch_t touch) {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::touchCreate\"関数が呼ばれました。\n");
	return NULL;
}

// 現在生成しているオブジェクト又はパーティクルを描画する
void PhysicusManagerCommon::drawEditing() {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::drawEditing\"関数が呼ばれました。\n");
}

// オブジェクト又はパーティクルを描画する
void PhysicusManagerCommon::draw() {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::touchCreate\"関数が呼ばれました。\n");
}

// オブジェクト又はパーティクルのフレームを描画する
void PhysicusManagerCommon::drawDebugFrame() {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::drawDebugFrame\"関数が呼ばれました。\n");
}

// 現在生成しているオブジェクト又はパーティクルのフレームを描画する
void PhysicusManagerCommon::drawEditingDebugFrame() {
	printfDx("ERROR: 継承されずに\"PhysicusManagerCommon::drawEditingDebugFrame\"関数が呼ばれました。\n");
}