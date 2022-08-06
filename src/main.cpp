#include "Interface/Interface.hpp"
#include <string>

int main(int argc, char **args) {
	std::string file = "items";
	if (argc > 1) {
		file = args[1];
		if (file.find_first_not_of(' ') == std::string::npos) {
			file = "items";
		}
	}
	Interface data(file);
	data.Update();
	data.PrintAll();
}
