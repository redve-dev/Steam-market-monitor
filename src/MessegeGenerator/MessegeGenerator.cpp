#include "MessegeGenerator.hpp"
#include "../rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <array>
#include <utility>

MessegeGenerator::MessegeGenerator(){
}

MessegeGenerator::~MessegeGenerator(){
}

rapidjson::Document LoadDictionary(const std::string& path){
	std::ifstream f(path);
	rapidjson::Document json;
	if (f.good()) {
		std::stringstream buffer;
		buffer << f.rdbuf();
		const auto json_str = buffer.str();
		
		json.Parse(json_str.c_str());
	}
	f.close();
	return json;
}

void MessegeGenerator::LoadDictionaryErrors(const std::string& path){
	const auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 3> elements{
		"FAILED_TO_GET_DATA",
		"NO_UNITS",
		"NO_ERROR"
	};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			errors[el] = dictionary[el.c_str()].GetString();
		}
	}
}

std::string MessegeGenerator::GetError(Item::ERROR_CODES e){
	using enum Item::ERROR_CODES;
	switch(e){
		case FAILED_TO_GET_DATA:
			return errors["FAILED_TO_GET_DATA"];
		case NO_UNITS:
			return errors["NO_UNITS"];
		case NO_ERROR:
			return "";
		default:
			return "UKNOWN_ERROR";
	}
}

void MessegeGenerator::LoadDictionarySpecials(const std::string& path){
	const auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 3> elements{
		"STATTRAK",
		"SOUVENIR",
		"NO_SPECIAL"};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			specials[el] = dictionary[el.c_str()].GetString();
		}
	}
}

std::string MessegeGenerator::GetSpecial(Item::SPECIAL s){
	using enum Item::SPECIAL;
	switch(s){
		case STATTRAK:
			return specials["STATTRAK"];
		case SOUVENIR:
			return specials["SOUVENIR"];
		case NO_SPECIAL:
			return "";
		default:
			return "UKNOWN_SPECIAL";
	}
}

void MessegeGenerator::LoadDictionaryConditions(const std::string& path){
	const auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 6> elements{
		"FACTORY_NEW",
		"MINIMAL_WEAR",
		"FIELD_TESTED",
		"WELL_WORN",
		"BATTLE_SCARRED",
		"NO_QUALITY"};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			condition[el] = dictionary[el.c_str()].GetString();
		}
	}
}

std::string MessegeGenerator::GetCondition(Item::QUALITY q){
	using enum Item::QUALITY;
	switch(q){
		case FACTORY_NEW:
			return condition["FACTORY_NEW"];
		case MINIMAL_WEAR:
			return condition["MINIMAL_WEAR"];
		case FIELD_TESTED:
			return condition["FIELD_TESTED"];
		case WELL_WORN:
			return condition["WELL_WORN"];
		case BATTLE_SCARRED:
			return condition["BATTLE_SCARRED"];
		case NO_QUALITY:
			return "";
		default:
			return "UKNOWN_CONDITION";
	}
}

void MessegeGenerator::LoadDictionaries(const std::string& path){
	LoadDictionaryConditions(path+"condition.json");
	LoadDictionaryErrors(path+"errors.json");
	LoadDictionarySpecials(path+"specials.json");
	LoadDictionaryCurrency(path+"currency.json");
}

void MessegeGenerator::LoadDictionaryCurrency(const std::string& path){
	const auto dictionary = LoadDictionary(path);
	for(int i=1; i<=41; i++){
		const auto t = std::to_string(i);
		if (dictionary.HasMember(t.c_str())){
			currency[i] = dictionary[t.c_str()].GetString();
		}
	}
}

std::string MessegeGenerator::GetCurrency(int c){
	return currency[c];
}
