/**
 * @file PhysicusObjectCommon.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "PhysicusObjectCommon.h"
#include "../PhysicusObject.h"
#include <vector>

using namespace Physicus;

// 矩形の始点と終点をセットする
void setDrawStartEnd(Object* obj, b2Vec2* start, b2Vec2* end, bool swap) {
	const std::vector<b2Vec2> locus = obj->getLocus();
	if(locus.size() < 2) {
		return;
	}
	const float scale = 1.0 / obj->getWorldScale();
	*start = B2Vec2::multiplication(locus.front(), scale);
	*end = B2Vec2::multiplication(locus.back(), scale);
	if(swap) {
		B2Vec2::setStartEnd(start, end);
	}
}

// 軌跡から線の太さを考慮した頂点を設定する
void getVertices(Object* obj, std::vector<b2Vec2> vertices, b2Vec2 outside[4], b2Vec2 inside[4]) {
	const float width = obj->getLineHalfWidth() / obj->getWorldScale();

	// 各頂点
	outside[0] = B2Vec2::rotate(vertices.at(0), width, Float::Angle::kRightTop, B2Vec2::Horizon::kLeading);
	inside[0] = B2Vec2::rotate(vertices.at(0), width, Float::Angle::kRightTop, B2Vec2::Horizon::kTrailing);
	outside[1] = B2Vec2::rotate(vertices.at(1), width, Float::Angle::kRightBottom, B2Vec2::Horizon::kLeading);
	inside[1] = B2Vec2::rotate(vertices.at(1), width, Float::Angle::kRightBottom, B2Vec2::Horizon::kTrailing);
	outside[2] = B2Vec2::rotate(vertices.at(2), width, Float::Angle::kLeftBottom, B2Vec2::Horizon::kLeading);
	inside[2] = B2Vec2::rotate(vertices.at(2), width, Float::Angle::kLeftBottom, B2Vec2::Horizon::kTrailing);
	outside[3] = B2Vec2::rotate(vertices.at(3), width, Float::Angle::kLeftTop, B2Vec2::Horizon::kLeading);
	inside[3] = B2Vec2::rotate(vertices.at(3), width, Float::Angle::kLeftTop, B2Vec2::Horizon::kTrailing);	
}

// 線の軌跡を作成する
void createLineLocus(Physicus::Object* obj) {
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

// １つの直線を分割して描画する
int drawSeparateLine(Physicus::Object* obj, b2Vec2 vec[4], float drawAdvance, int imageIndex) {
	int loopNum;
	float lastAdvance;
	auto images = obj->getImages();
	const float roughness = obj->getRoughness();
	const int separateNum = (int)(Float::kMax / roughness);
	float t;
	Float::setAdvance(loopNum, lastAdvance, drawAdvance, separateNum);
	b2Vec2 vertices[4];
	b2Vec2 plusVec[2];
	vertices[2] = vec[2];
	vertices[3] = vec[3];
	plusVec[0] = B2Vec2::multiplication(B2Vec2::sub(vec[0], vec[3]), roughness);
	plusVec[1] = B2Vec2::multiplication(B2Vec2::sub(vec[1], vec[2]), roughness);
	for(int i = 0; i < separateNum; i++) {
		// vertices[0]とvertices[1]を計算する
		if(drawAdvance == Float::kMax || loopNum > i) {
			t = Float::kMax;
		} else if (loopNum < i || drawAdvance == Float::kMin) {
			return imageIndex;
		} else {
			t = lastAdvance;
		}
		vertices[0] = B2Vec2::add(vertices[3], B2Vec2::multiplication(plusVec[0], t));
		vertices[1] = B2Vec2::add(vertices[2], B2Vec2::multiplication(plusVec[1], t));

		drawModiGraphF(vertices[3], vertices[2], vertices[1], vertices[0], images.at(imageIndex), TRUE);
		imageIndex = nextImageIndex(images, imageIndex, true, false);

		vertices[2] = vertices[1];
		vertices[3] = vertices[0];
	}
	return imageIndex;
}

// 編集中の手描き線・リンクボードオブジェクトを描画する
void drawEditingLine(Physicus::Object* obj) {
	const auto images = obj->getImages();
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

// 編集中の手描き線・リンクボードオブジェクトのデバッグフレームを描画する
void drawEditingLineDebug(Physicus::Object* obj) {
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