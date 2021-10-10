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
 * @brief 言語
 * 
 */
enum class Language {
    kNone,           // 未設定
    kJapanese,       // 日本語
    kEnglish,        // 英語
    kKorea,          // 韓国語　
    kChinese,        // 中国語
    kRussian,        // ロシア語
    kSpanish,        // スペイン語
    kFrench,         // フランス語
    kGerman,         // ドイツ語
    kItalian,        // イタリア語
    kPortuguese,     // ポルトガル語
    kDutch,          // オランダ語 
    kIcelandic,      // アイスランド語
    kDanish          // デンマーク語
};

#endif