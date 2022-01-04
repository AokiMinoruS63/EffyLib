/**
 * @file EffectParticle3D.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief エフェクト用のパーティクル構造体
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "EffectParticle3D.h"
#include "../../Utility/DxLibWrap.h"
#include "../../Common/Random/Random.h"
#include "../../Utility/TypeExtensions.h"

using namespace Effect;

/**
 * @brief ベクトルにパーリンノイズを適用させたベクトルを返す
 * 
 * @param vec 現在の座標
 * @param noise パーリンノイズ
 * @return Vec3 適用させたノイズ
 */
Vec3 getVec3Noise(Vec3 vec, PerlinNoise& noise) {
	const auto x = vec / 128.0f;
	const auto y = vec / 128.0f + Vec3 { 100, 100, 100 };
	const auto z = vec / 128.0f + Vec3 { -100, -100, -100 };
	auto value = Vec3 { (float)noise.noise(x.x, x.y, x.z), (float)noise.noise(y.x, y.y, y.z), (float)noise.noise(z.x, z.y, z.z) };
	value.norm();
	
	return value;
}

// コンストラクタ
Particle3D::Particle3D(Vec3 pos, float radian_min, float radian_max, float life_time, int image) {
	initBase(radian_min, radian_max, life_time, image);
	pos_ = randomVec3(Sphere(10.0)) + pos;
	velocity_ = (randomVec3(1.0) + randomVec3(Sphere(0.3))) * 20.0;

	static bool inited = false;
	// 全体のマテリアルの設定を行う
	if(!inited) {
		SetMaterialUseVertSpcColor(FALSE);
		SetMaterialUseVertDifColor(FALSE);
		inited = true;
	}
}

// デストラクタ
Particle3D::~Particle3D() {}

// 処理を行う
void Particle3D::run() {
	calcDeltaTime();
	lifeCheck();
}

// カールノイズによる移動
void Particle3D::movedByCurlNoise(PerlinNoise& noise) {	
	// 偏微分の差
	const float delta = 0.05;

	const Vec3 x0 = getVec3Noise((pos_ + Vec3 { -delta, 0.0, 0.0 } ), noise);
	const Vec3 x1 = getVec3Noise((pos_ + Vec3 { delta, 0.0, 0.0 } ) , noise);
	const Vec3 y0 = getVec3Noise((pos_ + Vec3 { 0.0, -delta, 0.0 } ), noise);
	const Vec3 y1 = getVec3Noise((pos_ + Vec3 { 0.0, delta, 0.0 } ) , noise);
	const Vec3 z0 = getVec3Noise((pos_ + Vec3 { 0.0, 0.0, -delta } ), noise);
	const Vec3 z1 = getVec3Noise((pos_ + Vec3 { 0.0, 0.0, delta } ) , noise);
	const Vec3 dx = x1 - x0;
	const Vec3 dy = y1 - y0;
	const Vec3 dz = z1 - z0;

	const float delta_time = getDeltaTime();
	const Vec3 curl = Vec3 { dy.z-dz.y, dz.x-dx.z, dx.y-dy.x } /(2.0f * delta);
	const Vec3 add = curl * delta_time * 20000.0f;

	velocity_ += -10.0f * (1.0f - weight_ * 0.5f) * velocity_ * delta_time;

	pos_ +=  velocity_  + add * velocity_ * 0.5 + add * 0.3;
}

// 描画
void Particle3D::draw() {
	const float t = (getNowCountFloat() - start_time_) / life_time_;
	float alpha = t < 0.5f ? 1.0f : std::sinf(t * kPiFloat) * std::sinf(t * kPiFloat);
	alpha = Float::clamp(alpha, 0.0f, 1.0f);
	const float wave = std::sinf( (t + offset_) * kTwoPiFloat * 5.0 );

	MATERIALPARAM prm;
	prm.Ambient = GetColorF(0.1f, 0.5f, 1.0f, alpha);
	prm.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, alpha);
	const float rate = (alpha + alpha * wave) * 10.0f;
	prm.Specular = GetColorF(0.1f, 0.5f, 1.0f, alpha * 0.5f);
	prm.Power = 50.0f;
	float r = 0.1f * rate;
	float g = 0.5 * rate;
	float b = 1.0f * rate;
	r = Float::clamp(r, 0.0f, 1.0f);
	g = Float::clamp(g, 0.0f, 1.0f);
	b = Float::clamp(b, 0.0f, 1.0f);
	
	prm.Emissive = GetColorF(r*0.5f, g*0.5f, b*0.5f, 0.3f * alpha);
	SetMaterialParam(prm);
	setDrawBlendMode(BlendMode::init(BlendMode::kAlpha, alpha ));
	DrawSphere3D(VGet(pos_.x, getScreenHeightWithPartition() - pos_.y, pos_.z), radius_, 16, Color::kBlue, Color::kBlue, TRUE);
	setDrawBlendMode(BlendMode::init(BlendMode::kNoBlend, 0 ));
}