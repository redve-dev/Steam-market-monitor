#include "functions.hpp"
#include <string>
#include <unordered_map>

std::string URLEncode(const std::string& input){
	std::string result="";
	const std::unordered_map<char, std::string> char_list{
		{' ', "%20"},
		{'!', "%21"},
		{'#', "%23"},
		{'$', "%24"},
		{'%', "%25"},
		{'&', "%26"},
		{'\'', "%27"},
		{'(', "%28"},
		{')', "%29"},
		{'*', "%2A"},
		{'+', "%2B"},
		{',', "%2C"},
		{'/', "%2F"},
		{':', "%3A"},
		{';', "%3B"},
		{'=', "%3D"},
		{'?', "%3F"},
		{'@', "%40"},
		{'[', "%5B"},
		{']', "%5D"},
	};

	for( char letter : input){
		if( char_list.count(letter) ){ result += char_list.at(letter); }
		else{ result += letter ; }
	}
	return result;
}

std::string GetItemRequest(const std::string& item_name, int curr){
	constexpr int appid=730;
	const std::string link="https://steamcommunity.com/market/priceoverview/?appid="+std::to_string(appid)+"&currency="+std::to_string(curr)+"&market_hash_name=";
	return link + URLEncode(item_name);
}
