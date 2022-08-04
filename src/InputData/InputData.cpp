#include "InputData.hpp"
#include <iostream>
#include <fstream>
#include <string>

InputData::InputData(const std::string& filepath){
	std::ifstream f(filepath);
	if( f.good() ){
		std::string name="";
		f>>currency>>delay;
		std::getline(f, name);
		while(std::getline(f, name)){
			items.push_back(Item(name, currency));
		}
	}
	f.close();
}

void InputData::Update(){
	for(auto& el: items){
		el.Update(delay);
	}
}
