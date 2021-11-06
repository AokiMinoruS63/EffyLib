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
#include "../../Assets/ComponentAssets.h"

using namespace Physicus;

// コンストラクタ
PhysicusWorld::PhysicusWorld(b2Vec2 gravity, float scale, Frame alive_area, float tie_loop_range){
	// 物理演算世界を初期化する
	world_ = new b2World(gravity);
	// 拡大率適用
	world_scale_ = scale;
	// オブジェクト生存エリア適用
	alive_area.applyScale(world_scale_);
	alive_area_ = alive_area;
	// 数珠繋ぎにする距離
	tie_loop_range_ = tie_loop_range;
	const std::vector<int> images = ComponentAssets::shared()->getImages().brush_crayon;
	current_setting_ = ObjectSetting::init(world_scale_, Type::kLinkBoard, b2_dynamicBody, images);
	// NULL代入する
	current_ = NULL;
	// プレビューデータの作成
	makePreviewData();
}

// デストラクタ
PhysicusWorld::~PhysicusWorld(){
	ForEach(objects_, [this](Object *item) { delete item; });
	delete world_;
}

// プレビューの作成
void PhysicusWorld::makePreviewData() {
	makeRectangle(b2Vec2(0, 580), b2Vec2(580, 600));	
}

// 矩形の即時作成
void PhysicusWorld::makeRectangle(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	auto tmp = current_setting_;
	current_setting_.bodyType = body_type;
	current_setting_.type = Type::kRectangle;

	touch_t touch;
	touch.pos_log_x.push_back(end.x);
	touch.pos_log_x.push_back(start.x);
	touch.pos_log_y.push_back(end.y);
	touch.pos_log_y.push_back(start.y);
	touch.input_log.push_back(false);
	touch.input_log.push_back(true);
	touch.x = start.x;
	touch.y = start.y;
	touch.status = TouchStatus::kJustRelease;
	auto body = new Object(touch, Type::kRectangle, world_, world_scale_, current_setting_);
	objects_.push_back(body);
	touch.x = end.x;
	touch.y = end.y;
	body->generation(touch, tie_loop_range_);

	current_setting_ = tmp;
}

// 時間を進める
void PhysicusWorld::timeCalc() {
	// 時間経過メソッド
	const float timeStep = 1.0f / 10.0f;
	const int velocityIterations = 6;
	const int positionIterations = 2;
	// 時間を進める
	world_->Step(timeStep, velocityIterations, positionIterations);
	// 生存可能エリアからオブジェクトが出ていたら消滅させる
	std::vector<Object*> removeList;
	ForEach(objects_, [this, &removeList](Object* item) { if(item->judgeAreaOut(alive_area_)){ removeList.push_back(item);} });
	auto itr = objects_.begin();
	while(itr != objects_.end()) {
		const int size = Filter(removeList, [&removeList, itr](Object* item){ return item == (*itr); }).size();
		if(size > 0) {
			itr = objects_.erase(itr);
		} else {
			++itr;
		}
	}

	// TODO: 描画進行率テスト。後で消す
	static LONG cnt = 0;
	ForEach(objects_, [this](Object* item) { item->setDrawAdvance(((float)(cnt%300)) / 300.0);});
	cnt++;
}

// スプライトに物理演算を適用する
void PhysicusWorld::applySprite(Sprite* sprite) {
	sprites_.push_back(sprite);
}

// タッチによるオブジェクトの干渉（生成も含む）
bool PhysicusWorld::touchCalc(touch_t touch, Type type) {
	bool generate = false;
	current_setting_.type = type;
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_ == NULL) {
		current_ = new Object(touch, type, world_, world_scale_, current_setting_);
		objects_.push_back(current_);
		generate = true;
	}

	if(current_ != NULL) {
		// 生成中
		if(current_->generation(touch, tie_loop_range_)) {
			// 生成完了
			current_->setAwake();
			current_ = NULL;
		}
	}

	return generate;
}


// オブジェクトを描画する
void PhysicusWorld::draw() {
	for(auto& itr: objects_) {
		if(itr != current_) {
			itr->draw();
		}
	}
	current_->drawEditing();
}


// オブジェクトのフレームを描画する
void PhysicusWorld::drawDebugFrame() {
	for(auto& itr: objects_) {
		if(itr != current_) {
			itr->drawDebugFrame();
		}
	}
	if(current_ != NULL) {
		current_->drawEditingDebugFrame();
	}
}