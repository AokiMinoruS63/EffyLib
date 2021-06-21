#include "DxLibWrap.h"

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
int drawCircleAA(int x, int y, int r, unsigned int Color, int GlobalPos, int FillFlag, int LineChickness) {
    if (GlobalPos == FALSE)
        setScreenPosToGlobal(&x, &y);
    return DrawCircleAA(x, y, r, Color, FillFlag, LineChickness);
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