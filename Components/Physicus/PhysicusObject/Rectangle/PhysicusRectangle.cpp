/**
 * @file  PhysicusRectangle.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusRectangle.h"
#include "../PhysicusObject.h"
#include "../Common/PhysicusObjectCommon.h"
#include <vector>

using namespace Physicus;

/**
 * @brief 矩形の線を考慮した頂点を設定する
 * 
 * @param obj 矩形オブジェクト
 * @param outside 外周
 * @param inside 内周
 */
void getVertices(Object* obj, b2Vec2 outside[4], b2Vec2 inside[4]) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end);
	Frame frame = {start, end};
	getVertices(obj, frame.verticesAround(), outside, inside);
}

// 矩形オブジェクトを作成成功なら**true**
bool createRectangleBody(Object* obj) {
	const auto locus = obj->getLocus();
	if(locus.size() < 2) {
		return false;
	}

	// TODO: 矩形オブジェクトを作成する
	b2Vec2 start, end, center, rect;
	start = locus.front();
	end = locus.back();
	B2Vec2::setStartEnd(&start, &end);
	center = B2Vec2::halfWay(start, end);
	rect = B2Vec2::multiplication(B2Vec2::sub(end, start), Float::kHalf);

	// 動体オブジェクトの参照値
	b2BodyDef bodyDef = B2BodyDef::generate(obj->getSetting().bodyType, center, Float::kMax, obj->getRotateFix());
	// ボディの作成
	auto body = obj->getWorld()->CreateBody(&bodyDef);
	obj->append(body);

	// 動体オブジェクトの形を定義する
	b2PolygonShape shape;
	shape.SetAsBox(rect.x, rect.y);

	// 動体オブジェクトの密度・摩擦の関連付け
	b2FixtureDef fixtureDef = obj->getSetting().fixture;
	fixtureDef.shape = &shape;
	// 動体に適用
	body->CreateFixture(&fixtureDef);
	return true;
}

/**
 * @brief 矩形を描画する
 * 
 * @param obj 描画するオブジェクト
 * @param outside 外側の頂点配列
 * @param inside 内側の頂点配列
 * @param drawAdvance 描画の進行率
 */
void draw(Object* obj, b2Vec2 outside[4], b2Vec2 inside[4], float drawAdvance = Float::kMax) {
	// 画像ハンドルがなければ処理しない
	const auto images = obj->getLineImages();
	if(IsEmpty(images)) {
		return;
	}
	const int color = obj->getColor();
	const float roughness = obj->getRoughness();
	int imageIndex = nextImageIndex(images, Array::kUnspecified, true, false);
	const float sharp = obj->getSharpness();

	b2Vec2 last[2], start[2];
	// 距離を決める
	float row = B2Vec2::distance(outside[0], outside[1]);
	float column = B2Vec2::distance(outside[1], outside[2]);
	float sharpDistance = Float::smaller(row * 0.5 * (Float::kMax - sharp), column * 0.5 * (Float::kMax - sharp));
	row -= sharpDistance * 2;
	column -= sharpDistance * 2;
	std::vector<float> section;
	section.push_back(row);
	section.push_back(sharpDistance);
	section.push_back(column);
	section.push_back(sharpDistance);
	section.push_back(row);
	section.push_back(sharpDistance);
	section.push_back(column);
	section.push_back(sharpDistance);
	int separateNum;
	float lastAdvance;
	float t;
	Float::setAdvance(separateNum, lastAdvance, section, drawAdvance);
	int nowIndex = 0;
	#define SET_ADVANCE t = separateNum > nowIndex ? Float::kMax : lastAdvance; \
						if(separateNum < nowIndex) { t = Float::kMin;}

	for(int i = 0; i < 4; i++) {
		nowIndex = i * 2;
		SET_ADVANCE
		const int next = (i + 1) % 4;
		b2Vec2 base[4] = { outside[next], inside[next], inside[i], outside[i] };
		b2Vec2 vertices[4];

		vertices[0] = B2Vec2::betweenFromDistance(base[0], B2Vec2::halfWay(base[0], base[3]), sharpDistance);
		vertices[1] = B2Vec2::betweenFromDistance(base[1], B2Vec2::halfWay(base[1], base[2]), sharpDistance);
		vertices[2] = B2Vec2::betweenFromDistance(base[2], B2Vec2::halfWay(base[2], base[1]), sharpDistance);
		vertices[3] = B2Vec2::betweenFromDistance(base[3], B2Vec2::halfWay(base[3], base[0]), sharpDistance);
		if(t > Float::kMin) {
			imageIndex = drawSeparateLine(obj, vertices, t, imageIndex);
		}
		if(i == 0) {
			start[0] = vertices[3];
			start[1] = vertices[2];
		} else {
			nowIndex = i * 2 - 1;
			SET_ADVANCE
			// TODO: 前の座標とベジェ曲線で繋ぐ
			b2Vec2 outsideArray[3] = {last[0], base[3], vertices[3]};
			b2Vec2 insideArray[3] = {last[1], base[2], vertices[2]};
			if(t > Float::kMin) {
				imageIndex = drawBezie(outsideArray, insideArray, roughness, images, true, false, imageIndex, t);
				imageIndex = nextImageIndex(images, imageIndex, true, false);
			}
			if(i == 3) {
				nowIndex = 7;
				SET_ADVANCE
				if(t == Float::kMin) {
					continue;
				}
				b2Vec2 outsideArrayEnd[3] = {vertices[0], base[0], start[0]};
				b2Vec2 insideArrayEnd[3] = {vertices[1], base[1], start[1]};
				drawBezie(outsideArrayEnd, insideArrayEnd, roughness, images, true, false, imageIndex, t);
				imageIndex = nextImageIndex(images, imageIndex, true, false);
			}
		}
		last[0] = vertices[0];
		last[1] = vertices[1];
	}
	#undef SET_ADVANCE
}

// 矩形オブジェクトを描画する
void drawRectangle(Object* obj) {
	// TODO: 矩形から枠を作成してそこを描画する
	
	const auto bodies = obj->getBodies();
	if(IsEmpty(bodies)) {
		return;
	}
	const auto body = bodies.front();
	const auto vertices = B2Body::vertices(body, 1.0 / obj->getWorldScale());
	b2Vec2 outside[4], inside[4];
	getVertices(obj, vertices, outside, inside);
	draw(obj, outside, inside, obj->getDrawAdvance());
}

// 編集中の矩形オブジェクトを描画する
void drawEditingRectangle(Object* obj) {
	// ボディ自体は作成されていないが、シミュレーションとして表示させる
	// 画像ハンドルがなければ処理しない
	const auto images = obj->getLineImages();
	if(IsEmpty(images)) {
		return;
	}
	b2Vec2 outside[4], inside[4];	
	getVertices(obj, outside, inside);
	draw(obj, outside, inside);
}

// 現在生成している矩形オブジェクトのフレームを描画する
void drawEditingRectangleDebug(Object* obj) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end);
	drawBox(start.x, start.y, end.x, end.y, Color::kWhite, FALSE);
}