#pragma once
#include "ParsedCommand.h"
#include "utils.h"

#include <sys/stat.h>
#include <sys/ioctl.h>
#include <iostream> 
#include <dirent.h>


bool getTerminalSize(int& columns, int& rows) {
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		perror("ioctl");
		return false;
	}
	columns = w.ws_col;
	rows = w.ws_row;
	return true;
}

bool ls(const std::vector<char*>& argv) {
	std::string path = getPath(argv);
	DIR* dir = opendir(path.c_str());	
	if(dir == NULL){
		perror("ls failed");
		return false;
	}
	dirent* entry;
	size_t filledStr = 0;
	int maxStrSize = 0;
	int rubbish = 0;
	getTerminalSize(maxStrSize,rubbish);
	while((entry = readdir(dir)) && entry!=NULL){
		int to_write;

		if(filledStr+to_write > maxStrSize){
			std::cout<< '\n';
			filledStr = 0;
		}

		if(entry->d_type == DT_DIR)	{
			to_write = strlen(entry->d_name)+4;
			std::cout<< COLOR_BLUE <<"[" <<entry->d_name<< "] "<<COLOR_RESET;
			filledStr += to_write;
			continue;
		}
		struct stat fileStat;
		std::string fullPath = path+'/'+entry->d_name;
		stat(fullPath.c_str(),&fileStat);
		if(fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH){
			to_write = strlen(entry->d_name)+4;
			std::cout<< COLOR_GREEN <<"*" <<entry->d_name<< "* "<<COLOR_RESET;
			filledStr += to_write;
			continue;
		}


		to_write = strlen(entry->d_name)+3;
		std::cout<< entry->d_name<< "  ";
		filledStr += to_write;
	}
	std::cout<< '\n';
	return true;
}
