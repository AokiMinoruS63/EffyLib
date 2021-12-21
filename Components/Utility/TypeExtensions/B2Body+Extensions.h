/**
 * @file B2Body+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2BODY_EXTENSION_H
#define B2BODY_EXTENSION_H

#include "Float+Extensions.h"
#include "B2Vec2+Extensions.h"
#include "../../OpenSource/Box2D/Box2D.h"
#include "../DxLibWrap.h"
#include "../../Physicus/PhysicusWorld/Frame/PhysicusWorldFrame.h"

namespace B2Body {
	// Box２Dの演算が正常に出来る最小限の距離
	static constexpr float kMinCreateVertexRange = 0.1;

	/**
	 * @brief 頂点変更フラグ
	 * 
	 */
	enum class VerticesChange {
		kNoRotate,
		kHalfPiRotate,
		kPiRotate,
		kPiHalfPiRotate
	};

	/**
	 * @brief b2Bodyの頂点座標を返す
	 * 
	 * @param body 
	 * @return const std::vector<b2Vec2> 
	 */
	inline const std::vector<b2Vec2> vertices(const b2Body* body, float scale = 1.0) {
		std::vector<b2Vec2> vertices;
		const auto fixture = body->GetFixtureList();
		const auto type = fixture->GetType();
		const auto position = fixture->GetBody()->GetPosition();

		switch (type) {
			case b2Shape::e_circle:
			{
				const b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
				return Physicus::Frame::verticesFromCircle(position, shape->m_radius);
			}
			break;
			case b2Shape::e_chain:
			printfDx("e_chain");
			break;
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)fixture->GetShape();
				b2Vec2 pos1 = B2Vec2::add(position, B2Vec2::rotate(shape->m_vertex1, body->GetAngle()));
				b2Vec2 pos2 = B2Vec2::add(position, B2Vec2::rotate(shape->m_vertex2, body->GetAngle()));
				B2Vec2::applyScale(&pos1, scale);
				B2Vec2::applyScale(&pos2, scale);
				vertices.push_back(pos1);
				vertices.push_back(pos2);
			}
			break;
			case b2Shape::e_polygon:
			{
				b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
				for(int i = 0; i < shape->m_count; i++) {
					b2Vec2 pos = B2Vec2::add(position, B2Vec2::rotate(shape->m_vertices[i], body->GetAngle()));
					B2Vec2::applyScale(&pos, scale);
					vertices.push_back(pos);
				}
			}
			break;
			case b2Shape::e_typeCount:
			printfDx("e_typeCount");
			break;
			default:
			printfDx("typeNone...");
			break;
		}
		return vertices;
	}

	/**
	 * @brief ボディの頂点（円の場合は納まる矩形）が全てエリア外に出ているか判定する
	 * 
	 * @param body 
	 * @param area 
	 * @return true 
	 * @return false 
	 */
	inline bool areaOut(b2Body* body, Physicus::Frame area) {
		const auto fixture = body->GetFixtureList();
		const auto type = fixture->GetType();
		const auto position = fixture->GetBody()->GetPosition();
		switch (type) {
			case b2Shape::e_circle:
			{
				const b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
				const auto rect = Physicus::Frame::fromCircle(position, shape->m_radius);
				if(area.anyAreaIn(rect)) {
					return false;
				}
			}
			break;
			case b2Shape::e_chain:
			printfDx("e_chain");
			break;
			case b2Shape::e_edge:
			{
				auto itr = fixture;
				b2EdgeShape* shape = (b2EdgeShape*)fixture->GetShape();
				while(itr != NULL) {
					b2Vec2 pos1 = B2Vec2::add(position, shape->m_vertex1);
					b2Vec2 pos2 = B2Vec2::add(position, shape->m_vertex2);
					if(area.areaIn(pos1) || area.areaIn(pos2)) {
						return false;
					}
					itr = itr->GetNext();
					shape = (b2EdgeShape*)itr->GetShape();
				}			
			}
			break;
			case b2Shape::e_polygon:
			{
				auto itr = fixture;
				b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
				while(itr != NULL) {
					for(int i = 0; i < shape->m_count; i++) {
						const b2Vec2 pos = B2Vec2::add(position, shape->m_vertices[i]);
						if(area.areaIn(pos)) {
							return false;
						}
					}
					itr = itr->GetNext();
					shape = (b2PolygonShape*)itr->GetShape();
				}
			}
			break;
			case b2Shape::e_typeCount:
			printfDx("e_typeCount");
			break;
			default:
			printfDx("typeNone...");
			break;
		}
		return true;
	}

	/**
	 * @brief オブジェクトのフレームを描画する
	 * 
	 * @param body 
	 * @param scale 
	 * @param color 
	 */
	inline void drawFrame(b2Body* body, float scale, int color = Color::kWhite) {
		const b2Vec2 position = body->GetPosition();
		const float angle = body->GetAngle();
		const auto fixture = body->GetFixtureList();
		const auto type = fixture->GetType();
		switch (type) {
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
				auto pos = fixture->GetBody()->GetPosition();
				drawCircle(pos.x / scale, pos.y / scale, shape->m_radius / scale, color);				
			}
			break;
			case b2Shape::e_chain:
			printfDx("e_chain");
			break;
			case b2Shape::e_edge:
			{
				auto nowFixture = fixture;
				while(nowFixture != NULL) {
					b2EdgeShape* shape = (b2EdgeShape*)nowFixture->GetShape();
					b2Vec2 start = B2Vec2::multiplication(B2Vec2::add(shape->m_vertex1, position), 1.0 / scale);
					b2Vec2 end = B2Vec2::multiplication(B2Vec2::add(shape->m_vertex2, position), 1.0 / scale);
					drawLine(start.x , start.y, end.x, end.y, color);
					nowFixture = nowFixture->GetNext();
				}
			}
			break;
			case b2Shape::e_polygon:
			{
				auto itr = fixture;
				b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
				while(itr != NULL && shape != NULL) {
					for(int i = 0; i < shape->m_count; i++) {
						auto localStart = shape->m_vertices[i];
						auto localEnd = shape->m_vertices[(i + 1) % shape->m_count];
						auto start = fixture->GetBody()->GetWorldPoint(localStart);
						auto end = fixture->GetBody()->GetWorldPoint(localEnd);
						drawLine(start.x / scale, start.y / scale, end.x / scale, end.y / scale, color);
					}
					itr = itr->GetNext();
					shape = (b2PolygonShape*)itr->GetShape();
				}
			}
			break;
			case b2Shape::e_typeCount:
			printfDx("e_typeCount");
			break;
			default:
			printfDx("typeNone...");
			break;
		}
	}
}

#endif