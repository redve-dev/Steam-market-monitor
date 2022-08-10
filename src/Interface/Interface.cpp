#include "Interface.hpp"
#include "../rapidjson/document.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

Interface::Interface() { 
	generator.LoadDictionaries("dictionaries/");
}

void Interface::Update() {
	for (auto &el : items) {
		el.Update(delay);
	}
}

void Interface::PrintAll() {
	for (size_t i = 0; i < items.size(); i++) {
		PrintOne(i);
	}
}

void Interface::PrintOne(int index) {
	const auto name = items.at(index).name;
	const auto special = generator.GetSpecial(items.at(index).special);
	const auto condition = generator.GetCondition(items.at(index).condition);
	
	if ( items.at(index).error_code != Item::ERROR_CODES::NO_ERROR ){
		const auto error_code = generator.GetError(items.at(index).error_code);
		printf("%s\t%s\t%s:\t%s\n", special.c_str(), name.c_str(), condition.c_str(), error_code.c_str());
		return;
	}
	const auto price = items.at(index).price;
	const auto currency = generator.GetCurrency(curr);
	printf("%s\t%s\t%s:\t%.2lf %s\n", special.c_str(), name.c_str(), condition.c_str(), price, currency.c_str());
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
