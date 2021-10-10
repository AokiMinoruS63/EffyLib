/**
 * @file TypeConversion.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 型変換の関数（主にビットマップフォントに使用予定）
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TYPE_CONVERSION_H
#define TYPE_CONVERSION_H

#include <vector>
#include <string>

/**
 * @brief UTF８から１０進数のUTF16のint型に変える
 * 
 * @param data 変換するUTF-8データ
 * @return int 変換後のUTF16の整数変換値
 */
static long utf8_to_long(const char* data) {
	if ((data[0] & 0x80) == 0x00) {
		return data[0];
	} else if ((data[0] & 0xe0) == 0xc0) {
		return ((data[0] & 0x1f) << 6) | (data[1] & 0x3f);
	} else if ((data[0] & 0xf0) == 0xe0) {
		return (static_cast<long>(data[0] & 0x0f) << 12) | ((data[1] & 0x3f) << 6) | (data[2] & 0x3f);
	} else if ((data[0] & 0xf8) == 0xf0) {
		return (static_cast<long>(data[0] & 0x07) << 18) | (static_cast<long>(data[1] & 0x3f) << 12) | ((data[2] & 0x3f) << 6) | (data[3] & 0x3f);
	} else {
		// invalid
		return 0;
	}
}


/**
 * @brief 文字列をUTF16に対応したvector<int>型に変換する
 * 
 * @param str 変換する文字列
 * @return std::vector<int> 変換したvector<int>
 */
static std::vector<int> stringToVectorInt(std::string str)
{
    using namespace std;
	vector<int> v={};

    unsigned char lead; 
    int char_size = 0;

    for (string::iterator it = str.begin(); it != str.end(); it += char_size) {

        lead = *it;

        if (lead < 0x80) {
            char_size = 1;
        } else if (lead < 0xE0) {
            char_size = 2;
        } else if (lead < 0xF0) {
            char_size = 3;
        } else {
            char_size = 4;
        }

		v.push_back(utf8_to_long(str.substr(distance(str.begin(), it), char_size).c_str()));

    }
	return std::move(v);
}

#endif