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

#include "../../OpenSource/Box2D/box2d/box2d.h"
#include "Float+Extensions.h"

namespace B2Joint {

	/**
	 * @brief 溶接ジョイントを作成する（溶接ジョイントは回転を抑制出来ないため、回転させない場合はrevoluteJointを使用）
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 溶接するボディ１
	 * @param body2 溶接するボディ２
	 * @param jointPosition 溶接する座標
	 * @return b2Joint* 
	 */
	static b2Joint* weldJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 jointPosition) {
		// ジョイントの定義
		b2WeldJointDef jointDef;
		jointDef.Initialize(body1, body2, jointPosition);
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}

	/**
	 * @brief 距離固定ジョイントの作成
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 連結するボディ１
	 * @param body2 連結するボディ２
	 * @param jointPosition 連結する座標
	 * @param length 距離
	 * @return b2Joint* 
	 */
	static b2Joint* distanceJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 jointPosition) {
		// ジョイントの定義
		b2DistanceJointDef jointDef;
		jointDef.Initialize(body1, body2, jointPosition, jointPosition);
		jointDef.stiffness = 99999;
		jointDef.collideConnected = true;
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
	 * @param jointPosition 連結する座標
	 * @return b2Joint* 
	 */
	static b2Joint* revoluteJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 jointPosition) {
		// ジョイントの定義
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(body1, body2, jointPosition);
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}

	/**
	 * @brief 滑車のジョイント
	 * 
	 * @param world 物理演算を行うワールド
	 * @param body1 連結するボディ１
	 * @param body2 連結するボディ２
	 * @param jointPosition 連結する座標
	 * @param axis 移動するベクトル
	 * @return b2Joint* 
	 */
	static b2Joint* prismaticJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 jointPosition, b2Vec2 axis = b2Vec2(1.0, 0)) {
		// ジョイントの定義
		b2PrismaticJointDef jointDef;
		jointDef.Initialize(body1, body2, jointPosition, axis);
		// ジョイントを作る
		return world->CreateJoint(&jointDef);
	}
};

#endif