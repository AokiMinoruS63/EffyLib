/**
 * @file GetBrowserSize.h
 * @brief ブラウザのみ使用。タッチコンポーネント。
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */


#ifndef GET_BROWSER_SIZE_H
#define GET_BROWSER_SIZE_H

#ifdef EMSCRIPTEN
#include <emscripten.h>

/**
 * @brief キャンバスの幅を取得する関数(正確なマウス座標を取得するのに使用)
 * @return キャンバスの幅を返す(int)
 */
EM_JS(int, getBrowserCanvasWidthEM, (), {
  return document.getElementById('canvas').clientWidth;
});

/**
 * @brief キャンバスの高さを取得する関数(正確なマウス座標を取得するのに使用)
 * @return キャンバスの高さを返す(int)
 */
EM_JS(int, getBrowserCanvasHeightEM, (), {
  return document.getElementById('canvas').clientHeight;
});

/**
 * @brief ブラウザが横幅の方が縦幅より長いかどうかを返す
 * @return 幅が高さより長いならtrue
 */
EM_JS(int, isBrowserLandscapeEM, (), {
  if(document.body.clientWidth<document.body.clientHeight){return 0;}
  return 1;
});

#endif
#endif