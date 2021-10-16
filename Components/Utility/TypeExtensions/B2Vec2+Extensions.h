/**
 * @file B2Vec2Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief b2Vec2型のextension
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2VEC2_EXTENSION_H
#define B2VEC2_EXTENSION_H

#include "Float+Extensions.h"
#include "../../OpenSource/Box2D/box2d/b2_math.h"
#include "../../Touch/TouchData.h"
#include <cmath>
#include <vector>

namespace B2Vec2 {
	// 頂点作成の追加が可能な最低限の距離。ジョイント繋がりの強さに直結する
	static const float kCreateVertexDistance = 3.0;

	/**
	 * @brief 列の位置
	 * 
	 */
	enum Horizon {
		kCenter,
		kLeading,
		kTrailing
	};

	/**
	 * @brief ２つのB2Vecの中間地点を返す
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @return b2Vec2 
	 */
	static b2Vec2 halfWay(b2Vec2 start, b2Vec2 end) {
		return b2Vec2(Float::halfWay(start.x, end.x), Float::halfWay(start.y, end.y));
	}

	/**
	 * @brief ２つの座標の中間地点を返す
	 * 
	 * @param sx 
	 * @param sy 
	 * @param gx 
	 * @param gy 
	 * @return b2Vec2 
	 */
	static b2Vec2 halfWay(float sx, float sy, float gx, float gy) {
		return b2Vec2(Float::halfWay(sx, gx), Float::halfWay(sy, gy));
	}

	/**
	 * @brief ２つの座標の距離を返す
	 * 
	 * @param sx 
	 * @param sy 
	 * @param gx 
	 * @param gy 
	 * @return float 
	 */
	static float distance(float sx, float sy, float gx, float gy) {
		return sqrtf(powf(gx - sx, 2) + powf(gy - sy, 2));
	}

	/**
	 * @brief ２つの座標の距離を返す
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @return float 
	 */
	static float distance(b2Vec2 start, b2Vec2 end) {
		return distance(start.x, start.y, end.x, end.y);
	}

	/**
	 * @brief 座標に拡大率を適用する
	 * 
	 * @param vec 座標
	 * @param scale 拡大率
	 */
	static void applyScale(b2Vec2 *vec, float scale) {
		vec->x *= scale;
		vec->y *= scale;
	}

	/**
	 * @brief ポリゴンに拡大率を適用する
	 * 
	 * @param vec ポリゴン
	 * @param scale 拡大率
	 */
	static void applyScale(std::vector<b2Vec2> vec, float scale) {
		if(scale == 0) {
			return;
		}
		for(auto& itr: vec) {
			itr.x *= scale;
			itr.y *= scale;
		}
	}

	/**
	 * @brief 座標に縮小率を適用する
	 * 
	 * @param vec 座標
	 * @param rate 縮小率
	 */
	static void applyRate(b2Vec2 *vec, float rate) {
		applyScale(vec, 1.0 / rate);
	}

	/**
	 * @brief ポリゴンに縮小率を適用する
	 * 
	 * @param vec ポリゴン
	 * @param rate 縮小率
	 */
	static void applyRate(std::vector<b2Vec2> vec, float rate) {
		applyScale(vec, 1.0 / rate);
	}

	/**
	 * @brief 基準点からの相対的な距離を算出するのに使用
	 * 
	 * @param base 基準点
	 * @param target 変換する座標
	 * @return b2Vec2 
	 */
	static b2Vec2 relativePosition(b2Vec2 base, b2Vec2 target) {
		return b2Vec2(target.x - base.x, target.y - base.y);
	}

	/**
	 * @brief 基準点からの相対的な距離をポリゴンに適用する
	 * 
	 * @param base 基準座標
	 * @param target 適用するポリゴン
	 */
	static void setRelativePosition(b2Vec2 base, std::vector<b2Vec2> target) {
		for(auto& itr: target) {
			itr = relativePosition(base, itr);
		}
	}

	/**
	 * @brief 二つのベクトルを足した値を返す
	 * 
	 * @param pos1 
	 * @param pos2 
	 * @return b2Vec2 
	 */
	static b2Vec2 add(b2Vec2 pos1, b2Vec2 pos2) {
		return b2Vec2(pos1.x + pos2.x, pos1.y + pos2.y);
	}

	/**
	 * @brief 始点を終点で引いた数を返す
	 * 
	 * @param pos1 
	 * @param pos2 
	 * @return b2Vec2 
	 */
	static b2Vec2 sub(b2Vec2 pos1, b2Vec2 pos2) {
		return b2Vec2(pos1.x - pos2.x, pos1.y - pos2.y);
	}

	/**
	 * @brief ベクトルをfloatで割る
	 * 
	 * @param pos 
	 * @param rate 
	 * @return b2Vec2 
	 */
	static b2Vec2 division(b2Vec2 pos, float rate) {
		if(rate == 0) {
			return pos;
		}
		return b2Vec2(pos.x / rate, pos.y / rate);
	}

	/**
	 * @brief 多角形の重心を求める
	 * 
	 * @param vec std::vector<b2Vec2>
	 * @return b2Vec2 
	 */
	static b2Vec2 center(std::vector<b2Vec2> vec) {
		b2Vec2 pos = b2Vec2();
		for(auto& itr: vec) {
			pos = B2Vec2::add(pos, itr);
		}
		return B2Vec2::division(pos, (float)vec.size());
	}

	/**
	 * @brief int型の座標からb2Vec2型の座標に変換する
	 * 
	 * @param x 
	 * @param y 
	 * @return b2Vec2 
	 */
	static b2Vec2 fromIntPos(int x, int y) {
		return b2Vec2((float)x, (float)y);
	}

	/**
	 * @brief touch_t型の座標からb2Vec2型の座標に変換する
	 * 
	 * @param touch 
	 * @param scale 
	 * @return b2Vec2 
	 */
	static b2Vec2 fromTouch(touch_t touch, float scale = 1.0) {
		return b2Vec2(((float)touch.x) * scale, ((float)touch.y) * scale);
	}

	/**
	 * @brief 軌跡としての頂点が作成出来るなら**true**
	 * 
	 * @param start 
	 * @param end 
	 * @return true 
	 * @return false 
	 */
	static bool checkCreatePos(b2Vec2 start, b2Vec2 end) {
		return B2Vec2::distance(start, end) >= kCreateVertexDistance;
	}

	/**
	 * @brief b2Bodyに使用出来る軌跡を作成する
	 * 
	 * @param xVec X配列
	 * @param yVec Y配列
	 * @param beginIndex タッチが開始されたインデックス
	 * @return std::vector<b2Vec2> 
	 */
	static std::vector<b2Vec2> locus(std::vector<int> xVec, std::vector<int> yVec, int beginIndex) {
		std::vector<b2Vec2> vertices;
		int beforeIndex = beginIndex;
		#define START fromIntPos(xVec[beforeIndex], yVec[beforeIndex])
		#define END fromIntPos(xVec.at(i), yVec.at(i))
		vertices.push_back(START);
		for(int i = beginIndex - 1; i >= 0; i--) {
			// 頂点の距離が近すぎて作成出来なければ頂点を作成しない
			if(!checkCreatePos(START, END)) {
				continue;
			}
			// 初回でなければ頂点を作成
			vertices.push_back(END);
			beforeIndex = i;
		}
		#undef START
		#undef END
		return vertices;
	}

	/**
	 * @brief 直近の軌跡を返す
	 * 
	 * @param locusList 軌跡
	 * @param current 現在の座標
	 * @param last 1つ前の座標
	 * @param lastLast 2つ前の座標
	 */
	static void recentLocus(std::vector<b2Vec2> locusList, b2Vec2* current, b2Vec2* last, b2Vec2* lastLast) {
		*current = locusList.back();
		*last = locusList.size() < 2 ? *current : locusList.at(locusList.size() - 2);
		*lastLast = locusList.size() < 3 ? sub(*current, *last) : locusList.at(locusList.size() - 3);
	}

	/**
	 * @brief ベース座標から半径分回転させる
	 * 
	 * @param pos ベース座標
	 * @param radius 半径
	 * @param radian 角度
	 * @param horizon -90度、90度に回転させる時のみ使用
	 * @return b2Vec2 
	 */
	static b2Vec2 rotate(b2Vec2 pos, float radius, float radian, Horizon horizon = kCenter ) {
		float adjustedAngle;
		switch(horizon) {
			case kLeading:
			adjustedAngle = - DX_PI_F / 2.0;
			break;
			case kTrailing:
			adjustedAngle = DX_PI_F / 2.0;
			break;
			adjustedAngle = 0;
			default:break;
		}
		const float x = pos.x + radius * cos( radian + adjustedAngle);
		const float y = pos.y + radius * sin( radian + adjustedAngle);
		return b2Vec2(x, y);
	}

	/**
	 * @brief 数珠繋ぎに出来る距離なら**true**
	 * 
	 * @param vec 
	 * @param range 判定する距離
	 * @return true 
	 * @return false 
	 */
	static bool isTieLoop(std::vector<b2Vec2> vec, float range) {
		return distance(vec.front().x, vec.front().y, vec.back().x, vec.back().y) < range;
	}

	/**
	 * @brief 角度を返す
	 * 
	 * @param start 始点
	 * @param end 終点
	 * @return float 
	 */
	static float angle(b2Vec2 start, b2Vec2 end) {
		return atan2(start.y - end.y, start.x - end.x);
	}
}

#endif