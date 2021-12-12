/**
 * @file PhysicusObjectManager.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief オブジェクト管理クラス
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusObjectManager.h"
#include "../../Assets/ComponentAssets.h"
#include "../../Utility/TypeExtensions.h"

using namespace Physicus;

// コンストラクタ
PhysicusObjectManager::PhysicusObjectManager(b2World* world, float scale, Frame alive_area, float tie_loop_range) {
	handle_counter_ = 1;
	world_ = world;
	world_scale_ = scale;
	alive_area_ = alive_area;
	tie_loop_range_ = tie_loop_range;
	// オブジェクト生存エリア適用
	alive_area.applyScale(world_scale_);
	alive_area_ = alive_area;
	// 数珠繋ぎにする距離
	tie_loop_range_ = tie_loop_range;
	const std::vector<int> images = ComponentAssets::shared()->getImages().brush_crayon;
	current_setting_ = ObjectSetting::init(world_scale_, ObjectType::kLinkBoard, b2_dynamicBody, images);
}

// デストラクタ
PhysicusObjectManager::~PhysicusObjectManager() {
	ForEach(objects_, [this](Object *item) { delete item; });
}

// オブジェクトの追加
Object* PhysicusObjectManager::addObject(Object* object) {
	addHandleCounter();
	objects_.push_back(object);
	return object;
}

// オブジェクトの追加
Object* PhysicusObjectManager::addObject(touch_t touch, ObjectType type, b2World* world, float scale, ObjectSetting setting) {
	auto object = new Object(handle_counter_, touch, ObjectType::kRectangle, world_, world_scale_, current_setting_);
	return addObject(object);
}

// 線で出来た矩形の即時作成
int PhysicusObjectManager::makeRectangleLine(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	int generate = handle_counter_;
	auto tmp = current_setting_;
	current_setting_.bodyType = body_type;
	current_setting_.type = ObjectType::kRectangle;

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
	auto body = addObject(touch, ObjectType::kRectangle, world_, world_scale_, current_setting_);
	touch.x = end.x;
	touch.y = end.y;
	body->generation(touch, tie_loop_range_);

	current_setting_ = tmp;
	return generate;
}

// 全てのオブジェクトの描画進行率を設定する
void PhysicusObjectManager::setDrawAdvanceAll(float advance) {
	advance = Float::clamp(advance, Float::kMin, Float::kMax);
	ForEach(objects_, [this, advance](Object* item) { item->setDrawAdvance(advance);});
}

// フレームアウトしているかチェックする
void PhysicusObjectManager::checkFrameOut() {
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
}

// タッチによってオブジェクトを生成する
int PhysicusObjectManager::touchCreate(touch_t touch) {
	int generate = NULL;
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_ == NULL) {
		current_ = new Object(handle_counter_, touch, current_setting_.type, world_, world_scale_, current_setting_);
		objects_.push_back(current_);
		generate = handle_counter_;
		addHandleCounter();
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
void PhysicusObjectManager::draw() {
	// オブジェクト描画
	for(auto& itr: objects_) {
		if(itr != current_) {
			itr->draw();
		}
	}
}

// 現在生成しているオブジェクトを描画する
void PhysicusObjectManager::drawEditing() {
	// 編集中のオブジェクト描画
	current_->drawEditing();
}

// オブジェクト又はパーティクルのフレームを描画する
void PhysicusObjectManager::drawDebugFrame() {
	// オブジェクト描画
	for(auto& itr: objects_) {
		if(itr != current_) {
			itr->drawDebugFrame();
		}
	}
}

// 現在生成しているオブジェクト又はパーティクルのフレームを描画する
void PhysicusObjectManager::drawEditingDebugFrame() {
	// 編集中のオブジェクト描画
	if(current_ != NULL) {
		current_->drawEditingDebugFrame();
	}
}