/**
 * @file PhysicusHandWritten.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_HANDWRITTEN_H
#define PHYSICUS_HANDWRITTEN_H

namespace Physicus {
	class Object;
};

/**
 * @brief 手描き線の軌跡を作成する
 * 
 * @param obj 
 */
void createHandwrittenLocus(Physicus::Object* obj);

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

/**
 * @brief 編集中の手描き線オブジェクトを描画する
 * 
 */
void drawEditingHandwritten(Physicus::Object*);

/**
 * @brief 編集中の手描き線オブジェクトのデバッグフレームを描画する
 * 
 * @param obj 
 */
void drawEditingHandwrittenDebug(Physicus::Object* obj);


#endif