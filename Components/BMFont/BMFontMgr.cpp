#include "BMFontMgr.h"
#include <string>
#include <utility>
#include "../Localize/GetEndUserLanguage.h"
#include "../Utility/DxLibWrap.h"

BMFontMgr::BMFontMgr() {
    
}

BMFontMgr::~BMFontMgr() {

}

BMFont_t BMFontMgr::get() {
    return bmfonts.at(0);
}

void BMFontMgr::load(const char* fileName) {
    // ファイルパスを構築する
    std::string filePath = "Components/BMFont/";
    std::string localizeStr = getEndUserLanguageToString();
    std::string binaryPath;
    std::string imgPath;
    filePath += localizeStr;
    filePath += "/";
    filePath += fileName;
    binaryPath = filePath + ".bin";
    imgPath = filePath + ".png";
    bmfonts.push_back((BMFont_t){
        // バイナリデータの読込
        BMFont::GetbmFont_t(loadToBuffer(binaryPath.c_str())),
        // 画像の読込
        LoadGraph(imgPath.c_str())
    });
}