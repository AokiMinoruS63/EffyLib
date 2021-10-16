/**
 * @file PhysicusObject.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief Box2D用のオブジェクト
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICUS_OBJECT_H
#define PHYSICUS_OBJECT_H

// TODO: include vector, Touch.h, box2d.h
#include "../../OpenSource/Box2D/box2d/box2d.h"
#include <vector>
#include "../../Touch/TouchData.h"
#include "PhysicusObjectType.h"
#include "../../Utility/TypeExtensions.h"

namespace Physicus {

	// オブジェクトの実体
	class Object {
		// MARK: - 変数

		// 線に使用する画像
		static const int kLineImgNum = 3;
		// オブジェクトの中に入っているボディ
		std::vector<b2Body *> bodies_;
		// 演算を行うワールド
		b2World* world_;
		// 線の太さ
		float line_width_;
		// 線の軌跡用の画像
		int line_img_[k_line_img_num];
		// 線の色
		int color_;
		// オブジェクトのタイプ
		Type type_;
		// タッチの軌跡
		std::vector<b2Vec2> locus_;

		// MARK: - コンストラクタ・デストラクタ
		public:
		Object(touch_t touch, Type type, b2World* world);
		~Object();

		// MARK: - Getter, Setter

		/**
		 * @brief 線の太さを取得する
		 * 
		 * @return float 
		 */
		float getLineWidth();

		/**
		 * @brief 線の太さをセットする
		 * 
		 * @param width 
		 */
		void setLineWidth(float width);

		/**
		 * @brief 線の画像を取得する
		 * 
		 * @return int* 
		 */
		int* getLineImg();
		/**
		 * @brief 線の画像をセットする
		 * 
		 * @param img 
		 */
		void setLineImg(int img[k_line_img_num]);

		// オブジェクトのタイプを返す
		Type getType();

		// MARK: - オブジェクトの設定

		/**
		 * @brief オブジェクトの生成（ボディの追加など）
		 * 
		 * @param touch 
		 */
		void generation(touch_t touch);

		// TODO: マウスドラッグ中でもボディが生成されるようにする（ただし、ドラッグ中は演算を行わないでリリースされた時に演算を開始させる）
		// TODO: この仕様も相まって前回のボディと前回のボディの終点座標と終点右と終点左の座標が必要
		// b2Vec2 touchStart(タッチした座標の記録に使用。ログが残らない場合があるため), lastAngle(始点の回転に使用), 
		// touchLast(前回の座標), touchCurrent
		// TODO: 円の場合や矩形の場合は実際に表示させるのではなく、ガイド線を表示するのみにした方が良い。
		// TODO: 描画メソッド、頂点作成メソッドなどを作成する
	};
}

#endif