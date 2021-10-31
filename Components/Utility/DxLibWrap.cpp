/**
 * @file DxLibWrap.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-10-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DxLibWrap.h"
#include <vector>
#include "TypeExtensions/Int+Extensions.h"
#include "TypeExtensions/Float+Extensions.h"
#include "TypeExtensions/B2Vec2+Extensions.h"
#include "TypeExtensions/VectorOrArray+Extension.h"

// バイナリをバッファに丸ごと読み込む
void* loadToBuffer(const char* filePath) {
    void *buffer;
    int fileHandle;
    long fileSize;

     // ファイルのサイズを得る
    fileSize = FileRead_size( filePath ) ;
    // ファイルを格納するメモリ領域の確保
    buffer = malloc( fileSize ) ;
    
    // ファイルを読み込む
    fileHandle = FileRead_open( filePath ) ;
    // ファイルを丸ごとメモリに読み込む
    FileRead_read( buffer, fileSize, fileHandle ) ;
    // ファイルを閉じる
    FileRead_close( fileHandle ) ;
    return std::move(buffer);
}

// マウスカーソルの位置を取得する
int getMousePoint(int *XBuf, int *YBuf) {
    int returnNum = GetMousePoint(XBuf, YBuf);
    #ifdef EMSCRIPTEN
    setBrowserGeneralPos(XBuf, YBuf);
    #else
    #endif
    setScreenPosToLocal(XBuf, YBuf);
    return returnNum;
}

// タッチされている箇所の情報を取得する
int getTouchInput(int InputNo, int *PositionX, int *PositionY, int GlobalPos, int *ID, int *Device) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(PositionX, PositionY);
    return GetTouchInput(InputNo, PositionX, PositionY, ID, Device);
}

// 線を描画
int drawLine( int x1 , int y1 , int x2 , int y2 , unsigned int Color, int GlobalPos, int Thickness) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawLine(x1, y1, x2, y2, Color, Thickness);
}

// 線を描画(アンチエイリアス付き)
int drawLineAA( int x1 , int y1 , int x2 , int y2 , unsigned int Color, int GlobalPos, int Thickness) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawLineAA(x1, y1, x2, y2, Color, Thickness);
}

// 四角形を描画
int drawBox(int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawBox(x1, y1, x2, y2, Color, FillFlag);
}

// 四角形を描画(アンチエイリアス付き)
int drawBoxAA(int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawBoxAA(x1, y1, x2, y2, Color, FillFlag);
}

// 円の描画
int drawCircle(int x, int y, int r, unsigned int Color, int GlobalPos, int FillFlag, int LineChickness) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawCircle(x, y, r, Color, FillFlag, LineChickness);
}

// 円の描画(アンチエイリアス付き)
int drawCircleAA(float x, float y, float r, int posnum, unsigned int Color, int GlobalPos, int FillFlag, int LineChickness) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawCircleAA(x, y, r, Color, FillFlag, LineChickness);
}

// 円の描画(アンチエイリアス付き)
int drawCircleAA(b2Vec2 center, float r, int posnum, unsigned int Color, int GlobalPos, int FillFlag, int LineChickness) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&center.x, &center.y);
    return drawCircleAA(center.x, center.y, r, posnum, Color, GlobalPos, FillFlag, LineChickness);
}

// 楕円を描く
int drawOval( int x , int y , int rx , int ry , unsigned int Color , int FillFlag, int GlobalPos, int LineChickness ) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawOval(x, y, rx, ry, Color, FillFlag, LineChickness);
}

// 楕円を描く(アンチエイリアス付き)
int drawOvalAA( int x , int y , int rx , int ry , unsigned int Color , int FillFlag, int GlobalPos, int LineChickness ) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawOvalAA(x, y, rx, ry, Color, FillFlag, LineChickness);
}

// 三角形の描画
int drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color , int FillFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
    }
    return DrawTriangle(x1, y1, x2, y2, x3, y3, Color, FillFlag);
}

// 三角形の描画(アンチエイリアス効果付き)
int drawTriangleAA( int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color , int FillFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
    }
    return DrawTriangleAA(x1, y1, x2, y2, x3, y3, Color, FillFlag);
}

// 点を描画する
int drawPixel( int x , int y , unsigned int Color, int GlobalPos) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawPixel(x, y, Color);
}

// 指定点の色を取得
unsigned int getPixel( int x , int y, int GlobalPos) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return GetPixel(x, y);
}

// メモリに読みこんだグラフィックの描画
int drawGraph( int x, int y, int GrHandle, int TransFlag, int GlobalPos) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawGraph(x, y, GrHandle, TransFlag);
}

// メモリに読みこんだグラフィックのＬＲ反転描画
int drawTurnGraph( int x, int y, int GrHandle, int TransFlag, int GlobalPos) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawTurnGraph(x, y, GrHandle, TransFlag);
}

// メモリに読みこんだグラフィックの拡大縮小描画
int drawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
    }
    return DrawExtendGraph(x1, y1, x2, y2, GrHandle, TransFlag);
} 

 // メモリに読みこんだグラフィックの回転描画
int drawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag, int GlobalPos, int ReverceXFlag, int ReverceYFlag ) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, TransFlag, ReverceXFlag, ReverceYFlag);
}

// メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
int drawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag, int GlobalPos, int ReverceXFlag, int ReverceYFlag) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph2(x, y, cx, cy, ExtRate, Angle, GrHandle, TransFlag, ReverceXFlag, ReverceYFlag);
}

// メモリに読みこんだグラフィックの回転描画(回転中心指定あり)
int drawRotaGraph3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag, int GlobalPos, int ReverceXFlag, int ReverceYFlag) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, TransFlag, ReverceXFlag, ReverceYFlag);
}

// メモリに読みこんだグラフィックの自由変形描画
int drawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
        setScreenPosToGlobal(&x4, &y4);
    }
    return DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, GrHandle, TransFlag);
}

// メモリに読みこんだグラフィックの自由変形描画(float)
int drawModiGraphF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int GrHandle , int TransFlag, int GlobalPos) {
	if (GlobalPos == FALSE) {
        setScreenPosToGlobal(&x1, &y1);
        setScreenPosToGlobal(&x2, &y2);
        setScreenPosToGlobal(&x3, &y3);
        setScreenPosToGlobal(&x4, &y4);
    }
    return DrawModiGraphF(x1, y1, x2, y2, x3, y3, x4, y4, GrHandle, TransFlag);
}

// メモリに読みこんだグラフィックの自由変形描画(float,引数がb2Vec2)
int drawModiGraphF( b2Vec2 pos1, b2Vec2 pos2, b2Vec2 pos3, b2Vec2 pos4, int GrHandle , int TransFlag, int GlobalPos) {
	return drawModiGraphF(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, pos4.x, pos4.y, GrHandle, TransFlag, GlobalPos);
}

// 画像を連続して描画する時の画像ハンドルを返す
int nextImageIndex(std::vector<int> images, int nowIndex, bool loop, bool edgeDraw) {
	const int countMin = edgeDraw || IsEmpty(images) ? 0 : 1;
	const int countMax = Int::clamp(edgeDraw ? images.size() - 1 : images.size() - 2, 0, images.size());
	int index;
	// 初期値
	if(nowIndex == Array::kUnspecified) {
		index = loop ? countMin : countMax;
	} else {
		index = Int::clamp(nowIndex, countMin, countMax);
		if(loop) {
			index++;
			if(index > countMax) {
				index = countMin;
			}
		} else {
			index--;
			if(index < 0) {
				return -1;
			}
		}
	}
	return index;
}

// ベジェ曲線の次の進行率を返す
float nextBezieAdvance(float nowAdvance, float roughness, bool loop, bool init) {
	roughness = Float::clamp(roughness, 0.0, 1.0);
	if(init) {
		return loop ? 0.0 : 1.0 - roughness;
	}
	float t = loop ? nowAdvance + roughness : nowAdvance - roughness ;
	return Float::clamp(t, 0.0, 1.0);
}

// 制御点が３つのベジェ曲線を画像で描画する
int drawBezie(b2Vec2 left[3], b2Vec2 right[3], float roughness, std::vector<int> images, bool loop, bool edgeDraw, int firstIndex, int GlobalPos) {
	float t = nextBezieAdvance(0.0, roughness, loop, true);
	const int imgCountMin = edgeDraw || images.size() < 2 ? 0 : 1;
	const int imgCountMax = Int::clamp(edgeDraw ? images.size() - 1 : images.size() - 2, 0, images.size());
	int imgIndex = firstIndex == Array::kUnspecified ? nextImageIndex(images, Array::kUnspecified, loop, edgeDraw) : firstIndex;
	float next;
	bool end = false;
	// 左の始点、終点、右の始点、終点
	b2Vec2 so, si, go, gi;
	roughness = Float::clamp(roughness, 0.0, 1.0);
	next = loop ? Float::clamp(t + roughness, 0.0, 1.0) : 1.0;
	while(!end) {
		so = B2Vec2::bezieValue(left, t);
		si = B2Vec2::bezieValue(right, t);
		go = B2Vec2::bezieValue(left, next);
		gi = B2Vec2::bezieValue(right, next);
		
		drawModiGraphF(so, si, gi, go, images.at(imgIndex), TRUE, GlobalPos);
		// 次の画像ハンドルを決める
		imgIndex = nextImageIndex(images, imgIndex, loop, edgeDraw);
		// 根本まで来ていたら描画しない
		if(!loop && imgIndex < imgCountMin) {
			break;
		}
		// 最後まで描画したら終了する
		if(t <= 0.0 - Float::kMinima || next >= 1.0 + Float::kMinima) {
			end = true;
		}
		// 進行率を決める
		t = nextBezieAdvance(t, roughness, loop);
		next = nextBezieAdvance(t, roughness, loop);
	}
	return imgIndex;
}

// グラフィックの指定矩形部分のみを描画
int drawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, 
                    int GraphHandle, int TransFlag, int TurnFlag, int GlobalPos, 
                    int ReverceXFlag, int ReverceYFlag ) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&DestX, &DestY);
    return DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, GraphHandle, TransFlag, ReverceXFlag, ReverceYFlag);
}

// ポリゴンから２D画像を描画します
int drawPolygon2D(DxLib::VERTEX2D *VertexArray, int PolygonNum, int GrHandle, int TransFlag, int GlobalPos) {
    if (GlobalPos == FALSE) {
        int x, y;
        float fx, fy;
        for(int i=0;i<PolygonNum*3;i++) {
            x = (int)VertexArray[i].pos.x;
            y = (int)VertexArray[i].pos.y;
            fx = VertexArray[i].pos.x - (float)x;
            fy = VertexArray[i].pos.y - (float)y;
            setScreenPosToGlobal(&x, &y);
            VertexArray[i].pos = VGet(((float)x) + fx, ((float)y) + fy, 0.0);

        }
    }
    return DrawPolygon2D(VertexArray, PolygonNum, GrHandle, TransFlag);
}