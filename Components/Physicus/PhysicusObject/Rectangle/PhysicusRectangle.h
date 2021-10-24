/**
 * @file  PhysicusRectangle.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
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