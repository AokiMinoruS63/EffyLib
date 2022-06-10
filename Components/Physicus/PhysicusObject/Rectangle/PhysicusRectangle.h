/**
 * @file PhysicusRectangle.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_RECTANGLE_H
#define PHYSICUS_RECTANGLE_H

namespace Physicus {
	class Object;
};

/**
 * @brief 矩形オブジェクトを作成成功なら**true**
 * @return true 
 * @return false 
 */
bool createRectangleBody(Physicus::Object* obj);

/**
 * @brief 矩形オブジェクトを描画する
 * 
 */
void drawRectangle(Physicus::Object* obj);

/**
 * @brief 編集中の矩形オブジェクトを描画する
 * 
 */
void drawEditingRectangle(Physicus::Object* obj);

/**
 * @brief 現在生成している矩形オブジェクトのフレームを描画する
 * 
 */
void drawEditingRectangleDebug(Physicus::Object* obj);

#endif