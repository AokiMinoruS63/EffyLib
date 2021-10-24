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
#include <vector>

using namespace Physicus;

/**
 * @brief 矩形の始点と終点をセットする
 * 
 * @param obj 矩形オブジェクト
 * @param start 始点
 * @param end 終点
 */
void setDrawStartEnd(Object* obj, b2Vec2* start, b2Vec2* end) {
	const std::vector<b2Vec2> locus = obj->getLocus();
	if(locus.size() < 2 || !obj->isRectangle()) {
		return;
	}
	const float scale = 1.0 / obj->getWorldScale();
	*start = B2Vec2::multiplication(locus.front(), scale);
	*end = B2Vec2::multiplication(locus.back(), scale);
	B2Vec2::setStartEnd(start, end);
}

/**
 * @brief 矩形の線を考慮した頂点を設定する
 * 
 * @param obj 
 * @param leftArray 
 * @param rightArray 
 */
void getVertices(Object* obj, b2Vec2 leftArray[8], b2Vec2 rightArray[8]) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end);
	Frame frame = {start, end};
	const float width = obj->getLineWidth() / obj->getWorldScale();
	// 各頂点
	leftArray[0] = B2Vec2::rotate(frame.leftTop(), width, Float::Angle::kRightTop, B2Vec2::Horizon::kLeading);
	rightArray[0] = B2Vec2::rotate(frame.leftTop(), width, Float::Angle::kRightTop, B2Vec2::Horizon::kTrailing);
	leftArray[1] = B2Vec2::rotate(frame.rightTop(), width, Float::Angle::kRightBottom, B2Vec2::Horizon::kLeading);
	rightArray[1] = B2Vec2::rotate(frame.rightTop(), width, Float::Angle::kRightBottom, B2Vec2::Horizon::kTrailing);
	leftArray[2] = B2Vec2::rotate(frame.rightBottom(), width, Float::Angle::kLeftBottom, B2Vec2::Horizon::kLeading);
	rightArray[2] = B2Vec2::rotate(frame.rightBottom(), width, Float::Angle::kLeftBottom, B2Vec2::Horizon::kTrailing);
	leftArray[3] = B2Vec2::rotate(frame.leftBottom(), width, Float::Angle::kLeftTop, B2Vec2::Horizon::kLeading);
	rightArray[3] = B2Vec2::rotate(frame.leftBottom(), width, Float::Angle::kLeftTop, B2Vec2::Horizon::kTrailing);	
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
	b2BodyDef bodyDef = B2BodyDef::dynamic(center, 1.0);
	// ボディの作成
	auto body = obj->getWorld()->CreateBody(&bodyDef);
	obj->append(body);

	// 動体オブジェクトの形を定義する
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(rect.x, rect.y);

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
	return true;
}

// 矩形オブジェクトを描画する
void drawRectangle(Object* obj) {
	// TODO: 矩形から枠を作成してそこを描画する
}

// 編集中の矩形オブジェクトを描画する
void drawEditingRectangle(Object* obj) {
	// ボディ自体は作成されていないが、シミュレーションとして表示させる
	// 画像ハンドルがなければ処理しない
	const auto images = obj->getLineImages();
	if(IsEmpty(images)) {
		return;
	}
	b2Vec2 left[8], right[8];
	const float roughness = obj->getRoughness();
	int imageIndex = nextImageIndex(images, Array::kUnspecified, true, false);
	getVertices(obj, left, right);
	// TODO: 角に丸みを持たせた場合の処理も行う
	obj->setSharpness(0.5);
	const float sharp = obj->getSharpness();
	b2Vec2 last[2], start[2];
	for(int i = 0; i < 4; i++) {
		const int next = (i + 1) % 4;
		b2Vec2 base[4] = { left[next], right[next], right[i], left[i] };
		b2Vec2 vertices[4];

		vertices[0] = B2Vec2::between(base[0], B2Vec2::halfWay(base[0], base[3]), Float::kMax - sharp);
		vertices[1] = B2Vec2::between(base[1], B2Vec2::halfWay(base[1], base[2]), Float::kMax - sharp);
		vertices[2] = B2Vec2::between(base[2], B2Vec2::halfWay(base[2], base[1]), Float::kMax - sharp);
		vertices[3] = B2Vec2::between(base[3], B2Vec2::halfWay(base[3], base[0]), Float::kMax - sharp);

		drawModiGraphF(vertices[0], vertices[1], vertices[2], vertices[3], images.at(imageIndex), TRUE);
		imageIndex = nextImageIndex(images, imageIndex, true, false);
		if(i == 0) {
			start[0] = vertices[3];
			start[1] = vertices[2];
		} else {
			// TODO: 前の座標とベジェ曲線で繋ぐ
			b2Vec2 leftArray[3] = {last[0], base[3], vertices[3]};
			b2Vec2 rightArray[3] = {last[1], base[2], vertices[2]};
			imageIndex = drawBezie(leftArray, rightArray, roughness, images, true, false, imageIndex);
			imageIndex = nextImageIndex(images, imageIndex, true, false);
			if(i == 3) {
				b2Vec2 leftArrayEnd[3] = {vertices[0], base[0], start[0]};
				b2Vec2 rightArrayEnd[3] = {vertices[1], base[1], start[1]};
				drawBezie(leftArrayEnd, rightArrayEnd, roughness, images, true, false, imageIndex);
				imageIndex = nextImageIndex(images, imageIndex, true, false);
			}
		}
		last[0] = vertices[0];
		last[1] = vertices[1];
	}
}

// 現在生成している矩形オブジェクトのフレームを描画する
void drawEditingRectangleDebug(Object* obj) {
	b2Vec2 start, end;
	setDrawStartEnd(obj, &start, &end);
	drawBox(start.x, start.y, end.x, end.y, Color::kWhite, FALSE);
}