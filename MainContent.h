/**
 * @file MainContent.h
 * @brief プラットフォーム共通のメインループ、メインの初期化をここに記述する。
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include <EffyLib.h>

class MainContent {
	/* インスタンス */
	private:
	TouchMgr* touchMgr_;
	BMFontMgr* bmFontMgr_;
	PhysicusWorld* world_;
	
	/* コンストラクタ・デストラクタ */
	public:
	MainContent();
	~MainContent();

	/* 関数 */

	/**
	 * @brief 　メインループ
	 * 
	 */
	void run();
};