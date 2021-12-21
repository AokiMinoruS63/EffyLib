/**
 * @file B2Joint+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2_JOINT_EXTENSION_H
#define B2_JOINT_EXTENSION_H

#include "../../OpenSource/Box2D/Box2D.h"
#include "Float+Extensions.h"

namespace B2Joint {
	// ジョイントのタイプ
	enum Type {
		// 溶接ジョイント
		kWeld = 0,
		// 回転ジョイント
		kRevolute = 1,
		// 距離固定ジョイント
		kDistance = 2,
		// 滑車ジョイント
		kPrismatic = 3
	};

	/**
	 * @brief 溶接ジョイントを作成する
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 溶接するボディ１
	 * @param body2 溶接するボディ２
	 * @param joint_position 溶接する座標
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */

	/**
	 * @brief 
	 * 
	 * @param world 
	 * @param body1 
	 * @param body2 
	 * @param joint_position 
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* weldJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 joint_position, bool collide_connected = false) {
		// ジョイントの定義
		b2WeldJointDef jointDef;
		jointDef.Initialize(body1, body2, joint_position);
		jointDef.collideConnected = collide_connected;
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}

	/**
	 * @brief 一番手前のボディとその一つ前のボディとの間に溶接ジョイントを作成する
	 * 
	 * @param world 物理演算を行うワールド
	 * @param bodies bodyVector
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* weldJointCurrent(b2World* world, std::vector<b2Body*> bodies, bool collide_connected = false) {
		// ボディが一つなら処理しない
		if(bodies.size() < 2) {
			return NULL;
		}
		const auto current = bodies.back();
		const auto last = bodies.at(bodies.size() - 2);
		return weldJoint(world, last, current, B2Vec2::halfWay(last->GetWorldCenter(), current->GetWorldCenter()), collide_connected);
	}

	/**
	 * @brief ボディを数珠繋ぎにする
	 * 
	 * @param world 
	 * @param bodies 
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* weldJointTieLoop(b2World* world, std::vector<b2Body*> bodies, bool collide_connected = false) {
		// ボディが一つなら処理しない
		if(bodies.size() < 2) {
			return NULL;
		}
		const auto current = bodies.back();
		const auto start = bodies.front();
		return weldJoint(world, current, start, B2Vec2::halfWay(current->GetWorldCenter(), start->GetWorldCenter()), collide_connected);
	}

	/**
	 * @brief 距離固定ジョイントの作成
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 連結するボディ１
	 * @param body2 連結するボディ２
	 * @param joint_position 連結する座標
	 * @param length 距離
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* distanceJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 joint_position, bool collide_connected = false) {
		// ジョイントの定義
		b2DistanceJointDef jointDef;
		jointDef.Initialize(body1, body2, joint_position, joint_position);
		jointDef.collideConnected = collide_connected;
		jointDef.length = 0;
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}

	/**
	 * @brief 回転ジョイントを作成する
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 連結するボディ１
	 * @param body2 連結するボディ２
	 * @param joint_position 連結する座標
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* revoluteJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 joint_position, bool collide_connected = false) {
		// ジョイントの定義
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(body1, body2, joint_position);
		jointDef.collideConnected = collide_connected;
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}

	/**
	 * @brief 滑車のジョイント
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 連結するボディ１
	 * @param body2 連結するボディ２
	 * @param joint_position 連結する座標
	 * @param axis 移動するベクトル
	 * @param collide_connected ジョイントで繋がれた同士のボディが互いに貫通しないなら**true**
	 * @return b2Joint* 
	 */
	inline b2Joint* prismaticJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 joint_position, b2Vec2 axis = b2Vec2(1.0, 0), bool collide_connected = false) {
		// ジョイントの定義
		b2PrismaticJointDef jointDef;
		jointDef.Initialize(body1, body2, joint_position, axis);
		jointDef.collideConnected = collide_connected;

		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}
};

#endif