#include "InputData.hpp"
#include <fstream>
#include <string>
#include <cstdlib>

InputData::InputData(const std::string &filepath) {
	std::ifstream f(filepath);
	if (f.good()) {
		std::string name = "";
		f >> currency >> delay;
		std::getline(f, name);
		while (std::getline(f, name)) {
			if (name.empty()) {
				continue;
			}
			items.emplace_back(name, currency);
		}
	}
	f.close();
}

void InputData::Update() {
	for (auto &el : items) {
		el.Update(delay);
	}
}

std::string GetCurrencyName(int curr){
	switch(curr){
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

void InputData::PrintAll(){
	for(size_t i=0; i<items.size(); i++){
		PrintOne(i);
	}
}

void InputData::PrintOne(int index){
	const auto name = items.at(index).name;
	const auto price = items.at(index).price;
	const auto curr = GetCurrencyName(items.at(index).curr);

	printf("%70s ", name.c_str());
	if ( items.at(index).error_code != Item::ERROR_CODES::NO_ERROR){
		switch( items.at(index).error_code){
			case Item::ERROR_CODES::FAILED_TO_GET_DATA:
				printf("FAIL\n");
				break;
			case Item::ERROR_CODES::NO_UNITS:
				printf("NO_UNITS\n");
				break;
			case Item::ERROR_CODES::NO_ERROR:
				break;
			default:
				printf("UNDEFINED ERROR\n");
				break;
		}
		return;
	}
	printf("%10.2lf %s\n", price, curr.c_str());
	return;
}
