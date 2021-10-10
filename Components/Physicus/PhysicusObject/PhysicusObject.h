/**
 * @file PhysicusObject.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief Box2D用のオブジェクト
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_H
#define PHYSICUS_OBJECT_H

// TODO: include vector, Touch.h, box2d.h
#include "../../OpenSource/Box2D/box2d/box2d.h"
#include <vector>
#include "../../Touch/TouchData.h"
#include "PhysicusObjectType.h"
#include "../../Utility/TypeExtensions.h"

namespace Physicus {

	// オブジェクトの実体
	class Object {
		// オブジェクトの中に入っているボディ
		std::vector<b2Body *> m_bodies;
		// 演算を行うワールド
		b2World* m_world;
		// 線の太さ
		float m_lineWidth;
		// 線の軌跡用の画像
		int m_img[3];
		// 線の色
		int m_color;
		// オブジェクトのタイプ
		Type m_type;

		public:
		Object(Type type, b2World* world, touch_t touch);
		~Object();

		void setLineWidth(float width);
		void setImg(int img[3]);

		// オブジェクトのタイプを返す
		Type getType();

		// TODO: マウスドラッグ中でもボディが生成されるようにする（ただし、ドラッグ中は演算を行わないでリリースされた時に演算を開始させる）
		// TODO: この仕様も相まって前回のボディと前回のボディの終点座標と終点右と終点左の座標が必要
		// b2Vec2 touchStart(タッチした座標の記録に使用。ログが残らない場合があるため), lastAngle(始点の回転に使用), 
		// touchLast(前回の座標), touchCurrent
		// TODO: 円の場合や矩形の場合は実際に表示させるのではなく、ガイド線を表示するのみにした方が良い。
		// TODO: 描画メソッド、頂点作成メソッドなどを作成する
	};
}

#endif