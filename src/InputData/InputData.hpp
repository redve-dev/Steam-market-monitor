#pragma once
#include "../Item/Item.hpp"
#include <string>
#include <vector>
class InputData {
  private:
	std::vector<Item> items;
	int delay;
	void LoadCurrency(const std::string &path);

  public:
	explicit InputData(const std::string &path);
	void LoadFile(const std::string &path);
	void Update();
	void PrintAll();
	void PrintOne(int index);
};
