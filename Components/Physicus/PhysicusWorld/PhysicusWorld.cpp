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
#include "../../Assets/ComponentAssets.h"

using namespace Physicus;

// コンストラクタ
PhysicusWorld::PhysicusWorld(b2Vec2 gravity, float scale, Frame alive_area, float tie_loop_range){
	// カウンタを初期化する
	object_handle_counter_ = 1;
	particle_handle_counter_ = 1;
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
	current_object_setting_ = ObjectSetting::init(world_scale_, ObjectType::kLinkBoard, b2_dynamicBody, images);
	current_particle_setting_ = ParticleSetting::init();
	// パーティクル生成クラスを初期化
	particle_system_ =  world_->CreateParticleSystem(&current_particle_setting_.setting);
	// NULL代入する
	current_object_ = NULL;
	current_particle_ = NULL;
}

// デストラクタ
PhysicusWorld::~PhysicusWorld(){
	ForEach(objects_, [this](Object *item) { delete item; });
	ForEach(particles_, [this](Particle *item) { delete item; });
	delete world_;
}

// オブジェクトのタイプを取得する
Physicus::ObjectType PhysicusWorld::getObjectType() {
	return current_object_setting_.type;
}

// オブジェクトのタイプを設定する
void PhysicusWorld::setObjectType(Physicus::ObjectType type) {
	current_object_setting_.type = type;
}

// パーティクルのタイプを取得する
Physicus::ParticleType PhysicusWorld::getParticleType() {
	return current_particle_setting_.type;
}
// パーティクルのタイプを設定する
void PhysicusWorld::setParticleType(Physicus::ParticleType type) {
	current_particle_setting_.type = type;
}

// パーティクルの設定を取得する
ParticleSetting PhysicusWorld::getParticleSetting() {
	return current_particle_setting_;
}

// パーティクルの設定を設定する
void PhysicusWorld::setParticleSetting(ParticleSetting setting) {
	current_particle_setting_ = setting;
}

// プレビューの作成
void PhysicusWorld::makePreviewData() {
	makeRectangle(b2Vec2(0, 580), b2Vec2(880, 600));
	makeRectangle(b2Vec2(0, 200), b2Vec2(20, 600));
	makeRectangle(b2Vec2(860, 200), b2Vec2(880, 600));	

	makeRectangle(b2Vec2(0, 200), b2Vec2(300, 230));

	auto setting = Physicus::ParticleSetting::init();
	setting.effect_setting.group = 2;
	setting.effect_setting.fill_color = Color::kDeepOrange;
	setting.effect_setting.effect = true;
	makeParticle(b2Vec2(200, 200), setting);
}

// 矩形の即時作成
int PhysicusWorld::makeRectangle(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	auto tmp = current_object_setting_;
	current_object_setting_.bodyType = body_type;
	current_object_setting_.type = ObjectType::kRectangle;

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
	auto body = new Object(object_handle_counter_, touch, ObjectType::kRectangle, world_, world_scale_, current_object_setting_);
	addObjectHandleCounter();
	objects_.push_back(body);
	touch.x = end.x;
	touch.y = end.y;
	body->generation(touch, tie_loop_range_);

	current_object_setting_ = tmp;
	return object_handle_counter_ - 1;
}

// パーティクルの即時作成
int PhysicusWorld::makeParticle(b2Vec2 position, Physicus::ParticleSetting setting) {
	makeParticleScreen(setting.effect_setting);
	// 生成開始
	touch_t touch = touch_t();
	touch.x = position.x;
	touch.y = position.y;
	touch.status = TouchStatus::kJustRelease;
	auto particle = new Particle(particle_handle_counter_, touch, particle_system_, world_, world_scale_, setting);
	particles_.push_back(particle);
	addParticleHandleCounter();
	return particle_handle_counter_ - 1;
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

// オブジェクトのハンドルのカウンタを進める
void PhysicusWorld::addObjectHandleCounter() {
	object_handle_counter_++;
}

// パーティクルのハンドルのカウンタを進める
void PhysicusWorld::addParticleHandleCounter() {
	particle_handle_counter_++;
}

// タッチによってオブジェクトを生成する
int PhysicusWorld::touchObjectCreate(touch_t touch) {
	int generate = NULL;
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_object_ == NULL) {
		current_object_ = new Object(object_handle_counter_, touch, current_object_setting_.type, world_, world_scale_, current_object_setting_);
		objects_.push_back(current_object_);
		generate = object_handle_counter_;
		addParticleHandleCounter();
	}

	if(current_object_ != NULL) {
		// 生成中
		if(current_object_->generation(touch, tie_loop_range_)) {
			// 生成完了
			current_object_->setAwake();
			current_object_ = NULL;
		}
	}
	return generate;
}

// タッチによってパーティクルを生成する
int PhysicusWorld::touchParticleCreate(touch_t touch) {
	int generate = NULL;
	makeParticleScreen(current_particle_setting_.effect_setting);
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_particle_ == NULL) {
		current_particle_ = new Particle(particle_handle_counter_, touch, particle_system_, world_, world_scale_, current_particle_setting_);
		particles_.push_back(current_particle_);
		generate = particle_handle_counter_;
		addParticleHandleCounter();
	}

	// TODO: 後で変える
	current_particle_ = NULL;

	if(current_particle_ != NULL) {
		// 生成中
		if(current_particle_->generation(touch)) {
			// 生成完了
			//current_particle_->setAwake();
			current_particle_ = NULL;
		}
	}
	return generate;
}

// パーティクル用のスクリーンを生成する
void PhysicusWorld::makeParticleScreen(Effect::LiquidSetting setting) {
	for(auto &itr: screen_) {
		if(itr->getGroup() == setting.group) {
			return;
		}
	}
	setting.setBlendMode(BlendMode::kAdd);
	if(setting.group != Particle::kNoGaussGroup) {
		screen_.push_back(new Effect::Liquid(setting));
	}
}

// オブジェクトとパーティクルを描画する
void PhysicusWorld::draw() {
	// オブジェクト描画
	for(auto& itr: objects_) {
		if(itr != current_object_) {
			itr->draw();
		}
	}
	// パーティクル描画
	// ぼかしを使用しないパーティクル
	for(auto& itr: particles_) {
		if(itr->getGroup() != Particle::kNoGaussGroup || itr == current_particle_) {
			continue;
		}
		itr->draw();
	}
	// ぼかしを使用するパーティクル
	for(auto& scr: screen_) {
		const bool isGauss = scr->getGroup() != Particle::kNoGaussGroup;
		if(isGauss) {
			scr->preRender();
		}
		for(auto& itr: particles_) {
			if(scr->getGroup() != itr->getGroup() || itr == current_particle_) {
				continue;
			}
			itr->draw();
		}
		if(isGauss) {
			scr->postRender();
		}
	}
	// 編集中のオブジェクト描画
	current_object_->drawEditing();
	// 編集中のパーティクル描画
	current_particle_->drawEditing();
}


// オブジェクトとパーティクルのフレームを描画する
void PhysicusWorld::drawDebugFrame() {
	// オブジェクト描画
	for(auto& itr: objects_) {
		if(itr != current_object_) {
			itr->drawDebugFrame();
		}
	}
	// パーティクル描画
	for(auto& itr: particles_) {
		if(itr != current_particle_) {
			itr->drawDebugFrame();
		}
	}
	// 編集中のオブジェクト描画
	if(current_object_ != NULL) {
		current_object_->drawEditingDebugFrame();
	}
	// 編集中のパーティクル描画
	if(current_particle_ != NULL) {
		current_particle_->drawEditingDebugFrame();
	}
}