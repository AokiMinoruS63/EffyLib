/**
 * @file SpriteStudio.h
 * @brief SpriteStudioの関数呼び出し
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef SPRITE_STUDIO_H
#define SPRITE_STUDIO_H

#include <string>
#include "SpriteStudioResult.h"
#include "SpriteStudioInstance.h"

namespace SpriteStudio {

	namespace Player {
		/**
		 * @brief SpriteStudioのモーションPlayerを追加する
		 * 
		 * @param path ファイルパス＋(ssbpファイル名 or ssproj名)
		 * @return int アクセスハンドル
		 */
		int add(std::string path);

		/**
		 * @brief SpriteStudioのモーションPlayerを削除する
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int remove(int handle);

		/**
		 * @brief 再生するssbpデータのdataKeyを設定します.
		 *
		 * @param handle アクセスハンドル
		 * @param  dataKey  再生するデータのdataKey
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setData(int handle, const std::string& dataKey);

		/**
		 * @brief 再生しているssbpデータのdataKeyを取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @return 再生しているssbp名
		 */
		std::string getPlayDataName(int handle);

		/**
		 * @brief 設定されているssbpデータを解放します.
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int releaseData(int handle);

		/**
		 * @brief 設定されているアニメーションを解放します.
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int releaseAnime(int handle);

		/**
		 * @brief 再生する
		 * 
		 * @param handle アクセスハンドル
		 * @param ssae_name パック名(ssae名）
		 * @param motion_name 再生するモーション名
		 * @param loop 再生ループ数の指定. 省略時は0
		 * @param start_frame_no 再生を開始するフレームNoの指定. 省略時は0
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int play(int handle, const std::string& ssae_name, const std::string& motion_name, int loop = 0, int startFrameNo = 0);

		/**
		 * @brief 再生する
		 * 
		 * @param handle アクセスハンドル
		 * @param anime_name パック名(ssae名/アニメーション名）
		 * @param motion_name 再生するモーション名
		 * @param loop 再生ループ数の指定. 省略時は0
		 * @param start_frame_no 再生を開始するフレームNoの指定. 省略時は0
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int play(int handle, const std::string& anime_name, int loop = 0, int start_frame_no = 0);

		/**
		 * @brief 再生を中断する
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int pauseAnimation(int handle);

		/**
		 * @brief 再生を再開する
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int resumeAnimation(int handle);

		/**
		 * @brief 再生を停止します.
		 * ゲーム側でアニメーションの表示フレームを制御する場合はstop()を呼び出した後
		 * ゲーム側の更新処理でsetFrameNo()を呼び出し指定のフレームを表示してください。
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int stopAnimation(int handle);

		/**
		 * @brief 再生しているアニメーションのパック名(ssae)を返します.
		 * 
		 * @param handle アクセスハンドル
		 * @return const std::string& パック名(ssae)
		 */
		const std::string& getPlayPackName(int handle);

		/**
		 * @brief 再生しているアニメーション名を返します.
		 * 
		 * @param handle アクセスハンドル
		 * @return const std::string& アニメーション名
		 */
		const std::string& getPlayAnimeName(int handle);

		/**
		 * @brief アニメーションの総フレームを取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @return 総フレーム
		 */
		int getMaxFrame(int handle);

		/**
		 * @brief 再生フレームNoを取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @return int 再生フレームNo. frame no.
		 */
		int getFrameNo(int handle);

		/**
		 * @brief 再生フレームNoを設定します.
		 * 
		 * @param handle アクセスハンドル
		 * @param frame_no 再生フレームNo. frame no.
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setFrameNo(int handle, int frame_no);

		/**
		 * @brief 再生スピードを取得します. 
		 * 
		 * @param handle アクセスハンドル
		 * @return float (1.0f:標準)
		 */
		float getStep(int handle);

		/**
		 * @brief 再生スピードを設定します. 
		 * 
		 * @param handle アクセスハンドル
		 * @param step (1.0f:標準)
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setStep(int handle, float step);

		/**
		 * @brief 指定されている再生ループ回数を取得します. 
		 * 
		 * @param handle アクセスハンドル
		 * @return int ループ回数(0:指定なし)
		 */
		int getLoop(int handle);

		/**
		 * @brief 再生ループ回数を設定します. 
		 * 
		 * @param handle アクセスハンドル
		 * @param loop ループ回数(0:指定なし)
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setLoop(int handle, int loop);

		/**
		 * @brief 現在までのループ再生回数を取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @return int ループ回数
		 */
		int getLoopCount(int handle);

		/**
		 * @brief 現在までのループ再生回数をクリアします.
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int clearLoopCount(int handle);

		/**
		 * @brief フレームスキップ（フレームレートに合わせ再生フレームをスキップする）の設定をします. (default: true)
		 * 
		 * @param handle アクセスハンドル
		 * @param enabled スキップするなら**true**
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setFrameSkipEnabled(int handle, bool enabled);

		/**
		 * @brief フレームスキップの設定状態を返します.
		 * 
		 * @param handle アクセスハンドル
		 * @return true スキップする
		 * @return false スキップしない
		 */
		bool isFrameSkipEnabled(int handle);

		/**
		 * @brief ラベル名からフレーム位置を取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @param find_label_name ラベル名
		 * @return int フレーム位置
		 */
		int getLabelToFrame(int handle, char* find_label_name);

		/**
		 * @brief 再生しているアニメーションに含まれるパーツ数を取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @return int パーツ数
		 */
		int getPartsCount(int handle);

		/**
		 * @brief indexからパーツ名を取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @param part_id パーツインデックス
		 * @return const char* パーツ名
		 */
		const char* getPartName(int handle, int part_id);

		/**
		 * @brief パーツ名からindexを取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @param part_name パーツ名
		 * @return int パーツインデックス
		 */
		int getIndexOfPart(int handle, const char* part_name);

		/**
		 * @brief パーツの名から、パーツ情報を取得します.
		 * 
		 * @param handle アクセスハンドル
		 * @param result パーツ情報を受け取るバッファ
		 * @param name 取得するパーツ名
		 * @param frame_no 取得するフレーム番号 -1の場合は現在再生しているフレームが適用される
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int getPartState(int handle, SpriteStudioResult& result, const char* name, int frame_no = -1);

		/**
		 * @brief パーツ名からパーツの表示、非表示を設定します.
		 * コリジョン用のパーツや差し替えグラフィック等、SS5上で表示を行うがゲーム中では非表示にする場合に使用します。
		 * SSの非表示アトリビュート設定するわけではないので注意してください。
		 * 
		 * @param handle アクセスハンドル
		 * @param parts_name パーツ名
		 * @param is_visible 表示するなら**true**
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setPartVisible(int handle, std::string parts_name, bool is_visible);

		/**
		 * @brief パーツ名からパーツに割り当たるセルを変更します.
		 * この関数で設定したパーツは参照セルアトリビュートの影響をうけません。
		 * アニメに設定されたセルに戻す場合は、セル名に""を指定してください。
		 * 
		 * @param handle アクセスハンドル
		 * @param parts_name パーツ名
		 * @param ssce_name セルマップ名
		 * @param cell_name 表示させたいセル名
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setPartCell(int handle, std::string parts_name, std::string ssce_name, std::string cell_name);

		/**
		 * @brief 座標をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param x X座標
		 * @param y Y座標
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setPosition(int handle, float x, float y);

		/**
		 * @brief 回転率をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param z Z軸回転角度
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setRotation(int handle, float z);

		/**
		 * @brief 回転率をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param x X軸回転角度
		 * @param y Y軸回転角度
		 * @param z Z軸回転角度
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setRotation(int handle, float x, float y, float z);

		/**
		 * @brief 拡大率をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param scale 拡大率
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setScale(int handle, float scale);

		/**
		 * @brief 拡大率をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param scale_x X拡大率
		 * @param scale_y Y拡大率
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setScale(int handle, float scale_x, float scale_y);

		/**
		 * @brief 透過値をセットする
		 * 
		 * @param handle アクセスハンドル
		 * @param alpha 0.0〜1.0まで透明度を指定する(０が透明)
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setAlpha(int handle, float alpha);

		/**
		 * @brief アニメの輝度を設定します.
		 * setColor(Color3B)ではなくこちらを使用してください。
		 * 制限としてカラーブレンドが適用されたパーツの色は変更できませんので注意してください。
		 * 
		 * @param handle アクセスハンドル
		 * @param r 赤成分(0～255)
		 * @param g 緑成分(0～255)
		 * @param b 青成分(0～255)
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setColor(int handle, int r, int g, int b);

		/**
		 * @brief 名前を指定してパーツの再生するインスタンスアニメを変更します。
		 * 指定したパーツがインスタンスパーツでない場合、falseを返します.
		 * インスタンスパーツ名はディフォルトでは「ssae名:モーション名」とつけられています。
		 * 再生するアニメの名前は"ssae名/アニメーション名"として再生してください。
		 * 現在再生しているアニメを指定することは入れ子となり無限ループとなるためできません。
		 * 変更するアニメーションは同じssbpに含まれる必要があります。
		 * 
		 * @param handle アクセスハンドル
		 * @param parts_name SS上のパーツ名
		 * @param anime_name 参照するアニメ名
		 * @param over_write インスタンスキーの上書きフラグ
		 * @param key_param インスタンスキーのパラメータ
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int changeInstanceAnime(int handle, std::string parts_name, std::string anime_name, bool over_write, SpriteStudioInstance key_param);

		/**
		 * @brief プレイヤーにインスタンスパラメータを設定します。
		 * 
		 * @param handle アクセスハンドル
		 * @param over_write インスタンスキーの上書きフラグ
		 * @param key_param インスタンスキーのパラメータ
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setInstanceParam(int handle, bool over_write, SpriteStudioInstance key_param);

		/**
		 * @brief プレイヤーからインスタンスパラメータを取得します。
		 * 
		 * @param handle アクセスハンドル
		 * @param over_write インスタンスキーの上書きフラグ
		 * @param key_param インスタンスキーのパラメータ
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int getInstanceParam(int handle, bool *over_write, SpriteStudioInstance *key_param);

		/**
		 * @brief アニメーションのループ範囲（再生位置）を上書きします。
		 * 
		 * @param handle アクセスハンドル
		 * @param frame 開始フレーム（-1で上書き解除）
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setStartFrame(int handle, int frame);

		/**
		 * @brief アニメーションのループ範囲（終了位置）を上書きします。
		 * SpriteStudioのフレーム数+1を設定してください。
		 * 
		 * @param handle アクセスハンドル
		 * @param frame 終了フレーム（-1で上書き解除）
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setEndFrame(int handle, int frame);

		/**
		 * @brief アニメーションのループ範囲（再生位置）を上書きします。
		 * 
		 * @param handle アクセスハンドル
		 * @param label_name 開始フレームとなるラベル名（""で上書き解除）
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setStartFrameToLabelName(int handle, char *label_name);

		/**
		 * @brief アニメーションのループ範囲（終了位置）を上書きします。
		 * 
		 * @param handle アクセスハンドル
		 * @param label_name 終了フレームとなるラベル名（""で上書き解除）
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setEndFrameToLabelName(int handle, char *label_name);

		/**
		 * @brief 表示を行うパーツ数を取得します
		 * 
		 * @param handle アクセスハンドル
		 * @return int パーツ数
		 */
		int getDrawSpriteCount(int handle);

		/**
		 * @brief 反転する
		 * 
		 * @param handle アクセスハンドル
		 * @param flip_x X軸で反転するなら**true**
		 * @param flip_y Y軸で反転するなら**true**
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int setFlip(int handle, bool flip_x, bool flip_y);

		/**
		 * @brief 時間を進める
		 * 
		 * @param handle アクセスハンドル
		 * @param dt 進める時間(ミリ秒経過時間)
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int update(int handle, float dt);

		/**
		 * @brief 描画する
		 * 
		 * @param handle アクセスハンドル
		 * @return int 成功…kSuccessCode, 失敗…kErrorCode
		 */
		int draw(int handle);
	}
}

#endif
