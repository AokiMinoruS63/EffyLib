/**
 * @file DeleterBase.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief デストラクタを汎用的に呼ぶためのインスタンス削除専用クラス
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DELETER_BASE_H
#define DELETER_BASE_H

class DeleterBase {
	public:
	virtual ~DeleterBase(){}
};

#endif