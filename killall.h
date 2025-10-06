#pragma once
#include "utils.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <dirent.h>
#include <cerrno>
#include <csignal>

bool IsNumber(const char* s) {
    if (s==nullptr) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') start = 1;
    if (start == 1 && strlen(s) == 1) return false; // только знак без цифр
    for (size_t i = start; i < strlen(s); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    return true;
}
bool killall(const std::vector<char*>& argv){
	DIR* dir = opendir("/proc");	
	if(dir == NULL){
		perror("getPid failed");
		return false;
	}
	dirent* entry;
	while((entry = readdir(dir)) && entry!=NULL){
		if(!IsNumber(entry->d_name))
			continue;
		std::string filePlace = std::string("/proc/") +entry->d_name+ std::string("/comm");
		std::ifstream in(filePlace);
		std::string processName;
		std::getline(in, processName);
		if(strcmp(processName.c_str(), argv[1]) == 0){
			if(kill(atoi(entry->d_name), SIGKILL)==0)
				std::cout<<COLOR_RED<< "PID " << entry->d_name << " is down!\n"<<COLOR_RESET;
			else
				perror("kill error!");
		}
			
	}
	
	return true;
}
