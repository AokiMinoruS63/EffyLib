/**
 * @file PhysicusEventManager.cpp
 * @brief イベント管理クラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "PhysicusEventManager.h"

using namespace Physicus;

// コンストラクタ
EventManager::EventManager() {
}

// デストラクタ
EventManager::~EventManager() {
}

// イベントの追加
int EventManager::setEvent(Event& event) {
	// TODO: イベントを追加する
	return 0;
}

// イベントの消去
int EventManager::deleteEvent(int handle) {
	// TODO: イベントの探査を行う
	return kErrorCode;
	return kSuccessCode;
}