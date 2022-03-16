#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>
#include "settingsManager.h"

class logManager {
public:
	static void write(std::string str) {
		static logManager s;
		s.fout << str;
	}
	static void writeln(std::string str) {
		write(str+"\n");
	}
private:
	std::ofstream fout;

	logManager() {
		fout.open(settingsManager::getInstance().path + "log.txt");
	}
	~logManager() {
		fout.close();
	}

	logManager(logManager const&) = delete;
	logManager& operator=(logManager const&) = delete;
};

#endif