/**
 * @file BMFontMgr.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ビットマップフォントを管理するマネージャ
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BMFONT_MGR_H
#define BMFONT_MGR_H

#include "../OpenSource/flatbuffersObjects/bmfont_generated.h"
#include <vector>

// TODO: BMフォント構造体
/*

  
 */
typedef struct {
    // アトラスデータが入ったバイナリデータ（参照も直接できる）
    const BMFont::bmFont_t *bmFont;
    // 参照する画像ファイル(128x128,256x256,512x512...などちょうどの大きさにする必要あり)
    int graphHandle;
}BMFont_t;

class BMFontMgr {
    private:
    // 読み込んだBMフォント
    std::vector<BMFont_t> bmfonts_;

    public:
    BMFontMgr();
    ~BMFontMgr();
    // getter
    BMFont_t get();
    // TODO: ロード関数
    void load(const char *fileName);
    // TODO: 描画関数
};
#endif