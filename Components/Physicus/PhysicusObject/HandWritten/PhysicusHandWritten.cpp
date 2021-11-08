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

// 手描き線の軌跡を作成する
void createHandwrittenLocus(Physicus::Object* obj) {
	b2Vec2 current, last, lastLast;
	const auto locus = obj->getLocus();
	auto bodies = obj->getBodies();
	b2Vec2 center;	
	b2Body* body;
	const float width = obj->getLineHalfWidth();
	B2Vec2::recentLocus(locus, &current, &last, &lastLast);
	const float angle = B2Vec2::angle(last, current);
	const bool firstAct = locus.size() == 2;
	if(locus.size() < 2) {
		printfDx("Error: locus の設定が間違っています。");
	}

	if(firstAct) {
		center = B2Vec2::halfWay(last, current);
	} else {
		center = B2Vec2::halfWay(locus.front(), locus.at(1));
	}

	// 動体オブジェクトの形を定義する
	const auto outsides = obj->getLocusOutsideLines();
	const auto insides = obj->getLocusInsideLines();
	b2Vec2 vec[4];
	
	if(firstAct) {
		vec[0] = B2Vec2::rotate(last, width, angle, B2Vec2::kLeading);
		vec[1] = B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing);
		obj->appendDrawLocusLine(vec[0], vec[1]);
	}
	vec[2] = B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing);
	vec[3] = B2Vec2::rotate(current, width, angle, B2Vec2::kLeading);
	obj->appendDrawLocusLine(vec[3], vec[2]);
}

// 手描き線オブジェクトを作成する
void createHandwrittenBody(Physicus::Object* obj, int index) {
	b2Vec2 current, last, lastLast;
	const auto locus = obj->getLocus();
	auto bodies = obj->getBodies();
	b2Vec2 center;	
	b2Body* body;
	const float width = obj->getLineHalfWidth();
	current = locus.at(index);
	last = locus.at(Int::clamp(index - 1, 0, locus.size()));
	lastLast = locus.at(Int::clamp(index - 2, 0, locus.size()));
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
		outsides.at(index - 1),
		insides.at(index - 1),
		insides.at(index),
		outsides.at(index)
	};

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

// 手描き線オブジェクトを描画する
void drawHandwritten(Physicus::Object* obj) {
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

// 編集中の手描き線オブジェクトを描画する
void drawEditingHandwritten(Physicus::Object* obj) {
	const auto images = obj->getLineImages();
	const auto locus = obj->getLocus();
	const float roughness = obj->getRoughness();
	const float drawAdvance = obj->getDrawAdvance();
	const float width = obj->getDrawLineHalfWidth();
	const int lineNum = locus.size() - 1;
	if(IsEmpty(images) || roughness <= Float::kMin || drawAdvance == Float::kMin || obj->getWorldScale() == Float::kMin || width < Float::kMin || lineNum < 1) {
		return;
	}

	const int color = obj->getColor();
	int loopCount = 0;
	b2Vec2 currentRect[4];
	b2Vec2 lastRect[4], lastHalf[2];

	// 進行度を決定する	
	int loopNum;
	float lastAdvance;
	Float::setAdvance(loopNum, lastAdvance, drawAdvance, lineNum);
	b2Vec2 vertices[4], halfLeft, halfRight, lastHalfLeft, lastHalfRight;
	for(loopCount = 0; loopCount < lineNum; loopCount++){
		const b2Vec2 last = B2Vec2::multiplication(locus.at(loopCount), Float::kMax /  obj->getWorldScale());
		const b2Vec2 current = B2Vec2::multiplication(locus.at(loopCount + 1), Float::kMax /  obj->getWorldScale());
		const float angle = B2Vec2::angle(last, current);
		const bool finalLoop = loopCount == lineNum - 1;
		if(loopCount == 0) {
			vertices[0] = B2Vec2::rotate(last, width, angle, B2Vec2::kLeading);
			vertices[1] = B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing);
		}
		vertices[2] = B2Vec2::rotate(current, width, angle, B2Vec2::kLeading);
		vertices[3] = B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing);
		halfLeft = B2Vec2::halfWay(vertices[0], vertices[2]);
		halfRight = B2Vec2::halfWay(vertices[1], vertices[3]);

		// fixtureが一つだけならそのまま描画
		if(lineNum == 1) {
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

		vertices[0] = vertices[2];
		vertices[1] = vertices[3];
		lastHalfLeft = halfLeft;
		lastHalfRight = halfRight;
	}
}

// 編集中の手描き線オブジェクトのデバッグフレームを描画する
void drawEditingHandwrittenDebug(Physicus::Object* obj) {
	std::vector<b2Vec2> outsides = obj->getLocusOutsideLines();
	std::vector<b2Vec2> insides = obj->getLocusInsideLines();
	if(outsides.size() < 2) {
		return;
	}
	const float scale = Float::kMax / obj->getWorldScale();
	const int color = obj->getColor();
	b2Vec2 outside[2], inside[2];
	for(int i = 0; i < outsides.size() - 1; i++) {
		outside[0] = B2Vec2::multiplication(outsides.at(i),     scale);
		outside[1] = B2Vec2::multiplication(outsides.at(i + 1), scale);
		inside[0] = B2Vec2::multiplication(insides.at(i),      scale);
		inside[1] = B2Vec2::multiplication(insides.at(i + 1),  scale);
		if(i == 0) {
			drawLine(outside[0].x , outside[0].y, inside[0].x, inside[0].y, color);
		}
		drawLine(outside[0].x , outside[0].y, outside[1].x, outside[1].y, color);
		drawLine(inside[0].x , inside[0].y, inside[1].x, inside[1].y, color);
		drawLine(inside[1].x , inside[1].y, outside[1].x, outside[1].y, color);
	}
}