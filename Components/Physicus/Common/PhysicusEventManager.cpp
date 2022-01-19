/**
 * @file PhysicusEventManager.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief イベント管理クラス
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
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