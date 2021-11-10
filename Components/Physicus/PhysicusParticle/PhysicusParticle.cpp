/**
 * @file PhysicusParticle.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusParticle.h"

using namespace Physicus;

Particle::Particle() {
	
}

Particle::~Particle() {

}

// パーティクルの生成
bool Particle::generation(touch_t touch) {
	return false;
}

// パーティクルの描画
void Particle::draw() {

}

// 編集中のパーティクルの描画
void Particle::drawEditing() {

}

// パーティクルのフレームの描画
void Particle::drawDebugFrame() {

}

// 編集中のパーティクルのフレームの描画
void Particle::drawEditingDebugFrame() {

}