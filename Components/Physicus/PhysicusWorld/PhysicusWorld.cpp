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
	// 物理演算世界を初期化する
	world_ = new b2World(gravity);
	// インスタンス生成
	objects_ = new PhysicusObjectManager(world_, scale, alive_area);
	particles_ = new PhysicusParticleManager(world_, scale, alive_area);
	// 拡大率適用
	world_scale_ = scale;
}

// デストラクタ
PhysicusWorld::~PhysicusWorld(){
	delete objects_;
	delete particles_;
	delete world_;
}

// パーティクルのタイプを取得する
Physicus::ParticleType PhysicusWorld::getParticleType(int handle) {
	return particles_->getType(handle);
}
// パーティクルのタイプを設定する
void PhysicusWorld::setParticleType(Physicus::ParticleType type, int handle) {
	particles_->setType(type, handle);
}

// パーティクルの設定を取得する
ParticleSetting PhysicusWorld::getParticleSetting(int handle) {
	return particles_->getSetting(handle);
}

// パーティクルの設定を設定する
void PhysicusWorld::setParticleSetting(ParticleSetting setting, int handle) {
	particles_->setSetting(setting, handle);
}

// 全てのオブジェクトの描画進行率を設定する
void PhysicusWorld::setObjectsDrawAdvanceAll(float advance) {
	objects_->setDrawAdvanceAll(advance);
}

// タッチによってオブジェクトを生成する
int PhysicusWorld::touchObjectCreate(touch_t touch) {
	return objects_->touchCreate(touch);
}

// タッチによってパーティクルを生成する
int PhysicusWorld::touchParticleCreate(touch_t touch) {
	return particles_->touchCreate(touch);
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
	makeParticleSingle(b2Vec2(200, 200), setting);
}

// 矩形の即時生成
int PhysicusWorld::makeRectangleLine(b2Vec2 start, b2Vec2 end, b2BodyType body_type) {
	return objects_->makeRectangleLine(start, end, body_type);
}

// パーティクルの即時生成
int PhysicusWorld::makeParticleSingle(b2Vec2 position, Physicus::ParticleSetting setting) {
	return particles_->makeParticleSingle(position, setting);
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
	particles_->checkFrameOut();
}

// オブジェクトとパーティクルを描画する
void PhysicusWorld::draw() {
	// オブジェクト描画
	objects_->draw();
	// パーティクル描画
	particles_->draw();
	// 編集中のオブジェクト描画
	objects_->drawEditing();
	// 編集中のパーティクル描画
	particles_->drawEditing();
}


// オブジェクトとパーティクルのフレームを描画する
void PhysicusWorld::drawDebugFrame() {
	// オブジェクト描画
	objects_->drawDebugFrame();
	// パーティクル描画
	particles_->drawDebugFrame();
	// 編集中のオブジェクト描画
	objects_->drawEditingDebugFrame();
	// 編集中のパーティクル描画
	particles_->drawEditingDebugFrame();
}
