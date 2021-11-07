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
 * @brief 手書き線オブジェクトを作成する
 * 
 */
void createHandwrittenBody(Physicus::Object*);

/**
 * @brief 手書き線オブジェクトを描画する
 * 
 * @param obj 
 * @param editing 編集中のオブジェクトなら**true**
 */
void drawHandwritten(Physicus::Object* obj, bool editing = false);

/**
 * @brief 編集中の手書き線オブジェクトを描画する
 * 
 */
void drawEditingHandwritten(Physicus::Object*);


#endif