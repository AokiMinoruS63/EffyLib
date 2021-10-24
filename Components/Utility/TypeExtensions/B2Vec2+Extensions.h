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
#include "Array+Extensions.h"
#include "../../OpenSource/Box2D/box2d/b2_math.h"
#include "../../Utility/DxLibWrap.h"
#include "../../Touch/TouchData.h"
#include <cmath>
#include <vector>

namespace B2Vec2 {
	// 頂点作成の追加が可能な最低限の距離。ジョイント繋がりの強さに直結する
	static const float kCreateVertexDistance = 3.0;
	// 半分
	static const b2Vec2 kHalf = b2Vec2(0.5, 0.5);

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
	 * @brief 交点があるかどうか
	 * 
	 */
	enum class Intersect {
		// 平行なため計算が出来ない
		kImpossibleCalc,
		// 交点が存在する
		kIntersection,
		// 交点が存在しない
		kNoIntersection
	};

	/**
	 * @brief 内積を求める
	 * 
	 * @param vl 
	 * @param vr 
	 * @return float 
	 */
	static float innerProduct(b2Vec2& vl, b2Vec2& vr) {
		return vl.x * vr.x + vl.y * vr.y;
	}

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
	 * @brief ２つの座標の進行度に応じた座標を返す
	 * 
	 * @param sx 
	 * @param sy 
	 * @param gx 
	 * @param gy 
	 * @param rate 進行度
	 * @return b2Vec2 
	 */
	static b2Vec2 between(float sx, float sy, float gx, float gy, float rate) {
		return b2Vec2(Float::between(sx, gx, rate), Float::between(sy, gy, rate));
	}

	/**
	 * @brief ２つの座標の進行度に応じた座標を返す
	 * 
	 * @param start 
	 * @param end 
	 * @param rate 進行度
	 * @return b2Vec2 
	 */
	static b2Vec2 between(b2Vec2 start, b2Vec2 end, float rate) {
		return between(start.x, start.y, end.x, end.y, rate);
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
	 * @brief ２つの頂点に掛け算をした結果を返す
	 * 
	 * @param pos1 
	 * @param pos2 
	 * @return b2Vec2 
	 */
	static b2Vec2 multiplication(b2Vec2 pos1, b2Vec2 pos2) {
		return b2Vec2(pos1.x * pos2.x, pos1.y * pos2.y);
	}

	/**
	 * @brief 頂点に掛け算をした結果を返す
	 * 
	 * @param pos 
	 * @param scale 
	 * @return b2Vec2 
	 */
	static b2Vec2 multiplication(b2Vec2 pos, float scale) {
		return b2Vec2(pos.x * scale, pos.y * scale);
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
		// TODO: lastLastの座標が折り返した時におかしくなるので要修正
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
	 * @brief 原点からの座標から回転後の座標を求める
	 * 
	 * @param pos 原点を０とした時の座標
	 * @param radian 角度
	 * @return b2Vec2 回転後の座標
	 */
	static b2Vec2 rotate(b2Vec2 pos, float radian) {
		return b2Vec2(pos.x * cos(radian) - pos.y * sin(radian), pos.x * sin(radian) + pos.y * cos(radian));
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

	/**
	 * @brief 単位ベクトルを返す
	 * 
	 * @param vec 
	 * @return b2Vec2 
	 */
	static b2Vec2 unitVector(b2Vec2 vec) {
		float length = powf((vec.x * vec.x) + (vec.y + vec.y), 0.5);
		if(length == 0) {
			return vec;
		}
		return division(vec, length);
	}

	/**
	 * @brief 交差の大きさを得る
	 * 
	 * @param posA 
	 * @param posB 
	 * @return float 
	 */
	static float crossValue(b2Vec2 posA, b2Vec2 posB) {
		return posA.x * posB.y - posA.y * posB.x;
	}

	/**
	 * @brief 二つの直線が交差するか判定する
	 * 
	 * @param result 交差する頂点
	 * @param posA 線分１の始点
	 * @param posB 線分１の終点
	 * @param posC 線分２の始点
	 * @param posD 線分２の終点
	 * @return Intersect 
	 */
	static Intersect intersectLines(b2Vec2* result, b2Vec2 posA, b2Vec2 posB, b2Vec2 posC, b2Vec2 posD) {
		const b2Vec2 v = sub(posC, posA);
		b2Vec2 v1 = sub(posB, posA);
		const b2Vec2 v2 = sub(posD, posC);
		const float cp = crossValue(v1, v2);
		if(cp == 0) {
			return Intersect::kImpossibleCalc;
		}
		const float cp1 = crossValue(v, v1);
		const float cp2 = crossValue(v, v2);
		float t1 = cp2 / cp;
		const float t2 = cp1 / cp;
		const float s = 0.00001;
		if(t1 + s < 0 || t1 - s > 1.0 || t2 + s < 0 || t2 - s > 1) {
			return Intersect::kNoIntersection;
		}
		applyScale(&v1, t1);
		if(result != NULL) {
			*result =  add(posA, v1);
		}
		return Intersect::kIntersection;
	}

	/**
	 * @brief ３つの制御点のベジェの座標を取得する
	 * 
	 * @param pos 制御点
	 * @param t 進行率(0.0 〜 1.0)
	 * @return b2Vec2 
	 */
	static b2Vec2 bezieValue(b2Vec2 pos[3], float t) {
		const float x[3] = { pos[0].x, pos[1].x, pos[2].x };
		const float y[3] = { pos[0].y, pos[1].y, pos[2].y };
		return b2Vec2(
			Float::bezieValue(x, t),
			Float::bezieValue(y, t)
		);
	}

	/**
	 * @brief DxLib::VECTORに変換
	 * 
	 * @param vec 
	 * @return DxLib::VECTOR 
	 */
	static DxLib::VECTOR toDxLibVector(b2Vec2 vec) {
		DxLib::VECTOR vector;
		vector.x = vec.x;
		vector.y = vec.y;
		vector.z = 0.0;
		return vector;
	}

	/**
	 * @brief DxLibの矩形の頂点に変換する
	 * 
	 * @param vertices 
	 * @param color 
	 * @return std::vector<VERTEX2D> 
	 */
	static std::vector<VERTEX2D> toDxLibRectVertices(std::vector<b2Vec2> vertices, int color) {
		const int max = 6;
		VERTEX2D vecs[max];
		int r, g, b;
		GetColor2(color, &r, &g, &b);
		// UV
		vecs[0].u = 0.0;
		vecs[0].v = 0.0;
		vecs[1].u = 1.0;
		vecs[1].v = 0.0;
		vecs[2].u = 0.0;
		vecs[2].v = 1.0;
		vecs[3].u = 1.0;
		vecs[3].v = 1.0;
		vecs[4].u = 0.0;
		vecs[4].v = 1.0;
		vecs[5].u = 1.0;
		vecs[5].v = 0.0;
		// rhw
		vecs[0].rhw = 1.0;
		vecs[1].rhw = 1.0;
		vecs[2].rhw = 1.0;
		vecs[3].rhw = 1.0;
		vecs[4].rhw = 1.0;
		vecs[5].rhw = 1.0;
		// dif
		for(int i = 0; i < max; i++) {
			vecs[i].dif.r = r;
			vecs[i].dif.g = g;
			vecs[i].dif.b = b;
			vecs[i].dif.a = 1.0;
		}
		// pos
		vecs[0].pos = toDxLibVector(vertices.at(0));
		vecs[1].pos = toDxLibVector(vertices.at(1));
		vecs[2].pos = toDxLibVector(vertices.at(2));
		vecs[3].pos = toDxLibVector(vertices.at(3));
		vecs[4].pos = toDxLibVector(vertices.at(2));
		vecs[5].pos = toDxLibVector(vertices.at(1));
		
		return Array::toVector(vecs, 6);
	}

	/**
	 * @brief ２つの座標を交換する
	 * 
	 * @param pos1 
	 * @param pos2 
	 */
	static void swap(b2Vec2* pos1, b2Vec2* pos2) {
		const b2Vec2 tmp = *pos1;
		*pos1 = *pos2;
		*pos2 = tmp;
	}

	/**
	 * @brief 矩形の始点と終点をセットする
	 * 
	 * @param start 
	 * @param end 
	 */
	static void setStartEnd(b2Vec2* start, b2Vec2* end) {
		if(start->x > end->x) {
			Float::swap(&start->x, &end->x);
		}
		if(start->y > end->y) {
			Float::swap(&start->y, &end->y);
		}
	}
}

#endif