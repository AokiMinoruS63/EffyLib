/* 
 * File:   Main
 * Author: nokotan
 *
 * Created on 2020/01/30, 0:57
 * 
 * DxLibToHTML5雛形ファイル
 */

#include <DxLib.h>
//#include "Components/Touch/TouchMgr.h"
//#include <hogeClass.h>
#include <Touch/TouchMgr.h>
#include <BMFont/BMFontMgr.h>
#include <utility>
#include <Utility/DxLibWrap.h>
#include <Utility/TypeConversion.h>
//#include <Components/hogeClass.h>
#ifdef EMSCRIPTEN
#  include <emscripten.h>
#endif

static bool shouldExit = false;
TouchMgr *touchMgr;
BMFontMgr *bmFontMgr;
const BMFont::bmFont_t *bmFont;

int drawFont(BMFont_t bm, int id, float x, float y, float scale = 1.0f, COLOR_U8 color = GetColorU8(255,255,255,255)) {
	int size[2]={0,0};
	// 画像取得に失敗したら何もしない
	if(GetGraphSize(bm.graphHandle, &size[0], &size[1]) == -1)return 0;
	const BMFont::char_t *str = bm.bmFont->chars()->LookupByKey(id);
	float half_width = ((float)str->width()) / 2.0f;
	float half_height = ((float)str->height()) / 2.0f;

	// オフセット値は逆にズレるので使用しない
	//x += str->xoffset();
	//y += str->yoffset();
	float sx = x - half_width * scale;
	float sy = y - half_height * scale;
	float gx = x + half_width * scale;
	float gy = y + half_height * scale;
	float su = ((float)str->x()) / ((float)size[0]);
	float sv = ((float)str->y()) / ((float)size[1]);
	float gu = ((float)(str->x() + str->width())) / ((float)size[0]);
	float gv = ((float)(str->y() + str->height())) / ((float)size[1]);
	//printfDx("sx: %f, sy: %f su: %f sv: %f\n", sx,sy,su,sv);
	
	VERTEX2D Vert[ 6 ] ;

	// ２ポリゴン分の頂点のデータをセットアップ
	Vert[ 0 ].pos = VGet(   sx,   sy, 0.0f ) ;
	Vert[ 0 ].rhw = 1.0f ;
	Vert[ 0 ].dif = color ;
	Vert[ 0 ].u   = su ;
	Vert[ 0 ].v   = sv ;

	Vert[ 1 ].pos = VGet( gx,   sy, 0.0f ) ;
	Vert[ 1 ].rhw = 1.0f ;
	Vert[ 1 ].dif = color ;
	Vert[ 1 ].u   = gu ;
	Vert[ 1 ].v   = sv ;

	Vert[ 2 ].pos = VGet(   sx, gy, 0.0f ) ;
	Vert[ 2 ].rhw = 1.0f ;
	Vert[ 2 ].dif = color ;
	Vert[ 2 ].u   = su ;
	Vert[ 2 ].v   = gv ;

	Vert[ 3 ].pos = VGet( gx, gy, 0.0f ) ;
	Vert[ 3 ].rhw = 1.0f ;
	Vert[ 3 ].dif = color ;
	Vert[ 3 ].u   = gu ;
	Vert[ 3 ].v   = gv ;

	Vert[ 4 ].pos = VGet(   sx, gy, 0.0f ) ;
	Vert[ 4 ].rhw = 1.0f ;
	Vert[ 4 ].dif = color ;
	Vert[ 4 ].u   = su ;
	Vert[ 4 ].v   = gv ;

	Vert[ 5 ].pos = VGet( gx,   sy, 0.0f ) ;
	Vert[ 5 ].rhw = 1.0f ;
	Vert[ 5 ].dif = color ;
	Vert[ 5 ].u   = gu ;
	Vert[ 5 ].v   = sv ;

	// ２Ｄの２ポリゴンの描画
	// TODO: パーティション座標に差し替え
	DrawPolygon2D( Vert, 2, bm.graphHandle, TRUE ) ;

	// 幅を返す
	return (str->xadvance() + bm.bmFont->info()->padding()->Get(1)+ bm.bmFont->info()->padding()->Get(3) + bm.bmFont->info()->spacing()->Get(0))  * scale;
}

//BMFont::BMFont bmFont;
void mainLoop() {
	if (ProcessMessage() == -1) {
		shouldExit = true;
	}

	ClearDrawScreen();

	{
		touchMgr->calc();
		
	}

	{
		int StringColor = CheckHitKey(KEY_INPUT_SPACE) ? GetColor(0, 255, 0) : GetColor(255, 255, 255);
		DrawString(3, 3, "Hello DxLib on HTML5!", StringColor);


		bmFont = bmFontMgr->get().bmFont;
		//DrawGraph(0,0,bmFontMgr->get().graphHandle,TRUE);
		DrawFormatString(100,3, GetColor(255,255,255), "bmFont %s stretchH: %f", bmFont->info()->face()->c_str(),
		bmFont->info()->stretchH());
		DrawFormatString(100,30, GetColor(255,255,255), "bmFont %s stretchH: %f spacing [%d,%d]", bmFont->info()->face()->c_str(),
		bmFont->info()->stretchH(), bmFont->info()->spacing()->Get(0), bmFont->info()->spacing()->Get(1));
		// LookupByKey(〜)で配列の中の要素が取得できる
		// 例、配列の中に[hoge:int (key)]の記述があればhogeがkeyとなってLookByKey(int)から探せる（キーはstringや他のものでも可能）
		auto fontCharInfo = bmFont->chars()->LookupByKey(9734);
		DrawFormatString(100,200,GetColor(255,255,255), "id: %d height: %d", fontCharInfo->id(), fontCharInfo->height());
		
		float X=50,Y=200;
		static LONG cnt = 0;
		float scale = ((float)(cnt%60) + 1) / 60; 
		for(int i=0;i<20;i++) {
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("き"), X, Y, scale));
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("あ"), X, Y, scale));
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("く"), X, Y, scale));
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("あ"), X, Y, scale));
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("き"), X, Y, scale));
			X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("く"), X, Y, scale));
		}
		cnt++;
		
		/*
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("あ"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("い"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("う"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("え"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("お"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("か"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("き"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("く"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("け"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("こ"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("さ"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("し"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("す"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("せ"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("そ"), X, Y));
		X += (float)(drawFont(bmFontMgr->get(), utf8_to_long("た"), X, Y));
		*/

		// 境界線描画
		DrawLine(1513,0,1513,1136,GetColor(255,0,0),2);
		DrawBox(0,0,874/2,1136,GetColor(0,0,100),TRUE);
		DrawBox(1514-874/2,0,1514,1136,GetColor(0,0,100),TRUE);

		touch_t touch = touchMgr->get();
		int CircleColor = ( touch.status != TouchStatus::NoTouch && touch.status != TouchStatus::JustRelease) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

		drawCircle(touch.x, touch.y, 64, CircleColor, TRUE);

		/*
		std::string c = "鳥";//"鼻";// 鳥 40165(9CE5)//u8"\u9F3B";// 鼻 40763
		char c2[] = u8"\u9CE5";//u8"\u9F3B";
		int byte = std::strlen("鳥");//std::strlen("鼻");//std::strlen("鼻");// 3byte
		//std::string str = "a";
		LONG num = (LONG)(c.c_str());// 
		//鼻=10891024 鳥=10891008
		DrawFormatString(3,30,GetColor(255,255,255),"char c1: %s c2: %s num %ld byte %d", c.c_str(), c2, utf8_to_int(c.c_str()), byte);
		// 区 点 JIS  SJIS EUC  UTF-8  UTF-16 字
		// 36 27 443B 92B9 C4BB E9B3A5 9CE5   鳥
		// 41 01 4921 9540 C9A1 E9BCBB 9F3B   鼻
		hoge->intputNum(3);
		printfDx("\n\ntestNum %d", hoge->outputNum());
		*/
		
	}

	ScreenFlip();
}


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main () {
#endif
	SetGraphMode(1514, 1136, 32);

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
    ChangeFont("07LogoTypeGothic7.ttf");
	SetDrawScreen(DX_SCREEN_BACK);

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