/**
 * @file PhysicusWorldFrame.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_WORLD_FRAME_H
#define PHYSICUS_WORLD_FRAME_H

#include "../../../OpenSource/Box2D/box2d/box2d.h"
#include "../../../Utility/TypeExtensions/B2Vec2+Extensions.h"

namespace Physicus {
	// 演算処理に使用する矩形エリア
	struct Frame{
		// 始点
		b2Vec2 start;
		// 終点
		b2Vec2 end;

		/**
		 * @brief 渡された座標が範囲内に収まっていれば**true**
		 * 
		 * @param point チェックする座標
		 * @return true 
		 * @return false 
		 */
		bool areaIn(b2Vec2 point) {
			return point.x > start.x && point.y > start.y && point.x < end.x && point.y < end.y;
		}

		/**
		 * @brief 矩形の頂点のどれかが範囲内に入っていれば**true**
		 * 
		 * @param rect 
		 * @return true 
		 * @return false 
		 */
		bool anyAreaIn(Frame rect) {
			return areaIn(b2Vec2(rect.start.x, rect.start.y)) || areaIn(b2Vec2(rect.end.x, rect.start.y)) || areaIn(b2Vec2(rect.start.x, rect.end.y)) || areaIn(b2Vec2(rect.end.x, rect.end.y));
		}

		/**
		 * @brief エリアに拡大率を適用する
		 * 
		 * @param scale 
		 */
		void applyScale(float scale) {
			B2Vec2::applyScale(&start, scale);
			B2Vec2::applyScale(&end, scale);
		}

		/**
		 * @brief 円から矩形を作成する
		 * 
		 * @param center 中心
		 * @param radius 半径
		 * @return Frame 
		 */
		static Frame fromCircle(b2Vec2 center, float radius) {
			return { b2Vec2(center.x - radius, center.y - radius), b2Vec2(center.x + radius, center.y + radius) };
		}
	};
}

#endif