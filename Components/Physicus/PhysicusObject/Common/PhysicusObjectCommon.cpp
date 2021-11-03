/**
 * @file PhysicusObjectCommon.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
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

// １つの直線を分割して描画する
int drawSeparateLine(Physicus::Object* obj, b2Vec2 vec[4], float drawAdvance, int imageIndex) {
	int loopNum;
	float lastAdvance;
	auto images = obj->getLineImages();
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