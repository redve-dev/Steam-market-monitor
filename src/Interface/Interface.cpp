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
	const auto error_code = generator.GetError(items.at(index).error_code);
	const auto special = generator.GetSpecial(items.at(index).special);
	const auto condition = generator.GetCondition(items.at(index).condition);
	const auto currency = generator.GetCurrency(curr);
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
		curr = json["currency"].Get<int>();
		Item::GenerateRequest(curr);
		if (json["items"].IsArray()) {
			for (auto &el : json["items"].GetArray()) {
				items.push_back(ReadItem(el));
			}
		}
	}
	f.close();
}
