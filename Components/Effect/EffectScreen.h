/**
 * @file EffectScreen.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EFFECT_SCREEN_H
#define EFFECT_SCREEN_H

// エフェクト用のスクリーン
class EffectScreen {

	// MARK: 定数

	public:
	// 1/kGaussRatioの大きさのスクリーンにする
	static const int kGaussRatio = 2;

	// MARK: 変数

	private:
	// 塗りつぶしスクリーン
	int fill_screen_;
	// 縁を描画するためのスクリーン
	int edge_screen_;
	// ガウス用のスクリーン
	int gauss_screen_;

	// バッファとして保存している明るさ情報
	Color::Color buf_bright_;

	// バッファとして保存しているブレンド情報
	BlendMode::Property buf_blend_;

	// バッファとして保存している線形補完情報
	int liner_inter_polation_;

	// MARK: コンストラクタ・デストラクタ

	public:
	EffectScreen();
	~EffectScreen();

	// MARK: Getter, Setter

	/**
	 * @brief 縁を描画するためのスクリーンの取得
	 * 
	 * @return int 
	 */
	int getEdgeScreen();
	
	/**
	 * @brief 塗りつぶし用のスクリーンの取得
	 * 
	 * @return int 
	 */
	int getFillScreen();

	/**
	 * @brief ガウス用のスクリーンの取得
	 * 
	 * @return int 
	 */
	int getGaussScreen();

	// MARK: 画面の明るさ情報、ブレンド情報の読み込み・保存

	private:
	/**
	 * @brief 明るさ情報の読み込み
	 * 
	 * @return int 
	 */
	int loadBright();

	/**
	 * @brief 明るさ情報の保存
	 * 
	 * @return int 
	 */
	int saveBright();

	/**
	 * @brief ブレンド情報の読み込み
	 * 
	 * @return int 
	 */
	int loadBlend();

	/**
	 * @brief ブレンド情報の保存
	 * 
	 * @return int 
	 */
	int saveBlend();

	/**
	 * @brief 線形補完情報の読み込み
	 * 
	 * @return int 
	 */
	int loadLinerInterPolation();

	/**
	 * @brief 線形補完情報の保存
	 * 
	 * @return int 
	 */
	int saveLinerInterPolation();

	public:

	/**
	 * @brief スクリーン情報のバッファからの読み込み
	 * 
	 * @return int 
	 */
	int loadScreenState();

	/**
	 * @brief スクリーン情報のバッファへの保存
	 * 
	 * @return int 
	 */
	int saveScreenState();
};

#endif