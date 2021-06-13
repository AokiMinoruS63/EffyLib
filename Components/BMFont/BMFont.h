/**
 * @file BMFont.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ビットマップファイル１つ分の情報を入れておく（マネージャクラスは別。このクラスは読み込みしないのでローカライズもここには記載しない）
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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