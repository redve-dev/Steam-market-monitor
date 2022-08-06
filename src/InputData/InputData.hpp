#pragma once
#include "../Item/Item.hpp"
#include <vector>
#include <unordered_map>
#include <string>
class InputData {
	//std::unordered_map<int, std::string> currencies;
	std::vector<Item> items;
	int delay;
	void LoadCurrency(const std::string& path);
	int currency;
	public:
	explicit InputData(const std::string &path);
	void Update();
	void PrintAll();
	void PrintOne(int index);
};
