#include "Item.hpp"
#include "../rapidjson/document.h"
#include <algorithm>
#include <chrono>
#include <curl/curl.h>
#include <string>
#include <thread>
#include <iostream>


Item::Item(const std::string &item_name)
	: name(item_name), condition(QUALITY::NO_QUALITY), special(SPECIAL::NO_SPECIAL) {}

size_t WriteFunc(char *contents, size_t size, size_t nmemb,
				 std::string *userp) {
	userp->append(contents, size * nmemb);
	return size * nmemb;
}

std::string Item::PerformRequest() {
	CURL *curl = curl_easy_init();

	std::string result = "";
	if (curl) {
		const auto combined_name=GenerateName();
		const auto encoded_name =
			curl_easy_escape(curl, combined_name.c_str(), combined_name.length());
		const auto encoded_link = request + encoded_name;
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

	if (!json["success"].Get<bool>()) {
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
		error_code = ERROR_CODES::NO_ERROR;
		return;
	}
	error_code = ERROR_CODES::NO_UNITS;
	return;
}

void Item::GenerateRequest(int curr){
	request="https://steamcommunity.com/market/priceoverview/?appid=730&currency=" +
		std::to_string(curr) + "&market_hash_name=";
}

std::string Item::GetQuality(){
	using enum QUALITY;
	switch (condition) {
		case FACTORY_NEW:
			return " (Factory New)";
		case MINIMAL_WEAR:
			return " (Minimal Wear)";
		case FIELD_TESTED:
			return " (Field-Tested)";
		case WELL_WORN:
			return " (Well-Worn)";
		case BATTLE_SCARRED:
			return " (Battle-Scarred)";
		case NO_QUALITY:
			return "";
		default:
			return "";
	}
}

std::string Item::GetSpecials(){
	using enum SPECIAL;
	switch (special){
		case STATTRAK:
			return "StatTrak™ ";
		case SOUVENIR:
			return "Souvenir ";
		case NO_SPECIAL:
			return "";
		default:
			return "";
	}
}

std::string Item::GenerateName(){
	std::string result="";
	result += GetSpecials();
	result += name;
	result += GetQuality();
	return result;
}

void Item::SetQuality(const std::string& quality){
	using enum QUALITY;
	if (quality == "Factory New")
		this->condition = FACTORY_NEW;
	if (quality == "Minimal Wear")
		this->condition = MINIMAL_WEAR;
	if (quality == "Field Tested")
		this->condition = FIELD_TESTED;
	if (quality == "Well Worn")
		this->condition = WELL_WORN;
	if (quality == "Battle Scarred")
		this->condition = BATTLE_SCARRED;
}

void Item::SetSpecial(const std::string& special){
	if (special == "StatTrak")
		this->special = SPECIAL::STATTRAK;
	if (special == "Souvenir")
		this->special = SPECIAL::SOUVENIR;
}
