#include "InputData/InputData.hpp"
#include "Item/Item.hpp"
#include <iostream>
#include <string>

int main(int argc, char **args) {
	std::string file = "items";
	if (argc > 1) {
		file = args[1];
		if (file.find_first_not_of(' ') == std::string::npos) {
			file = "items";
		}
	}
	InputData data(file);
	data.Update();
	data.PrintAll();
}
