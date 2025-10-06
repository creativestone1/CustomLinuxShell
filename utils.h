#pragma once

#include "ParsedCommand.h"
#include <string>
#include <limits.h>
#include "unistd.h"

static const char* home = getenv("HOME");

#define COLOR_BLACK   "\033[30m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_RESET   "\033[0m"


std::string getPath(const std::vector<char*>& argv){
	std::string target;
	
	if (argv.size() > 1 && argv[1] != NULL) {
		std::string rawPath = argv[1];

		if (rawPath == "~") {
			if (!home) 
				home = "/";
			target = home;
		} 
		else if (rawPath.rfind("~/", 0) == 0) {
			if (!home) 
				home = "/";
			target = std::string(home) + rawPath.substr(1); // ~ -> HOME
			} 
		else
			target = rawPath;
	} 
	else{
		char curPath[PATH_MAX];
		getcwd(curPath, sizeof(curPath));	
		target = std::string(curPath);
		//target = home ? home : "/";
	}
	return target;
}
