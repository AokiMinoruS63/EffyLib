/**
 * @file UUID.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief UUIDを作成
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UUID_H
#define UUID_H

#include <uuid/uuid.h>

/**
 * @brief UUIDを作成する
 * 
 * @return uuid_t ユニークID
 */
uuid_t UUID() {
	uuid_t uuid;
	return uuid_generate(uuid);
}

#endif