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

namespace Physicus {
	enum EventTrigger {
		// 生まれた時
		kBorn,
		// 寿命を迎えた時
		kDestroy,
		// 衝突した時
		kCollision
	};

	// 生まれた時の処理
	// 寿命を迎えた時
	// 衝突した時
	// 検査するハンドルが必要

	// 衝突した時
	// 衝突する相手のハンドルもしくはグループが必要
	// 変化した時の処理が必要

	// 何をするか
	// Physicusでないパーティクルの生成
	// パーティクルからObject の変更
	// 	

	// 結論。ぶっちゃけコールバックでいいよ。
	// コールバックをstd::vecdtorでまとめてそれを処理する感じでOK

	// コールバック関数
	typedef void (*CallBackFunction)();
	struct Event {
		// 条件を成立した時に行うコールバック関数
		CallBackFunction func;
		// イベントのトリガー
		EventTrigger trigger;
		// イベントの監視対象のハンドル
		int handle;
		// 条件が満たした時に何度も行うなら**true**
		bool no_destroy;

	};
}

//struct PhysicusParticleEvent {
	// TODO: 衝突判定するグループ、作用するグループ
	// TODO: トリガーも書く
	// トリガー何ある？　コリジョン、
	// イベント何ある？　グループの変更、パーティクルからオブジェクトの変更と変更時のパーティクルの発生
	// オブジェクトクラスにも画像（Sprite）を参照出来る様にする必要がある。その画像をどのように適用する必要があるか
	// 使い方？　とりあえず、スタックに積もう
	// このスタックを置く場所。とりあえず、ワールドクラスに置くしかないか？

	// 例、入れ替え変数
	// void changeParticleToObject(int particleHandle, ObjectSetting setting/*, ここにエフェクトスプライトを表示  */)
//}

#endif