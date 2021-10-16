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
#include "Enum/PhysicusObjectType.h"
#include "../../Utility/TypeExtensions.h"
#include "../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include "Constant/PhysicusConstant.h"

namespace Physicus {

	// オブジェクトの実体
	class Object {
		// MARK: - 定数
		public:
		// 線のデフォルトの幅
		constexpr static float kDefaultLineWidth = 10.0;
		// 線に使用する画像
		static const int kLineImgNum = 3;

		// MARK: - 変数
		private:
		// オブジェクトの中に入っているボディ
		std::vector<b2Body *> bodies_;
		// 演算を行うワールド
		b2World* world_;
		// 線の太さ
		float line_width_;
		// 線の軌跡用の画像
		int line_img_[kLineImgNum];
		// 線の色
		int color_;
		// 回転しないようにするなら**true**
		bool rotate_fix_;
		// オブジェクトのタイプ
		Type type_;
		// スケール
		float world_scale_;
		// タッチの軌跡
		std::vector<b2Vec2> locus_;
		// エリアアウトしても生存するなら**true**
		bool area_out_alive_;

		// MARK: - コンストラクタ・デストラクタ
		public:
		/**
		 * @brief Construct a new Object object
		 * 
		 * @param touch タッチ情報
		 * @param type オブジェクトの種類
		 * @param world 演算を行うワールド
		 * @param scale ワールドの拡大率
		 * @param line_width 線がある場合の線の幅
		 */
		Object(touch_t touch, Type type, b2World* world, float scale, float line_width);
		~Object();

		// MARK: - Getter, Setter

		/**
		 * @brief 物理演算のBody配列を取得する
		 * 
		 * @return std::vector<b2Body*> 
		 */
		std::vector<b2Body*>& getBodies();

		/**
		 * @brief 演算するワールドを取得する
		 * 
		 * @return b2World* 
		 */
		b2World* getWorld();

		/**
		 * @brief 軌跡を取得する
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> getLocus();

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
		void setLineImg(int img[kLineImgNum]);

		/**
		 * @brief オブジェクトの回転がロックされているかどうかを取得する
		 * 
		 * @return true 
		 * @return false 
		 */
		bool getRotateFix();

		/**
		 * @brief オブジェクトの回転のロックを設定する
		 * 
		 * @param fix 
		 */
		void setRotateFix(bool fix);

		/**
		 * @brief 演算がされている状態かチェックする
		 * 
		 * @param index 
		 * @return true 
		 * @return false 
		 */
		bool getAwake(int index = 0);

		/**
		 * @brief オブジェクトの演算をセットする
		 * 
		 * @param awake 演算を行うなら**true**
		 * @param index 指定すれば該当インデックスのみ演算状態の適用を行う
		 */
		void setAwake(bool awake = true, int index = Array::kUnspecified);

		// オブジェクトのタイプを返す
		Type getType();

		// MARK: - オブジェクトの設定

		/**
		 * @brief オブジェクトの生成（ボディの追加など）
		 * 
		 * @param touch 
		 * @param tie_loop_range 数珠繋ぎにする距離
		 * @return true オブジェクトが生成されたら**true**
		 * @return false 
		 */
		bool generation(touch_t touch, float tie_loop_range);

		/**
		 * @brief オブジェクトが生存可能エリアを出たらオブジェクトを消滅させる
		 * 
		 * @param alive_area 生存可能範囲
		 * @return true 
		 * @return false 
		 */
		bool judgeAreaOut(Frame alive_area);

		/**
		 * @brief 演算を行うボディを全て削除する
		 * 
		 */
		void bodiesDestroy();

		/**
		 * @brief ボディを追加する
		 * 
		 * @param body 
		 */
		void append(b2Body *body);

		/**
		 * @brief 直近のボディをジョイントで繋げる
		 * 
		 * @param type ジョイントのタイプ
		 */
		void linkCurrent(B2Joint::Type type);

		// MARK: - オブジェクトの描画

		/**
		 * @brief 現在生成しているオブジェクトのボーンを描画する
		 * 
		 */
		void drawOverlay();

		/**
		 * @brief オブジェクトの描画
		 * 
		 */
		void draw();

		/**
		 * @brief オブジェクトのフレームを描画
		 * 
		 */
		void drawDebugFrame();

		/**
		 * @brief 現在生成しているオブジェクトのフレームを描画する
		 * 
		 */
		void drawDebugFrameOverlay();

		// TODO: マウスドラッグ中でもボディが生成されるようにする（ただし、ドラッグ中は演算を行わないでリリースされた時に演算を開始させる）
		// TODO: この仕様も相まって前回のボディと前回のボディの終点座標と終点右と終点左の座標が必要
		// b2Vec2 touchStart(タッチした座標の記録に使用。ログが残らない場合があるため), lastAngle(始点の回転に使用), 
		// touchLast(前回の座標), touchCurrent
		// TODO: 円の場合や矩形の場合は実際に表示させるのではなく、ガイド線を表示するのみにした方が良い。
		// TODO: 描画メソッド、頂点作成メソッドなどを作成する
	};
}

#endif