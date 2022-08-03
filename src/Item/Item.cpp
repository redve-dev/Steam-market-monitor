#include "Item.hpp"
#include "../functions.hpp"
#include <chrono>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <thread>
#include "../rapidjson/document.h"

Item::Item( const std::string& item_name):
	name(item_name),
	request(GetItemRequest(item_name))
{
	std::cout<<request<<std::endl;
}

static size_t WriteFunc(void* contents, size_t size, size_t nmemb, void* userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string PerformRequest(const std::string& request){
	CURL* curl;
	std::string result="";
	curl = curl_easy_init();
	if ( curl ){
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return result;
}

void Item::Update( int delay ){
	const std::string output=PerformRequest(request);
	std::cout<<output<<std::endl;
	rapidjson::Document json;
	json.Parse(output.c_str());
	std::cout<<json["median_price"].GetString()<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

double Item::GetPrice() const {
	return average_price;
}
