#pragma once
#include "CommandLogger.h"
#include "ParsedCommand.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "nice.h"
#include "killall.h"
class Ppsh{
private:
	static void handleSigint(int) {
		if (childPid > 0) {
			kill(childPid, SIGINT);
		}
		std::cout << "\nInterrupted by signal\n";
	}
public:
	int startUp(){
		signal(SIGINT,handleSigint);

		CommandLogger logger;
		std::string line;
		while (true) {
			std::cout << "ppsh> ";
			std::getline(std::cin, line);

			logger.log(line);

			ParsedCommand command(line);
			if (command.argv.empty()) continue;

			if (line == "exit") break;
			if (strcmp(command.argv[0],"cd")==0){
				cd(command.argv);
				continue;
			}
			if (strcmp(command.argv[0],"ls")==0){
				ls(command.argv);
				continue;
			}	
			if (strcmp(command.argv[0],"cat")==0){
				cat(command.argv);
				continue;
			}	
			if(strcmp(command.argv[0], "nice") == 0){
				nice(command.argv,childPid);
				continue;
			}
			if (strcmp(command.argv[0],"killall")==0){
				killall(command.argv);
				continue;
			}

			static const int maxRestartCount = 5;
			int restartCount = 1;
			while(1){
				pid_t pid = fork();
				if (pid == 0) {
					//Если я - сын, я становлюсь вызванной утилитой
					execvp(command.argv[0], command.argv.data());
					perror("execvp failed");
					exit(1);
				} 
				else {
					childPid = pid;
					//Если я - отец, я жду пока завершится процесс вызванной утилиты
					int status = 0;
					waitpid(pid, &status, 0);
					if(WIFSIGNALED(status) && WCOREDUMP(status)){
						std::cout<<COLOR_RED << "child process terminated abnormally. restarting ["<<restartCount<<','<<maxRestartCount<<"]\n"<< COLOR_RESET;
						++restartCount;
						if(restartCount <= maxRestartCount)
							continue;
					}
					break;
				}
			}
		}
		return 0;
	}
private:
	static pid_t childPid;
};
pid_t Ppsh::childPid = -1;
