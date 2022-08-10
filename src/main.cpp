#include "Interface/Interface.hpp"
#include <string>

int main(int argc, char **args) {
	std::string file = "items.json";
	if (argc > 1) {
		file = args[1];
		if (file.find_first_not_of(' ') == std::string::npos) {
			file = "items.json";
		}
	}
	Interface data;
	data.LoadFromFile(file);
	data.Update();
	data.PrintAll();
}
