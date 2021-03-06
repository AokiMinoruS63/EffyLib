/**
 * @file PhysicusObject.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "PhysicusObject.h"
#include "../../Sprite/Sprite.h"
#include "Common/PhysicusObjectCommon.h"
#include "LinkBoard/PhysicusLinkBoard.h"
#include "HandWritten/PhysicusHandWritten.h"
#include "Rectangle/PhysicusRectangle.h"
#include "Circle/PhysicusCircle.h"
#include "Line/PhysicusLine.h"

using namespace Physicus;

// コンストラクタ
Object::Object(touch_t touch, ObjectType type, b2World* world, float scale, ObjectSetting setting) {
	lifeObjectInit();
	world_ = world;
	b2Vec2 vec = B2Vec2::fromTouch(touch, scale);
	locus_.push_back(vec);
	draw_advance_ = Float::kMax;
	world_scale_ = scale;
	setting_ = setting;
	sprite_ = new Sprite();
}

// デストラクタ
Object::~Object() {
	bodiesDestroy();
	world_ = NULL;
	delete sprite_;
}

// MARK: - Getter, Setter

// 演算ワールドのスケールを取得する
float Object::getWorldScale() {
	return world_scale_;
}

// 物理演算のBody群を取得する
std::vector<b2Body*>& Object::getBodies() {
	return bodies_;
}

// 演算を行うワールドを取得する
b2World* Object::getWorld() {
	return world_;
}

// 座標を取得する
b2Vec2 Object::getPosition(bool isDraw) {
	if(IsEmpty(bodies_)) {
		return B2Vec2::kZero;
	}
	const auto body = bodies_.front();
	b2Vec2 pos = body->GetPosition();
	if(isDraw) {
		pos = B2Vec2::division(pos, world_scale_);
	}
	return pos;
}

//軌跡を取得する
std::vector<b2Vec2> Object::getLocus() {
	return locus_;
}

// ボディvectorのBox2D頂点挿入時の頂点の順番変更フラグを返す
std::vector<B2Body::VerticesChange> Object::getBodiesVerticesChange() {
	return bodies_vertices_change_;
}

// ボディvectorのBox2D頂点挿入時の頂点の順番変更フラグを追加する
void Object::appendBodiesVerticesChange(B2Body::VerticesChange bodies_vertices_change) {
	bodies_vertices_change_.push_back(bodies_vertices_change);
}

// オブジェクトの設定を取得する
ObjectSetting Object::getSetting() {
	return setting_;
}

// 線の太さを取得する
float Object::getLineWidth() {
	return setting_.line_width;
}

// 線の半分の太さを取得する
float Object::getLineHalfWidth() {
	return setting_.line_width * Float::kHalf;
}

// 描画時の線の太さを取得する
float Object::getDrawLineWidth() {
	return getLineWidth() / world_scale_;
}

// 描画時の線の半分の太さを取得する
float Object::getDrawLineHalfWidth() {
	return getLineHalfWidth() / world_scale_;
}

// 線の太さをセットする
void Object::setLineWidth(float width) {
	setting_.line_width = width;
}

// 線の色を取得する
int Object::getColor() {
	return setting_.color;
}

// 線の色を設定する
void Object::setColor(int color) {
	setting_.color = color;
}

// 画像を取得する
std::vector<int> Object::getImages() {
	return setting_.images;
}

// std::vectorから画像をセットする
void Object::setImages(std::vector<int> images) {
	setting_.images = images;
}

// int配列から線の画像をセットする
void Object::setImages(int* images, int size) {
	setting_.images.clear();
	for(int i = 0; i < size; i++) {
		setting_.images.push_back(images[i]);
	}
}

// スプライトのタイプを取得する
SpriteType Object::getSpriteType() {
	return setting_.sprite_type;
}

// スプライトのタイプを設定する
void Object::setSpriteType(SpriteType sprite_type) {
	setting_.sprite_type = sprite_type;
}

// オブジェクトの回転がロックされているかどうかを取得する
bool Object::getRotateFix() {
	return setting_.rotate_fix;
}

// オブジェクトの回転のロックを設定する
void Object::setRotateFix(bool fix) {
	setting_.rotate_fix = fix;
}

// 演算がされている状態かチェックする
bool Object::getAwake(int index) {
	if(IsEmpty(bodies_)) {
		return false;
	}
	return bodies_.at(index)->IsAwake();
}

// オブジェクトの演算をセットする
void Object::setAwake(bool awake, int index) {
	if(index == Array::kUnspecified) {
		for(auto& itr: bodies_) {
			itr->SetAwake(awake);
		}
	} else {
		bodies_.at(index)->SetAwake(awake);
	}
}

// オブジェクトの角の尖り具合を取得する
float Object::getSharpness() {
	return setting_.sharpness;
}

// オブジェクトの角の尖り具合をセットする
void Object::setSharpness(float sharp) {
	setting_.sharpness = sharp;
}

// ベジェ曲線の補完係数を取得する
float Object::getRoughness() {
	return setting_.roughness;
}

// オブジェクトの角の尖り具合をセットする
void Object::setRoughness(float rough) {
	setting_.roughness = rough;
}

// オブジェクトの種類を取得する
ObjectType Object::getType() {
	return setting_.type;
}

// 描画の進行率を設定する
void Object::setDrawAdvance(float advance) {
	draw_advance_ = advance;
}

// 描画の進行率を取得する
float Object::getDrawAdvance() {
	return draw_advance_;
}

// オブジェクトのタイプが矩形なら**true**
bool Object::isRectangle() {
	return setting_.type == ObjectType::kRectangle;
}

// オブジェクトのタイプが円なら**true**
bool Object::isCircle() {
	return setting_.type == ObjectType::kCircle;
}

// オブジェクトが多角形なら**true**
bool Object::isPolygon() {
	return setting_.type == ObjectType::kPolygon;
}

// オブジェクトが連結している矩形なら**true**
bool Object::isLinkBoard() {
	return setting_.type == ObjectType::kLinkBoard;
}

// オブジェクトの生成（ボディの追加など）
bool Object::generation(touch_t touch, float tie_loop_range) {
	const b2Vec2 start = locus_.front();
	const b2Vec2 last = locus_.back();
	const b2Vec2 current = B2Vec2::fromTouch(touch, world_scale_);
	
	switch(setting_.type) {
		case ObjectType::kRectangle: 
		case ObjectType::kCircle:
		setting_.roughness = Constant::Object::kBezieRoughness;
		if(B2Vec2::checkCreatePos(start, current)) {
			if(locus_.size() == 1) {
				locus_.push_back(current);
			} else {
				locus_.back() = current;
			}
		}
		break;
		case ObjectType::kPolygon:
		if(B2Vec2::checkCreatePos(last, current)) {
			locus_.push_back(current);
			// TODO: 多角形の作成
		}
		break;
		case ObjectType::kLinkBoard:
		if(B2Vec2::checkCreatePos(last, current)) {
			locus_.push_back(current);
			createLineLocus(this);
		}
		break;
		case ObjectType::kHandWritten:
		if(B2Vec2::distance(last, current) > B2Vec2::kHandwrittenVertexDistance) {
			locus_.push_back(current);
			createLineLocus(this);
		}
		break;
		case ObjectType::kLine:
		if(B2Vec2::checkCreatePos(last, current)) {
			locus_.push_back(current);
			createStaticLineBody(this);
		}
		 break;
		default:break;
	}

	if(touch.status != TouchStatus::kJustRelease) {
		return false;
	}
	// オブジェクトを作成する
	switch(setting_.type) {
		case ObjectType::kRectangle: 
		if(!createRectangleBody(this)) {
			return false;
		}
		break;
		case ObjectType::kCircle:
		// startが円の中心、endで半径を決定する
		if(!createCircleBody(this)) {
			return false;
		}
		break;
		case ObjectType::kPolygon:
		// 先にセンターを作成する。その後に８角形以下の図形を繋げて作成する
		break;
		case ObjectType::kLinkBoard:
		// 距離が近ければ数珠繋ぎにする
		for(int i = 1; i < locus_.size(); i++) {
			createLinkBoardBody(this, i);
		}
		if(B2Vec2::isTieLoop(locus_, tie_loop_range)) {
			B2Joint::weldJointTieLoop(world_, bodies_);
		}
		break;
		case ObjectType::kLine:
		// 線ではfixtureしか使用しないため、連結はしない
		break;
		case ObjectType::kHandWritten:
		// 作成する
		for(int i = 1; i < locus_.size(); i++) {
			createHandwrittenBody(this, i);
		}
		// 相対座標に変換する
		locusLineToRelative();
		break;
		default:break;
	}
	return true;
}

// 軌跡を相対座標に変換する
void Object::locusLineToRelative() {
	if(IsEmpty(bodies_)) {
		return;
	}
	const auto position = bodies_.front()->GetPosition();
	for(auto &itr: locus_line_outside_) {
		itr = B2Vec2::sub(itr, position);
	}
	for(auto &itr: locus_line_inside_) {
		itr = B2Vec2::sub(itr, position);
	}
	
}

// オブジェクトが生存可能エリアを出たらオブジェクトを消滅させる
bool Object::judgeAreaOut(Frame alive_area) {
	// ボディが存在しないか、エリア外でも生存させるなら処理しない
	if(IsEmpty(bodies_) || setting_.area_out_alive) {
		return false;
	}
	// 全てのボディの頂点を判定して全てがエリア外に出ていたら消去
	for(auto& itr: bodies_) {
		if(!B2Body::areaOut(itr, alive_area)) {
			return false;
		}
	}
	bodiesDestroy();
	return true;
}

// 演算を行うボディを全て削除する
void Object::bodiesDestroy() {
	auto itr = bodies_.begin();
	while(itr != bodies_.end()) {
		world_->DestroyBody((*itr));
		itr = bodies_.erase(itr);
	}
}

// ボディを追加する
void Object::append(b2Body *body) {
	bodies_.push_back(body);
}

// 直近のボディをジョイントで繋げる
void Object::linkCurrent(B2Joint::Type type) {
	// TODO: ジョイントタイプ別に処理を行う
	B2Joint::weldJointCurrent(world_, bodies_);
}

// 軌跡のフレームを追加する
void Object::appendLocusFrame(Physicus::Frame frame) {
	locus_frame_log_.push_back(frame);
}

// 軌跡のフレームの末尾を削除する
void Object::removeLocusFrame() {
	if(!IsEmpty(locus_frame_log_)) {
		locus_frame_log_.pop_back();
	}
}

// 軌跡のフレームを取得する
std::vector<Physicus::Frame> Object::getLocusFrames() {
	return locus_frame_log_;
}

// 軌跡の線を追加する
void Object::appendDrawLocusLine(b2Vec2 outside) {
	const b2Vec2 unit = B2Vec2::unitVector(outside);
	const b2Vec2 linePos = B2Vec2::multiplication(unit, getDrawLineWidth());
	const b2Vec2 inside = B2Vec2::sub(outside, linePos);
	appendDrawLocusLine(outside, inside);
}

// 軌跡の線を追加する
void Object::appendDrawLocusLine(b2Vec2 outside, b2Vec2 inside) {
	locus_line_outside_.push_back(outside);
	locus_line_inside_.push_back(inside);
}

// 軌跡の線を削除する
void Object::removeLocusLines() {
	locus_line_inside_.clear();
	locus_line_outside_.clear();
}

// 軌跡の内側の線を取得する
std::vector<b2Vec2> Object::getLocusInsideLines() {
	return locus_line_inside_;
}

// 軌跡の外側の線を取得する
std::vector<b2Vec2> Object::getLocusOutsideLines() {
	return locus_line_outside_;
}

// オブジェクトの描画
void Object::draw() {
	switch(setting_.type) {
		case ObjectType::kRectangle: 
		// startが始点、endが終点
		drawRectangle(this);
		break;
		case ObjectType::kCircle:
		// startが円の中心、endで半径を決定する
		drawCircle(this);
		break;
		case ObjectType::kPolygon:
		// 先にセンターを作成する。その後に８角形以下の図形を繋げて作成する
		break;
		case ObjectType::kLinkBoard:
		drawLinkBoard(this);
		break;
		case ObjectType::kHandWritten:
		drawHandwritten(this);
		break;
		case ObjectType::kLine:
		drawStaticLine(this);
		break;
		default:
		break;
	}
}

// 現在生成しているオブジェクトを描画する
void Object::drawEditing() {
	switch(setting_.type) {
		case ObjectType::kRectangle: 
		// startが始点、endが終点
		drawEditingRectangle(this);
		break;
		case ObjectType::kCircle:
		// startが円の中心、endで半径を決定する
		drawEditingCircle(this);
		break;
		case ObjectType::kPolygon:
		// 先にセンターを作成する。その後に８角形以下の図形を繋げて作成する
		break;
		case ObjectType::kHandWritten:
		case ObjectType::kLinkBoard:
		drawEditingLine(this);
		break;
		case ObjectType::kLine:
		drawEditingStaticLine(this);
		break;
		default:break;
	}
}

// オブジェクトのフレームの描画
void Object::drawDebugFrame() {
	switch (setting_.type) {
		case ObjectType::kRectangle: 
		case ObjectType::kLinkBoard:
		case ObjectType::kHandWritten:
		case ObjectType::kLine:
		case ObjectType::kPolygon:
		// 先にセンターを作成する。その後に８角形以下の図形を繋げて作成する
		// startが始点、endが終点
		ForEach(bodies_, [this](b2Body *item) { B2Body::drawFrame(item, world_scale_, setting_.color); });
		break;
		case ObjectType::kCircle:
		// startが円の中心、endで半径を決定する
		drawCircleDebug(this);
		break;
		default:break;
	}
}

// 現在生成しているオブジェクトのフレームを描画する
void Object::drawEditingDebugFrame() {
	switch(setting_.type) {
		case ObjectType::kRectangle: 
		drawEditingRectangleDebug(this);
		break;
		case ObjectType::kCircle:
		// startが円の中心、endで半径を決定する
		drawEditingCircleDebug(this);
		break;
		case ObjectType::kPolygon:
		// 先にセンターを作成する。その後に８角形以下の図形を繋げて作成する
		break;
		case ObjectType::kLine:
		ForEach(bodies_, [this](b2Body *item) { B2Body::drawFrame(item, world_scale_, setting_.color); });
		break;
		case ObjectType::kHandWritten:
		case ObjectType::kLinkBoard:
		drawEditingLineDebug(this);
		break;
		default:

		break;
	}
}



/*
class box2DTest {
	private:

	// 軌跡
	std::vector<b2Vec2> locus;

	public:
	// 縮小率
	const float drawRate = 10.0;
	box2DTest() {
		// 重力は下方向に10働くとする
		b2Vec2 gravity(0.0f, 10.0f);
		world = new b2World(gravity);

		// 地面の参照値
		b2BodyDef groundBodyDef;

		groundBodyDef.position.Set(20.0f, 40.0f);
		// 地面の実体を定義しワールドに追加する
		auto groundBody = world->CreateBody(&groundBodyDef);
		grounds.push_back(groundBody);
		// 地面の形を定義する
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 5.0f);
		// 作成した地面の形を適用する
		groundBody->CreateFixture(&groundBox, 0.0f);

		create(200.0f, 4.0f);
	}
	~box2DTest(){}

	b2Body* create(float x, float y) {
		x /= drawRate;
		y /= drawRate;
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef;

		// 動体オブジェクトを定義する
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x, y);
		auto body = world->CreateBody(&bodyDef);
		bodies.push_back(body);
		// 動体オブジェクトの形を定義する
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(2.0f, 2.0f);

		// 動体オブジェクトの密度・摩擦の関連付け
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// 密度を設定
		fixtureDef.density = 1.0f;
		// 摩擦を設定
		fixtureDef.friction = 1.0f;
		// 反発を設定
		fixtureDef.restitution = 0.0;
		// 動体に適用
		body->CreateFixture(&fixtureDef);
		return body;
	}

	b2Body* create(b2Vec2 center, b2Vec2* vertices, int arrayLength) {
		center.x /= drawRate;
		center.y /= drawRate;
		for(int i = 0; i < arrayLength; i++) {
			vertices[i].x /= drawRate;
			vertices[i].y /= drawRate;
			vertices[i] = B2Vec2::relativePosition(center, vertices[i]);
		}
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef;

		// 動体オブジェクトを定義する
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = center;
		auto body = world->CreateBody(&bodyDef);
		bodies.push_back(body);
		// 動体オブジェクトの形を定義する
		b2PolygonShape dynamicBox;

		dynamicBox.Set(vertices, arrayLength);

		// 動体オブジェクトの密度・摩擦の関連付け
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// 密度を設定
		fixtureDef.density = 1.0f;
		// 摩擦を設定
		fixtureDef.friction = 1.0f;
		// 反発を設定
		fixtureDef.restitution = 0.0;
		// 動体に適用
		body->CreateFixture(&fixtureDef);
		return body;
	}

	b2Body* create(b2Vec2 center, std::vector<b2Vec2> vertices) {
		b2Vec2 verticesArray[b2_maxPolygonVertices];
		std::copy(vertices.begin(), vertices.end(), verticesArray);
		return create(center, verticesArray, vertices.size());
	}

	// 連結図形の作成
	void createChainPolygon(float x, float y) {
		x /= drawRate;
		y /= drawRate;

		// 動体オブジェクトの参照値
		b2BodyDef bodyDef = B2BodyDef::dynamic(x, y);

		auto body = world->CreateBody(&bodyDef);
		bodies.push_back(body);
		// 動体オブジェクトの形を定義する
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(2.0f, 2.0f);

		// 動体オブジェクトの密度・摩擦の関連付け
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// 密度を設定
		fixtureDef.density = 1.0f;
		// 摩擦を設定
		fixtureDef.friction = 0.1f;
		// 反発を設定
		fixtureDef.restitution = 0.3;
		// 動体に適用
		body->CreateFixture(&fixtureDef);

		// ボディ２つ目
		bodyDef.position.Set(x, y + 4.0);
		auto body2 = world->CreateBody(&bodyDef);
		bodies.push_back(body2);
		body2->CreateFixture(&fixtureDef);

		// ジョイントの定義
		b2WeldJointDef jointDef;
		jointDef.Initialize(body, body2, b2Vec2(x,y +2));
		// ジョイントを作る
		b2WeldJoint* frontJoint = (b2WeldJoint*)world->CreateJoint(&jointDef);
	}

	// 座標同士を繋げるオブジェクトを発生させる
	b2Body* createHandPath(b2Vec2 start, b2Vec2 end, b2Vec2 startLeft, b2Vec2 startRight,b2Vec2 endLeft, b2Vec2 endRight) {
		B2Vec2::applyRate(&start, drawRate);
		B2Vec2::applyRate(&end, drawRate);
		B2Vec2::applyRate(&startLeft, drawRate);
		B2Vec2::applyRate(&startRight, drawRate);
		B2Vec2::applyRate(&endLeft, drawRate);
		B2Vec2::applyRate(&endRight, drawRate);
		b2Vec2 center = B2Vec2::halfWay(start, end);
		
		startLeft = B2Vec2::relativePosition(center, startLeft);
		startRight = B2Vec2::relativePosition(center, startRight);
		endLeft = B2Vec2::relativePosition(center, endLeft);
		endRight = B2Vec2::relativePosition(center, endRight);
		

		// 動体オブジェクトの参照値
		// 回転を無効にすることでバネのある地面オブジェクトが作れる
		//b2BodyDef bodyDef = B2BodyDef::dynamic(B2Vec2::halfWay(start, end), 1.0, true);
		b2BodyDef bodyDef = B2BodyDef::dynamic(B2Vec2::halfWay(start, end), 1.0);

		// ボディの作成
		auto body = world->CreateBody(&bodyDef);
		bodies.push_back(body);
		body->SetBullet(false);

		// 動体オブジェクトの形を定義する
		b2PolygonShape dynamicBox;
		float width = 5.0;
		b2Vec2 rect[4] = {startLeft, startRight, endLeft, endRight};
		dynamicBox.Set(rect, 4);
		//dynamicBox.SetAsBox(5.0f, 5.0f);

		// 動体オブジェクトの密度・摩擦の関連付け
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// 密度を設定
		fixtureDef.density = 1.00f;
		// 摩擦を設定
		fixtureDef.friction = 0.1f;
		// 反発を設定
		fixtureDef.restitution = 0.0;
		// 動体に適用
		body->CreateFixture(&fixtureDef);
		
		return body;
	}

	// 塗りつぶしを行わない手描き線を描く
	void createHandWrittenLine(touch_t touch, float width, bool fillFlag = false) {
		b2Vec2 lastLeft;
		b2Vec2 lastRight;
		b2Vec2 currentLeft;
		b2Vec2 currentRight;
		b2Body* current;
		b2Body* last;
		// 塗りつぶしなら最初の頂点と最後の頂点を繋げる
		
		if(fillFlag) {
			const int addIndex = B2Vec2::checkCreatePos(locus.at(0), locus.back()) ? 0 : 1;
			locus.push_back(locus.at(addIndex));
		}
		
	b2Body* firstBody;
		for(int i = 1; i < locus.size() ; i++) {
			const b2Vec2 start = locus.at(i - 1);
			const b2Vec2 end = locus.at(i);
			const float angle = atan2(start.y - end.y, start.x - end.x);
			if(i == 1) {
				lastLeft = B2Vec2::rotate(start, width, angle, B2Vec2::Leading);
				lastRight = B2Vec2::rotate(start, width, angle, B2Vec2::Trailing);
			}
			currentLeft = B2Vec2::rotate(end, width, angle, B2Vec2::Leading);
			currentRight = B2Vec2::rotate(end, width, angle, B2Vec2::Trailing);

			current = createHandPath(start, end, lastLeft, lastRight, currentLeft, currentRight);
			if(i == 1) {
				firstBody = current;
			}
			if(i > 1) {
				B2Joint::weldJoint(world, last, current, B2Vec2::halfWay(last->GetWorldCenter(), current->GetWorldCenter()));
			} else if(fillFlag && i == locus.size() - 1) {
				// 塗りつぶしなら最後に制御点同士を繋げる
				lastLeft = currentLeft;
				lastRight = currentRight;
			}
			last = current;
			lastLeft = currentLeft;
			lastRight = currentRight;
		}
		if(fillFlag) {
			B2Joint::weldJoint(world, last, firstBody, B2Vec2::halfWay(last->GetWorldCenter(), firstBody->GetWorldCenter()));
		}
	}

	void createPolygon(touch_t touch, float width) {
		// 始点と終点を繋げる
		auto start = b2Vec2(locus.back().x, locus.back().y);
		auto end = b2Vec2(locus.begin()->x, locus.begin()->y);
		if(B2Vec2::checkCreatePos(start, end)) {
			locus.push_back(end);
		}
		// 重心
		auto center = B2Vec2::center(locus);

		// 重心から順に頂点を作成するため、作成する頂点数は最大値-1
		const int max = b2_maxPolygonVertices - 1;
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		std::vector<b2Vec2> vertices;
		b2Vec2 verticesArray[b2_maxPolygonVertices];
		b2Body *current, *last;
		last = NULL;
		vertices.push_back(center);
		#define CREATE std::copy(vertices.begin(), vertices.end(), verticesArray);\
					current = create(center, verticesArray, vertices.size());
		int i = 0;
		while(i < locus.size()) {
			vertices.push_back(locus.at(i));
			if(vertices.size() == max - 1) {
				CREATE
				if(last != NULL) {
					B2Joint::weldJoint(world, current, last, b2Vec2(center.x / drawRate, center.y / drawRate));
				}
				last = current;

				vertices.clear();
				vertices.push_back(center);
				continue;
			} else if(i == locus.size() - 1) {
				int index = 0;
				if(!B2Vec2::checkCreatePos(b2Vec2(vertices.back().x, vertices.back().y), locus[0])) {
					if(!B2Vec2::checkCreatePos(b2Vec2(vertices.back().x, vertices.back().y), locus[1])) {
						break;
					}
					index = 1;
				}
				vertices.push_back(locus[index]);
				CREATE
				B2Joint::weldJoint(world, current, last, b2Vec2(center.x / drawRate, center.y / drawRate));
				break;
			}
			i++;
		}
		#undef CREATE
	}

	// 手描き線の作成
	void createHandWritten(touch_t touch, float width) {
		// タッチリリース直後でなければ処理を行わない
		if(touch.status != TouchStatus::kJustRelease) {
			return;
		}

		// 軌跡を作成する
		locus = B2Vec2::locus(touch.pos_log_x, touch.pos_log_y, touch.beginIndex);
		// 軌跡の制御点が３つ以上なければ作成しない
		if(locus.size() < 3) {
			return;
		}

		// 始点と終点が範囲内なら塗りつぶし手描き線ポリゴンを作成し、それ以外なら手描き線を描画する
		if(B2Vec2::isFillPolygon(locus, 90.0)) {
			createHandWrittenLine(touch, width, true);
		} else {
			createHandWrittenLine(touch, width);
		}
	}

	// 塔の作成
	void createTower(touch_t touch) {
		if(touch.status != TouchStatus::kJustRelease) {
			return;
		}
		b2Body* before = NULL;
		for(int i=0;i<5;i++) {
			auto *body = create(touch.x, touch.y - ((float)i) * 40.0);
			if (before != NULL) {
				B2Joint::weldJoint(world, before, body, B2Vec2::halfWay(before->GetWorldCenter(), body->GetWorldCenter()));
			}
			before = body;
		}
	}

	void createCar(float x, float y) {
		x /= drawRate;
		y /= drawRate;
		// 動体オブジェクトの参照値
		b2BodyDef bodyDef;

		// 動体オブジェクトを定義する
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x - 5.0, y + 6.0);
		auto frontWheel = world->CreateBody(&bodyDef);
		bodyDef.position.Set(x + 5.0, y + 6.0);
		auto rearWheel = world->CreateBody(&bodyDef);
		bodyDef.position.Set(x, y);
		auto body = world->CreateBody(&bodyDef);
		bodies.push_back(frontWheel);
		bodies.push_back(rearWheel);
		bodies.push_back(body);

		b2CircleShape circle = b2CircleShape();
		circle.m_radius = 3.0;

		b2PolygonShape rectangle;
		rectangle.SetAsBox(10, 5);
		rectangle.m_count = 4;

		// それぞれのオブジェクトで適用したいなら下記のコメントアウトを削除
		
		// 動体オブジェクトの密度・摩擦の関連付け
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;

		// 密度を設定
		fixtureDef.density = 0.05f;
		// 摩擦を設定
		fixtureDef.friction = 0.8f;
		// 反発を設定
		fixtureDef.restitution = 0.1;

		// 動体に適用
		frontWheel->CreateFixture(&fixtureDef);
		rearWheel->CreateFixture(&fixtureDef);
		fixtureDef.shape = &rectangle;
		body->CreateFixture(&fixtureDef);
		

		// ジョイントの定義
		b2RevoluteJointDef jointDef;
		// 前輪
		jointDef.Initialize(body, frontWheel, frontWheel->GetWorldCenter());
		// １秒間に33回転
		jointDef.motorSpeed = 100;
		// 坂道の強さ
		jointDef.maxMotorTorque = 30;
		// 車輪を回すようにする
		jointDef.enableMotor = true;

		// ジョイントを作る
		b2RevoluteJoint* frontJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
		// 後輪
		jointDef.Initialize(body, rearWheel, rearWheel->GetWorldCenter());
		// ジョイントを作る
		b2RevoluteJoint* rearJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
	}

	private:
public:
	// 物理演算を行うワールド
	b2World* world;	

	// 地面の定義
	std::vector<b2Body *> grounds;

	// オブジェクトの定義
	std::vector<b2Body *> bodies;

	public:

	void calc() {

		// 時間経過メソッド
		const float timeStep = 1.0f / 10.0f;
		const int velocityIterations = 6;
		const int positionIterations = 2;

		world->Step(timeStep, velocityIterations, positionIterations);

		// オブジェクト消滅メソッド
		auto itr = bodies.begin();
		while(itr != bodies.end()) {
			auto pos = (*itr)->GetPosition();
			if(pos.x < 0 || pos.x > 113 || pos.y  < 0 || pos.y > 113) {
				world->DestroyBody((*itr));
				itr = bodies.erase(itr);
			} else {
				++itr;
			}
		}
	}

	void draw(b2Body *body) {
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		// b2Fixture
		auto fixture = body->GetFixtureList();
		auto type = fixture->GetType();
		switch (type) {
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();
				auto pos = fixture->GetBody()->GetPosition();
				drawCircle(pos.x * drawRate, pos.y * drawRate, shape->m_radius * drawRate, GetColor(255,255,255));
				//for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
				//	f->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).x;
				//}
				
			}
			break;
			case b2Shape::e_chain:
			printfDx("e_chain");
			break;
			case b2Shape::e_edge:
			printfDx("e_edge");
			break;
			case b2Shape::e_polygon:
			//printfDx("e_polygon");
			{
				b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
				
				int count = 0;
				for(int i = 0; i < shape->m_count; i++) {
					auto localStart = shape->m_vertices[i];
					auto localEnd = shape->m_vertices[(i + 1) % shape->m_count];
					auto start = fixture->GetBody()->GetWorldPoint(localStart);
					auto end = fixture->GetBody()->GetWorldPoint(localEnd);
					drawLine(start.x * drawRate, start.y * drawRate, end.x * drawRate, end.y * drawRate, GetColor(255,255,255));
					//printfDx("%d: x: %f, y: %f\n", i, start.x, start.y);
				}
			}
			break;
			case b2Shape::e_typeCount:
			printfDx("e_typeCount");
			break;
			default:
			printfDx("typeNone...");
			break;
		}
	}

	void draw() {
		ForEach(grounds, [this](b2Body *item) { this->draw(item); });
		ForEach(bodies, [this](b2Body *item) { this->draw(item); });
	}
};

box2DTest* test;
*/