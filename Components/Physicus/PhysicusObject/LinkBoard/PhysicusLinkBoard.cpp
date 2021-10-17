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
	} else {
		obj->appendBodiesVerticesChange(B2Body::VerticesChange::kPiHalfPiRotate);
	}
}

// リンクボードオブジェクトを描画する
void drawLinkBoard(Physicus::Object* obj) {
	// 画像ハンドルがなければ処理しない
	const auto images = obj->getLineImages();
	if(IsEmpty(images)) {
		return;
	}
	const auto bodies = obj->getBodies();
	int count = 0;
	int imageHandle = 0;
	int imageCount = 0;
	const int max = images.size() - 2;
	const int color = obj->getColor();
	int loopCount = 0;
	for(auto& itr: bodies) {
		// 描画画像決定メソッド
		imageHandle = images.at(imageCount + 1);
		if(itr == bodies.front()) {
			imageHandle = images.front();
		} else if(itr == bodies.back()) {
			imageHandle = images.back();
		} else {
			imageHandle = images.at(imageCount + 1);
			imageCount++;
			imageCount %= max;
		}
		count++;
		
		// 描画メソッド
		const auto vertices = B2Body::vertices(itr, 1.0 / obj->getWorldScale());
		if(vertices.size() == 4) {
			// 頂点の順番が自動で補正されるので手動で直す
			int indices[4] = {0, 1, 2, 3};
			auto changeType = obj->getBodiesVerticesChange().at(loopCount);
			if(changeType == B2Body::VerticesChange::kNoRotate) {
				indices[0] = 0;
				indices[1] = 1;
				indices[2] = 2;
				indices[3] = 3;
			} else if(changeType == B2Body::VerticesChange::kHalfPiRotate) {
				indices[3] = 0;
				indices[0] = 1;
				indices[1] = 2;
				indices[2] = 3;
			} else if(changeType == B2Body::VerticesChange::kPiRotate) {
				indices[2] = 0;
				indices[3] = 1;
				indices[0] = 2;
				indices[1] = 3;
			} else {
				indices[1] = 0;
				indices[2] = 1;
				indices[3] = 2;
				indices[0] = 3;
			}	
					
			drawModiGraphF( vertices.at(indices[0]).x, vertices.at(indices[0]).y, vertices.at(indices[1]).x, vertices.at(indices[1]).y, vertices.at(indices[2]).x, vertices.at(indices[2]).y, vertices.at(indices[3]).x, vertices.at(indices[3]).y, imageHandle , TRUE);
		}
		loopCount++;
	}
}

// 編集中のリンクボードオブジェクトを描画する
void drawEditingLinkBoard(Physicus::Object* obj) {
	drawLinkBoard(obj);
}