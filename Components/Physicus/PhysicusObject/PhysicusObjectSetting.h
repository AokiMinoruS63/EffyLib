/**
 * @file PhysicusObjectSetting.h
 * @brief オブジェクトの設定
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef PHYSICUS_OBJECT_SETTING_H
#define PHYSICUS_OBJECT_SETTING_H

#include <vector>
#include <string>
#include "PhysicusObjectType.h"
#include "../../OpenSource/Box2D/Box2D.h"
#include "../../Utility/TypeExtensions/B2Fixture+Extensions.h"
#include "../../Sprite/SpriteType.h"


namespace Physicus {
	// オブジェクトの設定
	struct ObjectSetting {
		// オブジェクトのタイプ
		ObjectType type;
		// ボディの演算タイプ（動くか止まったままかなど）
		b2BodyType bodyType;
		// 線の太さ
		float line_width;
		// 線の軌跡用の画像
		std::vector<int> images;
		// 描画タイプ
		SpriteType sprite_type;
		// 線の色
		int color;
		// 回転しないようにするなら**true**
		bool rotate_fix;
		// エリアアウトしても生存するなら**true**
		bool area_out_alive;
		// 角の尖り具合(1.0でそのまま、０で辺の中心から次の辺の中心までベジェ曲線で描画する)
		float sharpness;
		// ベジェの補完をどれだけ行うかの係数(0に近いほど多く行う。1が最大)
		float roughness;
		// fixtureの設定
		b2FixtureDef fixture;

		/**
		 * @brief 初期化
		 * 
		 * @param world_scale 
		 * @param type 
		 * @param bodyType 
		 * @param images 
		 * @param sprite_type 
		 * @param line_width 
		 * @param color 
		 * @param rotate_fix 
		 * @param area_out_alive 
		 * @param sharp 
		 * @param rough 
		 * @param fixture 
		 * @return ObjectSetting 
		 */
		static ObjectSetting init(
			float world_scale, 
			ObjectType type, 
			b2BodyType bodyType, 
			std::vector<int> images,
			SpriteType sprite_type = SpriteType::kStroke,
			float line_width = Constant::Object::kDefaultLineWidth, 
			int color = Color::kWhite, bool rotate_fix = false, bool area_out_alive = false,
			float sharp = Constant::Object::kDefaultSharpness,
			float rough = Constant::Object::kBezieRoughness,
			b2FixtureDef fixture = B2Fixture::defaultSetting()
			) {
			line_width *= world_scale;
			return {type, bodyType, line_width, images, sprite_type, color, rotate_fix, area_out_alive, sharp, rough, fixture};
		}

		/**
		 * @brief  初期化(画像を配列で渡す時の処理)
		 * 
		 * @param world_scale 
		 * @param type 
		 * @param bodyType 
		 * @param images 
		 * @param sprite_type 
		 * @param images_size 
		 * @param line_width 
		 * @param color 
		 * @param rotate_fix 
		 * @param area_out_alive 
		 * @param sharp 
		 * @param rough 
		 * @param fixture 
		 * @return ObjectSetting 
		 */
		static ObjectSetting init(
			float world_scale, 
			ObjectType type, 
			b2BodyType bodyType, 
			int* images,
			int images_size, 
			SpriteType sprite_type = SpriteType::kStroke,
			float line_width = Constant::Object::kDefaultLineWidth, 
			int color = Color::kWhite, 
			bool rotate_fix = false, 
			bool area_out_alive = false, 
			float sharp = Float::kMax, 
			float rough = Constant::Object::kBezieRoughness, 
			b2FixtureDef fixture = B2Fixture::defaultSetting()
			) {
			line_width *= world_scale;
			std::vector<int> image_vector;
			for(int i = 0; i < images_size; i++) {
				image_vector.push_back(images[i]);
			}
			return {type, bodyType, line_width, image_vector, sprite_type, color, rotate_fix, area_out_alive, sharp, rough, fixture};
		}
	};
}

#endif