#pragma once
#include <string>
#include <fstream>

//Простенький логгер
class CommandLogger {
    std::ofstream logFile;
public:
    CommandLogger() {
        const char* home = getenv("HOME");
        std::string path = std::string(home) + "/.ppsh_history";
        logFile.open(path, std::ios::app);
    }

    void log(const std::string& line) {
        if (logFile.is_open()) {
            logFile << line << "\n";
        }
    }

    ~CommandLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};
