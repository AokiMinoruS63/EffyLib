/**
 * @file GetBrowserSize.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ブラウザのみ使用。タッチコンポーネント。
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
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