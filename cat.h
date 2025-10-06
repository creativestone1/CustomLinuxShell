#pragma once
#include "utils.h"
#include <fstream>
#include <iostream>
bool cat(const std::vector<char*>& argv) {
	std::string path = argv[1];
	std::ifstream in(path);	
	while(!in.eof()){
		std::string str;
		std::getline(in, str);
		std::cout<< str<<'\n';
	}
	return true;
}
