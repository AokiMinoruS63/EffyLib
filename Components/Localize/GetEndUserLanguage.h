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
#include "../Utility/nameof.hpp"

#define TO_STRING(Variable) (#Variable)

#ifdef EMSCRIPTEN
#include <emscripten.h>

/**
 * @brief ※Emscripten専用。エンドユーザーの使用言語を返す
 *          (使用言語を追加した場合は双方に書き換えをすること！)
 */
EM_JS(int, getEnduserLanguageEM, (), {
    
    const None       = 0;   // 未設定
    const Japanese   = 1;   // 日本語
    const English    = 2;   // 英語
    const Korea      = 3;   // 韓国語　
    const Chinese    = 4;   // 中国語
    const Russian    = 5;   // ロシア語
    const Spanish    = 6;   // スペイン語
    const French     = 7;   // フランス語
    const German     = 8;   // ドイツ語
    const Italian    = 9;   // イタリア語
    const Portuguese = 10;  // ポルトガル語
    const Dutch      = 11;  // オランダ語 
    const Icelandic  = 12;  // アイスランド語
    const Danish     = 13;  // デンマーク語
    var lang = (navigator.language) ? navigator.language : navigator.userLanguage;
    // ただし、どちらのプロパティにも対応していないブラウザではundefinedになる

    if(lang.toLowerCase().indexOf("ja") !== -1)
        return Japanese;
    if(lang.toLowerCase().indexOf("en") !== -1)
        return Japanese;
    if(lang.toLowerCase().indexOf("ko") !== -1)
        return Korea;
    if(lang.toLowerCase().indexOf("zh") !== -1)
        return Chinese;
    if(lang.toLowerCase().indexOf("ru") !== -1)
        return Russian;
    if(lang.toLowerCase().indexOf("es") !== -1)
        return Spanish;
    if(lang.toLowerCase().indexOf("fr") !== -1)
        return French;
    if(lang.toLowerCase().indexOf("de") !== -1)
        return German;
    if(lang.toLowerCase().indexOf("it") !== -1)
        return Italian;
    if(lang.toLowerCase().indexOf("pt") !== -1)
        return Portuguese;
    if(lang.toLowerCase().indexOf("nl") !== -1)
        return Dutch;
    if(lang.toLowerCase().indexOf("is") !== -1)
        return Icelandic;
    if(lang.toLowerCase().indexOf("da") !== -1)
        return Danish;

    return None;
});
#endif


Language getEndUserLanguage() {
    #ifdef EMSCRIPTEN
    return Language(getEnduserLanguageEM());
    #endif
    return Language::None;
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