#pragma once
#include <vector>
#include <sstream>
#include <cstring>


struct ParsedCommand {
    std::vector<char*> argv;
	void addArg(std::string& argStr){
		char* newArg = reinterpret_cast<char*>(malloc(argStr.size()+1));
		std::strcpy(newArg,argStr.c_str());
		argv.push_back(newArg);
	}


	ParsedCommand(const std::string& input){
		std::stringstream ss(input);
		std::string token;
		while (ss >> token)
			addArg(token);	
	}
	~ParsedCommand(){
		for(auto i: argv){
			delete[] i;	
		}	
	}
};
