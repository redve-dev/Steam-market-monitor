#include "Item.hpp"
#include "../rapidjson/document.h"
#include <algorithm>
#include <array>
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

Item::Item(const std::string &item_name, int currency = 3)
	: name(item_name), curr(currency) {
}

size_t WriteFunc(char *contents, size_t size, size_t nmemb, std::string *userp) {
	userp->append(contents, size * nmemb);
	return size * nmemb;
}

std::string Item::PerformRequest() {
	CURL *curl = curl_easy_init();
	const static std::string link =
		"https://steamcommunity.com/market/priceoverview/?appid=730&currency=" +
		std::to_string(curr) + "&market_hash_name=";

	std::string result="";
	if (curl) {
		const auto encoded_name = curl_easy_escape(curl, name.c_str(), name.length());
		const auto encoded_link = link+encoded_name;
		curl_easy_setopt(curl, CURLOPT_URL, encoded_link.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return result;
}

double PriceFromString(std::string input) {
	// remove special characters
	auto IsNOTDigitOrDot = [](unsigned char x) {
		bool IsNum = x >= '0' && x <= '9';
		bool IsDot = x == '.' || x == ',';
		return !IsNum && !IsDot;
	};

	auto it = std::remove_if(input.begin(), input.end(), IsNOTDigitOrDot);
	input.erase(it, input.end());
	// why would steam always use dot or coma lol, this way is more fun
	std::replace(input.begin(), input.end(), ',', '.');
	return std::stod(input);
}

void Item::Update(int delay) {
	// prevent antispammer
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	const std::string output = PerformRequest();
	rapidjson::Document json;
	json.Parse(output.c_str());

	if (!json["success"].Get<bool>()){
		error_code = ERROR_CODES::FAILED_TO_GET_DATA;
		return;
	}
	if (json.HasMember("median_price")) {
		price = PriceFromString(json["median_price"].GetString());
		error_code = ERROR_CODES::NO_ERROR;
		return;
	}
	// extreme case, only 1 item on the market
	if (json.HasMember("lowest_price")) {
		price = PriceFromString(json["lowest_price"].GetString());
		return;
	}
		error_code = ERROR_CODES::NO_UNITS;
	return;
}
