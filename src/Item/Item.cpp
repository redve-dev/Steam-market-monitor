#include <iomanip>
#include <algorithm>
#include "Item.hpp"
#include "../functions.hpp"
#include <chrono>
#include <curl/curl.h>
#include <iostream>
#include <thread>
#include "../rapidjson/document.h"
#include <string>
#include <map>

Item::Item( const std::string& item_name, int currency=3):
	name(item_name),
	request(GetItemRequest(item_name, currency)),
	curr(currency)
{
}

void Item::PrintItemData(ERROR_CODES error){
	std::map<int, std::string> curr_map{
		{1, "USD"},
		{2, "GBP"},
		{3, "EUR"},
		{6, "PLN"},
	};

	if ( error != ERROR_CODES::NO_ERROR ){
		std::string error_msg="";
		switch(error){
			case ERROR_CODES::FAILED_TO_GET_DATA:
				error_msg="FAIL";
				break;
			case ERROR_CODES::NO_UNITS:
				error_msg="NO UNITS";
				break;
			default:
				error_msg="UNKNOWN ERROR";
		}
		std::cout
			<<std::right<<std::setw(65)<<name<<": "
			// make proper error messege alignment
			<<std::right<<std::setw(10+4)<<error_msg
			<<std::endl;
		return;
	}

	std::cout
		<<std::right<<std::setw(65)<<name<<": "
		<<std::right<<std::setw(10)<<std::setprecision(2)<<std::fixed<<price<<' '
		<<std::left <<std::setw(4)<<curr_map[curr]
		<<std::endl;
}


std::string PerformRequest(const std::string& request){
	CURL* curl = curl_easy_init();
	size_t (*WriteFunc)(char*, size_t, size_t, std::string*) = 
		[](char* contents, size_t size, size_t nmemb, std::string* userp){
			userp->append(contents, size * nmemb);
			return size * nmemb;
		};
	std::string result="";
	if ( curl ){
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return result;
}

double PriceFromString(std::string input){
	// remove special characters
	std::remove_if(input.begin(), input.end(), 
			[](unsigned char x){
			bool IsNum = x < '0' || x > '9';
			return IsNum && x != '.' && x != ',';
			});
	std::replace(input.begin(), input.end(), ',', '.');
	return std::stod(input);
}

void Item::Update( int delay ){
	// prevent antispammer
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	const std::string output=PerformRequest(request);
	rapidjson::Document json;
	json.Parse(output.c_str());

	if( !json["success"].Get<bool>() )
		return PrintItemData(ERROR_CODES::FAILED_TO_GET_DATA);
	if( json.HasMember("median_price")){
		price = PriceFromString(json["median_price"].GetString());
		return PrintItemData(ERROR_CODES::NO_ERROR);
	}
	// extreme case, only 1 item on the market
	if( json.HasMember("lowest_price")){
		price = PriceFromString(json["lowest_price"].GetString());
		return PrintItemData(ERROR_CODES::NO_ERROR);
	}
	return PrintItemData(ERROR_CODES::NO_UNITS);
}
