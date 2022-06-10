/**
 * @file PhysicusCircle.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_CIRCLE_H
#define PHYSICUS_CIRCLE_H

namespace Physicus {
	class Object;
};

/**
 * @brief 円オブジェクトを生成する
 * 
 * @param obj 
 * @return true 円オブジェクトをオブジェクトを作成成功なら**true**
 * @return false 
 */
bool createCircleBody(Physicus::Object* obj);

/**
 * @brief 生成した円オブジェクトを描画する
 * 
 * @param obj 
 */
void drawCircle(Physicus::Object* obj);

/**
 * @brief 生成した円オブジェクトのフレームを描画する
 * 
 * @param obj 
 */
void drawCircleDebug(Physicus::Object* obj);

/**
 * @brief 現在生成している円オブジェクトを描画する
 * 
 * @param obj 
 */
void drawEditingCircle(Physicus::Object* obj);

/**
 * @brief 現在生成している円オブジェクトのフレームを描画する
 * 
 */
void drawEditingCircleDebug(Physicus::Object* obj);



#endif