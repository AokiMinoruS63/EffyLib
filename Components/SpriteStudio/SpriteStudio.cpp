/**
 * @file SpriteStudio.cpp
 * @brief SpriteStudioの関数呼び出し
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudio.h"
#include "SpriteStudioManager.h"

using namespace SpriteStudio;

// MARK: - Player

// SpriteStudioのモーションPlayerを追加する
int Player::add(std::string path) {
	return SpriteStudioManager::shared()->addPlayer(path);
}

// SpriteStudioのモーションPlayerを削除する
int Player::remove(int handle) {
	return SpriteStudioManager::shared()->removePlayer(handle);
}

// 再生するssbpデータのdata_keyを設定します.
int Player::setData(int handle, const std::string& data_key) {
	return SpriteStudioManager::shared()->setPlayerData(handle, data_key);
}

// 再生しているssbpデータのdata_keyを取得します.
std::string Player::getPlayDataName(int handle) {
	return SpriteStudioManager::shared()->getPlayerPlayDataName(handle);
}

// 設定されているssbpデータを解放します.
int Player::releaseData(int handle) {
	return SpriteStudioManager::shared()->releasePlayerData(handle);
}

// 設定されているアニメーションを解放します.
int Player::releaseAnime(int handle) {
	return SpriteStudioManager::shared()->releasePlayerAnime(handle);
}

// 再生する
int Player::play(int handle, const std::string& ssae_name, const std::string& motion_name, int loop, int startFrameNo) {
	return SpriteStudioManager::shared()->playPlayer(handle, ssae_name, motion_name, loop, startFrameNo);
}

// 再生する
int Player::play(int handle, const std::string& anime_name, int loop, int start_frame_no) {
	return SpriteStudioManager::shared()->playPlayer(handle, anime_name, loop, start_frame_no);
}

// 再生を中断する
int Player::pauseAnimation(int handle) {
	return SpriteStudioManager::shared()->pausePlayerAnimation(handle);
}

// 再生を再開する
int Player::resumeAnimation(int handle) {
	return SpriteStudioManager::shared()->resumePlayerAnimation(handle);
}

// 再生を停止します.
int Player::stopAnimation(int handle) {
	return SpriteStudioManager::shared()->stopPlayerAnimation(handle);
}

// 再生しているアニメーションのパック名(ssae)を返します.
const std::string& Player::getPlayPackName(int handle) {
	return SpriteStudioManager::shared()->getPlayerPlayPackName(handle);
}

// 再生しているアニメーション名を返します.
const std::string& Player::getPlayAnimeName(int handle) {
	return SpriteStudioManager::shared()->getPlayerPlayAnimeName(handle);
}

// アニメーションの総フレームを取得します.
int Player::getMaxFrame(int handle) {
	return SpriteStudioManager::shared()->getPlayerMaxFrame(handle);
}

// 再生フレームNoを取得します.
int Player::getFrameNo(int handle) {
	return SpriteStudioManager::shared()->getPlayerFrameNo(handle);
}

// 再生フレームNoを設定します.
int Player::setFrameNo(int handle, int frame_no) {
	return SpriteStudioManager::shared()->setPlayerFrameNo(handle, frame_no);
}

// 再生スピードを取得します. 
float Player::getStep(int handle){
	return SpriteStudioManager::shared()->getPlayerStep(handle);
}

// 再生スピードを設定します. 
int Player::setStep(int handle, float step) {
	return SpriteStudioManager::shared()->setPlayerStep(handle, step);
}

// 指定されている再生ループ回数を取得します. 
int Player::getLoop(int handle) {
	return SpriteStudioManager::shared()->getPlayerLoop(handle);
}

// 再生ループ回数を設定します. 
int Player::setLoop(int handle, int loop) {
	return SpriteStudioManager::shared()->setPlayerLoop(handle, loop);
}

// 現在までのループ再生回数を取得します.
int Player::getLoopCount(int handle) {
	return SpriteStudioManager::shared()->getPlayerLoopCount(handle);
}

// 現在までのループ再生回数をクリアします.
int Player::clearLoopCount(int handle) {
	return SpriteStudioManager::shared()->clearPlayerLoopCount(handle);
}

// フレームスキップ（フレームレートに合わせ再生フレームをスキップする）の設定をします. (default: true)
int Player::setFrameSkipEnabled(int handle, bool enabled) {
	return SpriteStudioManager::shared()->setPlayerFrameSkipEnabled(handle, enabled);
}

// フレームスキップの設定状態を返します.
bool Player::isFrameSkipEnabled(int handle) {
	return SpriteStudioManager::shared()->isPlayerFrameSkipEnabled(handle);
}

// ラベル名からフレーム位置を取得します.
int Player::getLabelToFrame(int handle, char* find_label_name) {
	return SpriteStudioManager::shared()->getPlayerLabelToFrame(handle, find_label_name);
}

// 再生しているアニメーションに含まれるパーツ数を取得します.
int Player::getPartsCount(int handle) {
	return SpriteStudioManager::shared()->getPlayerPartsCount(handle);
}

// indexからパーツ名を取得します.
const char* Player::getPartName(int handle, int part_id) {
	return SpriteStudioManager::shared()->getPlayerPartName(handle, part_id);
}

// パーツ名からindexを取得します.
int Player::getIndexOfPart(int handle, const char* part_name) {
	return SpriteStudioManager::shared()->getPlayerIndexOfPart(handle, part_name);
}

// パーツの名から、パーツ情報を取得します.
int Player::getPartState(int handle, SpriteStudioResult& result, const char* name, int frame_no) {
	return SpriteStudioManager::shared()->getPlayerPartState(handle, result, name, frame_no);
}

// パーツ名からパーツの表示、非表示を設定します.
int Player::setPartVisible(int handle, std::string parts_name, bool is_visible) {
	return SpriteStudioManager::shared()->setPlayerPartVisible(handle, parts_name, is_visible);
}

// パーツ名からパーツに割り当たるセルを変更します.
int Player::setPartCell(int handle, std::string parts_name, std::string ssce_name, std::string cell_name) {
	return SpriteStudioManager::shared()->setPlayerPartCell(handle, parts_name, ssce_name, cell_name);
}

// 座標をセットする
int Player::setPosition(int handle, float x, float y) {
	return SpriteStudioManager::shared()->setPlayerPosition(handle, x, y);
}

// 回転率をセットする
int Player::setRotation(int handle, float z) {
	return SpriteStudioManager::shared()->setPlayerRotation(handle, z);
}

// 回転率をセットする
int Player::setRotation(int handle, float x, float y, float z) {
	return SpriteStudioManager::shared()->setPlayerRotation(handle, x, y, z);
}

// 拡大率をセットする
int Player::setScale(int handle, float scale) {
	return SpriteStudioManager::shared()->setPlayerScale(handle, scale);
}

// 拡大率をセットする
int Player::setScale(int handle, float scale_x, float scale_y) {
	return SpriteStudioManager::shared()->setPlayerScale(handle, scale_x, scale_y);
}

// 透過値をセットする
int Player::setAlpha(int handle, float alpha) {
	return SpriteStudioManager::shared()->setPlayerAlpha(handle, alpha);
}

// アニメの輝度を設定します.
int Player::setColor(int handle, int r, int g, int b) {
	return SpriteStudioManager::shared()->setPlayerColor(handle, r, g, b);
}

// 名前を指定してパーツの再生するインスタンスアニメを変更します。
int Player::changeInstanceAnime(int handle, std::string parts_name, std::string anime_name, bool over_write, SpriteStudioInstance key_param) {
	return SpriteStudioManager::shared()->changePlayerInstanceAnime(handle, parts_name, anime_name, over_write, key_param);
}

// プレイヤーにインスタンスパラメータを設定します。
int Player::setInstanceParam(int handle, bool over_write, SpriteStudioInstance key_param) {
	return SpriteStudioManager::shared()->setPlayerInstanceParam(handle, over_write, key_param);
}

// プレイヤーからインスタンスパラメータを取得します。
int Player::getInstanceParam(int handle, bool *over_write, SpriteStudioInstance *key_param) {
	return SpriteStudioManager::shared()->getPlayerInstanceParam(handle, over_write, key_param);
}

// アニメーションのループ範囲（再生位置）を上書きします。
int Player::setStartFrame(int handle, int frame) {
	return SpriteStudioManager::shared()->setPlayerStartFrame(handle, frame);
}

// アニメーションのループ範囲（終了位置）を上書きします。
int Player::setEndFrame(int handle, int frame) {
	return SpriteStudioManager::shared()->setPlayerEndFrame(handle, frame);
}

// アニメーションのループ範囲（再生位置）を上書きします。
int Player::setStartFrameToLabelName(int handle, char *label_name) {
	return SpriteStudioManager::shared()->setPlayerStartFrameToLabelName(handle, label_name);
}

// アニメーションのループ範囲（終了位置）を上書きします。
int Player::setEndFrameToLabelName(int handle, char *label_name) {
	return SpriteStudioManager::shared()->setPlayerEndFrameToLabelName(handle, label_name);
}

// 表示を行うパーツ数を取得します
int Player::getDrawSpriteCount(int handle) {
	return SpriteStudioManager::shared()->getPlayerDrawSpriteCount(handle);
}

// 反転する
int Player::setFlip(int handle, bool flip_x, bool flip_y) {
	return SpriteStudioManager::shared()->setPlayerFlip(handle, flip_x, flip_y);
}

// 時間を進める
int Player::update(int handle, float dt) {
	return SpriteStudioManager::shared()->updatePlayer(handle, dt);
}

// 描画する
int Player::draw(int handle) {
	return SpriteStudioManager::shared()->drawPlayer(handle);
}
