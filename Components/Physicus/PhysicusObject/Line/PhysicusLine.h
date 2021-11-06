/**
 * @file PhysicusLine.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-04
 * 
 * @copyright Copyright (c) 2021
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
void createLineBody(Physicus::Object* obj);

/**
 * @brief 生成した直線オブジェクトを描画する
 * 
 * @param obj 
 */
void drawLine(Physicus::Object* obj);

/**
 * @brief 現在生成している直線オブジェクトを描画する
 * 
 * @param obj 
 */
void drawEditingLine(Physicus::Object* obj);

#endif