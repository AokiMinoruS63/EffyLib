/**
 * @file DeleterBase.h
 * @brief デストラクタを汎用的に呼ぶためのインスタンス削除専用クラス
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#ifndef DELETER_BASE_H
#define DELETER_BASE_H

class DeleterBase {
	public:
	virtual ~DeleterBase(){}
};

#endif