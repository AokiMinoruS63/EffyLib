// ここにクラスを記述する

// 初期化時フォルダのBMフォントのルートフォルダを引数としてもらう
// そのフォルダの中に更にローカライズ用のフォルダがあり、その下にフォントのデータを置く
// この仕組みはローカライズした時にファイルを管理しやすいようにするため
// ローカライズフォルダの名前は（Components/Localize/Constant/LocalizeConstant.h）
// から参照
// 読み込むフォントファイルもvector<std::string>で渡す

#ifndef BMFONT_H
#define BMFONT_H

#include "BMFontData.h"

class BMFont {

};
#endif