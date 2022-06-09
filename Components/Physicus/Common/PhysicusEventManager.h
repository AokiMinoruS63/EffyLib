/**
 * @file PhysicusEventManager.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief イベント管理クラス
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
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