#include "Interface.hpp"
#include <iostream>
#include "../rapidjson/document.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

Interface::Interface(const std::string &filepath) { LoadFromFile(filepath); }

void Interface::Update() {
	for (auto &el : items) {
		el.Update(delay);
	}
}

std::string GetCurrencyName(int curr) {
	switch (curr) {
	case 1:
		return "USD";
	case 2:
		return "GBP";
	case 3:
		return "EUR";
	case 6:
		return "PLN";
	default:
		return "undefined";
	}
}

void Interface::PrintAll() {
	for (size_t i = 0; i < items.size(); i++) {
		PrintOne(i);
	}
}

void Interface::PrintOne(int index) {
	const auto name = items.at(index).name;
	const auto price = items.at(index).price;
	const auto error_code = items.at(index).error_code;
	const auto special = items.at(index).special;
	const auto condition = items.at(index).condition;

	printf("%70s ", name.c_str());
	if (items.at(index).error_code != Item::ERROR_CODES::NO_ERROR) {
		switch (items.at(index).error_code) {
		case Item::ERROR_CODES::FAILED_TO_GET_DATA:
			printf("FAIL\n");
			break;
		case Item::ERROR_CODES::NO_UNITS:
			printf("NO_UNITS\n");
			break;
		default:
			printf("UNDEFINED ERROR\n");
			break;
		}
		return;
	}
	printf("%10.2lf %s\n", price, "PLN");
	return;
}

Item ReadItem(const auto& el){
	auto name = el["name"].GetString();
	Item object(name);
	if ( el.HasMember("condition")){
		auto condition = el["condition"].GetString();
		object.SetQuality(condition);
		if (el.HasMember("special")){
			auto special = el["special"].GetString();
			object.SetSpecial(special);
		}
	}
	return object;
}

void Interface::LoadFromFile(const std::string &path) {
	items.clear();
	std::ifstream f(path);
	if (f.good()) {
		std::stringstream buffer;
		buffer << f.rdbuf();
		const auto json_str = buffer.str();
		rapidjson::Document json;
		json.Parse(json_str.c_str());
		delay = json["delay"].Get<int>();
		Item::GenerateRequest(json["currency"].Get<int>());
		if (json["items"].IsArray()) {
			for (auto &el : json["items"].GetArray()) {
				items.push_back(ReadItem(el));
			}
		}
	}
	f.close();
}
