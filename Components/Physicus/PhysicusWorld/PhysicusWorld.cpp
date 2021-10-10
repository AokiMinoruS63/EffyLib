/**
 * @file PhysicusWorld.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusWorld.h"
#include "../../Sprite/Sprite.h"

PhysicusWorld::PhysicusWorld(b2Vec2 gravity, float scale){
	// 物理演算世界を初期化する
	world_ = new b2World(gravity);
	// 拡大率適用
	world_scale_ = scale;
	// NULL代入する
	current_ = NULL;
}

PhysicusWorld::~PhysicusWorld(){}

// スプライトに物理演算を適用する
void PhysicusWorld::applySprite(Sprite* sprite) {
	sprites_.push_back(sprite);
}

// タッチによるオブジェクトの干渉（生成も含む）
bool PhysicusWorld::touchCalc(touch_t touch, Physicus::Type type) {
	bool generate = false;
	if(touch.status == TouchStatus::kJustTouch) {
		current_ = new Physicus::Object(touch, type, world_);
		// Object(Type type, b2World* world, touch_t touch);
		objects_.push_back(current_);
		generate = true;
	}

	if(current_ != NULL) {
		current_->generation(touch);
	}

	return generate;
	/*
	// 多角形 リリース生成
	Polygon,
	// 塗りつぶし多角形　 リリース生成
	FillPolygon,
	// 中身がスカスカな多角形　タッチ生成
	LinksBoard,
	// 円
	Circle,
	// 塗りつぶし多角形
	FillCircle,
	// 四角形
	Rectangle,
	// 塗りつぶし四角形
	FillRectangle
	*/
}