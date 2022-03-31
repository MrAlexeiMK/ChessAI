#pragma once

#include "play.h"
#include "settings.h"
#include "settingsManager.h"
#include "logManager.h"
#include "structures.h"
#include <msclr\marshal_cppstd.h>

namespace Chess {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	
	public ref class Main : public System::Windows::Forms::Form {
	private:
		msclr::interop::marshal_context context;
		string* path1 = new string("W.csv");
		string* path2 = new string("W.csv");

		System::ComponentModel::BackgroundWorker^ worker;
		System::Windows::Forms::CheckBox^ train_in_game;
		System::Windows::Forms::TableLayoutPanel^ tableLayout;
		System::Windows::Forms::FlowLayoutPanel^ f2;
		System::Windows::Forms::FlowLayoutPanel^ f3;
		System::Windows::Forms::FlowLayoutPanel^ f4;
		System::Windows::Forms::FlowLayoutPanel^ f1;
		System::Windows::Forms::Label^ bottom;
		System::Windows::Forms::MenuStrip^ menu;
		System::Windows::Forms::ToolStripMenuItem^ about;
		System::Windows::Forms::ToolStripMenuItem^ faq;
		System::Windows::Forms::ToolStripMenuItem^ author;
		System::Windows::Forms::ToolStripMenuItem^ settingsButton;
		System::Windows::Forms::NumericUpDown^ count;
		System::Windows::Forms::Button^ start;
		System::Windows::Forms::Button^ ai;
		System::Windows::Forms::Button^ train;
		System::Windows::Forms::OpenFileDialog^ select;
		System::Windows::Forms::Button^ select_play_ai;
		System::Windows::Forms::Button^ select_train_ai;
		System::Windows::Forms::ProgressBar^ progress;
		System::ComponentModel::IContainer^ components;

	public:
		Main(void) {
			InitializeComponent();
		}

		void updateSettings(bool ch) {
			settingsButton->Enabled = ch;
		}

	protected:
		~Main() {
			delete components;
			delete path1;
			delete path2;
		}

		#pragma region GUI
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->start = (gcnew System::Windows::Forms::Button());
			this->ai = (gcnew System::Windows::Forms::Button());
			this->train = (gcnew System::Windows::Forms::Button());
			this->select = (gcnew System::Windows::Forms::OpenFileDialog());
			this->select_play_ai = (gcnew System::Windows::Forms::Button());
			this->select_train_ai = (gcnew System::Windows::Forms::Button());
			this->progress = (gcnew System::Windows::Forms::ProgressBar());
			this->count = (gcnew System::Windows::Forms::NumericUpDown());
			this->worker = (gcnew System::ComponentModel::BackgroundWorker());
			this->train_in_game = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->f2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->f3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->f4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->bottom = (gcnew System::Windows::Forms::Label());
			this->f1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->settingsButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->about = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faq = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->author = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->count))->BeginInit();
			this->tableLayout->SuspendLayout();
			this->f2->SuspendLayout();
			this->f3->SuspendLayout();
			this->f4->SuspendLayout();
			this->f1->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// start
			// 
			this->start->Cursor = System::Windows::Forms::Cursors::Hand;
			this->start->Location = System::Drawing::Point(0, 0);
			this->start->Margin = System::Windows::Forms::Padding(0);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(198, 48);
			this->start->TabIndex = 1;
			this->start->Text = L"Играть на двоих";
			this->start->UseVisualStyleBackColor = true;
			this->start->Click += gcnew System::EventHandler(this, &Main::play_Click);
			// 
			// ai
			// 
			this->ai->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->ai->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ai->Location = System::Drawing::Point(122, 0);
			this->ai->Margin = System::Windows::Forms::Padding(0);
			this->ai->Name = L"ai";
			this->ai->Size = System::Drawing::Size(198, 48);
			this->ai->TabIndex = 2;
			this->ai->Text = L"Играть против ИИ";
			this->ai->UseVisualStyleBackColor = true;
			this->ai->Click += gcnew System::EventHandler(this, &Main::ai_Click);
			// 
			// train
			// 
			this->train->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->train->Cursor = System::Windows::Forms::Cursors::Hand;
			this->train->Location = System::Drawing::Point(122, 0);
			this->train->Margin = System::Windows::Forms::Padding(0);
			this->train->Name = L"train";
			this->train->Size = System::Drawing::Size(198, 48);
			this->train->TabIndex = 4;
			this->train->Text = L"Начать обучение";
			this->train->UseVisualStyleBackColor = true;
			this->train->Click += gcnew System::EventHandler(this, &Main::train_Click);
			// 
			// select
			// 
			this->select->FileName = L"W.csv";
			this->select->InitialDirectory = L"D:\\Catalog\\Projects\\MachineLearning\\Chess\\C++\\Chess\\Chess\\weights\\";
			this->select->RestoreDirectory = true;
			this->select->ShowHelp = true;
			// 
			// select_play_ai
			// 
			this->select_play_ai->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->select_play_ai->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->select_play_ai->Location = System::Drawing::Point(3, 12);
			this->select_play_ai->Name = L"select_play_ai";
			this->select_play_ai->Size = System::Drawing::Size(116, 33);
			this->select_play_ai->TabIndex = 5;
			this->select_play_ai->Text = L"W.csv";
			this->select_play_ai->UseVisualStyleBackColor = true;
			this->select_play_ai->Click += gcnew System::EventHandler(this, &Main::select_play_ai_Click);
			// 
			// select_train_ai
			// 
			this->select_train_ai->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->select_train_ai->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->select_train_ai->Location = System::Drawing::Point(3, 12);
			this->select_train_ai->Name = L"select_train_ai";
			this->select_train_ai->Size = System::Drawing::Size(116, 33);
			this->select_train_ai->TabIndex = 6;
			this->select_train_ai->Text = L"W.csv";
			this->select_train_ai->UseVisualStyleBackColor = true;
			this->select_train_ai->Click += gcnew System::EventHandler(this, &Main::select_train_ai_Click);
			// 
			// progress
			// 
			this->progress->BackColor = System::Drawing::Color::WhiteSmoke;
			this->progress->Location = System::Drawing::Point(3, 3);
			this->progress->Maximum = 1000;
			this->progress->Name = L"progress";
			this->progress->Size = System::Drawing::Size(402, 23);
			this->progress->Step = 1;
			this->progress->TabIndex = 7;
			this->progress->UseWaitCursor = true;
			// 
			// count
			// 
			this->count->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->count->Location = System::Drawing::Point(323, 23);
			this->count->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->count->Name = L"count";
			this->count->Size = System::Drawing::Size(116, 22);
			this->count->TabIndex = 8;
			this->count->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// worker
			// 
			this->worker->WorkerSupportsCancellation = true;
			this->worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::worker_DoWork);
			this->worker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Main::worker_ProgressChanged);
			// 
			// train_in_game
			// 
			this->train_in_game->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->train_in_game->Checked = true;
			this->train_in_game->CheckState = System::Windows::Forms::CheckState::Checked;
			this->train_in_game->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->train_in_game->Location = System::Drawing::Point(323, 12);
			this->train_in_game->Name = L"train_in_game";
			this->train_in_game->Size = System::Drawing::Size(116, 33);
			this->train_in_game->TabIndex = 10;
			this->train_in_game->Text = L"обучаться";
			this->train_in_game->UseVisualStyleBackColor = true;
			// 
			// tableLayout
			// 
			this->tableLayout->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayout->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Inset;
			this->tableLayout->ColumnCount = 1;
			this->tableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayout->Controls->Add(this->f2, 0, 1);
			this->tableLayout->Controls->Add(this->f3, 0, 2);
			this->tableLayout->Controls->Add(this->f4, 0, 3);
			this->tableLayout->Controls->Add(this->bottom, 0, 4);
			this->tableLayout->Controls->Add(this->f1, 0, 0);
			this->tableLayout->Location = System::Drawing::Point(0, 31);
			this->tableLayout->Name = L"tableLayout";
			this->tableLayout->RowCount = 5;
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 15)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 15)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->Size = System::Drawing::Size(502, 428);
			this->tableLayout->TabIndex = 11;
			// 
			// f2
			// 
			this->f2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->f2->AutoSize = true;
			this->f2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->f2->Controls->Add(this->select_play_ai);
			this->f2->Controls->Add(this->ai);
			this->f2->Controls->Add(this->train_in_game);
			this->f2->Location = System::Drawing::Point(30, 115);
			this->f2->Name = L"f2";
			this->f2->Size = System::Drawing::Size(442, 48);
			this->f2->TabIndex = 2;
			// 
			// f3
			// 
			this->f3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->f3->AutoSize = true;
			this->f3->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->f3->Controls->Add(this->select_train_ai);
			this->f3->Controls->Add(this->train);
			this->f3->Controls->Add(this->count);
			this->f3->Location = System::Drawing::Point(30, 221);
			this->f3->Name = L"f3";
			this->f3->Size = System::Drawing::Size(442, 48);
			this->f3->TabIndex = 3;
			// 
			// f4
			// 
			this->f4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->f4->AutoSize = true;
			this->f4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->f4->Controls->Add(this->progress);
			this->f4->Location = System::Drawing::Point(47, 315);
			this->f4->Name = L"f4";
			this->f4->Size = System::Drawing::Size(408, 29);
			this->f4->TabIndex = 4;
			// 
			// bottom
			// 
			this->bottom->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->bottom->AutoSize = true;
			this->bottom->Location = System::Drawing::Point(5, 363);
			this->bottom->Name = L"bottom";
			this->bottom->Size = System::Drawing::Size(492, 63);
			this->bottom->TabIndex = 6;
			this->bottom->Text = L"Chess AI © by MrAlexeiMK";
			this->bottom->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// f1
			// 
			this->f1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->f1->AutoSize = true;
			this->f1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->f1->Controls->Add(this->start);
			this->f1->Location = System::Drawing::Point(152, 19);
			this->f1->Name = L"f1";
			this->f1->Size = System::Drawing::Size(198, 48);
			this->f1->TabIndex = 5;
			// 
			// menu
			// 
			this->menu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->settingsButton, this->about });
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(502, 28);
			this->menu->TabIndex = 12;
			this->menu->Text = L"menuStrip1";
			// 
			// settingsButton
			// 
			this->settingsButton->Name = L"settingsButton";
			this->settingsButton->Size = System::Drawing::Size(98, 24);
			this->settingsButton->Text = L"Настройки";
			this->settingsButton->Click += gcnew System::EventHandler(this, &Main::settings_Click);
			// 
			// about
			// 
			this->about->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->faq, this->author });
			this->about->Name = L"about";
			this->about->Size = System::Drawing::Size(118, 24);
			this->about->Text = L"О программе";
			// 
			// faq
			// 
			this->faq->Name = L"faq";
			this->faq->Size = System::Drawing::Size(134, 26);
			this->faq->Text = L"FAQ";
			this->faq->Click += gcnew System::EventHandler(this, &Main::faq_Click);
			// 
			// author
			// 
			this->author->Name = L"author";
			this->author->Size = System::Drawing::Size(134, 26);
			this->author->Text = L"Автор";
			this->author->Click += gcnew System::EventHandler(this, &Main::author_Click);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(502, 446);
			this->Controls->Add(this->menu);
			this->Controls->Add(this->tableLayout);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menu;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Шахматы";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->count))->EndInit();
			this->tableLayout->ResumeLayout(false);
			this->tableLayout->PerformLayout();
			this->f2->ResumeLayout(false);
			this->f3->ResumeLayout(false);
			this->f4->ResumeLayout(false);
			this->f1->ResumeLayout(false);
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void Main_Load(System::Object^ sender, System::EventArgs^ e) {
			srand((unsigned int)time(NULL));
			select->InitialDirectory = gcnew String((settingsManager::getInstance().path+"weights\\").c_str());
			this->Text = gcnew String(settingsManager::getInstance().lang("Main").c_str());
			start->Text = gcnew String(settingsManager::getInstance().lang("Main.SinglePlay").c_str());
			ai->Text = gcnew String(settingsManager::getInstance().lang("Main.AiPlay").c_str());
			train->Text = gcnew String(settingsManager::getInstance().lang("Main.StartTrain").c_str());
			train_in_game->Text = gcnew String(settingsManager::getInstance().lang("Main.DoTrain").c_str());
			settingsButton->Text = gcnew String(settingsManager::getInstance().lang("Main.Settings").c_str());
			about->Text = gcnew String(settingsManager::getInstance().lang("Main.About").c_str());
			faq->Text = gcnew String(settingsManager::getInstance().lang("Main.FAQ").c_str());
			author->Text = gcnew String(settingsManager::getInstance().lang("Main.Author").c_str());
		}

		System::Void play_Click(System::Object^ sender, System::EventArgs^ e) {
			play^ pl = gcnew play(this, GameType::SINGLE, true, *path1, this->progress, false);
			pl->Show();
			this->Hide();
		}

		System::Void ai_Click(System::Object^ sender, System::EventArgs^ e) {
			bool isWhite = true;
			int ran = rand() % 2;
			if (ran == 1) isWhite = false;
			if (settingsManager::getInstance().firstStep == 1) isWhite = true;
			else if (settingsManager::getInstance().firstStep == 2) isWhite = false;
			play^ pl = gcnew play(this, GameType::AI, isWhite, *path1, this->progress, this->train_in_game->Checked);
			pl->Show();
			this->Hide();
		}
		System::Void select_play_ai_Click(System::Object^ sender, System::EventArgs^ e) {
			if (select->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				*path1 = context.marshal_as<string>(System::IO::Path::GetFileName(select->FileName));
				select_play_ai->Text = System::IO::Path::GetFileName(select->FileName);
			}
		}
		System::Void select_train_ai_Click(System::Object^ sender, System::EventArgs^ e) {
			if (select->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				*path2 = context.marshal_as<string>(System::IO::Path::GetFileName(select->FileName));
				select_train_ai->Text = System::IO::Path::GetFileName(select->FileName);
			}
		}
		System::Void train_Click(System::Object^ sender, System::EventArgs^ e) {
			if (!worker->IsBusy) {
				progress->Value = 0;
				progress->Maximum = (int)count->Value;
				play^ pl = gcnew play(this, GameType::TRAIN, true, *path2, this->progress, true);
				pl->Show();
				worker->RunWorkerAsync(1);
				settingsButton->Enabled = false;
			}
		}
		System::Void worker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			while (true) {
				if (worker->CancellationPending) {
					e->Cancel = true;
					break;
				}
				if (progress->Value == progress->Maximum) {
					menu->Invoke(gcnew Action<bool>(this, &Main::updateSettings), true);
					break;
				}
				Sleep(1000);
			}
			worker->CancelAsync();
		}
		System::Void worker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
			progress->Value += e->ProgressPercentage;
		}
		System::Void faq_Click(System::Object^ sender, System::EventArgs^ e) {
			Process::Start("https://github.com/MrAlexeiMK/Chess");
		}
		System::Void settings_Click(System::Object^ sender, System::EventArgs^ e) {
			settings^ s = gcnew settings();
			s->Show();
		}
		System::Void author_Click(System::Object^ sender, System::EventArgs^ e) {
			Process::Start("https://github.com/MrAlexeiMK");
		}
	};
}
