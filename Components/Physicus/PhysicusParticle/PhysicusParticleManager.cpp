/**
 * @file PhysicusParticleManager.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "PhysicusParticleManager.h"
#include "../../Utility/TypeExtensions.h"

using namespace Physicus;

// コンストラクタ
PhysicusParticleManager::PhysicusParticleManager(b2World* world, float scale, Physicus::Frame alive_area) {
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
	return (Physicus::Particle*)getDataFromHash(handle);
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
	particles_.push_back(particle);
	setHashData(particle);
	return particle;
}

// オブジェクトの追加
Physicus::Particle* PhysicusParticleManager::addParticle(touch_t touch, Physicus::ParticleSetting setting) {
	auto particle = new Particle(touch, system_, world_, world_scale_, setting);
	return addParticle(particle);
}

// パーティクルを削除する
void PhysicusParticleManager::removeParticles(std::vector<Physicus::Particle*> remove_list) {
	auto itr = particles_.begin();
	while(itr != particles_.end()) {
		const int size = Filter(remove_list, [&remove_list, itr](Particle* item){ return item == (*itr); }).size();
		if(size > 0) {
			itr = particles_.erase(itr);
		} else {
			++itr;
		}
	}
}

// シングルパーティクルの生成
int PhysicusParticleManager::makeParticleSingle(b2Vec2 position, Physicus::ParticleSetting setting) {
	makeScreen(setting.effect_setting);
	// 生成開始
	touch_t touch = touch_t();
	touch.x = position.x;
	touch.y = position.y;
	touch.status = TouchStatus::kJustRelease;
	addParticle(touch, setting);
	return getHandle();
}

// フレームアウトしているかチェックする
void PhysicusParticleManager::checkFrameOut() {
	// TODO: フレームアウト処理を作成する
}

// 寿命がフレーム数を超えているかチェックする
void PhysicusParticleManager::checkLifeEnd() {
	std::vector<Particle*> remove_list;
	ForEach(particles_, [this, &remove_list](Particle* item) { if(item->getLifeEnd()){ remove_list.push_back(item);} });
	removeParticles(remove_list);
}

// タッチによってパーティクルを生成する
int PhysicusParticleManager::touchCreate(touch_t touch) {
	int generate = NULL;
	makeScreen(current_setting_.effect_setting);
	// 生成開始
	if(touch.status == TouchStatus::kJustTouch && current_ == NULL) {
		current_ = new Particle(touch, system_, world_, world_scale_, current_setting_);
		addParticle(current_);
		generate = getHandle();
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

// 時間を進める
void PhysicusParticleManager::timeCalc() {
	for(auto& itr: particles_) {
		itr->timeCalc();
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