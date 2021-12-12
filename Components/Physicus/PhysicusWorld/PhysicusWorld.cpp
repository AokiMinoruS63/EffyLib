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
	particle_handle_counter_ = 1;
	// 物理演算世界を初期化する
	world_ = new b2World(gravity);
	// インスタンス生成
	objects_ = new PhysicusObjectManager(world_, scale, alive_area);
	// 拡大率適用
	world_scale_ = scale;

	current_particle_setting_ = ParticleSetting::init();
	// パーティクル生成クラスを初期化
	particle_system_ =  world_->CreateParticleSystem(&current_particle_setting_.setting);
	// NULL代入する
	current_particle_ = NULL;
}

// デストラクタ
PhysicusWorld::~PhysicusWorld(){
	delete objects_;
	ForEach(particles_, [this](Particle *item) { delete item; });
	delete world_;
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

// 全てのオブジェクトの描画進行率を設定する
void PhysicusWorld::setObjectsDrawAdvanceAll(float advance) {
	objects_->setDrawAdvanceAll(advance);
}

// プレビューの作成
void PhysicusWorld::makePreviewData() {
	makeRectangleLine(b2Vec2(0, 580), b2Vec2(880, 600));
	makeRectangleLine(b2Vec2(0, 200), b2Vec2(20, 600));
	makeRectangleLine(b2Vec2(860, 200), b2Vec2(880, 600));	

	makeRectangleLine(b2Vec2(0, 200), b2Vec2(300, 230));

	auto setting = Physicus::ParticleSetting::init();
	setting.effect_setting.group = 2;
	setting.effect_setting.fill_color = Color::kDeepOrange;
	setting.effect_setting.effect = true;
	makeParticle(b2Vec2(200, 200), setting);
}

// 矩形の即時作成
int PhysicusWorld::makeRectangleLine(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	return objects_->makeRectangleLine(start, end, body_type);
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
	objects_->checkFrameOut();

	// TODO: パーティクルの削除も行う
}

// パーティクルのハンドルのカウンタを進める
void PhysicusWorld::addParticleHandleCounter() {
	particle_handle_counter_++;
}

// タッチによってオブジェクトを生成する
int PhysicusWorld::touchObjectCreate(touch_t touch) {
	return objects_->touchCreate(touch);
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
	objects_->draw();

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
	objects_->drawEditing();
	// 編集中のパーティクル描画
	current_particle_->drawEditing();
}


// オブジェクトとパーティクルのフレームを描画する
void PhysicusWorld::drawDebugFrame() {
	// オブジェクト描画
	objects_->drawDebugFrame();

	// パーティクル描画
	for(auto& itr: particles_) {
		if(itr != current_particle_) {
			itr->drawDebugFrame();
		}
	}
	// 編集中のオブジェクト描画
	objects_->drawEditingDebugFrame();

	// 編集中のパーティクル描画
	if(current_particle_ != NULL) {
		current_particle_->drawEditingDebugFrame();
	}
}