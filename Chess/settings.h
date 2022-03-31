#pragma once

#include <msclr\marshal_cppstd.h>
#include "settingsManager.h"
#include "logManager.h"

namespace Chess {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::Text::RegularExpressions;

	public ref class settings : public System::Windows::Forms::Form {
	public:
		settings() {
			InitializeComponent();
			std::string langFile = settingsManager::getInstance().langFile;
			int step = settingsManager::getInstance().firstStep;
			lang->Text = context.marshal_as<String^>(langFile);
			firstStep->SelectedIndex = step;
			playSound->Checked = settingsManager::getInstance().playSound;
			maxSteps->Text = gcnew String(std::to_string(settingsManager::getInstance().maxSteps).c_str());
			layers->Text = gcnew String(settingsManager::getInstance().layersToString().c_str());
			lr->Text = gcnew String(std::to_string(settingsManager::getInstance().lr).c_str());
			sim->Text = gcnew String(std::to_string(settingsManager::getInstance().simulations).c_str());
			history->Text = gcnew String(std::to_string(settingsManager::getInstance().historySteps).c_str());
			depth->Text = gcnew String(std::to_string(settingsManager::getInstance().depth).c_str());
			maxDepth->Text = gcnew String(std::to_string(settingsManager::getInstance().maxDepth).c_str());
		}
	protected:
		~settings() {
			if (components) {
				delete components;
			}
		}
	private: 
		msclr::interop::marshal_context context;

		System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		System::Windows::Forms::Label^ langText;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel4;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel5;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel7;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel8;
		System::Windows::Forms::Label^ stepInfo;
		System::ComponentModel::Container ^components;
		System::Windows::Forms::ComboBox^ firstStep;
		System::Windows::Forms::Button^ lang;
		System::Windows::Forms::CheckBox^ playSound;
		System::Windows::Forms::Label^ maxStepsInfo;
		System::Windows::Forms::TextBox^ maxSteps;
		System::Windows::Forms::Label^ layersInfo;
		System::Windows::Forms::TextBox^ layers;
		System::Windows::Forms::Label^ lrInfo;
		System::Windows::Forms::TextBox^ lr;
		System::Windows::Forms::Label^ simInfo;
		System::Windows::Forms::TextBox^ sim;
		System::Windows::Forms::Label^ historyInfo;
		System::Windows::Forms::TextBox^ history;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel9;
		System::Windows::Forms::Label^ depthInfo;
		System::Windows::Forms::TextBox^ depth;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel10;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel11;
		System::Windows::Forms::Label^ maxDepthInfo;
		System::Windows::Forms::TextBox^ maxDepth;
		System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel12;
		System::Windows::Forms::OpenFileDialog^ chooseLangFile;

#pragma region GUI
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(settings::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->langText = (gcnew System::Windows::Forms::Label());
			this->lang = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->stepInfo = (gcnew System::Windows::Forms::Label());
			this->firstStep = (gcnew System::Windows::Forms::ComboBox());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->playSound = (gcnew System::Windows::Forms::CheckBox());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->maxStepsInfo = (gcnew System::Windows::Forms::Label());
			this->maxSteps = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel5 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->layersInfo = (gcnew System::Windows::Forms::Label());
			this->layers = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->lrInfo = (gcnew System::Windows::Forms::Label());
			this->lr = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel7 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->simInfo = (gcnew System::Windows::Forms::Label());
			this->sim = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel8 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->historyInfo = (gcnew System::Windows::Forms::Label());
			this->history = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel9 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->depthInfo = (gcnew System::Windows::Forms::Label());
			this->depth = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel10 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->chooseLangFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->flowLayoutPanel11 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->maxDepth = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel12 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->maxDepthInfo = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel5->SuspendLayout();
			this->flowLayoutPanel6->SuspendLayout();
			this->flowLayoutPanel7->SuspendLayout();
			this->flowLayoutPanel8->SuspendLayout();
			this->flowLayoutPanel9->SuspendLayout();
			this->flowLayoutPanel11->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Inset;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel11, 0, 9);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel4, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel5, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel6, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel7, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel8, 0, 7);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel9, 0, 8);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 10;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(243, 441);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->langText);
			this->flowLayoutPanel1->Controls->Add(this->lang);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(5, 5);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// langText
			// 
			this->langText->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->langText->Location = System::Drawing::Point(3, 7);
			this->langText->Name = L"langText";
			this->langText->Size = System::Drawing::Size(77, 24);
			this->langText->TabIndex = 1;
			this->langText->Text = L"Язык";
			this->langText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lang
			// 
			this->lang->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lang->Cursor = System::Windows::Forms::Cursors::Hand;
			this->lang->Location = System::Drawing::Point(86, 3);
			this->lang->Name = L"lang";
			this->lang->Size = System::Drawing::Size(129, 32);
			this->lang->TabIndex = 0;
			this->lang->Text = L"ru-RU.txt";
			this->lang->UseVisualStyleBackColor = true;
			this->lang->Click += gcnew System::EventHandler(this, &settings::lang_Click);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->stepInfo);
			this->flowLayoutPanel2->Controls->Add(this->firstStep);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel2->Location = System::Drawing::Point(5, 48);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// stepInfo
			// 
			this->stepInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->stepInfo->Location = System::Drawing::Point(3, 0);
			this->stepInfo->Name = L"stepInfo";
			this->stepInfo->Size = System::Drawing::Size(77, 41);
			this->stepInfo->TabIndex = 2;
			this->stepInfo->Text = L"Первый ход";
			this->stepInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// firstStep
			// 
			this->firstStep->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->firstStep->Cursor = System::Windows::Forms::Cursors::Hand;
			this->firstStep->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->firstStep->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->firstStep->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"50/50", L"белые", L"чёрные" });
			this->firstStep->Location = System::Drawing::Point(86, 8);
			this->firstStep->Name = L"firstStep";
			this->firstStep->Size = System::Drawing::Size(129, 24);
			this->firstStep->TabIndex = 0;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->playSound);
			this->flowLayoutPanel3->Location = System::Drawing::Point(5, 91);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel3->TabIndex = 2;
			// 
			// playSound
			// 
			this->playSound->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->playSound->Checked = true;
			this->playSound->CheckState = System::Windows::Forms::CheckState::Checked;
			this->playSound->Cursor = System::Windows::Forms::Cursors::Default;
			this->playSound->Location = System::Drawing::Point(3, 3);
			this->playSound->Name = L"playSound";
			this->playSound->Size = System::Drawing::Size(164, 38);
			this->playSound->TabIndex = 4;
			this->playSound->Text = L"    Звуки";
			this->playSound->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->Controls->Add(this->maxStepsInfo);
			this->flowLayoutPanel4->Controls->Add(this->maxSteps);
			this->flowLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel4->Location = System::Drawing::Point(5, 134);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel4->TabIndex = 3;
			// 
			// maxStepsInfo
			// 
			this->maxStepsInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->maxStepsInfo->Location = System::Drawing::Point(3, 0);
			this->maxStepsInfo->Name = L"maxStepsInfo";
			this->maxStepsInfo->Size = System::Drawing::Size(77, 41);
			this->maxStepsInfo->TabIndex = 3;
			this->maxStepsInfo->Text = L"Максимум ходов";
			this->maxStepsInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// maxSteps
			// 
			this->maxSteps->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->maxSteps->Location = System::Drawing::Point(86, 9);
			this->maxSteps->MaxLength = 5;
			this->maxSteps->Name = L"maxSteps";
			this->maxSteps->Size = System::Drawing::Size(129, 22);
			this->maxSteps->TabIndex = 4;
			this->maxSteps->Text = L"150";
			this->maxSteps->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->maxSteps->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::maxSteps_KeyPress);
			// 
			// flowLayoutPanel5
			// 
			this->flowLayoutPanel5->Controls->Add(this->layersInfo);
			this->flowLayoutPanel5->Controls->Add(this->layers);
			this->flowLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel5->Location = System::Drawing::Point(5, 177);
			this->flowLayoutPanel5->Name = L"flowLayoutPanel5";
			this->flowLayoutPanel5->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel5->TabIndex = 4;
			// 
			// layersInfo
			// 
			this->layersInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->layersInfo->Location = System::Drawing::Point(3, 0);
			this->layersInfo->Name = L"layersInfo";
			this->layersInfo->Size = System::Drawing::Size(77, 41);
			this->layersInfo->TabIndex = 5;
			this->layersInfo->Text = L"Слои";
			this->layersInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// layers
			// 
			this->layers->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->layers->Location = System::Drawing::Point(86, 9);
			this->layers->MaxLength = 100;
			this->layers->Name = L"layers";
			this->layers->Size = System::Drawing::Size(129, 22);
			this->layers->TabIndex = 5;
			this->layers->Text = L"256,400,1";
			this->layers->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->layers->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::layers_KeyPress);
			// 
			// flowLayoutPanel6
			// 
			this->flowLayoutPanel6->Controls->Add(this->lrInfo);
			this->flowLayoutPanel6->Controls->Add(this->lr);
			this->flowLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel6->Location = System::Drawing::Point(5, 220);
			this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			this->flowLayoutPanel6->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel6->TabIndex = 5;
			// 
			// lrInfo
			// 
			this->lrInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lrInfo->Location = System::Drawing::Point(3, 0);
			this->lrInfo->Name = L"lrInfo";
			this->lrInfo->Size = System::Drawing::Size(77, 41);
			this->lrInfo->TabIndex = 6;
			this->lrInfo->Text = L"Коэффициент";
			this->lrInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lr
			// 
			this->lr->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lr->Location = System::Drawing::Point(86, 9);
			this->lr->MaxLength = 15;
			this->lr->Name = L"lr";
			this->lr->Size = System::Drawing::Size(129, 22);
			this->lr->TabIndex = 6;
			this->lr->Text = L"0.1";
			this->lr->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->lr->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::lr_KeyPress);
			// 
			// flowLayoutPanel7
			// 
			this->flowLayoutPanel7->Controls->Add(this->simInfo);
			this->flowLayoutPanel7->Controls->Add(this->sim);
			this->flowLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel7->Location = System::Drawing::Point(5, 263);
			this->flowLayoutPanel7->Name = L"flowLayoutPanel7";
			this->flowLayoutPanel7->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel7->TabIndex = 6;
			// 
			// simInfo
			// 
			this->simInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->simInfo->Location = System::Drawing::Point(3, 0);
			this->simInfo->Name = L"simInfo";
			this->simInfo->Size = System::Drawing::Size(77, 41);
			this->simInfo->TabIndex = 7;
			this->simInfo->Text = L"Симуляции";
			this->simInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// sim
			// 
			this->sim->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->sim->Location = System::Drawing::Point(86, 9);
			this->sim->MaxLength = 15;
			this->sim->Name = L"sim";
			this->sim->Size = System::Drawing::Size(129, 22);
			this->sim->TabIndex = 7;
			this->sim->Text = L"10";
			this->sim->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->sim->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::sim_KeyPress);
			// 
			// flowLayoutPanel8
			// 
			this->flowLayoutPanel8->Controls->Add(this->historyInfo);
			this->flowLayoutPanel8->Controls->Add(this->history);
			this->flowLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel8->Location = System::Drawing::Point(5, 306);
			this->flowLayoutPanel8->Name = L"flowLayoutPanel8";
			this->flowLayoutPanel8->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel8->TabIndex = 7;
			// 
			// historyInfo
			// 
			this->historyInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->historyInfo->Location = System::Drawing::Point(3, 0);
			this->historyInfo->Name = L"historyInfo";
			this->historyInfo->Size = System::Drawing::Size(77, 41);
			this->historyInfo->TabIndex = 8;
			this->historyInfo->Text = L"Истории ходов";
			this->historyInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// history
			// 
			this->history->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->history->Location = System::Drawing::Point(86, 9);
			this->history->MaxLength = 15;
			this->history->Name = L"history";
			this->history->Size = System::Drawing::Size(129, 22);
			this->history->TabIndex = 8;
			this->history->Text = L"5";
			this->history->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->history->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::history_KeyPress);
			// 
			// flowLayoutPanel9
			// 
			this->flowLayoutPanel9->Controls->Add(this->depthInfo);
			this->flowLayoutPanel9->Controls->Add(this->depth);
			this->flowLayoutPanel9->Controls->Add(this->flowLayoutPanel10);
			this->flowLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel9->Location = System::Drawing::Point(5, 349);
			this->flowLayoutPanel9->Name = L"flowLayoutPanel9";
			this->flowLayoutPanel9->Size = System::Drawing::Size(233, 35);
			this->flowLayoutPanel9->TabIndex = 8;
			// 
			// depthInfo
			// 
			this->depthInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->depthInfo->Location = System::Drawing::Point(3, 0);
			this->depthInfo->Name = L"depthInfo";
			this->depthInfo->Size = System::Drawing::Size(77, 41);
			this->depthInfo->TabIndex = 9;
			this->depthInfo->Text = L"Глубина";
			this->depthInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// depth
			// 
			this->depth->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->depth->Location = System::Drawing::Point(86, 9);
			this->depth->MaxLength = 15;
			this->depth->Name = L"depth";
			this->depth->Size = System::Drawing::Size(129, 22);
			this->depth->TabIndex = 9;
			this->depth->Text = L"20";
			this->depth->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->depth->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::depth_KeyPress);
			// 
			// flowLayoutPanel10
			// 
			this->flowLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel10->Location = System::Drawing::Point(3, 44);
			this->flowLayoutPanel10->Name = L"flowLayoutPanel10";
			this->flowLayoutPanel10->Size = System::Drawing::Size(230, 0);
			this->flowLayoutPanel10->TabIndex = 0;
			// 
			// chooseLangFile
			// 
			this->chooseLangFile->FileName = L"ru-RU.txt";
			// 
			// flowLayoutPanel11
			// 
			this->flowLayoutPanel11->Controls->Add(this->maxDepthInfo);
			this->flowLayoutPanel11->Controls->Add(this->maxDepth);
			this->flowLayoutPanel11->Controls->Add(this->flowLayoutPanel12);
			this->flowLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel11->Location = System::Drawing::Point(5, 392);
			this->flowLayoutPanel11->Name = L"flowLayoutPanel11";
			this->flowLayoutPanel11->Size = System::Drawing::Size(233, 44);
			this->flowLayoutPanel11->TabIndex = 10;
			// 
			// maxDepth
			// 
			this->maxDepth->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->maxDepth->Location = System::Drawing::Point(86, 9);
			this->maxDepth->MaxLength = 3;
			this->maxDepth->Name = L"maxDepth";
			this->maxDepth->Size = System::Drawing::Size(129, 22);
			this->maxDepth->TabIndex = 9;
			this->maxDepth->Text = L"8";
			this->maxDepth->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->maxDepth->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &settings::maxDepth_KeyPress);
			// 
			// flowLayoutPanel12
			// 
			this->flowLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel12->Location = System::Drawing::Point(3, 44);
			this->flowLayoutPanel12->Name = L"flowLayoutPanel12";
			this->flowLayoutPanel12->Size = System::Drawing::Size(230, 0);
			this->flowLayoutPanel12->TabIndex = 0;
			// 
			// maxDepthInfo
			// 
			this->maxDepthInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->maxDepthInfo->Location = System::Drawing::Point(3, 0);
			this->maxDepthInfo->Name = L"maxDepthInfo";
			this->maxDepthInfo->Size = System::Drawing::Size(77, 41);
			this->maxDepthInfo->TabIndex = 9;
			this->maxDepthInfo->Text = L"Макс. глубина";
			this->maxDepthInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(267, 465);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"settings";
			this->Text = L"Настройки";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &settings::settings_FormClosed);
			this->Load += gcnew System::EventHandler(this, &settings::settings_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel4->ResumeLayout(false);
			this->flowLayoutPanel4->PerformLayout();
			this->flowLayoutPanel5->ResumeLayout(false);
			this->flowLayoutPanel5->PerformLayout();
			this->flowLayoutPanel6->ResumeLayout(false);
			this->flowLayoutPanel6->PerformLayout();
			this->flowLayoutPanel7->ResumeLayout(false);
			this->flowLayoutPanel7->PerformLayout();
			this->flowLayoutPanel8->ResumeLayout(false);
			this->flowLayoutPanel8->PerformLayout();
			this->flowLayoutPanel9->ResumeLayout(false);
			this->flowLayoutPanel9->PerformLayout();
			this->flowLayoutPanel11->ResumeLayout(false);
			this->flowLayoutPanel11->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void settings_Load(System::Object^ sender, System::EventArgs^ e) {
			chooseLangFile->InitialDirectory = gcnew String((settingsManager::getInstance().path+"langs\\").c_str());
			this->Text = gcnew String(settingsManager::getInstance().lang("Main").c_str());
			langText->Text = gcnew String(settingsManager::getInstance().lang("Settings.Lang.Label").c_str());
			stepInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.FirstStep.Label").c_str());
			maxStepsInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.MaxSteps.Label").c_str());
			for (int i = 0; i < 3; ++i) {
				firstStep->Items[i] = gcnew String(settingsManager::getInstance().lang("Settings.FirstStep.ComboBox."+std::to_string(i+1)).c_str());
			}
			playSound->Text = gcnew String(settingsManager::getInstance().lang("Settings.PlaySound.Label").c_str());
			layersInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.Layers.Label").c_str());
			lrInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.Lr.Label").c_str());
			simInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.Sim.Label").c_str());
			historyInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.History.Label").c_str());
			depthInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.Depth.Label").c_str());
			maxDepthInfo->Text = gcnew String(settingsManager::getInstance().lang("Settings.MaxDepth.Label").c_str());
		}
		System::Void lang_Click(System::Object^ sender, System::EventArgs^ e) {
			if (chooseLangFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				std::string path = context.marshal_as<std::string>(System::IO::Path::GetFileName(chooseLangFile->FileName));
				lang->Text = System::IO::Path::GetFileName(chooseLangFile->FileName);
			}
		}
		System::Void settings_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			settingsManager::getInstance().update(
				context.marshal_as<std::string>(lang->Text),
				firstStep->SelectedIndex,
				playSound->Checked,
				atoi(context.marshal_as<std::string>(maxSteps->Text).c_str()),
				context.marshal_as<std::string>(layers->Text),
				std::stod(context.marshal_as<std::string>(lr->Text).c_str()),
				atoi(context.marshal_as<std::string>(sim->Text).c_str()),
				atoi(context.marshal_as<std::string>(history->Text).c_str()),
				atoi(context.marshal_as<std::string>(depth->Text).c_str()),
				atoi(context.marshal_as<std::string>(maxDepth->Text).c_str())
			);
			Application::Exit();
			Process::Start(Application::ExecutablePath);
		}
		System::Void maxSteps_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
		}
		System::Void lr_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			Regex^ regex = gcnew Regex("[0-9.]");
			if (!regex->IsMatch(e->KeyChar.ToString()) && !Char::IsControl(e->KeyChar)) {
				e->Handled = true;
			}
		}
		System::Void layers_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			Regex^ regex = gcnew Regex("[0-9,]");
			if (!regex->IsMatch(e->KeyChar.ToString()) && !Char::IsControl(e->KeyChar)) {
				e->Handled = true;
			}
		}
		System::Void sim_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
		}
		System::Void history_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
		}
		System::Void depth_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
		}
		System::Void maxDepth_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
		}
	};
}
