/**
 * @file PhysicusLinkBoard.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief リンクボード関係のメソッドを記述
 * @version 0.1
 * @date 2021-10-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_LINK_BOARD_H
#define PHYSICUS_LINK_BOARD_H

namespace Physicus {
	class Object;
};

/**
 * @brief リンクボードオブジェクトを作成する
 * 
 * @param obj 
 * @param index 
 */
void createLinkBoardBody(Physicus::Object* obj, int index);

/**
 * @brief リンクボードオブジェクトを描画する
 * 
 */
void drawLinkBoard(Physicus::Object*);

#endif