/**
 * @file MainContent.h
 * @brief プラットフォーム共通のメインループ、メインの初期化をここに記述する。
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

	private:

	/**
	 * @brief 初期化
	 * 
	 * @return int エラーなら**kErrorCode**を返す
	 */
	int init() {
		if (DxLib_Init() == kErrorCode) {
			return kErrorCode;
		}
		#ifdef EMSCRIPTEN
		ChangeFont("07LogoTypeGothic7.ttf");
		#endif
		return kSuccessCode;
	}

	public:

	/**
	 * @brief 　メインループ
	 * 
	 */
	void run();
};