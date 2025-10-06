#pragma once
#include "utils.h"
#include <vector>
#include <sys/wait.h>
#include <sys/resource.h>
#include <iostream>
#include <string>
bool nice(const std::vector<char*>& argv, int& childPid){
	int nicePriority = 0;
	int execOffset = 1; //offset in vector where the command to exec starts
	if(argv[1][0] == '-'){
		if(argv[1][1] == 'n'){
			nicePriority = atoi(argv[2]);
			execOffset+=2;
		}
	}
	std::cout<< argv[execOffset]<<"<<\n";
	pid_t pid = fork();
	if (pid == 0) {
		
		 if (setpriority(PRIO_PROCESS, 0, nicePriority) == -1) {
            perror("setpriority failed");
            exit(1);
        }
		
		//Если я - сын, я становлюсь вызванной утилитой
		execvp(argv[execOffset], &argv[execOffset]);
		perror("execvp failed");
		exit(1);
	} 
	else {
		childPid = pid;
		//Если я - отец, я жду пока завершится процесс вызванной утилиты
		waitpid(pid, 0, 0);
	}		
	return true;
}
