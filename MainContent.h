/**
 * @file MainContent.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief プラットフォーム共通のメインループ、メインの初期化をここに記述する。
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
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