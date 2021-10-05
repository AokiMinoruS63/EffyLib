/**
 * @file B2Body+Extensions.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief b2Bodyのエクステンション
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef B2_BODY_EXTENSION_H
#define B2_BODY_EXTENSION_H

#include "../../Box2D/box2d/b2_body.h"
#include <vector>

namespace B2Body {
	// TODO: 塗りつぶし図形、円、四角
	enum Type {
		FillPolygon,
		LinksBoard,
		Circle,
		FillCircle,
		Rectangle,
		FillRectangle
	};
	// TODO: 
	struct object {
		Type type;
		std::vector<b2Body *> bodies;
	} 

}

#endif