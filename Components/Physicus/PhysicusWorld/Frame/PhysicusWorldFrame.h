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

#include "../../../OpenSource/Box2D/Box2D.h"
#include "../../../Utility/TypeExtensions/B2Vec2+Extensions.h"
#include <vector>

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

		/**
		 * @brief 円から矩形の各頂点をstd::vectorで返す
		 * 
		 * @param center 
		 * @param radius 
		 * @return std::vector<b2Vec2> 
		 */
		static std::vector<b2Vec2> verticesFromCircle(b2Vec2 center, float radius) {
			std::vector<b2Vec2> vecs;
			const auto frame = fromCircle(center, radius);
			vecs.push_back(b2Vec2(frame.start.x, frame.start.y));
			vecs.push_back(b2Vec2(frame.end.x, frame.start.y));
			vecs.push_back(b2Vec2(frame.start.x, frame.end.y));
			vecs.push_back(b2Vec2(frame.end.x, frame.end.y));
			return vecs;
		}

		/**
		 * @brief 左上座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 leftTop() {
			return start;
		}

		/**
		 * @brief 上座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 top() {
			return b2Vec2(Float::halfWay(start.x, end.x), start.y);
		}

		/**
		 * @brief 右上座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 rightTop() {
			return b2Vec2(end.x, start.y);
		}

		/**
		 * @brief 左座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 left() {
			return b2Vec2(start.x, Float::halfWay(start.y, end.y));
		}

		/**
		 * @brief 中央座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 center() {
			return b2Vec2(Float::halfWay(start.x, end.x), Float::halfWay(start.y, end.y));
		}

		/**
		 * @brief 右座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 right() {
			return b2Vec2(end.x, Float::halfWay(start.y, end.y));
		}

		/**
		 * @brief 左下座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 leftBottom() {
			return b2Vec2(start.x, end.y);
		}

		/**
		 * @brief 下座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 bottom() {
			return b2Vec2(Float::halfWay(start.x, end.x), end.y);
		}

		/**
		 * @brief 右下座標
		 * 
		 * @return b2Vec2 
		 */
		b2Vec2 rightBottom() {
			return end;
		}

		/**
		 * @brief 頂点を返す
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> vertices() {
			std::vector<b2Vec2> vecs;
			vecs.push_back(leftTop());
			vecs.push_back(rightTop());
			vecs.push_back(leftBottom());
			vecs.push_back(rightBottom());
			return vecs;
		}

		/**
		 * @brief 左上からの時計回り順に頂点を返す
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> verticesAround() {
			std::vector<b2Vec2> vecs;
			vecs.push_back(leftTop());
			vecs.push_back(rightTop());
			vecs.push_back(rightBottom());
			vecs.push_back(leftBottom());
			return vecs;
		}
	};
}

#endif