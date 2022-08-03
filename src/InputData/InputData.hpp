#pragma once
#include "../Item/Item.hpp"
#include <vector>
struct InputData{
	std::vector<Item> items;
	int currency;
	int delay;
	InputData(const std::string& path);
	void Update();
	void Print();
};
