#include "MessegeGenerator.hpp"
#include "../rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <array>

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
		rapidjson::Document json;
		json.Parse(json_str.c_str());
	}
	f.close();
	return json;
}

void MessegeGenerator::LoadDictionaryErrors(const std::string& path){
	auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 3> elements{
		"FAILED_TO_GET_DATA",
		"NO_UNITS",
		"NO_ERROR"
	};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			errors[el] = dictionary[el.c_str()].GetString()
		}
	}
}

void MessegeGenerator::LoadDictionarySpecials(const std::string& path){
	auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 3> elements{
		"STATTRAK",
		"SOUVENIR",
		"NO_SPECIAL"
	};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			errors[el] = dictionary[el.c_str()].GetString()
		}
	}

}

void MessegeGenerator::LoadDictionaryConditions(const std::string& path){
	auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 6> elements{
		"FACTORY_NEW",
		"MINIMAL_WEAR",
		"FIELD_TESTED",
		"WELL_WORN",
		"BATTLE_SCARRED",
		"NO_QUALITY"
	};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			errors[el] = dictionary[el.c_str()].GetString()
		}
	}

}
void MessegeGenerator::LoadDictionaryCurrency(const std::string& path){
	auto dictionary = LoadDictionary(path);
	static const std::array<std::string, 3> elements{
		"FAILED_TO_GET_DATA",
		"NO_UNITS",
		"NO_ERROR"
	};

	for(auto & el : elements){
		if (dictionary.HasMember(el.c_str())){
			errors[el] = dictionary[el.c_str()].GetString()
		}
	}

}
