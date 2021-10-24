/* 
 * File:   Main
 * Author: nokotan
 *
 * Created on 2020/01/30, 0:57
 * 
 * DxLibToHTML5雛形ファイル
 */

#include <DxLib.h>
#include "MainContent.h"
#ifdef EMSCRIPTEN
#  include <emscripten.h>
#endif

static bool shouldExit = false;
MainContent* mainContent;

void mainLoop() {
	if (ProcessMessage() == -1) {
		shouldExit = true;
	}
	mainContent->run();
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main () {
#endif
// Emscriptenは非同期読み込み不可のようなのでそれ以外の時のみ使用する
#ifndef EMSCRIPTEN
	// 非同期読み込みモードオン
	SetUseASyncLoadFlag( TRUE ) ;
#endif
	mainContent = new MainContent();

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(mainLoop, 0, 1);	
#else
    while (!shouldExit) {
		mainLoop();
    }
    
    DxLib_End();
 #endif

    return 0;
}