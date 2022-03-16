#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Main.h"

using namespace Chess;

[System::STAThreadAttribute]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	msclr::interop::marshal_context context;
	settingsManager::getInstance().init(context.marshal_as<std::string>(
		Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData))+"\\Chess by MrAlexeiMK\\");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Main);
	return 0;
}