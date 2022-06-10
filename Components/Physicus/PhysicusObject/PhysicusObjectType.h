/**
 * @file PhysicusObjectType.h
 * @brief B2Object::Objectの種類
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_OBJECT_TYPE_H
#define PHYSICUS_OBJECT_TYPE_H

namespace Physicus {
	enum class ObjectType {
		// 四角形
		kRectangle,
		// 円
		kCircle,
		// 多角形
		kPolygon,
		// 連結している形状同士で干渉する矩形の集合体
		kLinkBoard,
		// 連結している形状同士では干渉しない矩形の集合体
		kHandWritten,
		// 線
		kLine
	};
}

#endif