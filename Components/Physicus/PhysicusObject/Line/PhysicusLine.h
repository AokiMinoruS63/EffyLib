/**
 * @file PhysicusLine.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_LINE_H
#define PHYSICUS_LINE_H

namespace Physicus {
	class Object;
};

/**
 * @brief 直線オブジェクトを生成する
 * 
 * @param obj 
 */
void createStaticLineBody(Physicus::Object* obj);

/**
 * @brief 生成した直線オブジェクトを描画する
 * 
 * @param obj 
 */
void drawStaticLine(Physicus::Object* obj);

/**
 * @brief 現在生成している直線オブジェクトを描画する
 * 
 * @param obj 
 */
void drawEditingStaticLine(Physicus::Object* obj);

#endif