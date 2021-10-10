/**
 * @file GetEndUserLanguage.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief エンドユーザーの言語情報取得関数群
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GET_ENDUSER_LANGUAGE_H
#define GET_ENDUSER_LANGUAGE_H

#include "Enum/LocalizeConstant.h"
#include <string>
#include <utility>
#include "../OpenSource/nameof.hpp"

#define TO_STRING(Variable) (#Variable)

#ifdef EMSCRIPTEN
#include <emscripten.h>

/**
 * @brief ※Emscripten専用。エンドユーザーの使用言語を返す
 *          (使用言語を追加した場合は双方に書き換えをすること！)
 */
EM_JS(int, getEnduserLanguageEM, (), {
    
    const kNone       = 0;   // 未設定
    const kJapanese   = 1;   // 日本語
    const kEnglish    = 2;   // 英語
    const kKorea      = 3;   // 韓国語　
    const kChinese    = 4;   // 中国語
    const kRussian    = 5;   // ロシア語
    const kSpanish    = 6;   // スペイン語
    const kFrench     = 7;   // フランス語
    const kGerman     = 8;   // ドイツ語
    const kItalian    = 9;   // イタリア語
    const kPortuguese = 10;  // ポルトガル語
    const kDutch      = 11;  // オランダ語 
    const kIcelandic  = 12;  // アイスランド語
    const kDanish     = 13;  // デンマーク語
    var lang = (navigator.language) ? navigator.language : navigator.userLanguage;
    // ただし、どちらのプロパティにも対応していないブラウザではundefinedになる

    if(lang.toLowerCase().indexOf("ja") !== -1)
        return kJapanese;
    if(lang.toLowerCase().indexOf("en") !== -1)
        return kJapanese;
    if(lang.toLowerCase().indexOf("ko") !== -1)
        return kKorea;
    if(lang.toLowerCase().indexOf("zh") !== -1)
        return kChinese;
    if(lang.toLowerCase().indexOf("ru") !== -1)
        return kRussian;
    if(lang.toLowerCase().indexOf("es") !== -1)
        return kSpanish;
    if(lang.toLowerCase().indexOf("fr") !== -1)
        return kFrench;
    if(lang.toLowerCase().indexOf("de") !== -1)
        return kGerman;
    if(lang.toLowerCase().indexOf("it") !== -1)
        return kItalian;
    if(lang.toLowerCase().indexOf("pt") !== -1)
        return kPortuguese;
    if(lang.toLowerCase().indexOf("nl") !== -1)
        return kDutch;
    if(lang.toLowerCase().indexOf("is") !== -1)
        return kIcelandic;
    if(lang.toLowerCase().indexOf("da") !== -1)
        return kDanish;

    return None;
});
#endif


Language getEndUserLanguage() {
    #ifdef EMSCRIPTEN
    return Language(getEnduserLanguageEM());
    #endif
    return Language::kNone;
}

/**
 * @brief エンドユーザーの使用言語を文字列で返す
 * 
 * @return エンドユーザーの使用言語
 */
std::string getEndUserLanguageToString() {
    Language lang;
    std::string endUserStr="";
    #ifdef EMSCRIPTEN
    lang = Language(getEnduserLanguageEM());
    #endif
    endUserStr = NAMEOF_ENUM(lang);
    return std::move(endUserStr);
}

#endif