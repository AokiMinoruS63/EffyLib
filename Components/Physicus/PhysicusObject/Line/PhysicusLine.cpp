/**
 * @file PhysicusLine.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusLine.h"
#include "../PhysicusObject.h"
#include "../Common/PhysicusObjectCommon.h"
#include "../../../Utility/DxLibWrap.h"
#include "../../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include <vector>

// 直線オブジェクトを生成する
void createLineBody(Physicus::Object* obj) {
	b2Vec2 current, last, lastLast;
	const auto locus = obj->getLocus();
	auto bodies = obj->getBodies();
	b2Vec2 center;	
	b2Body* body;

	B2Vec2::recentLocus(locus, &current, &last, &lastLast);

	if(IsEmpty(bodies)) {
		center = B2Vec2::halfWay(last, current);
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef = B2BodyDef::generate(obj->getSetting().bodyType, center, Float::kMax, obj->getRotateFix());
		body = obj->getWorld()->CreateBody(&bodyDef);
		obj->append(body);
	} else {
		body = bodies.front();
		center = body->GetPosition();
	}	

	// 動体オブジェクトの形を定義する
	b2EdgeShape shape;
	shape.Set(B2Vec2::relativePosition(center, last), B2Vec2::relativePosition(center, current));

	// 動体オブジェクトの密度・摩擦の関連付け
	b2FixtureDef fixtureDef = obj->getSetting().fixture;
	fixtureDef.shape = &shape;
	// 動体に適用
	body->CreateFixture(&fixtureDef);
	
	// 直線オブジェクトは演算が出来ないため、接続は行わない
}

// 生成した直線オブジェクトを描画する
void drawLine(Physicus::Object* obj) {
	const auto images = obj->getLineImages();
	const auto bodies = obj->getBodies();
	const float roughness = obj->getRoughness();
	const float drawAdvance = obj->getDrawAdvance();
	const float width = obj->getDrawLineHalfWidth();
	if(IsEmpty(images) || IsEmpty(bodies) || roughness <= Float::kMin || drawAdvance == Float::kMin || obj->getWorldScale() == Float::kMin || width < Float::kMin) {
		return;
	}

	const int color = obj->getColor();
	int loopCount = 0;
	b2Vec2 currentRect[4];
	b2Vec2 lastRect[4], lastHalf[2];
	auto body = bodies.front();
	auto fixtureList = B2Fixture::toVector(body->GetFixtureList());
	const int fixtureNum = fixtureList.size();

	// 進行度を決定する	
	int loopNum;
	float lastAdvance;
	Float::setAdvance(loopNum, lastAdvance, drawAdvance, fixtureNum);
	b2Vec2 vertices[4], halfLeft, halfRight, lastHalfLeft, lastHalfRight;
	for(auto& itr: fixtureList){
		auto line = B2Fixture::Edge::vertices(itr, Float::kMax /  obj->getWorldScale());
		const b2Vec2 last = line.at(0);
		const b2Vec2 current = line.at(1);
		const float angle = B2Vec2::angle(last, current);
		const bool finalLoop = itr == fixtureList.back();
		if(loopCount == 0) {
			vertices[0] = B2Vec2::rotate(last, width, angle, B2Vec2::kLeading);
			vertices[1] = B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing);
		}
		vertices[2] = B2Vec2::rotate(current, width, angle, B2Vec2::kLeading);
		vertices[3] = B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing);
		halfLeft = B2Vec2::halfWay(vertices[0], vertices[2]);
		halfRight = B2Vec2::halfWay(vertices[1], vertices[3]);

		// fixtureが一つだけならそのまま描画
		if(fixtureNum == 1) {
			b2Vec2 vec[4] = {vertices[0], vertices[1], vertices[3], vertices[2]};
				drawSeparateLine(obj, vec, lastAdvance, 0);
			return;
		}
		if(loopCount == 0) {
			// 半分まで描く
			float rate;
			if(loopCount < loopNum) {
				rate = Float::kMax;
			} else if(loopCount > loopNum) {
				rate = Float::kMin;
			} else {
				rate = lastAdvance;
			}
			b2Vec2 left = B2Vec2::between(vertices[0], halfLeft, rate);
			b2Vec2 right = B2Vec2::between(vertices[1], halfRight, rate);
			drawModiGraphF( vertices[0], vertices[1], right, left, images.front() , TRUE);
		} else {
			// 前のボディの半分から現在のボディの半分までベジェ曲線を描く
			float rate;
			if(loopCount < loopNum) {
				rate = Float::kMax;
			} else if(loopCount > loopNum) {
				rate = Float::kMin;
			} else {
				rate = finalLoop ? Float::clamp(lastAdvance * 2.0, Float::kMin, Float::kMax) : lastAdvance;
			}
			if(rate > Float::kMin) {
				b2Vec2 leftVec[3] = {lastHalfLeft, vertices[0], halfLeft};
				b2Vec2 rightVec[3] = {lastHalfRight, vertices[1], halfRight};
				drawBezie(leftVec, rightVec, roughness, images, true, false, Array::kUnspecified, rate );
			}
		}
		if(finalLoop) {
			if(loopCount != loopNum || lastAdvance < Float::kHalf) {
				return;
			}
			const float rate =  (lastAdvance - Float::kHalf) * 2.0;
			vertices[2] = B2Vec2::between(halfLeft, vertices[2], rate);
			vertices[3] = B2Vec2::between(halfRight, vertices[3], rate);
			drawModiGraphF( halfLeft, halfRight, vertices[3], vertices[2], images.back() , TRUE);
		}


		loopCount++;
		vertices[0] = vertices[2];
		vertices[1] = vertices[3];
		lastHalfLeft = halfLeft;
		lastHalfRight = halfRight;
	}
}

// 現在生成している直線オブジェクトを描画する
void drawEditingLine(Physicus::Object* obj) {
	drawLine(obj);
}