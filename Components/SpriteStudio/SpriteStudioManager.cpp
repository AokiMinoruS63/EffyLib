/**
 * @file SpriteManager.cpp
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include "SpriteStudioManager.h"
#include "../OpenSource/ssbpLib/SS5Player.h"
#include "../Utility/TypeExtensions/String+Extensions.h"

// コンストラクタ
SpriteStudioManager::SpriteStudioManager() {
}

// デストラクタ
SpriteStudioManager::~SpriteStudioManager() {
}

// SpriteStudioのモーションPlayerを追加する
int SpriteStudioManager::addPlayer(std::string path) {
	ss::Player* player = ss::Player::create();
	if(player == NULL) {
		return kErrorCode;
	}
	ss::ResourceManager::getInstance()->addData(path);
	
	player->setData(StringExtension::extractFileName(path));
	return setHashData(player);
}

// SpriteStudioのモーションPlayerを削除する
int SpriteStudioManager::removePlayer(int handle) {
	removeHashData(handle);
	return kSuccessCode;
}

// 再生するssbpデータのdata_keyを設定します.
int SpriteStudioManager::setPlayerData(int handle, const std::string& data_key) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setData(data_key);
	return kSuccessCode;
}

// 再生しているssbpデータのdataKeyを取得します.
std::string SpriteStudioManager::getPlayerPlayDataName(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return "";
	}
	return player->getPlayDataName();
}

// 設定されているssbpデータを解放します.
int SpriteStudioManager::releasePlayerData(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->releaseData();
	return kSuccessCode;
}

// 設定されているアニメーションを解放します.
int SpriteStudioManager::releasePlayerAnime(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->releaseAnime();
	return kSuccessCode;
}

// 再生する
int SpriteStudioManager::playPlayer(int handle, const std::string& ssae_name, const std::string& motion_name, int loop, int start_frame_no) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->play(ssae_name, motion_name, loop, start_frame_no);
	return kSuccessCode;
}

// 再生する
int SpriteStudioManager::playPlayer(int handle, const std::string& anime_name, int loop, int start_frame_no) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->play(anime_name, loop, start_frame_no);
	return kSuccessCode;
}

// 再生を中断する
int SpriteStudioManager::pausePlayerAnimation(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->animePause();
	return kSuccessCode;
}

// 再生を再開する
int SpriteStudioManager::resumePlayerAnimation(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->animeResume();
	return kSuccessCode;
}

// 再生を停止します.
int SpriteStudioManager::stopPlayerAnimation(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->stop();
	return kSuccessCode;
}

static const std::string s_nullString = "";

// 再生しているアニメーションのパック名(ssae)を返します.
const std::string& SpriteStudioManager::getPlayerPlayPackName(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return s_nullString;
	}
	return player->getPlayPackName();
}

// ssbpファイルに含まれるアニメーション名のリストを返す
std::vector<std::string> SpriteStudioManager::getPlayerAnimeName(int handle, std::string ssae_name) {
	ss::Player *player = getHashData(handle);
	std::string dataName = player == NULL ? "" : player->getPlayDataName();
	std::vector<std::string> list = ss::ResourceManager::getInstance()->getAnimeName(dataName);
	if (ssae_name == "") {
		return list;
	}
	std::vector<std::string> filter_list;
	const std::string check = ssae_name + "/";
	for (const auto& e : list) {
		if (e.size() >= check.size() && std::equal(std::begin(check), std::end(check), std::begin(e))) {
			filter_list.push_back(e);
		}
	}
	return filter_list;
}

// 再生しているアニメーション名を返します.
const std::string& SpriteStudioManager::getPlayerPlayAnimeName(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return s_nullString;
	}
	return player->getPlayAnimeName();
}

// アニメーションの総フレームを取得します.
int SpriteStudioManager::getPlayerMaxFrame(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getMaxFrame();
}

// 再生フレームNoを取得します.
int SpriteStudioManager::getPlayerFrameNo(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getFrameNo();
}

// フレームサイズを取得する
int SpriteStudioManager::getPlayerFrameSize(int handle, int* width, int* height) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	return player->getFrameSize(width, height);
}

// プレイヤーのアニメーションがセットされているかチェックする
int SpriteStudioManager::isPlayerAnimation(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	return player->isAnimation() ? 1 : 0;
}

// 再生フレームNoを設定します.
int SpriteStudioManager::setPlayerFrameNo(int handle, int frame_no) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setFrameNo(frame_no);
	return kSuccessCode;
}

// 再生中のPlayerに座標などの設定値を反映させる
int SpriteStudioManager::applyPlayer(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->apply();
	return kSuccessCode;
}

// 再生スピードを取得します. 
float SpriteStudioManager::getPlayerStep(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 1.0;
	}
	return player->getStep();
}

// 再生スピードを設定します. 
int SpriteStudioManager::setPlayerStep(int handle, float step) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setStep(step);
	return kSuccessCode;
}

// 指定されている再生ループ回数を取得します. 
int SpriteStudioManager::getPlayerLoop(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getLoop();
}

// 再生ループ回数を設定します. 
int SpriteStudioManager::setPlayerLoop(int handle, int loop) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setLoop(loop);
	return kSuccessCode;
}

// 現在までのループ再生回数を取得します.
int SpriteStudioManager::getPlayerLoopCount(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getLoopCount();
}

// 現在までのループ再生回数をクリアします.
int SpriteStudioManager::clearPlayerLoopCount(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->clearLoopCount();
	return kSuccessCode;
}

// フレームスキップ（フレームレートに合わせ再生フレームをスキップする）の設定をします. (default: true)
int SpriteStudioManager::setPlayerFrameSkipEnabled(int handle, bool enabled) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setFrameSkipEnabled(enabled);
	return kSuccessCode;
}

// フレームスキップの設定状態を返します.
bool SpriteStudioManager::isPlayerFrameSkipEnabled(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return true;
	}
	return player->isFrameSkipEnabled();
}

// ラベル名からフレーム位置を取得します.
int SpriteStudioManager::getPlayerLabelToFrame(int handle, char* find_label_name) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getLabelToFrame(find_label_name);
}

// 再生しているアニメーションに含まれるパーツ数を取得します.
int SpriteStudioManager::getPlayerPartsCount(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return 0;
	}
	return player->getPartsCount();
}

// indexからパーツ名を取得します.
const char* SpriteStudioManager::getPlayerPartName(int handle, int part_id) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return "";
	}
	return player->getPartName(part_id);
}

// パーツ名からindexを取得します.
int SpriteStudioManager::getPlayerIndexOfPart(int handle, const char* part_name) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	return player->indexOfPart(part_name);
}

/**
 * @brief ss::ResluteStateのパーツ情報をSpriteStudioResultに代入する
 * 
 * @param result EffyLib側で管理しているSpriteStudioのパーツ情報
 * @param state ssbpLib側で管理しているSpriteStudioのパーツ情報
 */
void convertPartState(SpriteStudioResult& result, ss::ResluteState state) {
	result.flags = state.flags;
	result.cellIndex = state.cellIndex;
	result.x = state.x;
	result.y = state.y;
	result.z = state.z;
	result.pivotX = state.pivotX;
	result.pivotY = state.pivotY;
	result.rotationX = state.rotationX;
	result.rotationY = state.rotationY;
	result.rotationZ = state.rotationZ;
	result.scaleX = state.scaleX;
	result.scaleY = state.scaleY;
	result.opacity = state.opacity;
	result.size_X = state.size_X;
	result.size_Y = state.size_Y;
	result.uv_move_X = state.uv_move_X;
	result.uv_move_Y = state.uv_move_Y;
	result.uv_rotation = state.uv_rotation;
	result.uv_scale_X = state.uv_scale_X;
	result.uv_scale_Y = state.uv_scale_Y;
	result.boundingRadius = state.boundingRadius;
	result.colorBlendFunc = state.colorBlendFunc;
	result.colorBlendType = state.colorBlendType;
	result.flipX = state.flipX;
	result.flipY = state.flipY;
	result.isVisibled = state.isVisibled;

	result.part_type = state.part_type;
	result.part_boundsType = state.part_boundsType;
	result.part_alphaBlendType = state.part_alphaBlendType;
	result.part_labelcolor = state.part_labelcolor;
	result.parent_index = state.parent_index;
}

// パーツの名から、パーツ情報を取得します.
int SpriteStudioManager::getPlayerPartState(int handle, SpriteStudioResult& result, const char* name, int frame_no) {
	ss::Player *player = getHashData(handle);
	if(player == NULL ) {
		return kErrorCode;
	}
	ss::ResluteState state = ss::ResluteState();
	bool is_success = player->getPartState(state, name, frame_no);
	// 失敗したらエラーを返す
	if(!is_success) {
		result = SpriteStudioResult();
		return kErrorCode;
	}
	// ssbpLib側で管理しているSpriteStudioのパーツ情報からEffyLib側で管理しているSpriteStudioのパーツ情報に変換
	convertPartState(result, state);

	return kSuccessCode;
}

// パーツインデックスから、パーツ情報を取得します.
int SpriteStudioManager::getPlayerPartState(int handle, SpriteStudioResult& result, const int index, int frame_no) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	ss::ResluteState state = ss::ResluteState();
	bool is_success = player->getPartState(state, index, frame_no);
	// 失敗したらエラーを返す
	if(!is_success) {
		result = SpriteStudioResult();
		return kErrorCode;
	}

	// ssbpLib側で管理しているSpriteStudioのパーツ情報からEffyLib側で管理しているSpriteStudioのパーツ情報に変換
	convertPartState(result, state);

	return kSuccessCode;
}

// パーツ名からパーツの表示、非表示を設定します.
int SpriteStudioManager::setPlayerPartVisible(int handle, std::string parts_name, bool is_visible) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setPartVisible(parts_name, is_visible);
	return kSuccessCode;
}

// パーツ名からパーツに割り当たるセルを変更します.
int SpriteStudioManager::setPlayerPartCell(int handle, std::string parts_name, std::string ssce_name, std::string cell_name) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setPartCell(parts_name, ssce_name, cell_name);
	return kSuccessCode;
}

// 座標を取得する
int SpriteStudioManager::getPlayerPosition(int handle, float *x, float *y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->getPosition(x, y);
	return kSuccessCode;
}

// SpriteStudioのモーションPlayerの座標をセットする
int SpriteStudioManager::setPlayerPosition(int handle, float x, float y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setPosition(x, y);
	return kSuccessCode;
}

// SpriteStudioのモーションPlayerの回転率を取得する
int SpriteStudioManager::getPlayerRotation(int handle, float *z) {
	float x, y;
	return getPlayerRotation(handle, &x, &y, z);
}

// SpriteStudioのモーションPlayerの回転率を取得する
int SpriteStudioManager::getPlayerRotation(int handle, float *x, float *y, float *z) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->getRotation(x, y, z);
	return kSuccessCode;
}

// SpriteStudioのモーションPlayerの回転率をセットする
int SpriteStudioManager::setPlayerRotation(int handle, float z) {
	return setPlayerRotation(handle, 0.0f, 0.0f, z);
}

// SpriteStudioのモーションPlayerの回転率をセットする
int SpriteStudioManager::setPlayerRotation(int handle, float x, float y, float z) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setRotation(x, y, z);
	return kSuccessCode;
}

// 拡大率を取得する
int SpriteStudioManager::getPlayerScale(int handle, float *scale_x, float *scale_y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->getScale(scale_x, scale_y);
	return kSuccessCode;
}

// SpriteStudioのモーションPlayerの拡大率をセットする
int SpriteStudioManager::setPlayerScale(int handle, float scale) {
	return setPlayerScale(handle, scale, scale);
}

// SpriteStudioのモーションPlayerの拡大率をセットする
int SpriteStudioManager::setPlayerScale(int handle, float scale_x, float scale_y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setScale(scale_x, scale_y);
	return kSuccessCode;
}

// 透過値を取得する
int SpriteStudioManager::getPlayerAlpha(int handle, float *alpha) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	int alpha_float;
	player->getAlpha(&alpha_float);
	*alpha = alpha_float == 0 ? 0.0 : ((float)alpha_float) / 255.0;
	return kSuccessCode;
}

// SpriteStudioのモーションPlayerの透過値をセットする
int SpriteStudioManager::setPlayerAlpha(int handle, float alpha) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setAlpha((int)((float)alpha * 255.0));
	return kSuccessCode;
}

// アニメの輝度を取得します.
int SpriteStudioManager::getPlayerColor(int handle, int *r, int *g, int *b) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->getColor(r, g, b);
	return kSuccessCode;
}

// アニメの輝度を設定します.
int SpriteStudioManager::setPlayerColor(int handle, int r, int g, int b) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setColor(r, g, b);
	return kSuccessCode;
}

/**
 * @brief SpriteStudioのInstanceからss::Instanceへの変換
 * 
 * @param key_param SpriteStudioInstance
 * @return ss::Instance 
 */
ss::Instance convertInstance(SpriteStudioInstance key_param) {
	ss::Instance instance;
	instance.refStartframe = key_param.refStartframe;
	instance.refEndframe = key_param.refEndframe;
	instance.refSpeed = key_param.refSpeed;
	instance.refloopNum = key_param.refloopNum;
	instance.infinity = key_param.infinity;
	instance.reverse = key_param.reverse;
	instance.pingpong = key_param.pingpong;
	instance.independent = key_param.independent;
	return instance;
}

// 名前を指定してパーツの再生するインスタンスアニメを変更します。
int SpriteStudioManager::changePlayerInstanceAnime(int handle, std::string parts_name, std::string anime_name, bool over_write, SpriteStudioInstance key_param) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	ss::Instance instance = convertInstance(key_param);
	return player->changeInstanceAnime(parts_name, anime_name, over_write, instance) ? kSuccessCode : kErrorCode;
}

// プレイヤーにインスタンスパラメータを設定します。
int SpriteStudioManager::setPlayerInstanceParam(int handle, bool over_write, SpriteStudioInstance key_param) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	ss::Instance instance = convertInstance(key_param);
	player->setInstanceParam(over_write, instance);
	return kSuccessCode;
}

// プレイヤーからインスタンスパラメータを取得します。
int SpriteStudioManager::getPlayerInstanceParam(int handle, bool *over_write, SpriteStudioInstance *key_param) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	ss::Instance instance;
	player->getInstanceParam(over_write, &instance);
	key_param->refStartframe = instance.refStartframe;
	key_param->refEndframe = instance.refEndframe;
	key_param->refSpeed = instance.refSpeed;
	key_param->refloopNum = instance.refloopNum;
	key_param->infinity = instance.infinity;
	key_param->reverse = instance.reverse;
	key_param->pingpong = instance.pingpong;
	key_param->independent = instance.independent;

	return kSuccessCode;
}

// アニメーションのループ範囲（再生位置）を上書きします。
int SpriteStudioManager::setPlayerStartFrame(int handle, int frame) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setStartFrame(frame);
	return kSuccessCode;
}

// アニメーションのループ範囲（終了位置）を上書きします。
int SpriteStudioManager::setPlayerEndFrame(int handle, int frame) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setEndFrame(frame);
	return kSuccessCode;
}

// アニメーションのループ範囲（再生位置）を上書きします。
int SpriteStudioManager::setPlayerStartFrameToLabelName(int handle, char *label_name) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setStartFrameToLabelName(label_name);
	return kSuccessCode;
}

// アニメーションのループ範囲（終了位置）を上書きします。
int SpriteStudioManager::setPlayerEndFrameToLabelName(int handle, char *label_name) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setEndFrameToLabelName(label_name);
	return kSuccessCode;
}

// 表示を行うパーツ数を取得します
int SpriteStudioManager::getPlayerDrawSpriteCount(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	return player->getDrawSpriteCount();
}

// 反転状態を取得する
int SpriteStudioManager::getPlayerFlip(int handle, bool *flip_x, bool *flip_y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->getFlip(flip_x, flip_y);
	return kSuccessCode;
}

// 反転する
int SpriteStudioManager::setPlayerFlip(int handle, bool flip_x, bool flip_y) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->setFlip(flip_x, flip_y);
	return kSuccessCode;
}

// 時間を進める
int SpriteStudioManager::updatePlayer(int handle, float dt) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->update(dt);
	return kSuccessCode;
}

// 描画する
int SpriteStudioManager::drawPlayer(int handle) {
	ss::Player *player = getHashData(handle);
	if(player == NULL) {
		return kErrorCode;
	}
	player->draw();
	return kSuccessCode;
}
