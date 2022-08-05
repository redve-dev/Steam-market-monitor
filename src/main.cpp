#include "InputData/InputData.hpp"
#include "Item/Item.hpp"
#include <iostream>
#include <string>

int main(int argc, char **args) {
	std::string file = "items";
	if (argc > 0) {
		file = args[1];
	}
	InputData data(file);
	data.Update();
}
