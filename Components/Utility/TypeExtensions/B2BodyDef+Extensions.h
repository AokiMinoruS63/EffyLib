/**
 * @file B2BodyDefExtensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief b2BodyDef型のextension
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2_BODY_DEF_EXTENSION_H
#define B2_BODY_DEF_EXTENSION_H

#include "../../OpenSource/Box2D/box2d/b2_body.h"

namespace B2BodyDef {
	/**
	 * @brief ダイナミックボディの参照を作成する
	 * 
	 * @param x 
	 * @param y 
	 * @param rate
	 * @param fixedRotation
	 * @return b2BodyDef 
	 */
	b2BodyDef dynamic(float x, float y, float rate = 1.0, bool fixedRotation = false) {
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef;

		// 動体オブジェクトを定義する
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x / rate, y / rate);
		bodyDef.fixedRotation = fixedRotation;
		return bodyDef;
	}

	/**
	 * @brief ダイナミックボディの参照を作成する
	 * 
	 * @param vec 
	 * @param rate
	 * @param fixedRotation
	 * @return b2BodyDef 
	 */
	b2BodyDef dynamic(b2Vec2 vec, float rate = 1.0, bool fixedRotation = false) {
		return dynamic(vec.x, vec.y, rate, fixedRotation);
	}

	/**
	 * @brief キネマティックボディの参照を作成する
	 * 
	 * @param x 
	 * @param y 
	 * @return b2BodyDef 
	 */
	b2BodyDef kinematic(float x, float y, float rate = 1.0) {
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef;

		// 動体オブジェクトを定義する
		
		bodyDef.type = b2_kinematicBody;
		bodyDef.bullet = false;
		bodyDef.position.Set(x / rate, y / rate);
		return bodyDef;
	}

	/**
	 * @brief キネマティックボディの参照を作成する
	 * 
	 * @param vec 
	 * @return b2BodyDef 
	 */
	b2BodyDef kinematic(b2Vec2 vec, float rate = 1.0) {
		return kinematic(vec.x, vec.y, rate);
	}
}

#endif