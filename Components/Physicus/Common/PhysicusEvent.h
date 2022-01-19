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
#include "../../Utility/DxLibWrap.h"

namespace Physicus {
	enum class EventTrigger {
		// 生まれた時
		kBorn,
		// 寿命を迎える直前
		kWillDestroy,
		// 寿命を迎えた直後
		kDidDestroy,
		// 衝突した時
		kCollision,
		// オブジェクト・パーティクルのカウントがあるカウントに達した時
		kTimePassed
	};

	// イベントの衝突監視を行うタイプ
	enum class EventTargetType {
		// オブジェクト
		kObject,
		// パーティクル
		kParticle
	};

	// 衝突判定を行うハンドル情報(EventTriggerがkCollisionの時のみ使用)
	struct CollisionEventHandle {
		// オブジェクトorパーティクルどちらのハンドルか
		EventTargetType collision_type;
		// 衝突の判定を行う物のハンドル
		int handle;
	};

	struct Event {
		// TODO: 今のままだと条件が複雑かつ曖昧なため、もっとシンプルに考える。
		// それにEventという名前なのに実際はトリガーの事が書かれている。曖昧な命名は良くない
		// これはそもそもオブジェクトに持たせるべきでは？ -> 決定
		// 衝突検知はどうする？そもそも衝突判定自体重いから考えるべきでは？
		// 衝突判定だけはマネージャクラスに入れる必要がある。
		// いや、ボディとパーティクル間も管理しなければいけないため、ワールドクラスか？
		// まぁともかく、EventTargetTypeとハンドル２組の衝突判定を行う訳である。

		// イベントハンドルはWorldでユニークで持っていた方が良さそう。知らんけど。いや、そうか？？？
		// オブジェクト指向でマネージャクラスは使用しない方が良いのでは？
		// ということで、オブジェクトが持っているイベントはオブジェクトがイベントハンドルを採番し、
		// 衝突イベントはワールドクラスがイベントハンドルを採番する。
		// 消去する時はそれぞれに消去する関数を使い、消去するようにする

		// イベントハンドル
		int handle;
		// 条件を成立した時に行うコールバック関数
		std::function<void()> func;
		// イベントのトリガー
		EventTrigger trigger;
		// 条件となる時間(EventTriggerがkTimePassedの時のみ使用)
		LONG target_count;
		// 衝突の判定を行う物体のハンドル(EventTriggerがkCollisionの時のみ使用)
		CollisionEventHandle mineHandle, targetHandle;
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