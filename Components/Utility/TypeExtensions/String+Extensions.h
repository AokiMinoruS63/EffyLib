/**
 * @file String+Extensions.h
 * @brief 
 * 
 * Copyright (c) 2021-2022 AokiMinoru
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 * 
 */

#include <string>

namespace StringExtension {
	/**
	 * @brief ファイル名を抽出する
	 * 
	 * @param path ファイルパス
	 * @param without_extension 拡張子を除くなら**true**
	 * @return std::string ファイル名
	 */
	inline std::string extractFileName(const std::string &path, bool without_extension = true) {
		std::string fn;
		std::string::size_type fpos;
		if((fpos = path.find_last_of("/")) != std::string::npos){
			fn = path.substr(fpos+1);
		}
		else if((fpos = path.find_last_of("\\")) != string::npos){
			fn = path.substr(fpos+1);
		}
		else{
			fn = path;
		}

		if(without_extension && (fpos = fn.find_last_of(".")) != string::npos){
			fn = fn.substr(0, fpos);
		}

		return fn;
	}
}
