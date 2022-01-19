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
	objects_.push_back(object);
	setHashData(object);
	return object;
}

// オブジェクトの追加
Object* PhysicusObjectManager::addObject(touch_t touch, ObjectType type, b2World* world, float scale, ObjectSetting setting) {
	auto object = new Object(touch, ObjectType::kRectangle, world_, world_scale_, current_setting_);
	return addObject(object);
}

// オブジェクトの削除
void PhysicusObjectManager::removeObjects(std::vector<Physicus::Object*> remove_list) {
	auto itr = objects_.begin();
	while(itr != objects_.end()) {
		const int size = Filter(remove_list, [&remove_list, itr](Object* item){ return item == (*itr); }).size();
		if(size > 0) {
			itr = objects_.erase(itr);
		} else {
			++itr;
		}
	}
}

// 矩形の即時作成
int PhysicusObjectManager::makeRectangle(b2Vec2 start, b2Vec2 end, SpriteType sprite_type, b2BodyType body_type) {
	auto tmp = current_setting_;
	current_setting_.bodyType = body_type;
	current_setting_.type = ObjectType::kRectangle;
	current_setting_.sprite_type = sprite_type;

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
	return getHandle();
}

// 線で出来た矩形の即時生成
int PhysicusObjectManager::makeRectangleStroke(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	return makeRectangle(start, end, SpriteType::kStroke, body_type);
}

// 塗りつぶし矩形の即時生成
int PhysicusObjectManager::makeRectangleFill(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	return makeRectangle(start, end, SpriteType::kFill, body_type);
}

// オブジェクトを取得する
Physicus::Object* PhysicusObjectManager::getObject(int handle) {
	return (Physicus::Object*)getDataFromHash(handle);
}

// 画像を取得する
std::vector<int> PhysicusObjectManager::getImages(int handle) {
	if(handle == kCurrentHandle) {
		return current_setting_.images;
	}
	auto object = getObject(handle);
	if(object == NULL) {
		printfDx("ERROR: \"PhysicusObjectManager::getImages\"関数で画像の取得に失敗しました。\n");
		std::vector<int> none;
		return none;
	}
	return object->getImages();
}

// std::vectorから線の画像をセットする
void PhysicusObjectManager::setImages(std::vector<int> images, int handle) {
	if(handle == kCurrentHandle) {
		current_setting_.images = images;
		return;
	}
	auto object = getObject(handle);
	if(object == NULL) {
		printfDx("ERROR: \"PhysicusObjectManager::setImages\"関数で画像の設定に失敗しました。\n");
		return;
	}
	return object->setImages(images);
}

// int配列から線の画像をセットする
void PhysicusObjectManager::setImages(int* images, int size, int handle) {
	if(handle == kCurrentHandle) {
		current_setting_.images.clear();
		for(int i = 0; i < size; i++) {
			current_setting_.images.push_back(images[i]);
		}
		return;
	}
	auto object = getObject(handle);
	if(object == NULL) {
		printfDx("ERROR: \"PhysicusObjectManager::setImages\"関数で画像の設定に失敗しました。\n");
		return;
	}
	return object->setImages(images, size);
}

// オブジェクトのスプライトのタイプを取得する
SpriteType PhysicusObjectManager::getObjectSpriteType(int handle) {
	if(handle == kCurrentHandle) {
		return current_setting_.sprite_type;
	}
	auto object = getObject(handle);
	if(object == NULL) {
		printfDx("ERROR: \"PhysicusObjectManager::getObjectSpriteType\"関数でオブジェクトのスプライトタイプの取得に失敗しました。\n");
		return SpriteType::kStroke;
	}
	return object->getSpriteType();
}

// オブジェクトのスプライトのタイプを設定する
void PhysicusObjectManager::setObjectSpriteType(SpriteType sprite_type, int handle) {
	if(handle == kCurrentHandle) {
		current_setting_.sprite_type = sprite_type;
		return;
	}
	auto object = getObject(handle);
	if(object == NULL) {
		printfDx("ERROR: \"PhysicusObjectManager::setObjectSpriteType\"関数でオブジェクトのスプライトタイプの設定に失敗しました。\n");
		return;
	}
	object->setSpriteType(sprite_type);
}

// 全てのオブジェクトの描画進行率を設定する
void PhysicusObjectManager::setDrawAdvanceAll(float advance) {
	advance = Float::clamp(advance, Float::kMin, Float::kMax);
	ForEach(objects_, [this, advance](Object* item) { item->setDrawAdvance(advance);});
}

// 時間を進める
void PhysicusObjectManager::timeCalc() {
	for(auto& itr: objects_) {
		itr->timeCalc();
	}
}

// フレームアウトしているかチェックする
void PhysicusObjectManager::checkFrameOut() {
	std::vector<Object*> remove_list;
	ForEach(objects_, [this, &remove_list](Object* item) { if(item->judgeAreaOut(alive_area_)){ remove_list.push_back(item);} });
	removeObjects(remove_list);
}

// 寿命がフレーム数を超えているかチェックする
void PhysicusObjectManager::checkLifeEnd() {
	std::vector<Object*> remove_list;
	ForEach(objects_, [this, &remove_list](Object* item) { if(item->getLifeEnd()){ remove_list.push_back(item);} });
	removeObjects(remove_list);
}

// タッチによってオブジェクトを生成する
int PhysicusObjectManager::touchCreate(touch_t touch) {
	int generate = NULL;
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_ == NULL) {
		current_ = new Object(touch, current_setting_.type, world_, world_scale_, current_setting_);
		addObject(current_);
		generate = getHandle();
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