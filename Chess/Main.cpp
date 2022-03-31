#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Main.h"
#include "mcts.h"

using namespace Chess;

[System::STAThreadAttribute]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	msclr::interop::marshal_context context;
	string appdata = context.marshal_as<std::string>(Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData))+ "\\Chess by MrAlexeiMK\\";
	settingsManager::getInstance().init(appdata);
	mcts::getInstance().init("mcts.txt");
	mcts::getInstance().log();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Main);
	return 0;
}