/**
 * @file PhysicusObjectSetting.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief オブジェクトの設定
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_SETTING_H
#define PHYSICUS_OBJECT_SETTING_H

#include <vector>
#include "../Enum/PhysicusObjectType.h"
#include "../../../OpenSource/Box2D/box2d/box2d.h"
#include "../../../Utility/TypeExtensions/B2Fixture+Extensions.h"


namespace Physicus {
	// オブジェクトの設定
	struct ObjectSetting {
		// オブジェクトのタイプ
		Type type;
		// ボディの演算タイプ（動くか止まったままかなど）
		b2BodyType bodyType;
		// 線の太さ
		float line_width;
		// 線の軌跡用の画像
		std::vector<int> line_images;
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
		 * @param line_images 
		 * @param line_width 
		 * @param color 
		 * @param rotate_fix 
		 * @param area_out_alive 
		 * @param sharp 
		 * @param rough 
		 * @param fixture 
		 * @return ObjectSetting 
		 */
		static ObjectSetting init(float world_scale, Type type, b2BodyType bodyType, std::vector<int> line_images, float line_width = Constant::Object::kDefaultLineWidth, int color = Color::kWhite, bool rotate_fix = false, bool area_out_alive = false, float sharp = Constant::Object::kDefaultSharpness, float rough = Constant::Object::kBezieRoughness, b2FixtureDef fixture = B2Fixture::defaultSetting()) {
			line_width *= world_scale;
			return {type, bodyType, line_width, line_images, color, rotate_fix, area_out_alive, sharp, rough, fixture};
		}

		/**
		 * @brief  初期化(画像を配列で渡す時の処理)
		 * 
		 * @param world_scale 
		 * @param type 
		 * @param bodyType 
		 * @param line_images 
		 * @param line_images_size 
		 * @param line_width 
		 * @param color 
		 * @param rotate_fix 
		 * @param area_out_alive 
		 * @param sharp 
		 * @param rough 
		 * @param fixture 
		 * @return ObjectSetting 
		 */
		static ObjectSetting init(float world_scale, Type type, b2BodyType bodyType, int* line_images, int line_images_size, float line_width = Constant::Object::kDefaultLineWidth, int color = Color::kWhite, bool rotate_fix = false, bool area_out_alive = false, float sharp = Float::kMax, float rough = Constant::Object::kBezieRoughness, b2FixtureDef fixture = B2Fixture::defaultSetting()) {
			line_width *= world_scale;
			std::vector<int> images;
			for(int i = 0; i < line_images_size; i++) {
				images.push_back(line_images[i]);
			}
			return {type, bodyType, line_width, images, color, rotate_fix, area_out_alive, sharp, rough, fixture};
		}
	};
}

#endif