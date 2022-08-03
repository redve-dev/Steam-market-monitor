#include <algorithm>
#include "Item.hpp"
#include "../functions.hpp"
#include <chrono>
#include <curl/curl.h>
#include <iostream>
#include <thread>
#include "../rapidjson/document.h"
#include <string>

Item::Item( const std::string& item_name, int curr=3):
	name(item_name),
	request(GetItemRequest(item_name, curr))
{
}

Item::Item( const std::string& item_name):
	name(item_name),
	request(GetItemRequest(item_name, 3))
{
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
	rapidjson::Document json;
	json.Parse(output.c_str());

	average_price = -1.;
	if(json["success"].Get<bool>()){
		const std::string temp_str = json["median_price"].GetString();

		// remove currency sign from the end of string
		std::string str_no_curr = temp_str.substr(0, temp_str.find(',')+3);
		std::replace(str_no_curr.begin(), str_no_curr.end(), ',', '.');
		average_price= std::stod(str_no_curr);
	}
	else{
		std::cerr<<"Couldn't perform request\n";
		std::cout<<"api request: "<<request<<std::endl;
	}

	std::cout<<name<<' '<<GetPrice()<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

double Item::GetPrice() const {
	return average_price;
}

void Item::SetCurrency(int t){
	curr=t;
	request = GetItemRequest(name, curr);
}
