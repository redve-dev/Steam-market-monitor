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

Item::Item( const std::string& item_name, int currency):
	name(item_name),
	request(GetItemRequest(item_name, currency)),
	curr(currency)
{
}

Item::Item( const std::string& item_name):
	name(item_name),
	request(GetItemRequest(item_name, 3)),
	curr(3)
{
}

static size_t WriteFunc(void* contents, size_t size, size_t nmemb, void* userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void Item::PrintItemData(){
	std::map<int, std::string> curr_map{
		{1, "USD"},
		{2, "GBP"},
		{3, "EUR"},
		{6, "PLN"},
	};

	if ( error_code != ERROR_CODES::NO_ERROR ){
		std::string error_msg="";
		switch(error_code){
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
			<<std::right<<std::setw(50)<<name<<": "
			<<std::right<<std::setw(14)<<error_msg
			<<std::endl;
		return;
	}

	std::cout
		<<std::right<<std::setw(50)<<name<<": "
		<<std::right<<std::setw(10)<<std::setprecision(2)<<std::fixed<<average_price<<' '
		<<std::left<<std::setw(4)<<curr_map[curr]
		<<std::endl;
}

std::string PerformRequest(const std::string& request){
	CURL* curl;
	std::string result="";
	curl = curl_easy_init();
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

void Item::Update( int delay ){
	// prevent antispammer
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	const std::string output=PerformRequest(request);
	rapidjson::Document json;
	json.Parse(output.c_str());

	average_price = 0.;
	error_code = ERROR_CODES::NO_ERROR;
	if( !json["success"].Get<bool>() ){
		std::cerr<<"Couldn't perform request for item: "<<name<<std::endl;
		std::cerr<<"api request: "<<request<<std::endl<<std::endl;
		error_code = ERROR_CODES::FAILED_TO_GET_DATA;
		return PrintItemData();
	}
	if( !json.HasMember("median_price")){
		error_code = ERROR_CODES::NO_UNITS;
		return PrintItemData();
	}
	const std::string temp_str = json["median_price"].GetString();

	// remove currency sign from the end of string
	std::string str_no_curr = temp_str.substr(0, temp_str.find(',')+3);
	std::replace(str_no_curr.begin(), str_no_curr.end(), ',', '.');
	average_price= std::stod(str_no_curr);

	PrintItemData();
}

void Item::SetCurrency(int t){
	curr=t;
	request = GetItemRequest(name, curr);
}
