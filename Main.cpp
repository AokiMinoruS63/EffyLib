/* 
 * File:   Main
 * Author: nokotan
 *
 * Created on 2020/01/30, 0:57
 * 
 * DxLibToHTML5雛形ファイル
 */

#include <DxLib.h>
#include <math.h>
#include <EffyLib.h>
#ifdef EMSCRIPTEN
#  include <emscripten.h>
#endif

static bool shouldExit = false;
TouchMgr *touchMgr;
BMFontMgr *bmFontMgr;
const BMFont::bmFont_t *bmFont;

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
		b2BodyDef bodyDef = B2BodyDef::dynamic(B2Vec2::halfWay(start, end), 1.0, true);

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
		fixtureDef.density = 0.01f;
		// 摩擦を設定
		fixtureDef.friction = 0.1f;
		// 反発を設定
		fixtureDef.restitution = 0.0;
		// 動体に適用
		body->CreateFixture(&fixtureDef);
		
		return body;
	}

	// 塗りつぶしを行わない手書き線を描く
	void createHandWrittenLine(touch_t touch, float width) {
		b2Vec2 lastLeft;
		b2Vec2 lastRight;
		b2Vec2 currentLeft;
		b2Vec2 currentRight;
		b2Body* current;
		b2Body* last;
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
			if(i > 1) {
				B2Joint::weldJoint(world, last, current, B2Vec2::halfWay(last->GetWorldCenter(), current->GetWorldCenter()));
			}
			last = current;
			lastLeft = currentLeft;
			lastRight = currentRight;
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
				if(!B2Vec2::checkCreatePos(b2Vec2(vertices.back().x, vertices.back().y), locus[0])) {
					break;
				}
				vertices.push_back(locus[0]);
				CREATE
				break;
			}
			i++;
		}
		#undef CREATE
	}

	// 手書き線の作成
	void createHandWritten(touch_t touch, float width) {
		// タッチリリース直後かつ３つ以上タッチログがなければ処理を行わない
		if(touch.status != TouchStatus::JustRelease || touch.beginIndex < 3) {
			return;
		}

		// 軌跡を作成する
		locus = B2Vec2::locus(touch.posLogX, touch.posLogY, touch.beginIndex);

		// 始点と終点が範囲内なら塗りつぶし手描き線ポリゴンを作成し、それ以外なら手描き線を描画する
		if(B2Vec2::isFillPolygon(locus, 90.0)) {
			createPolygon(touch, width);
		} else {
			createHandWrittenLine(touch, width);
		}
	}

	// 塔の作成
	void createTower(touch_t touch) {
		if(touch.status != TouchStatus::JustRelease) {
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
		/* 前輪 */
		jointDef.Initialize(body, frontWheel, frontWheel->GetWorldCenter());
		// １秒間に33回転
		jointDef.motorSpeed = 100;
		// 坂道の強さ
		jointDef.maxMotorTorque = 30;
		// 車輪を回すようにする
		jointDef.enableMotor = true;

		// ジョイントを作る
		b2RevoluteJoint* frontJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
		/* 後輪 */
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
				/*
				for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
					f->GetBody()->GetWorldPoint(b2Vec2(0.0, 0.0)).x;
				}
				*/
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

//BMFont::BMFont bmFont;
void mainLoop() {
	if (ProcessMessage() == -1) {
		shouldExit = true;
	}

	ClearDrawScreen();

	// box2Dテスト
	test->calc();
	test->draw();

	// タッチ計算
	touchMgr->calc();

	// タッチ画像描画
	{	
		touch_t touch = touchMgr->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);
		//drawCircle(touch.x, touch.y, 64, CircleColor);

		if (touch.status == TouchStatus::JustTouch) {
			//test->create(touch.x * 0.1, touch.y * 0.1);
			//test->createCar(touch.x, touch.y);
			//test->createChainPolygon(touch.x, touch.y);
		}
		test->createHandWritten(touch, 10.0);
		//test->createTower(touch);
	}
	/*
	{
		static LONG cnt = 0;
		if(cnt%60 == 0) {
			test->createCar((float)(GetRand(500) + 1), (float)(GetRand(300) + 1));
		}
		cnt++;
	}
	*/

	ScreenFlip();
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main () {
#endif

#ifdef EMSCRIPTEN
	SetGraphMode(1136, 852, 32);
#else
	SetGraphMode(852, 1136, 32)
#endif
// Emscriptenは非同期読み込み不可のようなのでそれ以外の時のみ使用する
#ifndef EMSCRIPTEN
	// 非同期読み込みモードオン
	SetUseASyncLoadFlag( TRUE ) ;
#endif
    if (DxLib_Init() == -1) {
		return -1;
    }
	touchMgr = new TouchMgr();
	bmFontMgr = new BMFontMgr();
	bmFontMgr->load("GameFont_Blue");
	test = new box2DTest();
	

    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);
	Sprite *spr = new Sprite();
	//Sprite *spr = new Sprite();
	//spr->setColor(255,255,255,255);
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(mainLoop, 0, 1);	
#else
    while (!shouldExit) {
		mainLoop();
    }
    
    DxLib_End();
 #endif

    return 0;
}