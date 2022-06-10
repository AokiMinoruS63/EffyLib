/**
 * @file PhysicusHandWritten.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_HANDWRITTEN_H
#define PHYSICUS_HANDWRITTEN_H

namespace Physicus {
	class Object;
};

/**
 * @brief 手描き線オブジェクトを作成する
 * 
 * @param obj オブジェクトの生成
 * @param index 現在のインデックス
 */
void createHandwrittenBody(Physicus::Object* obj, int index);

/**
 * @brief 手描き線オブジェクトを描画する
 * 
 * @param obj 
 */
void drawHandwritten(Physicus::Object* obj);

#endif