#pragma once

#include "time.h"
#include "matrix.h"
#include "neuralNetwork.h"
#include "chess.h"
#include "logManager.h"
#include "settingsManager.h"
#include "structures.h"

namespace Chess {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class play : public System::Windows::Forms::Form {
	public:
		chess* game = new chess(1000);
		neuralNetwork* AI;
		string *weightsPath = new string;
		GameType gameType = GameType::SINGLE;
		bool isWhite = true;
		bool doTrain = false;
		int last = -1;

		play(Form^ mainForm, GameType gameType, bool isWhite, string weightsPath, 
			System::Windows::Forms::ProgressBar^ progressBar, bool doTrain) {
			this->isWhite = isWhite;
			this->mainForm = mainForm;
			this->gameType = gameType;
			*this->weightsPath = weightsPath;
			this->progressBar = progressBar;
			this->doTrain = doTrain;

			InitializeComponent();

			step_sound = gcnew System::Media::SoundPlayer("sounds/step_sound.wav");
			if (gameType != GameType::SINGLE) {
				AI = new neuralNetwork(settingsManager::getInstance().layers, settingsManager::getInstance().lr);
				try {
					AI->loadW(settingsManager::getInstance().path + "weights\\" + weightsPath);
				}
				catch (...) {
					AI->saveW(settingsManager::getInstance().path + "weights\\" + weightsPath);
				};
			}
			dropColor();
			update();
		}

#pragma region COMPONENTS
	private:

		System::ComponentModel::BackgroundWorker^ worker;
		System::Media::SoundPlayer^ step_sound;
		System::Windows::Forms::ProgressBar^ progressBar;
		System::ComponentModel::BackgroundWorker^ worker_ai;
	    System::Windows::Forms::Label^ log;

	    System::Windows::Forms::Label^ rl;
		System::Windows::Forms::Form^ mainForm;
		System::Windows::Forms::Button^ back;
		System::Windows::Forms::Label^ endGame;
		System::Windows::Forms::FlowLayoutPanel^ board;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::PictureBox^ pictureBox2;
		System::Windows::Forms::PictureBox^ pictureBox3;
		System::Windows::Forms::PictureBox^ pictureBox4;
		System::Windows::Forms::PictureBox^ pictureBox5;
		System::Windows::Forms::PictureBox^ pictureBox6;
		System::Windows::Forms::PictureBox^ pictureBox7;
		System::Windows::Forms::PictureBox^ pictureBox8;
		System::Windows::Forms::PictureBox^ pictureBox9;
		System::Windows::Forms::PictureBox^ pictureBox10;
		System::Windows::Forms::PictureBox^ pictureBox11;
		System::Windows::Forms::PictureBox^ pictureBox12;
		System::Windows::Forms::PictureBox^ pictureBox13;
		System::Windows::Forms::PictureBox^ pictureBox14;
		System::Windows::Forms::PictureBox^ pictureBox15;
		System::Windows::Forms::PictureBox^ pictureBox16;
		System::Windows::Forms::PictureBox^ pictureBox17;
		System::Windows::Forms::PictureBox^ pictureBox18;
		System::Windows::Forms::PictureBox^ pictureBox19;
		System::Windows::Forms::PictureBox^ pictureBox20;
		System::Windows::Forms::PictureBox^ pictureBox21;
		System::Windows::Forms::PictureBox^ pictureBox22;
		System::Windows::Forms::PictureBox^ pictureBox23;
		System::Windows::Forms::PictureBox^ pictureBox24;
		System::Windows::Forms::PictureBox^ pictureBox25;
		System::Windows::Forms::PictureBox^ pictureBox26;
		System::Windows::Forms::PictureBox^ pictureBox27;
		System::Windows::Forms::PictureBox^ pictureBox28;
		System::Windows::Forms::PictureBox^ pictureBox29;
		System::Windows::Forms::PictureBox^ pictureBox30;
		System::Windows::Forms::PictureBox^ pictureBox31;
		System::Windows::Forms::PictureBox^ pictureBox32;
		System::Windows::Forms::PictureBox^ pictureBox33;
		System::Windows::Forms::PictureBox^ pictureBox34;
		System::Windows::Forms::PictureBox^ pictureBox35;
		System::Windows::Forms::PictureBox^ pictureBox36;
		System::Windows::Forms::PictureBox^ pictureBox37;
		System::Windows::Forms::PictureBox^ pictureBox38;
		System::Windows::Forms::PictureBox^ pictureBox39;
		System::Windows::Forms::PictureBox^ pictureBox40;
		System::Windows::Forms::PictureBox^ pictureBox41;
		System::Windows::Forms::PictureBox^ pictureBox42;
		System::Windows::Forms::PictureBox^ pictureBox43;
		System::Windows::Forms::PictureBox^ pictureBox44;
		System::Windows::Forms::PictureBox^ pictureBox45;
		System::Windows::Forms::PictureBox^ pictureBox46;
		System::Windows::Forms::PictureBox^ pictureBox47;
		System::Windows::Forms::PictureBox^ pictureBox48;
		System::Windows::Forms::PictureBox^ pictureBox49;
		System::Windows::Forms::PictureBox^ pictureBox50;
		System::Windows::Forms::PictureBox^ pictureBox51;
		System::Windows::Forms::PictureBox^ pictureBox52;
		System::Windows::Forms::PictureBox^ pictureBox53;
		System::Windows::Forms::PictureBox^ pictureBox54;
		System::Windows::Forms::PictureBox^ pictureBox55;
		System::Windows::Forms::PictureBox^ pictureBox56;
		System::Windows::Forms::PictureBox^ pictureBox57;
		System::Windows::Forms::PictureBox^ pictureBox58;
		System::Windows::Forms::PictureBox^ pictureBox59;
		System::Windows::Forms::PictureBox^ pictureBox60;
		System::Windows::Forms::PictureBox^ pictureBox61;
		System::Windows::Forms::PictureBox^ pictureBox62;
		System::Windows::Forms::PictureBox^ pictureBox63;
		System::Windows::Forms::PictureBox^ pictureBox64;
		System::ComponentModel::Container^ components;
#pragma endregion

	protected:
		~play() {
			if (components) {
				delete components;
				delete mainForm;
				delete game;
				delete AI;
				delete weightsPath;
			}
		}
		void update() {
			string pos = "";
			if (isWhite) pos = game->getStringWhitePos();
			else pos = game->getStringBlackPos();
			for (int i = 0; i < board->Controls->Count; ++i) {
				board->Controls[i]->BackgroundImage = nullptr;
				string num = to_string(i);
				System::String^ name = gcnew System::String(num.c_str());
				board->Controls[i]->Name = name;
				board->Controls[i]->Cursor = Cursors::Hand;
				if (pos[i] != ' ') {
					string file = "icons/" + string(1, pos[i]) + ".png";
					System::String^ s = gcnew System::String(file.c_str());
					board->Controls[i]->BackgroundImage = Image::FromFile(s);
				}
			}
		}
		void dropColor() {
			bool white = isWhite;
			for (int i = 0; i < this->board->Controls->Count; ++i) {
				if (i % 8 != 0) white = !white;
				if(white) this->board->Controls[i]->BackColor = System::Drawing::Color::GhostWhite;
				else this->board->Controls[i]->BackColor = System::Drawing::Color::CadetBlue;
			}
		}
		void simulate() {
			game->setMaxSteps(settingsManager::getInstance().maxSteps);
			this->back->Visible = false;
			worker->RunWorkerAsync(1);
		}
		step toStep(int from, int to) {
			int a = from / 8;
			int b = from % 8;
			int c = to / 8;
			int d = to % 8;
			return { {a, b}, {c, d} };
		}
		coords toCoords(int from) {
			int a = from / 8;
			int b = from % 8;
			return { a, b };
		}
		int toComponent(coords v) {
			return 8 * v.row + v.column;
		}
		void updateEndGame() {
			endGame->Text = gcnew String(settingsManager::getInstance().lang("Game.EndGame." + game->getStatus()).c_str());
		}
		void clearEndGame() {
			endGame->Text = "";
		}
		void clearLogs() {
			log->Text = "";
		}
		void updateLogs() {
			log->Text = gcnew String(settingsManager::getInstance().lang("Game.Training").c_str());
		}
		void doneLogs() {
			log->Text = gcnew String(settingsManager::getInstance().lang("Game.Done").c_str());
		}
		void updateProgressBar() {
			progressBar->Value++;
		}
		void backUpdate(bool ch) {
			back->Enabled = ch;
		}
		void closeForm() {
			this->Close();
		}
#pragma region GUI
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(play::typeid));
			this->board = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox37 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox38 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox39 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox40 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox41 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox42 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox43 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox44 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox45 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox46 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox47 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox48 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox49 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox50 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox51 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox52 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox53 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox54 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox55 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox56 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox57 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox58 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox59 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox60 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox61 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox62 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox63 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox64 = (gcnew System::Windows::Forms::PictureBox());
			this->worker = (gcnew System::ComponentModel::BackgroundWorker());
			this->back = (gcnew System::Windows::Forms::Button());
			this->worker_ai = (gcnew System::ComponentModel::BackgroundWorker());
			this->log = (gcnew System::Windows::Forms::Label());
			this->endGame = (gcnew System::Windows::Forms::Label());
			this->board->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox38))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox39))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox40))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox41))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox42))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox43))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox44))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox45))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox46))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox47))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox48))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox49))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox50))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox51))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox52))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox53))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox54))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox55))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox56))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox57))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox58))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox59))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox60))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox61))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox62))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox63))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox64))->BeginInit();
			this->SuspendLayout();
			// 
			// board
			// 
			this->board->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->board->Controls->Add(this->pictureBox1);
			this->board->Controls->Add(this->pictureBox2);
			this->board->Controls->Add(this->pictureBox3);
			this->board->Controls->Add(this->pictureBox4);
			this->board->Controls->Add(this->pictureBox5);
			this->board->Controls->Add(this->pictureBox6);
			this->board->Controls->Add(this->pictureBox7);
			this->board->Controls->Add(this->pictureBox8);
			this->board->Controls->Add(this->pictureBox9);
			this->board->Controls->Add(this->pictureBox10);
			this->board->Controls->Add(this->pictureBox11);
			this->board->Controls->Add(this->pictureBox12);
			this->board->Controls->Add(this->pictureBox13);
			this->board->Controls->Add(this->pictureBox14);
			this->board->Controls->Add(this->pictureBox15);
			this->board->Controls->Add(this->pictureBox16);
			this->board->Controls->Add(this->pictureBox17);
			this->board->Controls->Add(this->pictureBox18);
			this->board->Controls->Add(this->pictureBox19);
			this->board->Controls->Add(this->pictureBox20);
			this->board->Controls->Add(this->pictureBox21);
			this->board->Controls->Add(this->pictureBox22);
			this->board->Controls->Add(this->pictureBox23);
			this->board->Controls->Add(this->pictureBox24);
			this->board->Controls->Add(this->pictureBox25);
			this->board->Controls->Add(this->pictureBox26);
			this->board->Controls->Add(this->pictureBox27);
			this->board->Controls->Add(this->pictureBox28);
			this->board->Controls->Add(this->pictureBox29);
			this->board->Controls->Add(this->pictureBox30);
			this->board->Controls->Add(this->pictureBox31);
			this->board->Controls->Add(this->pictureBox32);
			this->board->Controls->Add(this->pictureBox33);
			this->board->Controls->Add(this->pictureBox34);
			this->board->Controls->Add(this->pictureBox35);
			this->board->Controls->Add(this->pictureBox36);
			this->board->Controls->Add(this->pictureBox37);
			this->board->Controls->Add(this->pictureBox38);
			this->board->Controls->Add(this->pictureBox39);
			this->board->Controls->Add(this->pictureBox40);
			this->board->Controls->Add(this->pictureBox41);
			this->board->Controls->Add(this->pictureBox42);
			this->board->Controls->Add(this->pictureBox43);
			this->board->Controls->Add(this->pictureBox44);
			this->board->Controls->Add(this->pictureBox45);
			this->board->Controls->Add(this->pictureBox46);
			this->board->Controls->Add(this->pictureBox47);
			this->board->Controls->Add(this->pictureBox48);
			this->board->Controls->Add(this->pictureBox49);
			this->board->Controls->Add(this->pictureBox50);
			this->board->Controls->Add(this->pictureBox51);
			this->board->Controls->Add(this->pictureBox52);
			this->board->Controls->Add(this->pictureBox53);
			this->board->Controls->Add(this->pictureBox54);
			this->board->Controls->Add(this->pictureBox55);
			this->board->Controls->Add(this->pictureBox56);
			this->board->Controls->Add(this->pictureBox57);
			this->board->Controls->Add(this->pictureBox58);
			this->board->Controls->Add(this->pictureBox59);
			this->board->Controls->Add(this->pictureBox60);
			this->board->Controls->Add(this->pictureBox61);
			this->board->Controls->Add(this->pictureBox62);
			this->board->Controls->Add(this->pictureBox63);
			this->board->Controls->Add(this->pictureBox64);
			this->board->Location = System::Drawing::Point(16, 15);
			this->board->Margin = System::Windows::Forms::Padding(4);
			this->board->Name = L"board";
			this->board->Size = System::Drawing::Size(803, 803);
			this->board->TabIndex = 2;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &play::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox2->Location = System::Drawing::Point(100, 0);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(100, 100);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &play::pictureBox2_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox3->Location = System::Drawing::Point(200, 0);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(100, 100);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &play::pictureBox3_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox4->Location = System::Drawing::Point(300, 0);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(100, 100);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &play::pictureBox4_Click);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox5->Location = System::Drawing::Point(400, 0);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(100, 100);
			this->pictureBox5->TabIndex = 4;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &play::pictureBox5_Click);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox6->Location = System::Drawing::Point(500, 0);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(100, 100);
			this->pictureBox6->TabIndex = 5;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &play::pictureBox6_Click);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox7->Location = System::Drawing::Point(600, 0);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(100, 100);
			this->pictureBox7->TabIndex = 6;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &play::pictureBox7_Click);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox8->Location = System::Drawing::Point(700, 0);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(100, 100);
			this->pictureBox8->TabIndex = 7;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &play::pictureBox8_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox9->Location = System::Drawing::Point(0, 100);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(100, 100);
			this->pictureBox9->TabIndex = 8;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &play::pictureBox9_Click);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox10->Location = System::Drawing::Point(100, 100);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(100, 100);
			this->pictureBox10->TabIndex = 9;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &play::pictureBox10_Click);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox11->Location = System::Drawing::Point(200, 100);
			this->pictureBox11->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(100, 100);
			this->pictureBox11->TabIndex = 10;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->Click += gcnew System::EventHandler(this, &play::pictureBox11_Click);
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox12->Location = System::Drawing::Point(300, 100);
			this->pictureBox12->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(100, 100);
			this->pictureBox12->TabIndex = 11;
			this->pictureBox12->TabStop = false;
			this->pictureBox12->Click += gcnew System::EventHandler(this, &play::pictureBox12_Click);
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox13->Location = System::Drawing::Point(400, 100);
			this->pictureBox13->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(100, 100);
			this->pictureBox13->TabIndex = 12;
			this->pictureBox13->TabStop = false;
			this->pictureBox13->Click += gcnew System::EventHandler(this, &play::pictureBox13_Click);
			// 
			// pictureBox14
			// 
			this->pictureBox14->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox14->Location = System::Drawing::Point(500, 100);
			this->pictureBox14->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(100, 100);
			this->pictureBox14->TabIndex = 13;
			this->pictureBox14->TabStop = false;
			this->pictureBox14->Click += gcnew System::EventHandler(this, &play::pictureBox14_Click);
			// 
			// pictureBox15
			// 
			this->pictureBox15->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox15->Location = System::Drawing::Point(600, 100);
			this->pictureBox15->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(100, 100);
			this->pictureBox15->TabIndex = 14;
			this->pictureBox15->TabStop = false;
			this->pictureBox15->Click += gcnew System::EventHandler(this, &play::pictureBox15_Click);
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox16->Location = System::Drawing::Point(700, 100);
			this->pictureBox16->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(100, 100);
			this->pictureBox16->TabIndex = 15;
			this->pictureBox16->TabStop = false;
			this->pictureBox16->Click += gcnew System::EventHandler(this, &play::pictureBox16_Click);
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox17->Location = System::Drawing::Point(0, 200);
			this->pictureBox17->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(100, 100);
			this->pictureBox17->TabIndex = 16;
			this->pictureBox17->TabStop = false;
			this->pictureBox17->Click += gcnew System::EventHandler(this, &play::pictureBox17_Click);
			// 
			// pictureBox18
			// 
			this->pictureBox18->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox18->Location = System::Drawing::Point(100, 200);
			this->pictureBox18->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(100, 100);
			this->pictureBox18->TabIndex = 17;
			this->pictureBox18->TabStop = false;
			this->pictureBox18->Click += gcnew System::EventHandler(this, &play::pictureBox18_Click);
			// 
			// pictureBox19
			// 
			this->pictureBox19->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox19->Location = System::Drawing::Point(200, 200);
			this->pictureBox19->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(100, 100);
			this->pictureBox19->TabIndex = 18;
			this->pictureBox19->TabStop = false;
			this->pictureBox19->Click += gcnew System::EventHandler(this, &play::pictureBox19_Click);
			// 
			// pictureBox20
			// 
			this->pictureBox20->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox20->Location = System::Drawing::Point(300, 200);
			this->pictureBox20->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(100, 100);
			this->pictureBox20->TabIndex = 19;
			this->pictureBox20->TabStop = false;
			this->pictureBox20->Click += gcnew System::EventHandler(this, &play::pictureBox20_Click);
			// 
			// pictureBox21
			// 
			this->pictureBox21->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox21->Location = System::Drawing::Point(400, 200);
			this->pictureBox21->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(100, 100);
			this->pictureBox21->TabIndex = 20;
			this->pictureBox21->TabStop = false;
			this->pictureBox21->Click += gcnew System::EventHandler(this, &play::pictureBox21_Click);
			// 
			// pictureBox22
			// 
			this->pictureBox22->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox22->Location = System::Drawing::Point(500, 200);
			this->pictureBox22->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(100, 100);
			this->pictureBox22->TabIndex = 21;
			this->pictureBox22->TabStop = false;
			this->pictureBox22->Click += gcnew System::EventHandler(this, &play::pictureBox22_Click);
			// 
			// pictureBox23
			// 
			this->pictureBox23->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox23->Location = System::Drawing::Point(600, 200);
			this->pictureBox23->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(100, 100);
			this->pictureBox23->TabIndex = 22;
			this->pictureBox23->TabStop = false;
			this->pictureBox23->Click += gcnew System::EventHandler(this, &play::pictureBox23_Click);
			// 
			// pictureBox24
			// 
			this->pictureBox24->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox24->Location = System::Drawing::Point(700, 200);
			this->pictureBox24->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(100, 100);
			this->pictureBox24->TabIndex = 23;
			this->pictureBox24->TabStop = false;
			this->pictureBox24->Click += gcnew System::EventHandler(this, &play::pictureBox24_Click);
			// 
			// pictureBox25
			// 
			this->pictureBox25->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox25->Location = System::Drawing::Point(0, 300);
			this->pictureBox25->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(100, 100);
			this->pictureBox25->TabIndex = 24;
			this->pictureBox25->TabStop = false;
			this->pictureBox25->Click += gcnew System::EventHandler(this, &play::pictureBox25_Click);
			// 
			// pictureBox26
			// 
			this->pictureBox26->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox26->Location = System::Drawing::Point(100, 300);
			this->pictureBox26->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(100, 100);
			this->pictureBox26->TabIndex = 25;
			this->pictureBox26->TabStop = false;
			this->pictureBox26->Click += gcnew System::EventHandler(this, &play::pictureBox26_Click);
			// 
			// pictureBox27
			// 
			this->pictureBox27->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox27->Location = System::Drawing::Point(200, 300);
			this->pictureBox27->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(100, 100);
			this->pictureBox27->TabIndex = 26;
			this->pictureBox27->TabStop = false;
			this->pictureBox27->Click += gcnew System::EventHandler(this, &play::pictureBox27_Click);
			// 
			// pictureBox28
			// 
			this->pictureBox28->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox28->Location = System::Drawing::Point(300, 300);
			this->pictureBox28->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(100, 100);
			this->pictureBox28->TabIndex = 27;
			this->pictureBox28->TabStop = false;
			this->pictureBox28->Click += gcnew System::EventHandler(this, &play::pictureBox28_Click);
			// 
			// pictureBox29
			// 
			this->pictureBox29->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox29->Location = System::Drawing::Point(400, 300);
			this->pictureBox29->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(100, 100);
			this->pictureBox29->TabIndex = 28;
			this->pictureBox29->TabStop = false;
			this->pictureBox29->Click += gcnew System::EventHandler(this, &play::pictureBox29_Click);
			// 
			// pictureBox30
			// 
			this->pictureBox30->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox30->Location = System::Drawing::Point(500, 300);
			this->pictureBox30->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(100, 100);
			this->pictureBox30->TabIndex = 29;
			this->pictureBox30->TabStop = false;
			this->pictureBox30->Click += gcnew System::EventHandler(this, &play::pictureBox30_Click);
			// 
			// pictureBox31
			// 
			this->pictureBox31->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox31->Location = System::Drawing::Point(600, 300);
			this->pictureBox31->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(100, 100);
			this->pictureBox31->TabIndex = 30;
			this->pictureBox31->TabStop = false;
			this->pictureBox31->Click += gcnew System::EventHandler(this, &play::pictureBox31_Click);
			// 
			// pictureBox32
			// 
			this->pictureBox32->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox32->Location = System::Drawing::Point(700, 300);
			this->pictureBox32->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(100, 100);
			this->pictureBox32->TabIndex = 31;
			this->pictureBox32->TabStop = false;
			this->pictureBox32->Click += gcnew System::EventHandler(this, &play::pictureBox32_Click);
			// 
			// pictureBox33
			// 
			this->pictureBox33->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox33->Location = System::Drawing::Point(0, 400);
			this->pictureBox33->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(100, 100);
			this->pictureBox33->TabIndex = 32;
			this->pictureBox33->TabStop = false;
			this->pictureBox33->Click += gcnew System::EventHandler(this, &play::pictureBox33_Click);
			// 
			// pictureBox34
			// 
			this->pictureBox34->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox34->Location = System::Drawing::Point(100, 400);
			this->pictureBox34->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(100, 100);
			this->pictureBox34->TabIndex = 33;
			this->pictureBox34->TabStop = false;
			this->pictureBox34->Click += gcnew System::EventHandler(this, &play::pictureBox34_Click);
			// 
			// pictureBox35
			// 
			this->pictureBox35->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox35->Location = System::Drawing::Point(200, 400);
			this->pictureBox35->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(100, 100);
			this->pictureBox35->TabIndex = 34;
			this->pictureBox35->TabStop = false;
			this->pictureBox35->Click += gcnew System::EventHandler(this, &play::pictureBox35_Click);
			// 
			// pictureBox36
			// 
			this->pictureBox36->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox36->Location = System::Drawing::Point(300, 400);
			this->pictureBox36->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(100, 100);
			this->pictureBox36->TabIndex = 35;
			this->pictureBox36->TabStop = false;
			this->pictureBox36->Click += gcnew System::EventHandler(this, &play::pictureBox36_Click);
			// 
			// pictureBox37
			// 
			this->pictureBox37->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox37->Location = System::Drawing::Point(400, 400);
			this->pictureBox37->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox37->Name = L"pictureBox37";
			this->pictureBox37->Size = System::Drawing::Size(100, 100);
			this->pictureBox37->TabIndex = 36;
			this->pictureBox37->TabStop = false;
			this->pictureBox37->Click += gcnew System::EventHandler(this, &play::pictureBox37_Click);
			// 
			// pictureBox38
			// 
			this->pictureBox38->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox38->Location = System::Drawing::Point(500, 400);
			this->pictureBox38->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox38->Name = L"pictureBox38";
			this->pictureBox38->Size = System::Drawing::Size(100, 100);
			this->pictureBox38->TabIndex = 37;
			this->pictureBox38->TabStop = false;
			this->pictureBox38->Click += gcnew System::EventHandler(this, &play::pictureBox38_Click);
			// 
			// pictureBox39
			// 
			this->pictureBox39->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox39->Location = System::Drawing::Point(600, 400);
			this->pictureBox39->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox39->Name = L"pictureBox39";
			this->pictureBox39->Size = System::Drawing::Size(100, 100);
			this->pictureBox39->TabIndex = 38;
			this->pictureBox39->TabStop = false;
			this->pictureBox39->Click += gcnew System::EventHandler(this, &play::pictureBox39_Click);
			// 
			// pictureBox40
			// 
			this->pictureBox40->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox40->Location = System::Drawing::Point(700, 400);
			this->pictureBox40->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox40->Name = L"pictureBox40";
			this->pictureBox40->Size = System::Drawing::Size(100, 100);
			this->pictureBox40->TabIndex = 39;
			this->pictureBox40->TabStop = false;
			this->pictureBox40->Click += gcnew System::EventHandler(this, &play::pictureBox40_Click);
			// 
			// pictureBox41
			// 
			this->pictureBox41->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox41->Location = System::Drawing::Point(0, 500);
			this->pictureBox41->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox41->Name = L"pictureBox41";
			this->pictureBox41->Size = System::Drawing::Size(100, 100);
			this->pictureBox41->TabIndex = 40;
			this->pictureBox41->TabStop = false;
			this->pictureBox41->Click += gcnew System::EventHandler(this, &play::pictureBox41_Click);
			// 
			// pictureBox42
			// 
			this->pictureBox42->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox42->Location = System::Drawing::Point(100, 500);
			this->pictureBox42->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox42->Name = L"pictureBox42";
			this->pictureBox42->Size = System::Drawing::Size(100, 100);
			this->pictureBox42->TabIndex = 41;
			this->pictureBox42->TabStop = false;
			this->pictureBox42->Click += gcnew System::EventHandler(this, &play::pictureBox42_Click);
			// 
			// pictureBox43
			// 
			this->pictureBox43->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox43->Location = System::Drawing::Point(200, 500);
			this->pictureBox43->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox43->Name = L"pictureBox43";
			this->pictureBox43->Size = System::Drawing::Size(100, 100);
			this->pictureBox43->TabIndex = 42;
			this->pictureBox43->TabStop = false;
			this->pictureBox43->Click += gcnew System::EventHandler(this, &play::pictureBox43_Click);
			// 
			// pictureBox44
			// 
			this->pictureBox44->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox44->Location = System::Drawing::Point(300, 500);
			this->pictureBox44->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox44->Name = L"pictureBox44";
			this->pictureBox44->Size = System::Drawing::Size(100, 100);
			this->pictureBox44->TabIndex = 43;
			this->pictureBox44->TabStop = false;
			this->pictureBox44->Click += gcnew System::EventHandler(this, &play::pictureBox44_Click);
			// 
			// pictureBox45
			// 
			this->pictureBox45->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox45->Location = System::Drawing::Point(400, 500);
			this->pictureBox45->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox45->Name = L"pictureBox45";
			this->pictureBox45->Size = System::Drawing::Size(100, 100);
			this->pictureBox45->TabIndex = 44;
			this->pictureBox45->TabStop = false;
			this->pictureBox45->Click += gcnew System::EventHandler(this, &play::pictureBox45_Click);
			// 
			// pictureBox46
			// 
			this->pictureBox46->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox46->Location = System::Drawing::Point(500, 500);
			this->pictureBox46->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox46->Name = L"pictureBox46";
			this->pictureBox46->Size = System::Drawing::Size(100, 100);
			this->pictureBox46->TabIndex = 45;
			this->pictureBox46->TabStop = false;
			this->pictureBox46->Click += gcnew System::EventHandler(this, &play::pictureBox46_Click);
			// 
			// pictureBox47
			// 
			this->pictureBox47->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox47->Location = System::Drawing::Point(600, 500);
			this->pictureBox47->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox47->Name = L"pictureBox47";
			this->pictureBox47->Size = System::Drawing::Size(100, 100);
			this->pictureBox47->TabIndex = 46;
			this->pictureBox47->TabStop = false;
			this->pictureBox47->Click += gcnew System::EventHandler(this, &play::pictureBox47_Click);
			// 
			// pictureBox48
			// 
			this->pictureBox48->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox48->Location = System::Drawing::Point(700, 500);
			this->pictureBox48->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox48->Name = L"pictureBox48";
			this->pictureBox48->Size = System::Drawing::Size(100, 100);
			this->pictureBox48->TabIndex = 47;
			this->pictureBox48->TabStop = false;
			this->pictureBox48->Click += gcnew System::EventHandler(this, &play::pictureBox48_Click);
			// 
			// pictureBox49
			// 
			this->pictureBox49->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox49->Location = System::Drawing::Point(0, 600);
			this->pictureBox49->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox49->Name = L"pictureBox49";
			this->pictureBox49->Size = System::Drawing::Size(100, 100);
			this->pictureBox49->TabIndex = 48;
			this->pictureBox49->TabStop = false;
			this->pictureBox49->Click += gcnew System::EventHandler(this, &play::pictureBox49_Click);
			// 
			// pictureBox50
			// 
			this->pictureBox50->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox50->Location = System::Drawing::Point(100, 600);
			this->pictureBox50->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox50->Name = L"pictureBox50";
			this->pictureBox50->Size = System::Drawing::Size(100, 100);
			this->pictureBox50->TabIndex = 49;
			this->pictureBox50->TabStop = false;
			this->pictureBox50->Click += gcnew System::EventHandler(this, &play::pictureBox50_Click);
			// 
			// pictureBox51
			// 
			this->pictureBox51->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox51->Location = System::Drawing::Point(200, 600);
			this->pictureBox51->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox51->Name = L"pictureBox51";
			this->pictureBox51->Size = System::Drawing::Size(100, 100);
			this->pictureBox51->TabIndex = 50;
			this->pictureBox51->TabStop = false;
			this->pictureBox51->Click += gcnew System::EventHandler(this, &play::pictureBox51_Click);
			// 
			// pictureBox52
			// 
			this->pictureBox52->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox52->Location = System::Drawing::Point(300, 600);
			this->pictureBox52->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox52->Name = L"pictureBox52";
			this->pictureBox52->Size = System::Drawing::Size(100, 100);
			this->pictureBox52->TabIndex = 51;
			this->pictureBox52->TabStop = false;
			this->pictureBox52->Click += gcnew System::EventHandler(this, &play::pictureBox52_Click);
			// 
			// pictureBox53
			// 
			this->pictureBox53->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox53->Location = System::Drawing::Point(400, 600);
			this->pictureBox53->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox53->Name = L"pictureBox53";
			this->pictureBox53->Size = System::Drawing::Size(100, 100);
			this->pictureBox53->TabIndex = 52;
			this->pictureBox53->TabStop = false;
			this->pictureBox53->Click += gcnew System::EventHandler(this, &play::pictureBox53_Click);
			// 
			// pictureBox54
			// 
			this->pictureBox54->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox54->Location = System::Drawing::Point(500, 600);
			this->pictureBox54->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox54->Name = L"pictureBox54";
			this->pictureBox54->Size = System::Drawing::Size(100, 100);
			this->pictureBox54->TabIndex = 53;
			this->pictureBox54->TabStop = false;
			this->pictureBox54->Click += gcnew System::EventHandler(this, &play::pictureBox54_Click);
			// 
			// pictureBox55
			// 
			this->pictureBox55->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox55->Location = System::Drawing::Point(600, 600);
			this->pictureBox55->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox55->Name = L"pictureBox55";
			this->pictureBox55->Size = System::Drawing::Size(100, 100);
			this->pictureBox55->TabIndex = 54;
			this->pictureBox55->TabStop = false;
			this->pictureBox55->Click += gcnew System::EventHandler(this, &play::pictureBox55_Click);
			// 
			// pictureBox56
			// 
			this->pictureBox56->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox56->Location = System::Drawing::Point(700, 600);
			this->pictureBox56->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox56->Name = L"pictureBox56";
			this->pictureBox56->Size = System::Drawing::Size(100, 100);
			this->pictureBox56->TabIndex = 55;
			this->pictureBox56->TabStop = false;
			this->pictureBox56->Click += gcnew System::EventHandler(this, &play::pictureBox56_Click);
			// 
			// pictureBox57
			// 
			this->pictureBox57->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox57->Location = System::Drawing::Point(0, 700);
			this->pictureBox57->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox57->Name = L"pictureBox57";
			this->pictureBox57->Size = System::Drawing::Size(100, 100);
			this->pictureBox57->TabIndex = 56;
			this->pictureBox57->TabStop = false;
			this->pictureBox57->Click += gcnew System::EventHandler(this, &play::pictureBox57_Click);
			// 
			// pictureBox58
			// 
			this->pictureBox58->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox58->Location = System::Drawing::Point(100, 700);
			this->pictureBox58->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox58->Name = L"pictureBox58";
			this->pictureBox58->Size = System::Drawing::Size(100, 100);
			this->pictureBox58->TabIndex = 57;
			this->pictureBox58->TabStop = false;
			this->pictureBox58->Click += gcnew System::EventHandler(this, &play::pictureBox58_Click);
			// 
			// pictureBox59
			// 
			this->pictureBox59->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox59->Location = System::Drawing::Point(200, 700);
			this->pictureBox59->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox59->Name = L"pictureBox59";
			this->pictureBox59->Size = System::Drawing::Size(100, 100);
			this->pictureBox59->TabIndex = 58;
			this->pictureBox59->TabStop = false;
			this->pictureBox59->Click += gcnew System::EventHandler(this, &play::pictureBox59_Click);
			// 
			// pictureBox60
			// 
			this->pictureBox60->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox60->Location = System::Drawing::Point(300, 700);
			this->pictureBox60->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox60->Name = L"pictureBox60";
			this->pictureBox60->Size = System::Drawing::Size(100, 100);
			this->pictureBox60->TabIndex = 59;
			this->pictureBox60->TabStop = false;
			this->pictureBox60->Click += gcnew System::EventHandler(this, &play::pictureBox60_Click);
			// 
			// pictureBox61
			// 
			this->pictureBox61->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox61->Location = System::Drawing::Point(400, 700);
			this->pictureBox61->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox61->Name = L"pictureBox61";
			this->pictureBox61->Size = System::Drawing::Size(100, 100);
			this->pictureBox61->TabIndex = 60;
			this->pictureBox61->TabStop = false;
			this->pictureBox61->Click += gcnew System::EventHandler(this, &play::pictureBox61_Click);
			// 
			// pictureBox62
			// 
			this->pictureBox62->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox62->Location = System::Drawing::Point(500, 700);
			this->pictureBox62->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox62->Name = L"pictureBox62";
			this->pictureBox62->Size = System::Drawing::Size(100, 100);
			this->pictureBox62->TabIndex = 61;
			this->pictureBox62->TabStop = false;
			this->pictureBox62->Click += gcnew System::EventHandler(this, &play::pictureBox62_Click);
			// 
			// pictureBox63
			// 
			this->pictureBox63->BackColor = System::Drawing::Color::CadetBlue;
			this->pictureBox63->Location = System::Drawing::Point(600, 700);
			this->pictureBox63->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox63->Name = L"pictureBox63";
			this->pictureBox63->Size = System::Drawing::Size(100, 100);
			this->pictureBox63->TabIndex = 62;
			this->pictureBox63->TabStop = false;
			this->pictureBox63->Click += gcnew System::EventHandler(this, &play::pictureBox63_Click);
			// 
			// pictureBox64
			// 
			this->pictureBox64->BackColor = System::Drawing::Color::GhostWhite;
			this->pictureBox64->Location = System::Drawing::Point(700, 700);
			this->pictureBox64->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox64->Name = L"pictureBox64";
			this->pictureBox64->Size = System::Drawing::Size(100, 100);
			this->pictureBox64->TabIndex = 63;
			this->pictureBox64->TabStop = false;
			this->pictureBox64->Click += gcnew System::EventHandler(this, &play::pictureBox64_Click);
			// 
			// worker
			// 
			this->worker->WorkerSupportsCancellation = true;
			this->worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &play::worker_DoWork);
			// 
			// back
			// 
			this->back->Location = System::Drawing::Point(874, 28);
			this->back->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(314, 61);
			this->back->TabIndex = 1;
			this->back->Text = L"В главное меню";
			this->back->UseVisualStyleBackColor = true;
			this->back->Click += gcnew System::EventHandler(this, &play::back_Click);
			// 
			// worker_ai
			// 
			this->worker_ai->WorkerSupportsCancellation = true;
			this->worker_ai->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &play::worker_ai_DoWork);
			// 
			// log
			// 
			this->log->Location = System::Drawing::Point(874, 271);
			this->log->Name = L"log";
			this->log->Size = System::Drawing::Size(314, 167);
			this->log->TabIndex = 5;
			this->log->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// endGame
			// 
			this->endGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->endGame->Location = System::Drawing::Point(874, 106);
			this->endGame->Name = L"endGame";
			this->endGame->Size = System::Drawing::Size(314, 155);
			this->endGame->TabIndex = 7;
			this->endGame->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// play
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1250, 837);
			this->ControlBox = false;
			this->Controls->Add(this->endGame);
			this->Controls->Add(this->log);
			this->Controls->Add(this->board);
			this->Controls->Add(this->back);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"play";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Шахматы";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &play::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &play::play_Load);
			this->board->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox38))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox39))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox40))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox41))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox42))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox43))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox44))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox45))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox46))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox47))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox48))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox49))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox50))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox51))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox52))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox53))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox54))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox55))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox56))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox57))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox58))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox59))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox60))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox61))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox62))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox63))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox64))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void play_Load(System::Object^ sender, System::EventArgs^ e) {
			this->Text = gcnew String(settingsManager::getInstance().lang("Main").c_str());
			back->Text = gcnew String(settingsManager::getInstance().lang("Game.Back").c_str());
			endGame->Text = "";
			log->Text = "";

			if (gameType == GameType::AI && !isWhite) worker_ai->RunWorkerAsync();
			if (gameType == GameType::TRAIN) simulate();
		}
		System::Void back_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
			if (worker->IsBusy) worker->CancelAsync();
			if (worker_ai->IsBusy) worker_ai->CancelAsync();
			if (gameType == GameType::TRAIN) progressBar->Value = progressBar->Maximum;
		}
		System::Void Form1_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			mainForm->Show();
			if (worker->IsBusy) worker->CancelAsync();
			if (worker_ai->IsBusy) worker_ai->CancelAsync();
			if (gameType == GameType::TRAIN) progressBar->Value = progressBar->Maximum;
		}
		System::Void click(System::Windows::Forms::PictureBox^ pb, int n) {
			if (last != -2 && gameType != GameType::TRAIN) {
				if (last == -1) {
					if (pb->BackgroundImage != nullptr) {
						if (!isWhite) n = 63 - n;
						last = n;
						coords v = toCoords(last);
						for (step st : game->current_steps) {
							if (st.from == v) {
								int ind = toComponent(st.to);
								if (!isWhite) ind = 63 - ind;
								this->board->Controls[ind]->BackColor = System::Drawing::Color::LightSteelBlue;
							}
						}
						pb->BackColor = System::Drawing::Color::Red;
					}
				}
				else {
					if (!isWhite) n = 63 - n;
					step st = toStep(last, n);
					if (game->isEqualColor(st.from, st.to)) {
						last = n;
						dropColor();
						coords v = toCoords(n);
						for (step st : game->current_steps) {
							if (st.from == v) {
								int ind = toComponent(st.to);
								if (!isWhite) ind = 63 - ind;
								this->board->Controls[ind]->BackColor = System::Drawing::Color::LightSteelBlue;
							}
						}
						pb->BackColor = System::Drawing::Color::Red;
					}
					else {
						if (last != n) {
							bool valid = game->doStep(st);
							if (valid) {
								if(settingsManager::getInstance().playSound) step_sound->Play();
								string status = game->getStatus();
								if (status != "ingame") {
									this->endGame->Text = gcnew String(settingsManager::getInstance().lang("Game.EndGame."+status).c_str());
									last = -2;
									if (doTrain) {
										worker_ai->RunWorkerAsync();
									}
								}
								else if (gameType == GameType::AI) {
									worker_ai->RunWorkerAsync();
								}
							}
						}
						dropColor();
						update();
						last = -1;
					}
				}
			}
		}
		System::Void worker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			while (true) {
				endGame->Invoke(gcnew Action(this, &play::clearLogs));
				string status = game->getStatus();

				if (worker->CancellationPending) {
					e->Cancel = true;
					break;
				}

				while (status == "ingame") {
					if (worker->CancellationPending) {
						e->Cancel = true;
						break;
					}
					game->doStepAI(*AI);
					board->Invoke(gcnew Action(this, &play::update));
					if (settingsManager::getInstance().playSound) step_sound->Play();
					status = game->getStatus();
				}
				if (!e->Cancel) {
					endGame->Invoke(gcnew Action(this, &play::updateEndGame));
					log->Invoke(gcnew Action(this, &play::updateLogs));
					game->trainAI(*AI);
					AI->saveW(settingsManager::getInstance().path+"weights\\" + *weightsPath);
					progressBar->Invoke(gcnew Action(this, &play::updateProgressBar));
					if (progressBar->Value == progressBar->Maximum) {
						Invoke(gcnew Action(this, &play::closeForm));
						break;
					}
					else {
						game->replay();
						endGame->Invoke(gcnew Action(this, &play::clearEndGame));
						dropColor();
						board->Invoke(gcnew Action(this, &play::update));
					}
				}
			}
			worker->CancelAsync();
		}
		System::Void worker_ai_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			string status = game->getStatus();
			if (status != "ingame") {
				log->Invoke(gcnew Action(this, &play::updateLogs));
				back->Invoke(gcnew Action<bool>(this, &play::backUpdate), false);
				game->trainAI(*AI);
				AI->saveW(settingsManager::getInstance().path+"weights\\" + *weightsPath);
				log->Invoke(gcnew Action(this, &play::doneLogs));
				back->Invoke(gcnew Action<bool>(this, &play::backUpdate), true);
			}
			else {
				game->doStepAI(*AI);
				if (settingsManager::getInstance().playSound) step_sound->Play();
				status = game->getStatus();
				if (status != "ingame") {
					string file = "icons/" + status + ".png";
					endGame->Invoke(gcnew Action(this, &play::updateEndGame));
					last = -2;
					if (doTrain) {
						log->Invoke(gcnew Action(this, &play::updateLogs));
						back->Invoke(gcnew Action<bool>(this, &play::backUpdate), false);
						game->trainAI(*AI);
						AI->saveW(settingsManager::getInstance().path+"weights\\" + *weightsPath);
						log->Invoke(gcnew Action(this, &play::doneLogs));
						back->Invoke(gcnew Action<bool>(this, &play::backUpdate), true);
					}
				}
				board->Invoke(gcnew Action(this, &play::update));
				if (last != -1 && last != -2) {
					coords v = toCoords(last);
					for (step st : game->current_steps) {
						if (st.from == v) {
							int ind = toComponent(st.to);
							if (!isWhite) ind = 63 - ind;
							board->Controls[ind]->BackColor = System::Drawing::Color::LightSteelBlue;
						}
					}
				}
			}
			worker_ai->CancelAsync();
		}
#pragma region CEILS
		System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox1, 0);
		}
		System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox2, 1);
		}
		System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox3, 2);
		}
		System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox4, 3);
		}
		System::Void pictureBox5_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox5, 4);
		}
		System::Void pictureBox6_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox6, 5);
		}
		System::Void pictureBox7_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox7, 6);
		}
		System::Void pictureBox8_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox8, 7);
		}
		System::Void pictureBox9_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox9, 8);
		}
		System::Void pictureBox10_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox10, 9);
		}
		System::Void pictureBox11_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox11, 10);
		}
		System::Void pictureBox12_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox12, 11);
		}
		System::Void pictureBox13_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox13, 12);
		}
		System::Void pictureBox14_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox14, 13);
		}
		System::Void pictureBox15_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox15, 14);
		}
		System::Void pictureBox16_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox16, 15);
		}
		System::Void pictureBox17_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox17, 16);
		}
		System::Void pictureBox18_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox18, 17);
		}
		System::Void pictureBox19_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox19, 18);
		}
		System::Void pictureBox20_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox20, 19);
		}
		System::Void pictureBox21_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox21, 20);
		}
		System::Void pictureBox22_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox22, 21);
		}
		System::Void pictureBox23_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox23, 22);
		}
		System::Void pictureBox24_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox24, 23);
		}
		System::Void pictureBox25_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox25, 24);
		}
		System::Void pictureBox26_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox26, 25);
		}
		System::Void pictureBox27_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox27, 26);
		}
		System::Void pictureBox28_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox28, 27);
		}
		System::Void pictureBox29_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox29, 28);
		}
		System::Void pictureBox30_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox30, 29);
		}
		System::Void pictureBox31_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox31, 30);
		}
		System::Void pictureBox32_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox32, 31);
		}
		System::Void pictureBox33_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox33, 32);
		}
		System::Void pictureBox34_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox34, 33);
		}
		System::Void pictureBox35_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox35, 34);
		}
		System::Void pictureBox36_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox36, 35);
		}
		System::Void pictureBox37_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox37, 36);
		}
		System::Void pictureBox38_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox38, 37);
		}
		System::Void pictureBox39_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox39, 38);
		}
		System::Void pictureBox40_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox40, 39);
		}
		System::Void pictureBox41_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox41, 40);
		}
		System::Void pictureBox42_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox42, 41);
		}
		System::Void pictureBox43_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox43, 42);
		}
		System::Void pictureBox44_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox44, 43);
		}
		System::Void pictureBox45_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox45, 44);
		}
		System::Void pictureBox46_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox46, 45);
		}
		System::Void pictureBox47_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox47, 46);
		}
		System::Void pictureBox48_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox48, 47);
		}
		System::Void pictureBox49_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox49, 48);
		}
		System::Void pictureBox50_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox50, 49);
		}
		System::Void pictureBox51_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox51, 50);
		}
		System::Void pictureBox52_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox52, 51);
		}
		System::Void pictureBox53_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox53, 52);
		}
		System::Void pictureBox54_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox54, 53);
		}
		System::Void pictureBox55_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox55, 54);
		}
		System::Void pictureBox56_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox56, 55);
		}
		System::Void pictureBox57_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox57, 56);
		}
		System::Void pictureBox58_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox58, 57);
		}
		System::Void pictureBox59_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox59, 58);
		}
		System::Void pictureBox60_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox60, 59);
		}
		System::Void pictureBox61_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox61, 60);
		}
		System::Void pictureBox62_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox62, 61);
		}
		System::Void pictureBox63_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox63, 62);
		}
		System::Void pictureBox64_Click(System::Object^ sender, System::EventArgs^ e) {
			click(this->pictureBox64, 63);
		}
#pragma endregion
	};
}
