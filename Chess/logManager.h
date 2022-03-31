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
	static void writeln() {
		write("\n");
	}
	static void writeln(std::vector<uint64_t> arr) {
		for (size_t i = 0; i < arr.size(); ++i) {
			std::string s = std::to_string(arr[i]);
			if (i < arr.size() - 1) s += ", ";
			write(s);
		}
		write("\n");
	}
	static void writeln(std::pair<int, int> p) {
		writeln(std::to_string(p.first) + " -> " + std::to_string(p.second));
	}
	static void writeln(std::pair<size_t, size_t> p) {
		writeln(std::to_string(p.first) + " -> " + std::to_string(p.second));
	}
	static void writeln(int a) {
		writeln(std::to_string(a));
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