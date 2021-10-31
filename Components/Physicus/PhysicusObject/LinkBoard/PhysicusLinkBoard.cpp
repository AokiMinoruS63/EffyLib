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
#include "../../../Utility/DxLibWrap.h"
#include "../../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include <vector>

using namespace Physicus;

// 中身がスカスカなオブジェクトの作成
void createLinkBoardBody(Object* obj) {
	// 線の太さが一定以下なら処理を行わない
	if(obj->getLineWidth() < B2Body::kMinCreateVertexRange) {
		return;
	}
	b2Vec2 current, last, lastLast;
	const auto locus = obj->getLocus();
	B2Vec2::recentLocus(locus, &current, &last, &lastLast);
	
	b2Vec2 center = B2Vec2::halfWay(last, current);
	const float width = obj->getLineHalfWidth();
	const float angle = B2Vec2::angle(last, current);
	std::vector<Frame> locus_frame = obj->getLocusFrames();
	float lastAngle = locus.size() <= 2 ? angle :  B2Vec2::angle(lastLast, last);

	// 直近の軌跡から矩形を作成する
	b2Vec2 vertices[4] = {
		IsEmpty(locus_frame) ? B2Vec2::rotate(last, width, angle, B2Vec2::kLeading) : locus_frame.back().start,
		IsEmpty(locus_frame) ? B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing) : locus_frame.back().end,
		B2Vec2::rotate(current, width, angle, B2Vec2::kLeading),
		B2Vec2::rotate(current, width, angle, B2Vec2::kTrailing),
	};
	if(locus_frame.size() > 1) {
		// 重なり確認のため前の前の座標も確認
		const b2Vec2 checkVertices[2] = {
			locus_frame.at(locus_frame.size() - 2).start,
			locus_frame.at(locus_frame.size() - 2).end
		};
		const bool right_cross = B2Vec2::intersectLines(NULL, vertices[0], vertices[2], checkVertices[1], vertices[1]) == B2Vec2::Intersect::kIntersection;
		const bool left_cross =  B2Vec2::intersectLines(NULL, vertices[1], vertices[3], checkVertices[0], vertices[0]) == B2Vec2::Intersect::kIntersection;
		// 右下に折り返して当たった時の処理
		if(right_cross) {
			// vertex[1] を手前に戻す
			vertices[1] = B2Vec2::halfWay(vertices[1], checkVertices[1]);
		} else if(left_cross) {
			// 左下に折り返して当たった時の処理
			// vertex[0] を手前に戻す
			vertices[0] = B2Vec2::halfWay(vertices[0], checkVertices[0]);
		}
	}
	obj->appendLocusFrame({vertices[2], vertices[3]});

	const float angleDifference = Float::angleDifference(angle, lastAngle);
	if(angleDifference > DX_PI_F * 0.4) {
		vertices[0] = B2Vec2::rotate(last, width, angle, B2Vec2::kLeading);
		vertices[1] = B2Vec2::rotate(last, width, angle, B2Vec2::kTrailing);
	}
	
	for(int i = 0; i < 4; i++) {
		vertices[i] = B2Vec2::relativePosition(center, vertices[i]);
	}
	
	// 動体オブジェクトの参照値
	b2BodyDef bodyDef = B2BodyDef::dynamic(center);
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
	

	// 頂点の順番が変更されたか確認する
	const auto verticesCheck = B2Body::vertices(body);
	const auto fixture = body->GetFixtureList();
	const auto position = fixture->GetBody()->GetPosition();
	if(B2Vec2::distance(vertices[0], B2Vec2::sub(verticesCheck[0], position)) < 1.0) {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kNoRotate);
	} else if(B2Vec2::distance(vertices[0], B2Vec2::sub(verticesCheck[1], position)) < 1.0) {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kHalfPiRotate);
	} else if(B2Vec2::distance(vertices[0], B2Vec2::sub(verticesCheck[2], position)) < 1.0) {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kPiRotate);
	} else if(B2Vec2::distance(vertices[0], B2Vec2::sub(verticesCheck[3], position)) < 1.0) {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kPiHalfPiRotate);
	} else {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kNoRotate);
		printfDx("VerticesCreateError:  \n");
		printfDx("Angle current %f, last %f  \n", angle, lastAngle);
		for(int i = 0; i < 4; i++) {
			const auto pos = B2Vec2::sub(verticesCheck[i], position);
			printfDx("i: %d, x: %f, y: %f, cx: %f, cy: %f\n", i, vertices[i].x, vertices[i].x, pos.x, pos.y);
		}
		printfDx("\n");
	}
}

// リンクボードオブジェクトを描画する
void drawLinkBoard(Object* obj) {
	// 画像ハンドルがなければ処理しない
	const auto images = obj->getLineImages();
	if(IsEmpty(images)) {
		return;
	}
	const auto bodies = obj->getBodies();
	const int color = obj->getColor();
	int loopCount = 0;
	b2Vec2 currentRect[4];
	b2Vec2 lastRect[4], lastHalf[2];
	const float roughness = obj->getRoughness();
	for(auto& itr: bodies) {		
		// 描画メソッド
		const auto vertices = B2Body::vertices(itr, 1.0 / obj->getWorldScale());
		if(vertices.size() == 4) {
			// 頂点の順番が自動で補正されるので手動で直す
			int indices[4] = {0, 1, 2, 3};
			int rotateNum = 0;
			auto changeType = obj->getBodiesVerticesChange().at(loopCount);
			if(changeType == B2Body::VerticesChange::kNoRotate) {
				rotateNum = 0;
			} else if(changeType == B2Body::VerticesChange::kHalfPiRotate) {
				rotateNum = 3;
			} else if(changeType == B2Body::VerticesChange::kPiRotate) {
				rotateNum = 2;
			} else {
				rotateNum = 1;
			}
			for(int i = 0; i < 4; i++) {
				indices[(rotateNum + i) % 4] = i;
			}
			for(int i = 0; i < 4; i++) {
				currentRect[i] = vertices.at(indices[i]);
			}
			// 半分の地点を定義
			const b2Vec2 halfLeft = B2Vec2::halfWay(currentRect[0], currentRect[3]);
			const b2Vec2 halfRight = B2Vec2::halfWay(currentRect[1], currentRect[2]);

			// ボディが一つだけならそのまま描画
			if(bodies.size() == 1) {
				drawModiGraphF( vertices.at(indices[0]), vertices.at(indices[1]), vertices.at(indices[2]), vertices.at(indices[3]), images.front() , TRUE);
			} else {
				// それ以外ならベジェ曲線を描く
				if(itr == bodies.front()) {
					// 半分まで描く
					drawModiGraphF( currentRect[0], currentRect[1], halfRight, halfLeft, images.front() , TRUE);
				} else {
					// 前のボディの半分から現在のボディの半分までベジェ曲線を描く
					b2Vec2 leftVec[3] = {lastHalf[0], B2Vec2::halfWay(lastRect[3], currentRect[0]), halfLeft};
					b2Vec2 rightVec[3] = {lastHalf[1], B2Vec2::halfWay(lastRect[2], currentRect[1]), halfRight};
					drawBezie(leftVec, rightVec, roughness, images, true, false, Array::kUnspecified );
				}
				// 最後なら半分から最後まで描く
				if(itr == bodies.back()) {
					drawModiGraphF( halfRight, halfLeft, currentRect[3], currentRect[2], images.back() , TRUE);
				}
			}
			// 代入処理
			for(int i = 0; i < 4; i++) {
				lastRect[i] = currentRect[i];
			}
			lastHalf[0] = halfLeft;
			lastHalf[1] = halfRight;
		}
		loopCount++;
	}
}

// 編集中のリンクボードオブジェクトを描画する
void drawEditingLinkBoard(Object* obj) {
	drawLinkBoard(obj);
}