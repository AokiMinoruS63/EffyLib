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
#include "../../OpenSource/Box2D/Box2D.h"
#include <vector>
#include "../../Touch/TouchData.h"
#include "Enum/PhysicusObjectType.h"
#include "../../Utility/TypeExtensions.h"
#include "../PhysicusWorld/Frame/PhysicusWorldFrame.h"
#include "Constant/PhysicusConstant.h"
#include "Setting/PhysicusObjectSetting.h"

namespace Physicus {

	// オブジェクトの実体
	class Object {
		// MARK: - 定数
		public:

		// MARK: - 変数
		private:
		// オブジェクトの中に入っているボディ
		std::vector<b2Body *> bodies_;
		// 演算を行うワールド
		b2World* world_;
		// タッチの軌跡
		std::vector<b2Vec2> locus_;
		// 軌跡の外側の線(回転は考慮しない座標)
		std::vector<b2Vec2> locus_line_outside_;
		// 軌跡の内側の線(回転は考慮しない座標)
		std::vector<b2Vec2> locus_line_inside_;
		// 軌跡の線のログ
		std::vector<Physicus::Frame> locus_frame_log_;
		// 描画の進行率
		float draw_advance_;
		// 拡大率
		float world_scale_;
		// オブジェクトの設定
		ObjectSetting setting_;
		// ボディの頂点の順番変更フラグ（Box２D側で頂点の順番が調整されてしまうため、ここに保存）
		std::vector<B2Body::VerticesChange> bodies_vertices_change_;

		// MARK: - コンストラクタ・デストラクタ
		public:
		/**
		 * @brief Construct a new Object object
		 * 
		 * @param touch タッチ情報
		 * @param type オブジェクトの種類
		 * @param world 演算を行うワールド
		 * @param scale ワールドの拡大率
		 * @param setting オブジェクトの設定
		 */
		Object(touch_t touch, Type type, b2World* world, float scale, ObjectSetting setting);
		~Object();

		// MARK: - Getter, Setter

		/**
		 * @brief 演算ワールドのスケールを取得する
		 * 
		 * @return float 
		 */
		float getWorldScale();

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
		 * @brief 座標を取得する
		 * 
		 * @param isDraw 描画時の座標なら**true**
		 * @return b2Vec2 
		 */
		b2Vec2 getPosition(bool isDraw);

		/**
		 * @brief 軌跡を取得する
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> getLocus();

		/**
		 * @brief ボディvectorの角度の変更フラグを返す
		 * 
		 * @return std::vector<bool> 
		 */
		std::vector<B2Body::VerticesChange> getBodiesVerticesChange();

		/**
		 * @brief ボディvectorのBox2D頂点挿入時の頂点の順番変更フラグを追加する
		 * 
		 * @param bodies_vertices_change
		 */
		void appendBodiesVerticesChange(B2Body::VerticesChange bodies_vertices_change);

		/**
		 * @brief ボディvectorのBox2D頂点挿入時の頂点の順番変更フラグを取得する
		 * 
		 * @return ObjectSetting 
		 */
		ObjectSetting getSetting();

		/**
		 * @brief 線の太さを取得する
		 * 
		 * @return float 
		 */
		float getLineWidth();

		/**
		 * @brief 線の半分の太さを取得する
		 * 
		 * @return float 
		 */
		float getLineHalfWidth();

		/**
		 * @brief 描画時の線の太さを取得する
		 * 
		 * @return float 
		 */
		float getDrawLineWidth();

		/**
		 * @brief 描画時の線の半分の太さを取得する
		 * 
		 * @return float 
		 */
		float getDrawLineHalfWidth();

		/**
		 * @brief 線の太さをセットする
		 * 
		 * @param width 
		 */
		void setLineWidth(float width);

		/**
		 * @brief 線の色を取得する
		 * 
		 * @return int 
		 */
		int getColor();

		/**
		 * @brief 線の色を設定する
		 * 
		 * @param color 
		 */
		void setColor(int color);

		/**
		 * @brief 線の画像を取得する
		 * 
		 * @return std::vector<int> 
		 */
		std::vector<int> getLineImages();

		/**
		 * @brief std::vectorから線の画像をセットする
		 * 
		 * @param images 画像ハンドル
		 */
		void setLineImages(std::vector<int> images);

		/**
		 * @brief int配列から線の画像をセットする
		 * 
		 * @param images 画像ハンドル
		 * @param size 配列の要素数
		 */
		void setLineImages(int* images, int size);

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

		/**
		 * @brief オブジェクトの角の尖り具合を取得する
		 * 
		 * @return float 
		 */
		float getSharpness();

		/**
		 * @brief オブジェクトの角の尖り具合をセットする
		 * 
		 * @param sharp 
		 */
		void setSharpness(float sharp);

		/**
		 * @brief ベジェ曲線の補完係数を取得する
		 * 
		 * @return float 
		 */
		float getRoughness();

		/**
		 * @brief ベジェ曲線の補完係数をセットする
		 * 
		 * @param roughness 
		 */
		void setRoughness(float roughness);

		/**
		 * @brief オブジェクトのタイプを返す
		 * 
		 * @return Type 
		 */
		Type getType();

		/**
		 * @brief 描画の進行率を設定する
		 * 
		 * @param advance 0.0〜1.0。1.0で全て表示
		 */
		void setDrawAdvance(float advance);

		/**
		 * @brief 描画の進行率を取得する
		 * 
		 * @return float 0.0〜1.0。1.0で全て表示
		 */
		float getDrawAdvance();

		/**
		 * @brief オブジェクトのタイプが矩形なら**true**
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isRectangle();

		/**
		 * @brief オブジェクトのタイプが円なら**true**
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isCircle();

		/**
		 * @brief オブジェクトが多角形なら**true**
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isPolygon();

		/**
		 * @brief オブジェクトが連結している矩形なら**true**
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isLinkBoard();

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
		 * @brief 軌跡を相対座標に変換する
		 * 
		 */
		void locusLineToRelative();

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

		// MARK: - 軌跡フレームログ操作

		/**
		 * @brief 軌跡のフレームを追加する
		 * 
		 * @param frame 
		 */
		void appendLocusFrame(Physicus::Frame frame);

		/**
		 * @brief 軌跡のフレームの後ろを削除する
		 * 
		 */
		void removeLocusFrame();
		/**
		 * @brief 軌跡のフレームを取得する
		 * 
		 * @return std::vector<Physicus::Frame> 
		 */
		std::vector<Physicus::Frame> getLocusFrames();

		/**
		 * @brief 軌跡の線を追加する
		 * 
		 * @param outside 外側の線の頂点座標
		 */
		void appendDrawLocusLine(b2Vec2 outside);

		/**
		 * @brief 軌跡の線を追加する
		 * 
		 * @param outside 外側の線の頂点座標
		 * @param inside 内側の線の頂点座標
		 */
		void appendDrawLocusLine(b2Vec2 outside, b2Vec2 inside);

		/**
		 * @brief 軌跡の線を削除する
		 * 
		 */
		void removeLocusLines();

		/**
		 * @brief 軌跡の内側の線を取得する
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> getLocusInsideLines(); 

		/**
		 * @brief 軌跡の外側の線を取得する
		 * 
		 * @return std::vector<b2Vec2> 
		 */
		std::vector<b2Vec2> getLocusOutsideLines(); 

		// MARK: - オブジェクトの描画

		/**
		 * @brief 現在生成しているオブジェクトのボーンを描画する
		 * 
		 */
		void drawEditing();

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
		void drawEditingDebugFrame();

		// TODO: マウスドラッグ中でもボディが生成されるようにする（ただし、ドラッグ中は演算を行わないでリリースされた時に演算を開始させる）
		// TODO: この仕様も相まって前回のボディと前回のボディの終点座標と終点右と終点左の座標が必要
		// b2Vec2 touchStart(タッチした座標の記録に使用。ログが残らない場合があるため), lastAngle(始点の回転に使用), 
		// touchLast(前回の座標), touchCurrent
		// TODO: 円の場合や矩形の場合は実際に表示させるのではなく、ガイド線を表示するのみにした方が良い。
		// TODO: 描画メソッド、頂点作成メソッドなどを作成する
	};
}

#endif