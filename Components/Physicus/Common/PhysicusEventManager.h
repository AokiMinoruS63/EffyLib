/**
 * @file PhysicusEventManager.h
 * @brief イベント管理クラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_EVENT_MANAGER_H
#define PHYSICUS_EVENT_MANAGER_H

#include "../../Common/Object/HandleObject.h"
#include "../../Common/Type/ReturnType.h"
#include "PhysicusEvent.h"

namespace Physicus {
	class EventManager: public HandleObject<Event> {
		// MARK: - コンストラクタ・デストラクタ
		EventManager();
		~EventManager();

		// MARK: - イベントの追加・削除

		/**
		 * @brief イベントの追加
		 * 
		 * @param event 
		 * @return int イベントハンドル
		 */
		int setEvent(Event& event);

		/**
		 * @brief イベントの消去
		 * 
		 * @param handle 削除するイベントハンドル
		 * @return 正常に削除されたら**kSuccessCode**
		 */
		int deleteEvent(int handle);


	};
}

#endif