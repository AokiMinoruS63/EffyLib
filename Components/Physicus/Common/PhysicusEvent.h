/**
 * @file PhysicusEvent.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 衝突時のイベント
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_EVENT_H
#define PHYSICUS_EVENT_H

#include <functional>

namespace Physicus {
	enum EventTrigger {
		// 生まれた時
		kBorn,
		// 寿命を迎えた時
		kDestroy,
		// 衝突した時
		kCollision,
		// オブジェクト・パーティクルのカウントがあるカウントに達した時
		kTimePassed
	};

	struct Event {
		// イベントの監視対象のハンドル
		int handle;
		// 条件を成立した時に行うコールバック関数
		std::function<void()> func;
		// イベントのトリガー
		EventTrigger trigger;
		// 条件となる時間
		LONG target_count;
		// 条件となるターゲットのハンドル
		int target_handle;
		// 条件となるターゲットのグループ
		int target_group;
		// 条件が満たした時に何度も行うなら**true**
		bool no_destroy;
	};

	/*
	// コールバック関数の使い方
	Event ev;
	// 通常の関数を代入したい時
	ev.func = [&]() { return hoge(); };
	// インスタンスの関数を代入したい時
	HogeClass* hoge_class = new HogeClass();
	ev.func = [&]() { return hoge_class->hoge(); };
	*/
}

#endif