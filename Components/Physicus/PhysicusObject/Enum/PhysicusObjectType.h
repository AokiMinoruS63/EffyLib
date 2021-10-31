/**
 * @file PhysicusObjectType.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief B2Object::Objectの種類
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_TYPE_H
#define PHYSICUS_OBJECT_TYPE_H

namespace Physicus {
	enum Type {
		// 四角形
		kRectangle,
		// 円
		kCircle,
		// 多角形
		kPolygon,
		// 連結している矩形
		kLinkBoard,
	};
}

#endif