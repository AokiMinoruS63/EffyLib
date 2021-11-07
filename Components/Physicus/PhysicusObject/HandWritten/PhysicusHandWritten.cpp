/**
 * @file PhysicusHandWritten.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusHandWritten.h"
#include "../PhysicusObject.h"
#include "../Common/PhysicusObjectCommon.h"
#include "../../../Utility/DxLibWrap.h"
#include "../../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include <vector>

// 手書き線オブジェクトを作成する
void createHandwrittenBody(Physicus::Object* obj) {
	b2Vec2 current, last, lastLast;
	const auto locus = obj->getLocus();
	auto bodies = obj->getBodies();
	b2Vec2 center;	
	b2Body* body;
	const float width = obj->getLineHalfWidth();
	B2Vec2::recentLocus(locus, &current, &last, &lastLast);
	const float angle = B2Vec2::angle(last, current);
	const bool firstBody = IsEmpty(bodies);

	if(firstBody) {
		center = B2Vec2::halfWay(last, current);
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef = B2BodyDef::generate(b2_dynamicBody, center, Float::kMax, obj->getRotateFix());
		bodyDef.awake = false;
		body = obj->getWorld()->CreateBody(&bodyDef);
		obj->append(body);
	} else {
		body = bodies.front();
		center = body->GetPosition();
	}

	// 動体オブジェクトの形を定義する
	b2PolygonShape shape;
	const auto outsides = obj->getLocusOutsideLines();
	const auto insides = obj->getLocusInsideLines();
	b2Vec2 vec[4] = {
		IsEmpty(outsides) ? B2Vec2::rotate(last, width, angle, B2Vec2::kLeading) : outsides.back(),
		IsEmpty(insides) ? B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing) : insides.back(),
		B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing),
		B2Vec2::rotate(current, width, angle, B2Vec2::kLeading)
	};
	if(firstBody) {
		obj->appendDrawLocusLine(vec[0], vec[1]);
	}
	obj->appendDrawLocusLine(vec[3], vec[2]);
	for(int i = 0; i < 4; i++) {
		vec[i] = B2Vec2::relativePosition(center, vec[i]);
	}
	shape.Set(vec, 4);

	// 動体オブジェクトの密度・摩擦の関連付け
	b2FixtureDef fixtureDef = obj->getSetting().fixture;
	fixtureDef.shape = &shape;
	// 動体に適用
	body->CreateFixture(&fixtureDef);
}

// 手書き線オブジェクトを描画する
void drawHandwritten(Physicus::Object* obj, bool editing) {
	const auto images = obj->getLineImages();
	const auto bodies = obj->getBodies();
	const float roughness = obj->getRoughness();
	const float drawAdvance = obj->getDrawAdvance();
	const float width = obj->getDrawLineHalfWidth();
	const float scale = obj->getWorldScale();
	const b2Vec2 localPosition = obj->getPosition(false);
	const b2Vec2 grobalPosition = obj->getPosition(true);
	if(IsEmpty(images) || IsEmpty(bodies) || roughness <= Float::kMin || drawAdvance == Float::kMin || obj->getWorldScale() == Float::kMin || width < Float::kMin || scale <= Float::kMin) {
		return;
	}

	const int color = obj->getColor();
	int loopCount = 0;
	b2Vec2 currentRect[4];
	b2Vec2 lastRect[4], lastHalf[2];
	auto body = bodies.front();
	const float angle = body->GetAngle();
	auto fixtureList = B2Fixture::toVector(body->GetFixtureList());
	const int fixtureNum = fixtureList.size();

	// 進行度を決定する	
	int loopNum;
	float lastAdvance;
	Float::setAdvance(loopNum, lastAdvance, drawAdvance, fixtureNum);

	b2Vec2 vertices[4], halfLeft, halfRight, lastHalfLeft, lastHalfRight;
	auto insides = obj->getLocusInsideLines();
	auto outsides = obj->getLocusOutsideLines();
	for(auto& itr: fixtureList){
		const bool finalLoop = itr == fixtureList.back();
		vertices[0] = outsides.at(loopCount);
		vertices[1] = insides.at(loopCount);
		vertices[2] = outsides.at(loopCount + 1);
		vertices[3] = insides.at(loopCount + 1);

		for(int i = 0; i < 4; i++) {
			if(editing) {
				vertices[i] = B2Vec2::sub(vertices[i], localPosition);
			}
			vertices[i] = B2Vec2::rotate(vertices[i], angle);
			vertices[i] = B2Vec2::multiplication(vertices[i], 1.0 / scale);
			vertices[i] = B2Vec2::add(vertices[i], grobalPosition);
		}
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
		lastHalfLeft = halfLeft;
		lastHalfRight = halfRight;
	}
}

// 編集中の手書き線オブジェクトを描画する
void drawEditingHandwritten(Physicus::Object* obj) {
	drawHandwritten(obj, true);
}