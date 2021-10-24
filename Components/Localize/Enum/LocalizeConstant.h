/**
 * @file LocalizeConstant.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 言語一覧。BMフォント、シナリオなどローカライズが必要なアセットフォルダはこの名称で分岐させること！
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LOCALIZE_CONSTANT_H
#define LOCALIZE_CONSTANT_H

/**
 * @brief 言語(フォルダ名と直結しているため、命名規則に従って接頭辞にkが付かない)
 * 
 */
enum class Language {
    None,           // 未設定
    Japanese,       // 日本語
    English,        // 英語
    Korea,          // 韓国語　
    Chinese,        // 中国語
    Russian,        // ロシア語
    Spanish,        // スペイン語
    French,         // フランス語
    German,         // ドイツ語
    Italian,        // イタリア語
    Portuguese,     // ポルトガル語
    Dutch,          // オランダ語 
    Icelandic,      // アイスランド語
    Danish          // デンマーク語
};

#endif