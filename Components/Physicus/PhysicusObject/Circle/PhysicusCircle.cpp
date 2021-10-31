/**
 * @file PhysicusCircle.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusCircle.h"
#include "../PhysicusObject.h"
#include "../Common/PhysicusObjectCommon.h"
#include <vector>
#include "../../../Utility/TypeExtensions.h"

/**
 * @brief 円の線の軌跡をセットする
 * 
 * @param obj セットするオブジェクト
 * @param radius 半径
 */
void setCircleLinePositions(Physicus::Object* obj, float radius) {
	obj->removeLocusLines();
	// 円の場合は頂点の分割数を増やす
	obj->setRoughness(Constant::Object::kBezieCircleRoughness);
	const float roughness = obj->getRoughness() * Float::kQuarter;
	float t = 0;
	radius += obj->getDrawLineHalfWidth();
	bool loopEnd = false;
	#define APPEND_LINE obj->appendDrawLocusLine(B2Vec2::bezieCirclePos(B2Vec2::kZero, radius, t));
	APPEND_LINE
	t += roughness;
	while(!loopEnd) {
		APPEND_LINE
		if(t + roughness > 1.0) {
			loopEnd = true;
		}
		t += roughness;
	}
	#undef APPEND_LINE
}

/**
 * @brief 円描画時の頂点座標をセットする
 * 
 * @param si 内側の始点
 * @param so 外側の始点
 * @param gi 内側の終点
 * @param go 外側の終点
 * @param position オブジェクトの座標
 * @param inside 内側頂点配列
 * @param outside 外側頂点配列
 * @param current 始点のインデックス
 * @param next 終点のインデックス
 * @param angle オブジェクトの角度
 */
void setDrawPos(b2Vec2& si, b2Vec2& so, b2Vec2& gi, b2Vec2& go, b2Vec2 position, std::vector<b2Vec2> inside, std::vector<b2Vec2> outside, int current, int next, float angle) {
	si = inside.at(current);
	so = outside.at(current);
	gi = inside.at(next);
	go = outside.at(next);
	si = B2Vec2::rotate(si, angle);
	so = B2Vec2::rotate(so, angle);
	gi = B2Vec2::rotate(gi, angle);
	go = B2Vec2::rotate(go, angle);
	
	si = B2Vec2::add(position, si);
	so = B2Vec2::add(position, so);
	gi = B2Vec2::add(position, gi);
	go = B2Vec2::add(position, go);
}

/**
 * @brief 円の軌跡を描画する
 * 
 * @param obj オブジェクト
 * @param angle オブジェクトの角度
 * @param position オブジェクトの座標
 * @param edgeDraw 画像の先端と末尾も描画するなら**true**
 */
void drawCircleLine(Physicus::Object* obj, float angle, b2Vec2 position, bool edgeDraw = false) {
	const auto inside = obj->getLocusInsideLines();
	const auto outside = obj->getLocusOutsideLines();
	auto images = obj->getLineImages();

	if(inside.size() < 2 || IsEmpty(images)) {
		return;
	}
	const int imgCountMin = edgeDraw || images.size() < 2 ? 0 : 1;
	const int imgCountMax = Int::clamp(edgeDraw ? images.size() - 1 : images.size() - 2, 0, images.size());
	int imgIndex = imgCountMin;
	const float scale = obj->getWorldScale();
	b2Vec2 so, si, go, gi;
	for(int i = 0; i < inside.size() - 1; i++) {
		setDrawPos(si, so, gi, go, position, inside, outside, i, i + 1, angle);
		drawModiGraphF(so, si, gi, go, images.at(imgIndex), TRUE);
		imgIndex++;
		if(imgIndex > imgCountMax) {
			imgIndex = imgCountMin;
		}
	}
	setDrawPos(si, so, gi, go, position, inside, outside, inside.size() - 1, 0, angle);
	drawModiGraphF(so, si, gi, go, images.at(imgIndex), TRUE);
}

// 円オブジェクトを作成成功なら**true**
bool createCircleBody(Physicus::Object* obj) {
	const auto locus = obj->getLocus();
	if(locus.size() < 2) {
		return false;
	}
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end, false);
	float radius = B2Vec2::xyShortDistance(start, end);

	setCircleLinePositions(obj, radius);

	start = locus.front();
	end = locus.back();
	radius = B2Vec2::xyShortDistance(start, end);

	// 動体オブジェクトの参照値
	b2BodyDef bodyDef = B2BodyDef::generate(obj->getSetting().bodyType, start);
	bodyDef.position = start;
	// ボディの作成
	auto body = obj->getWorld()->CreateBody(&bodyDef);
	obj->append(body);

	// 動体オブジェクトの形を定義する
	b2CircleShape shape;
	shape.m_radius = radius;

	// 動体オブジェクトの密度・摩擦の関連付け
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	// 密度を設定
	fixtureDef.density = 1.00f;
	// 摩擦を設定
	fixtureDef.friction = 0.1f;
	// 反発を設定
	fixtureDef.restitution = 0.0;
	// 動体に適用
	body->CreateFixture(&fixtureDef);
	return true;
}

// 生成した円オブジェクトを描画する
void drawCircle(Physicus::Object* obj) {
	auto bodies = obj->getBodies();
	if(IsEmpty(bodies)) {
		return;
	}
	auto body = bodies.front();
	drawCircleLine(obj, body->GetAngle(), obj->getPosition(true));
}

// 生成した円オブジェクトのフレームを描画する
void drawCircleDebug(Physicus::Object* obj) {
	std::vector<b2Body*> bodies = obj->getBodies();
	if(IsEmpty(bodies)) {
		return;
	}
	b2Body* body = bodies.front();
	const auto fixture = body->GetFixtureList();
	auto position = fixture->GetBody()->GetPosition();
	const b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
	const float scale = obj->getWorldScale();
	const float radius = shape->m_radius;
	const float lineLength = radius * Float::kThreeQuarters;
	b2Vec2 lineEnd = B2Vec2::rotate(position, lineLength, body->GetAngle());
	B2Vec2::applyScale(&position, 1.0 / scale);
	B2Vec2::applyScale(&lineEnd, 1.0 / scale);
	
	drawCircle((int)position.x, (int)position.y, (int)(radius / scale), Color::kWhite, FALSE, FALSE);
	drawLine(position.x, position.y, lineEnd.x, lineEnd.y, Color::kWhite);
}

// 現在生成している円オブジェクトを描画する
void drawEditingCircle(Physicus::Object* obj) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end, false);
	float radius = B2Vec2::xyShortDistance(start, end);

	setCircleLinePositions(obj, radius);
	drawCircleLine(obj, Float::kMin, start);
}

// 現在生成している矩形オブジェクトのフレームを描画する
void drawEditingCircleDebug(Physicus::Object* obj) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end, false);
	const float radius = B2Vec2::xyShortDistance(start, end);
	drawCircle(start.x, start.y, radius, Color::kWhite, FALSE, FALSE);
	drawBox(start.x, start.y, end.x, end.y, Color::kWhite, FALSE);
}