#pragma once
#include "../Item/Item.hpp"
#include <string>
#include <vector>
class Interface {
  private:
	std::vector<Item> items;
	int delay;
	void LoadCurrency(const std::string &path);

  public:
	explicit Interface(const std::string &path);
	void LoadFromFile(const std::string &path);
	void Update();
	void PrintAll();
	void PrintOne(int index);
};
