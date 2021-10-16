/**
 * @file PhysicusLinksBoard.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusLinkBoard.h"
#include "../PhysicusObject.h"

// 中身がスカスカなオブジェクトの作成
void createLinkBoardBody(Physicus::Object* obj) {
	// 線の太さが一定以下なら処理を行わない
	if(obj->getLineWidth() < B2Body::kMinCreateVertexRange) {
		return;
	}
	b2Vec2 current, last, lastLast;
	B2Vec2::recentLocus(obj->getLocus(), &current, &last, &lastLast);
	
	b2Vec2 center = B2Vec2::halfWay(last, current);
	const float width = obj->getLineWidth();
	const float angle = B2Vec2::angle(last, current);
	const float lastAngle = IsEmpty(obj->getBodies()) ? angle : B2Vec2::angle(lastLast, last);

	// 直近の軌跡から矩形を作成する
	b2Vec2 vertices[4] = {
		B2Vec2::rotate(last, width, lastAngle, B2Vec2::kLeading),
		B2Vec2::rotate(last, width, lastAngle, B2Vec2::kTrailing),
		B2Vec2::rotate(current, width, angle, B2Vec2::kLeading),
		B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing)
	};
	
	
	for(int i = 0; i < 4; i++) {
		vertices[i] = B2Vec2::relativePosition(center, vertices[i]);
	}
	
	// 動体オブジェクトの参照値
	b2BodyDef bodyDef = B2BodyDef::dynamic(center, 1.0);
	// まだ物理演算を適用させない
	bodyDef.awake = false;
	// ボディの作成
	auto body = obj->getWorld()->CreateBody(&bodyDef);
	
	obj->append(body);

	// 動体オブジェクトの形を定義する
	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, 4);

	// 動体オブジェクトの密度・摩擦の関連付け
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// 密度を設定
	fixtureDef.density = 1.00f;
	// 摩擦を設定
	fixtureDef.friction = 0.1f;
	// 反発を設定
	fixtureDef.restitution = 0.0;
	// 動体に適用
	body->CreateFixture(&fixtureDef);
	
	// 接続を行う
	obj->linkCurrent(B2Joint::kWeld);
}