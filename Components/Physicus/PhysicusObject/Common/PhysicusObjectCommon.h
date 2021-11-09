/**
 * @file PhysicusObjectCommon.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_COMMON_H
#define PHYSICUS_OBJECT_COMMON_H

#include "../../../OpenSource/Box2D/Box2D.h"
#include <vector>

namespace Physicus {
	class Object;
};

/**
 * @brief 始点と終点をセットする
 * 
 * @param obj オブジェクト
 * @param start 始点
 * @param end 終点
 * @param swap 座標を始点と終点を入れ替えるなら**true**
 */
void setDrawStartEnd(Physicus::Object* obj, b2Vec2* start, b2Vec2* end, bool swap = true);

using namespace Physicus;

/**
 * @brief 軌跡から線の太さを考慮した頂点を設定する
 * 
 * @param obj 矩形オブジェクト
 * @param vertices 頂点配列
 * @param outside 外周
 * @param inside 内周
 */
void getVertices(Physicus::Object* obj, std::vector<b2Vec2> vertices, b2Vec2 outside[4], b2Vec2 inside[4]);

/**
 * @brief 線の軌跡を作成する
 * 
 * @param obj 
 */
void createLineLocus(Physicus::Object* obj);

/**
 * @brief １つの直線を分割して描画する
 * 
 * @param obj オブジェクト
 * @param vec 頂点（外側終点、内側終点、内側始点、外側始点）
 * @param drawAdvance 進行率
 * @param imageIndex 現在のオブジェクトの画像インデックス
 * @return int 描画終了時のimageIndex
 */
int drawSeparateLine(Physicus::Object* obj, b2Vec2 vec[4], float drawAdvance, int imageIndex);

/**
 * @brief 編集中の手描き線・リンクボードオブジェクトを描画する
 * 
 */
void drawEditingLine(Physicus::Object*);

/**
 * @brief 編集中の手描き線・リンクボードのデバッグフレームを描画する
 * 
 * @param obj 
 */
void drawEditingLineDebug(Physicus::Object* obj);

#endif