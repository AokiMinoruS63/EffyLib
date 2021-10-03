/**
 * @file Equatable.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief ID付きのクラス
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EQUATABLE_H
#define EQUATABLE_H

#include <uuid/uuid.h>

// プロトコル。クラスが等しいかどうか
class Equatable {
	public:
	uuid_t id;
	Equatable() {
		uuid_generate(id);
	}
	~Equatable(){}

	/**
	 * @brief クラス同士の比較で同一なら**true**
	 * 
	 * @param data 
	 * @return true 
	 * @return false 
	 */

};

bool operator==(const Equatable& lhs, const Equatable& rhs)
{
	printfDx("id Equarl\n");
	for(int i = 0; i < 16; i++) {
		if(lhs.id[i] != rhs.id[i]) {
			return false;
		}
	}
    return true;
}

#endif