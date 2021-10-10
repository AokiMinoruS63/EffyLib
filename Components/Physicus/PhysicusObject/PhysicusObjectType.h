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
		// 多角形
		Polygon,
		// 塗りつぶし多角形
		FillPolygon,
		// 中身がスカスカな多角形
		LinksBoard,
		// 円
		Circle,
		// 塗りつぶし多角形
		FillCircle,
		// 四角形
		Rectangle,
		// 塗りつぶし四角形
		FillRectangle
	};
}

#endif