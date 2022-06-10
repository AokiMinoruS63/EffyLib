/**
 * @file PhysicusLinkBoard.h
 * @brief リンクボード関係のメソッドを記述
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
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