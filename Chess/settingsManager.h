#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

class settingsManager {
public:
	std::string path;
	std::string langFile = "ru-RU.txt";
	int firstStep = 0;
	bool playSound = true;
	int maxSteps = 150;
	std::vector<int> layers;
	double lr = 0.1;
	int simulations = 10;
	int historySteps = 5;
	int depth = 20;
	int maxDepth = 8;

	static settingsManager& getInstance() {
		static settingsManager instance;
		return instance;
	}

	void init(std::string path) {
		System::IO::Directory::CreateDirectory(gcnew System::String(path.c_str()));
		System::IO::Directory::CreateDirectory(gcnew System::String((path+"weights\\").c_str()));
		System::IO::Directory::CreateDirectory(gcnew System::String((path+"langs\\").c_str()));

		for (std::string lFile : langFiles) {
			std::ifstream src;
			std::ofstream dst;
			src.open("langs/"+lFile, std::ios::in | std::ios::binary);
			dst.open(path + "langs\\"+lFile, std::ios::out | std::ios::binary);
			dst << src.rdbuf();
			src.close();
			dst.close();
		}

		this->path = path;
		std::string temp;
		std::ifstream fin(path+"settings.txt");
		if (!fin.good()) fin.open("settings.txt");
		
		std::string tempLayers;
		fin >> temp >> langFile;
		fin >> temp >> firstStep;
		fin >> temp >> playSound;
		fin >> temp >> maxSteps;
		fin >> temp >> tempLayers;
		fin >> temp >> lr;
		fin >> temp >> simulations;
		fin >> temp >> historySteps;
		fin >> temp >> depth;
		fin >> temp >> maxDepth;
		parseLayers(tempLayers);

		fin.close();
	}
	void update(std::string langFile, int firstStep, bool playSound, int maxSteps, std::string layers, double lr, 
		int simulations, int historySteps, int depth, int maxDepth) {
		this->langFile = langFile;
		this->firstStep = firstStep;
		this->playSound = playSound;
		this->maxSteps = maxSteps;
		parseLayers(layers);
		this->lr = lr;
		this->simulations = simulations;
		this->historySteps = historySteps;
		this->depth = depth;
		this->maxDepth = maxDepth;

		std::ofstream fout(path+"settings.txt");

		fout << "LangFile: " << langFile << std::endl;
		fout << "FirstStep: " << firstStep << std::endl;
		fout << "PlaySound: " << playSound << std::endl;
		fout << "MaxSteps: " << maxSteps << std::endl;
		fout << "Layers: " << layersToString() << std::endl;
		fout << "LearningRate: " << lr << std::endl;
		fout << "Simulations: " << simulations << std::endl;
		fout << "HistorySteps: " << historySteps << std::endl;
		fout << "Depth: " << depth << std::endl;
		fout << "MaxDepth: " << maxDepth << std::endl;

		fout.close();
	}
	std::string layersToString() {
		std::string res = "";
		for (int layer : layers) {
			res += std::to_string(layer) + ",";
		}
		res = res.substr(0, res.size()-1);
		return res;
	}
	std::string lang(std::string key) {
		if (mapLang.empty()) {
			std::ifstream lin(path+"langs\\"+langFile);
			if (!lin.good()) lin.open("langs\\"+langFile);
			std::string temp;
			std::string k, value = "";
			while (lin >> temp) {
				if (temp.back() == ':') {
					size_t pos;
					while ((pos = value.find("_")) != std::string::npos) {
						value.replace(pos, 1, " ");
					}
					mapLang[k] = value.substr(0, value.size()-1);
					value = "";
					k = temp.substr(0, temp.size()-1);
				}
				else {
					value += temp+" ";
				}
			}
			if (value != "") {
				size_t pos;
				while ((pos = value.find("_")) != std::string::npos) {
					value.replace(pos, 1, " ");
				}
				mapLang[k] = value.substr(0, value.size() - 1);
			}
			lin.close();
		}
		return mapLang[key];
	}
private:
	static settingsManager* instance;
	std::map<std::string, std::string> mapLang;
	const std::vector<std::string> langFiles = {"ru-RU.txt", "en-EN.txt"};

	void parseLayers(std::string str) {
		layers.clear();
		std::string layer = "";
		for (size_t i = 0; i < str.size(); ++i) {
			if (str[i] == ',') {
				layers.push_back(atoi(layer.c_str()));
				layer = "";
			}
			else layer += str[i];
		}
		if (layer != "") {
			layers.push_back(atoi(layer.c_str()));
		}
		layers[0] = 256*historySteps;
		layers[layers.size()-1] = 1;
	}

	settingsManager() {}
	~settingsManager() {}

	settingsManager(settingsManager const&) = delete;
	settingsManager& operator=(settingsManager const&) = delete;
};

#endif