#pragma once
#include "utils.h"

#include <unistd.h>
#include <iostream>
bool cd(const std::vector<char*>& argv) {
	std::string path = getPath(argv);
	std::cout<<COLOR_CYAN<<"path>>" <<path<<"<<\n"<<COLOR_RESET;
	if (chdir(path.c_str()) != 0) {
		perror("cd failed");
	}
	return true;
}

