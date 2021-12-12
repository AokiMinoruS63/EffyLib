/**
 * @file PhysicusParticleManager.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusParticleManager.h"
#include "../../Utility/TypeExtensions.h"

using namespace Physicus;

// コンストラクタ
PhysicusParticleManager::PhysicusParticleManager(b2World* world, float scale, Physicus::Frame alive_area) {
	handle_counter_ = 1;
	world_ = world;
	world_scale_ = scale;
	alive_area_ = alive_area;
	// 設定を初期化
	current_setting_ = ParticleSetting::init();
	// パーティクル生成クラスを初期化
	system_ =  world_->CreateParticleSystem(&current_setting_.setting);
	// パーティクル生存エリア適用
	alive_area.applyScale(world_scale_);
	alive_area_ = alive_area;
	// NULL代入する
	current_ = NULL;
}

// デストラクタ
PhysicusParticleManager::~PhysicusParticleManager() {
	ForEach(particles_, [this](Particle *item) { delete item; });
}

// パーティクルを取得する
Physicus::Particle* PhysicusParticleManager::getParticle(int handle) {
	for(auto& itr: particles_) {
		if(itr->getHandle() == handle) {
			return itr;
		}
	}
	return NULL;
}

// パーティクルのタイプを取得する
Physicus::ParticleType PhysicusParticleManager::getType(int handle) {
	if(handle == kCurrentHandle) {
		return current_setting_.type;
	}
	auto particle = getParticle(handle);
	if(particle == NULL) {
		printfDx("ERROR: \"PhysicusParticleManager::getType\"関数でパーティクルのタイプの取得に失敗しました。\n");
		return Physicus::ParticleSetting::init().type;
	}
	return particle->getType();
}

// パーティクルのタイプを設定する
void PhysicusParticleManager::setType(Physicus::ParticleType type, int handle) {
	if(handle == kCurrentHandle) {
		current_setting_.type = type;
		return;
	}
	auto particle = getParticle(handle);
	if(particle == NULL) {
		printfDx("ERROR: \"PhysicusParticleManager::setType\"関数でパーティクルの設定のセットに失敗しました。\n");
		return;
	}
	particle->setType(type);
}

// パーティクルの設定を取得する
Physicus::ParticleSetting PhysicusParticleManager::getSetting(int handle) {
	if(handle == kCurrentHandle) {
		return current_setting_;
	}
	auto particle = getParticle(handle);
	if(particle == NULL) {
		printfDx("ERROR: \"PhysicusParticleManager::getSetting\"関数でパーティクルの設定の取得に失敗しました。\n");
		return Physicus::ParticleSetting::init();
	}
	return particle->getSetting();
}

// パーティクルの設定を設定する
void PhysicusParticleManager::setSetting(Physicus::ParticleSetting setting, int handle) {
	if(handle == kCurrentHandle) {
		current_setting_ = setting;
		return;
	}
	auto particle = getParticle(handle);
	if(particle == NULL) {
		printfDx("ERROR: \"PhysicusParticleManager::setSetting\"関数でパーティクルの設定のセットに失敗しました。\n");
		return;
	}
	return particle->setSetting(setting);
}

// パーティクルの追加
Physicus::Particle* PhysicusParticleManager::addParticle(Physicus::Particle* particle) {
	addHandleCounter();
	particles_.push_back(particle);
	return particle;
}

// オブジェクトの追加
Physicus::Particle* PhysicusParticleManager::addParticle(touch_t touch, Physicus::ParticleSetting setting) {
	auto particle = new Particle(handle_counter_, touch, system_, world_, world_scale_, setting);
	return addParticle(particle);
}

// シングルパーティクルの生成
int PhysicusParticleManager::makeParticleSingle(b2Vec2 position, Physicus::ParticleSetting setting) {
	const int generate = handle_counter_;
	makeScreen(setting.effect_setting);
	// 生成開始
	touch_t touch = touch_t();
	touch.x = position.x;
	touch.y = position.y;
	touch.status = TouchStatus::kJustRelease;
	addParticle(touch, setting);
	return generate;
}

// フレームアウトしているかチェックする
void PhysicusParticleManager::checkFrameOut() {
	// TODO: フレームアウト処理を作成する
}

// タッチによってパーティクルを生成する
int PhysicusParticleManager::touchCreate(touch_t touch) {
	int generate = NULL;
	makeScreen(current_setting_.effect_setting);
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_ == NULL) {
		current_ = new Particle(handle_counter_, touch, system_, world_, world_scale_, current_setting_);
		particles_.push_back(current_);
		generate = handle_counter_;
		addHandleCounter();
	}

	// TODO: 後で変える
	current_ = NULL;

	if(current_ != NULL) {
		// 生成中
		if(current_->generation(touch)) {
			// 生成完了
			//current_->setAwake();
			current_ = NULL;
		}
	}
	return generate;
}

// パーティクル用のスクリーンを生成する
void PhysicusParticleManager::makeScreen(Effect::LiquidSetting setting) {
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

// パーティクルを描画する
void PhysicusParticleManager::draw() {
	// ぼかしを使用しないパーティクル
	for(auto& itr: particles_) {
		if(itr->getGroup() != Particle::kNoGaussGroup || itr == current_) {
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
			if(scr->getGroup() != itr->getGroup() || itr == current_) {
				continue;
			}
			itr->draw();
		}
		if(isGauss) {
			scr->postRender();
		}
	}
}

// 現在生成しているパーティクルを描画する
void PhysicusParticleManager::drawEditing() {
	current_->drawEditing();
}

// パーティクルのフレームを描画する
void PhysicusParticleManager::drawDebugFrame() {
	for(auto& itr: particles_) {
		if(itr != current_) {
			itr->drawDebugFrame();
		}
	}
}

// 現在生成しているパーティクルのフレームを描画する
void PhysicusParticleManager::drawEditingDebugFrame() {
	if(current_ != NULL) {
		current_->drawEditingDebugFrame();
	}
}