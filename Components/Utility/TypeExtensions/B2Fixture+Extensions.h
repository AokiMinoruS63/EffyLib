/**
 * @file B2Fixture+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2FIXTURE_EXTENSION_H
#define B2FIXTURE_EXTENSION_H

#include "../../OpenSource/Box2D/Box2D.h"
#include <vector>

namespace B2Fixture {
	/**
	 * @brief fixtureのデフォルトのプリセット
	 * 
	 * @return b2FixtureDef 
	 */
	inline b2FixtureDef defaultSetting() {
		b2FixtureDef fixtureDef = b2FixtureDef();
		// 密度を設定
		fixtureDef.density = 1.00f;
		// 摩擦を設定
		fixtureDef.friction = 0.1f;
		// 反発を設定
		fixtureDef.restitution = 0.0;
		
		return fixtureDef;
	}
	/**
	 * @brief fixtureのサイズを得る
	 * 
	 * @param fixture fixtureのポインタ
	 * @return int 
	 */
	inline int count(b2Fixture* fixture) {
		int count = 0;
		b2Fixture* itr;
		itr = fixture;
		while(itr != NULL) {
			count++;
			itr = itr->GetNext();
		}
		return count;
	}

	/**
	 * @brief fixtureListをstd::vectorに変換する
	 * 
	 * @param fixture 
	 * @return std::vector<b2Fixture*> 
	 */
	inline std::vector<b2Fixture*> toVector(b2Fixture* fixture) {
		auto itr = fixture;
		std::vector<b2Fixture*> vec;
		while(itr != NULL) {
			vec.push_back(itr);
			itr = itr->GetNext();
		}
		// fixtureListは先入先出し方式なので反転させる
		std::reverse(vec.begin(), vec.end());
		return vec;
	}

	namespace Edge {
		/**
		 * @brief 始点と終点の頂点座標を返す
		 * 
		 * @param fixture 
		 * @param scale 
		 * @return std::vector<b2Vec2> 
		 */
		inline std::vector<b2Vec2> vertices(b2Fixture* fixture, float scale = 1.0) {
			std::vector<b2Vec2> vec;
			b2Vec2 position = fixture->GetBody()->GetPosition();
			b2EdgeShape* shape = (b2EdgeShape*)fixture->GetShape();

			b2Vec2 pos1 = B2Vec2::multiplication(B2Vec2::add(position, shape->m_vertex1), scale);
			b2Vec2 pos2 = B2Vec2::multiplication(B2Vec2::add(position, shape->m_vertex2), scale);
			vec.push_back(pos1);
			vec.push_back(pos2);
			return vec;
		}
	}
}

#endif