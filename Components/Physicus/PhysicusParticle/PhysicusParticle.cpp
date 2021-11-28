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
#include "../../Utility/DxLibWrap.h"
#include "../../Utility/TypeExtensions.h"

using namespace Physicus;

Particle::Particle(touch_t touch, b2ParticleSystem* particle_system, b2World* world, float scale, ParticleSetting setting) {
	// TODO: タッチから生成する
	//printfDx("生成メソッド\n");
	world_ = world;
	b2Vec2 vec = B2Vec2::fromTouch(touch, scale);
	world_scale_ = scale;
	setting_ = setting;
	//setting_.setting.radius = 0.5;
	locus_.push_back(vec);
	particle_system_ = particle_system;

	b2PolygonShape shape;
	shape.SetAsBox(2, 2);
	b2ParticleGroupDef pd = b2ParticleGroupDef();
	pd.flags = b2_waterParticle;
	//pd.flags = b2_tensileParticle | b2_viscousParticle;
	//pd.angularVelocity = 0.2;
	//pd.flags = b2_colorMixingParticle;
	//pd.flags = b2_elasticParticle;
	//pd.flags = b2_springParticle;
	//pd.flags = b2_reactiveParticle;
	pd.groupFlags = b2_solidParticleGroup;
	pd.position.Set(touch.x * scale, touch.y * scale);
	//pd.angle = -0.5f;
	pd.angularVelocity = 2.0f;
	pd.strength = 0.0;
	//pd.angle = -0.5f;
	//pd.angularVelocity = 2.0f;
	pd.shape = &shape;
	//pd.color.Set(0, 0, 255, 255);
	particle_ = particle_system_->CreateParticleGroup(pd);

	/*
	{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			{
				b2PolygonShape shape;
				const b2Vec2 vertices[4] = {
					b2Vec2(-4, -1),
					b2Vec2(4, -1),
					b2Vec2(4, 0),
					b2Vec2(-4, 0)};
				shape.Set(vertices, 4);
				ground->CreateFixture(&shape, 0.0f);
			}

			{
				b2PolygonShape shape;
				const b2Vec2 vertices[4] = {
					b2Vec2(-4, -0.1f),
					b2Vec2(-2, -0.1f),
					b2Vec2(-2, 2),
					b2Vec2(-4, 2)};
				shape.Set(vertices, 4);
				ground->CreateFixture(&shape, 0.0f);
			}

			{
				b2PolygonShape shape;
				const b2Vec2 vertices[4] = {
					b2Vec2(2, -0.1f),
					b2Vec2(4, -0.1f),
					b2Vec2(4, 2),
					b2Vec2(2, 2)};
				shape.Set(vertices, 4);
				ground->CreateFixture(&shape, 0.0f);
			}
		}

		m_particleSystem->SetRadius(0.035f);

		{
			b2CircleShape shape;
			shape.m_p.Set(0, 3);
			shape.m_radius = 0.5f;
			b2ParticleGroupDef pd;
			pd.flags = b2_springParticle;
			pd.groupFlags = b2_solidParticleGroup;
			pd.shape = &shape;
			pd.color.Set(255, 0, 0, 255);
			m_particleSystem->CreateParticleGroup(pd);
		}

		{
			b2CircleShape shape;
			shape.m_p.Set(-1, 3);
			shape.m_radius = 0.5f;
			b2ParticleGroupDef pd;
			pd.flags = b2_elasticParticle;
			pd.groupFlags = b2_solidParticleGroup;
			pd.shape = &shape;
			pd.color.Set(0, 255, 0, 255);
			m_particleSystem->CreateParticleGroup(pd);
		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(1, 0.5f);
			b2ParticleGroupDef pd;
			pd.flags = b2_elasticParticle;
			pd.groupFlags = b2_solidParticleGroup;
			pd.position.Set(1, 4);
			pd.angle = -0.5f;
			pd.angularVelocity = 2.0f;
			pd.shape = &shape;
			pd.color.Set(0, 0, 255, 255);
			m_particleSystem->CreateParticleGroup(pd);
		}

		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd);
			b2CircleShape shape;
			shape.m_p.Set(0, 8);
			shape.m_radius = 0.5f;
			body->CreateFixture(&shape, 0.5f);
		}
	*/
}

Particle::~Particle() {

}

// グループを取得する
int Particle::getGroup() {
	return setting_.group;
}

// パーティクルの生成
bool Particle::generation(touch_t touch) {
	return false;
}

// パーティクルの描画
void Particle::draw() {
	//printfDx("パーティクル描画メソッド\n");
	// TODO: 液体以外にも画像などの描画も行う
	b2Vec2* vecList { particle_system_->GetPositionBuffer() + particle_->GetBufferIndex() };
	for(int i = 0; i < particle_->GetParticleCount(); i++) {
		b2Vec2 position = vecList[i];
		int x = (int)(position.x / world_scale_);
		int y = (int)(position.y / world_scale_);
		int r = (int)(setting_.setting.radius / world_scale_);
		// 楕円の描画を行う
		drawOval(x, y, r - setting_.draw_small_value_x, r - setting_.draw_small_value_y, Color::kWhite, TRUE);
	}
}

// 編集中のパーティクルの描画
void Particle::drawEditing() {
	//printfDx("編集中パーティクル描画メソッド\n");
}

// パーティクルのフレームの描画
void Particle::drawDebugFrame() {
	//printfDx("パーティクルデバッグフレーム描画メソッド\n");
	//座標バッファ
	b2Vec2* vecList { particle_system_->GetPositionBuffer() + particle_->GetBufferIndex() };
	for(int i = 0; i < particle_->GetParticleCount(); i++) {
		b2Vec2 position = vecList[i];
		int x = (int)(position.x / world_scale_);
		int y = (int)(position.y / world_scale_);
		int r = (int)(setting_.setting.radius / world_scale_);
		DrawCircle(x, y, r, Color::kWhite, FALSE);
		//DrawFormatString(x, y, Color::kWhite, "%d", i);
		//DrawCircle(x, y, r, setting_.color, FALSE);
	}
	for(int i = 0; i < particle_->GetParticleCount(); i++) {
		b2Vec2 position = vecList[i];
		int x = (int)(position.x / world_scale_);
		int y = (int)(position.y / world_scale_);
		int r = (int)(setting_.setting.radius / world_scale_);
		//DrawCircle(x, y, r, Color::kBlue);
		//DrawFormatString(x, y, Color::kWhite, "%d", i);
		//DrawCircle(x, y, r, setting_.color, FALSE);
	}
	
	/*
	// 各パーティクルのデータから画像を更新する
    for (b2ParticleGroup* group : this->particleGroups)
    {
        
        //グループのパーティクルを更新
        void ** userData { particleSystem->GetUserDataBuffer() + group->GetBufferIndex() };
        
        
        
        //色バッファ
        b2ParticleColor * colorList { particleSystem->GetColorBuffer() + group->GetBufferIndex() };
        
        //バッファループ
        for(int i = 0; i < group->GetParticleCount();i++,vecList++,userData++)
        {
            // 位置を更新
            if(Sprite* particleImage { static_cast<Sprite*>(*userData) })
            {
                particleImage->setColor(Color3B((*colorList).r, (*colorList).g, (*colorList).b));
                particleImage->setPosition((*vecList).x * PTM_RATIO, (*vecList).y*PTM_RATIO);
            }
        }
    }
	*/
	/*
	while(group != NULL) {
		auto position = group->GetPosition();
		auto count = position.Length();
		//for(int i = 0; i < count; i++) {
			drawCircle((int)(position.x / world_scale_), (int)(position.y / world_scale_), (int)(setting_.setting.radius / world_scale_), setting_.color, FALSE, FALSE);
		//}
		group = group->GetNext();
	}
	*/
	// GetPositionBuffer();
	/*
	auto system = particle_system_;
	while(system != NULL) {
		auto position = particle_system_->GetPositionBuffer();
		auto count = position->Length();
		for(int i = 0; i < count; i++){
			drawCircle((int)(position[i].x / world_scale_), (int)(position[i].y / world_scale_), (int)(setting_.setting.radius / world_scale_), setting_.color, FALSE, FALSE);
		//console.log('x, y:', buf[i], buf[i+1]);
		system = system->GetNext();
		}
	}
	*/
}

// 編集中のパーティクルのフレームの描画
void Particle::drawEditingDebugFrame() {
	//printfDx("編集中パーティクルデバッグフレーム描画メソッド\n");
	drawDebugFrame();
}