#pragma once
#include "TGenerate.h"
#include <algorithm>
#include <ctime>
#include <iomanip>

namespace SintezPP_All {
	//глобальные переменные
	static std::vector<int>V;
	static std::vector<double> VectI;
	static std::vector<size_t> Vect;
	static std::vector<TPKP> Schemes;
	static int countP, countS;
	static bool SecondClick;
	static int L;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  projectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  повторитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  закрытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  режимыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem2;

	private: System::Windows::Forms::ToolStripMenuItem^  дополнительноToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem3;

	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox3;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox2;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  загрузитьToolStripMenuItem;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox9;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox8;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox7;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox6;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox5;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox4;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьXLSToolStripMenuItem;

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->projectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->повторитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьXLSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->закрытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->режимыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->дополнительноToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox9 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox8 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox7 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox6 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox5 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox4 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox3 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuStrip1.BackgroundImage")));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->projectToolStripMenuItem,
					this->режимыToolStripMenuItem, this->дополнительноToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1020, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// projectToolStripMenuItem
			// 
			this->projectToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->повторитьToolStripMenuItem,
					this->сохранитьToolStripMenuItem, this->сохранитьXLSToolStripMenuItem, this->загрузитьToolStripMenuItem, this->закрытьToolStripMenuItem
			});
			this->projectToolStripMenuItem->Name = L"projectToolStripMenuItem";
			this->projectToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->projectToolStripMenuItem->Text = L"Проект";
			// 
			// повторитьToolStripMenuItem
			// 
			this->повторитьToolStripMenuItem->Name = L"повторитьToolStripMenuItem";
			this->повторитьToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->повторитьToolStripMenuItem->Text = L"Повторить";
			this->повторитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::повторитьToolStripMenuItem_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьToolStripMenuItem_Click);
			// 
			// сохранитьXLSToolStripMenuItem
			// 
			this->сохранитьXLSToolStripMenuItem->Name = L"сохранитьXLSToolStripMenuItem";
			this->сохранитьXLSToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->сохранитьXLSToolStripMenuItem->Text = L"Сохранить как XLS";
			this->сохранитьXLSToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьXLSToolStripMenuItem_Click);
			// 
			// загрузитьToolStripMenuItem
			// 
			this->загрузитьToolStripMenuItem->Name = L"загрузитьToolStripMenuItem";
			this->загрузитьToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->загрузитьToolStripMenuItem->Text = L"Загрузить";
			this->загрузитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::загрузитьToolStripMenuItem_Click);
			// 
			// закрытьToolStripMenuItem
			// 
			this->закрытьToolStripMenuItem->Name = L"закрытьToolStripMenuItem";
			this->закрытьToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->закрытьToolStripMenuItem->Text = L"Закрыть";
			this->закрытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::закрытьToolStripMenuItem_Click);
			// 
			// режимыToolStripMenuItem
			// 
			this->режимыToolStripMenuItem->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->режимыToolStripMenuItem->CheckOnClick = true;
			this->режимыToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ToolStripMenuItem1,
					this->ToolStripMenuItem2, this->ToolStripMenuItem3, this->toolStripSeparator1
			});
			this->режимыToolStripMenuItem->Name = L"режимыToolStripMenuItem";
			this->режимыToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->режимыToolStripMenuItem->Text = L"Режимы";
			// 
			// ToolStripMenuItem1
			// 
			this->ToolStripMenuItem1->BackColor = System::Drawing::SystemColors::Window;
			this->ToolStripMenuItem1->CheckOnClick = true;
			this->ToolStripMenuItem1->Name = L"ToolStripMenuItem1";
			this->ToolStripMenuItem1->Size = System::Drawing::Size(205, 22);
			this->ToolStripMenuItem1->Text = L"Генерировать все";
			this->ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem1_Click);
			// 
			// ToolStripMenuItem2
			// 
			this->ToolStripMenuItem2->BackColor = System::Drawing::SystemColors::Window;
			this->ToolStripMenuItem2->CheckOnClick = true;
			this->ToolStripMenuItem2->Name = L"ToolStripMenuItem2";
			this->ToolStripMenuItem2->Size = System::Drawing::Size(205, 22);
			this->ToolStripMenuItem2->Text = L"Генерировать с In и Out";
			this->ToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem2_Click);
			// 
			// ToolStripMenuItem3
			// 
			this->ToolStripMenuItem3->CheckOnClick = true;
			this->ToolStripMenuItem3->Name = L"ToolStripMenuItem3";
			this->ToolStripMenuItem3->Size = System::Drawing::Size(205, 22);
			this->ToolStripMenuItem3->Text = L"Ручной";
			this->ToolStripMenuItem3->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem3_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(202, 6);
			// 
			// дополнительноToolStripMenuItem
			// 
			this->дополнительноToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->справкаToolStripMenuItem,
					this->оПрограммеToolStripMenuItem
			});
			this->дополнительноToolStripMenuItem->ForeColor = System::Drawing::SystemColors::ControlText;
			this->дополнительноToolStripMenuItem->Name = L"дополнительноToolStripMenuItem";
			this->дополнительноToolStripMenuItem->Size = System::Drawing::Size(107, 20);
			this->дополнительноToolStripMenuItem->Text = L"Дополнительно";
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->справкаToolStripMenuItem->Text = L"Справка";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->panel1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->panel1->Controls->Add(this->label16);
			this->panel1->Controls->Add(this->label15);
			this->panel1->Controls->Add(this->comboBox1);
			this->panel1->Controls->Add(this->label14);
			this->panel1->Controls->Add(this->label13);
			this->panel1->Controls->Add(this->label12);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->maskedTextBox9);
			this->panel1->Controls->Add(this->maskedTextBox8);
			this->panel1->Controls->Add(this->maskedTextBox7);
			this->panel1->Controls->Add(this->maskedTextBox6);
			this->panel1->Controls->Add(this->maskedTextBox5);
			this->panel1->Controls->Add(this->maskedTextBox4);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->maskedTextBox3);
			this->panel1->Controls->Add(this->maskedTextBox2);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->listBox1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->maskedTextBox1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Location = System::Drawing::Point(8, 32);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(173, 575);
			this->panel1->TabIndex = 1;
			// 
			// label16
			// 
			this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(118, 529);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(0, 13);
			this->label16->TabIndex = 28;
			// 
			// label15
			// 
			this->label15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(118, 503);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(0, 13);
			this->label15->TabIndex = 27;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(17, 397);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 26;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(87, 365);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(10, 13);
			this->label14->TabIndex = 25;
			this->label14->Text = L"-";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(87, 339);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(10, 13);
			this->label13->TabIndex = 24;
			this->label13->Text = L"-";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(14, 365);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(22, 13);
			this->label12->TabIndex = 23;
			this->label12->Text = L"k+:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(14, 339);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(19, 13);
			this->label11->TabIndex = 22;
			this->label11->Text = L"k-:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(87, 313);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(22, 13);
			this->label10->TabIndex = 21;
			this->label10->Text = L"dk:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(19, 313);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(17, 13);
			this->label9->TabIndex = 20;
			this->label9->Text = L"E:";
			// 
			// maskedTextBox9
			// 
			this->maskedTextBox9->Location = System::Drawing::Point(42, 362);
			this->maskedTextBox9->Mask = L"#0.0";
			this->maskedTextBox9->Name = L"maskedTextBox9";
			this->maskedTextBox9->Size = System::Drawing::Size(38, 20);
			this->maskedTextBox9->TabIndex = 19;
			this->maskedTextBox9->Text = L"-20";
			// 
			// maskedTextBox8
			// 
			this->maskedTextBox8->Location = System::Drawing::Point(110, 362);
			this->maskedTextBox8->Mask = L"#0.0";
			this->maskedTextBox8->Name = L"maskedTextBox8";
			this->maskedTextBox8->Size = System::Drawing::Size(35, 20);
			this->maskedTextBox8->TabIndex = 18;
			this->maskedTextBox8->Text = L"-20";
			// 
			// maskedTextBox7
			// 
			this->maskedTextBox7->Location = System::Drawing::Point(110, 336);
			this->maskedTextBox7->Mask = L"#0.0";
			this->maskedTextBox7->Name = L"maskedTextBox7";
			this->maskedTextBox7->Size = System::Drawing::Size(35, 20);
			this->maskedTextBox7->TabIndex = 17;
			this->maskedTextBox7->Text = L"-20";
			// 
			// maskedTextBox6
			// 
			this->maskedTextBox6->Location = System::Drawing::Point(42, 336);
			this->maskedTextBox6->Mask = L"#0.0";
			this->maskedTextBox6->Name = L"maskedTextBox6";
			this->maskedTextBox6->Size = System::Drawing::Size(38, 20);
			this->maskedTextBox6->TabIndex = 16;
			this->maskedTextBox6->Text = L"-45";
			// 
			// maskedTextBox5
			// 
			this->maskedTextBox5->Location = System::Drawing::Point(110, 310);
			this->maskedTextBox5->Mask = L"0.000";
			this->maskedTextBox5->Name = L"maskedTextBox5";
			this->maskedTextBox5->Size = System::Drawing::Size(35, 20);
			this->maskedTextBox5->TabIndex = 15;
			this->maskedTextBox5->Text = L"01";
			// 
			// maskedTextBox4
			// 
			this->maskedTextBox4->Location = System::Drawing::Point(42, 310);
			this->maskedTextBox4->Mask = L"0.000";
			this->maskedTextBox4->Name = L"maskedTextBox4";
			this->maskedTextBox4->Size = System::Drawing::Size(38, 20);
			this->maskedTextBox4->TabIndex = 14;
			this->maskedTextBox4->Text = L"0001";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(20, 287);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(27, 13);
			this->label8->TabIndex = 13;
			this->label8->Text = L"Out:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(20, 261);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(19, 13);
			this->label7->TabIndex = 12;
			this->label7->Text = L"In:";
			// 
			// maskedTextBox3
			// 
			this->maskedTextBox3->Location = System::Drawing::Point(65, 284);
			this->maskedTextBox3->Mask = L"00";
			this->maskedTextBox3->Name = L"maskedTextBox3";
			this->maskedTextBox3->Size = System::Drawing::Size(80, 20);
			this->maskedTextBox3->TabIndex = 11;
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->Location = System::Drawing::Point(64, 258);
			this->maskedTextBox2->Mask = L"00";
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->Size = System::Drawing::Size(81, 20);
			this->maskedTextBox2->TabIndex = 10;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(22, 529);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 13);
			this->label6->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(22, 516);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 13);
			this->label5->TabIndex = 8;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(22, 503);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 13);
			this->label4->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 490);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(24, 545);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(22, 92);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(123, 160);
			this->listBox1->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(22, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Add ger ratio:";
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Location = System::Drawing::Point(22, 68);
			this->maskedTextBox1->Mask = L"#00.000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(123, 20);
			this->maskedTextBox1->TabIndex = 2;
			this->maskedTextBox1->Text = L"+0";
			this->maskedTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::maskedTextBox1_KeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Choose W:";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(22, 25);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(123, 20);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// listBox2
			// 
			this->listBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listBox2->BackColor = System::Drawing::SystemColors::Window;
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(565, 32);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(443, 576);
			this->listBox2->TabIndex = 2;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox2_SelectedIndexChanged);
			// 
			// listBox3
			// 
			this->listBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Location = System::Drawing::Point(187, 382);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(372, 225);
			this->listBox3->TabIndex = 3;
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->BackColor = System::Drawing::SystemColors::Control;
			this->panel2->Location = System::Drawing::Point(187, 32);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(372, 344);
			this->panel2->TabIndex = 4;
			this->panel2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel2_MouseClick);
			this->panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel2_MouseMove);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(1020, 616);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->listBox3);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SintezPP";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

int Display(TMake &Make){
	Graphics^ g = Graphics::FromHwnd(this->panel2->Handle);
	g->Clear(Color::White);
	int p(0);
	int l = Make.getYmaxGearBox();
	int k;
	if (this->panel2->Width / Make.getYmaxGearBox() < (this->panel2->Height - 10) / 13)
		k = this->panel2->Width / Make.getYmaxGearBox();
	else
		k = (this->panel2->Height - 10) / 13;
	int x, y;
	Pen^ MyPen = gcnew Pen(Brushes::Black);
	MyPen->Width = 4;
	for (int j = 1; j <= Make.getCountPlanRyad(); j++){
		p = 0;
		for (size_t i = 0; i < Make.getSizeV(); i++)
		if (Make.getCellV(i) == 3 * 1000 + 100 * j)
		if (p == 0){
			p = i;
		}
		else {
			g->DrawLine(MyPen, p%l * k, p / l * k, i%l * k, i / l * k);
		}
		p = 0;
		for (size_t i = 0; i < Make.getSizeV(); i++){
			if (Make.getCellV(i) == 2 * 1000 + 100 * j)
				p = i;
			if (Make.getCellV(i) == 1 * 1000 + 100 * j)
				g->DrawLine(MyPen, p%l * k, p / l * k, i%l * k, i / l * k);
		}
		p = l + 1;
	}
	for (size_t i = 0; i < Make.getSizeV(); i++)
	if (Make.getCellV(i) == 6600){
		g->DrawLine(MyPen, i%l * k, i / l * k, p%l * k, p / l * k);
		p = i;
	}
	for (size_t i = 0; i < Make.getSizeV(); i++){
		if (Make.getCellV(i) == 4400) g->DrawRectangle(MyPen, (int)i%l * k - 1, i / l * k - 1, 2, 2);
		if (Make.getCellV(i) == 5500) g->DrawRectangle(MyPen, (int)i%l * k, i / l * k, 2, 2);
	}
	MyPen->Width = 2;
	for (size_t i = 0; i < Make.getSizeLinksForPaint(); i++){
		y = Make.getCellLinksForPaint(i, 0);
		x = Make.getCellLinksForPaint(i, 1);
		for (size_t j = 2; j < Make.getSizeLinksForPaint(i); j = j + 2){
			g->DrawLine(MyPen, Make.getCellLinksForPaint(i, j + 1) * k, (Make.getCellLinksForPaint(i, j)) * k, x * k, y * k);
			y = Make.getCellLinksForPaint(i, j);
			x = Make.getCellLinksForPaint(i, j + 1);
		}
	}
	return 0;
		}

int DisplayEptry(TMake &Make, std::vector<int>&Vect){
			Graphics^ g = Graphics::FromHwnd(this->panel2->Handle);
			g->Clear(Color::White);
			int p(0);
			Vect.clear();
			int l = Make.getYmaxGearBox();
			int k;
			if (this->panel2->Width / Make.getYmaxGearBox() < (this->panel2->Height - 10) / 13)
				k = this->panel2->Width / Make.getYmaxGearBox();
			else
				k = (this->panel2->Height - 10) / 13;
			Pen^ MyPen = gcnew Pen(Brushes::Black);
			MyPen->Width = 4;
			for (int j = 1; j <= Make.getCountPlanRyad(); j++){
				p = 0;
				for (unsigned int i = 0; i < Make.getSizeV(); i++)
					if (Make.getCellV(i) == 3*1000 + 100*j)
						if (p == 0){
							p = i;
							Vect.push_back(3*1000 + 100*j);
							Vect.push_back(p%l*k);
							Vect.push_back(p/l*k);
							
						} else {							
							g->DrawLine(MyPen , p%l*k, p/l*k, i%l*k, i/l*k);
							Vect.push_back(3*1000 + 100*j);
							Vect.push_back(i%l*k);
							Vect.push_back(i/l*k);
							
						}					
				p = 0;
				for (unsigned int i = 0; i < Make.getSizeV(); i++){
					if (Make.getCellV(i) == 2*1000 + 100*j){							
						p = i;
						Vect.push_back(2*1000 + 100*j);
						Vect.push_back(p%l*k);
						Vect.push_back(p/l*k);
					}
					if (Make.getCellV(i) == 1*1000 + 100*j){
						g->DrawLine(MyPen , p%l*k, p/l*k, i%l*k, i/l*k);
						Vect.push_back(1*1000 + 100*j);
						Vect.push_back(i%l*k);
						Vect.push_back(i/l*k);
					}
				}
				p = l+1;
			}
			for (unsigned int i = 0; i < Make.getSizeV(); i++)
				if (Make.getCellV(i) == 6600){	
					g->DrawLine(MyPen, i%l*k, i/l*k , p%l*k, p/l*k);
					p = i;
					Vect.push_back(6600);
					Vect.push_back(p%l*k);
					Vect.push_back(p/l*k);
				}
			for (unsigned int i = 0; i < Make.getSizeV(); i++){
				if (Make.getCellV(i) == 4400){
					g->DrawRectangle(MyPen , (int)i%l*k-1, i/l*k-1, 2,2);
					Vect.push_back(4400);
					Vect.push_back(i%l*k);
					Vect.push_back(i/l*k);
				}
				if (Make.getCellV(i) == 5500){
					g->DrawRectangle(MyPen , (int)i%l*k, i/l*k, 2,2);
					Vect.push_back(5500);
					Vect.push_back(i%l*k);
					Vect.push_back(i/l*k);
				}
			}
			return 0;
		}

int Convert(int i){
			return ((i%10) - 1)*3 + i/10;
		}

void GetParam(int CountP, int W)
		{
			size_t F, N, CountSV, CountT;
			switch (W){
				case 2:
					F = 1;
					CountT = CountP - 1;
					N = CountT;
					CountSV = 2*N - W;
					break;
				case 3:
					F = 2;
					if (CountP < 3) CountT = 0;
					if (CountP == 3) CountT = 1;
					if ((CountP > 3) && (CountP <= 6)) CountT = 2;
					if ((CountP > 6) && (CountP <= 10)) CountT = 3;
					if ((CountP > 10) && (CountP <= 12)) CountT = 4;
					N = CountT + 1;
					CountSV = 2*N - W;
					break;
				default:
					return;
					break;
			}
			this->label3->Text = "Friction clutch: " + F.ToString();
			this->label4->Text = "Brakes: " + CountT.ToString();
			this->label5->Text = "Planetary gears: " + N.ToString();
			this->label6->Text = "Links: " + CountSV.ToString();
		}

bool GetParam(int CountP, int W, std::vector<size_t> v){
			size_t CountSV, CountT;
			switch (W){
			case 2:
				CountT = CountP - 1;
				CountSV = 2 * CountT - W;
				break;
			case 3:
				if (CountP < 3) CountT = 0;
				if (CountP == 3) CountT = 1;
				if ((CountP > 3) && (CountP <= 6)) CountT = 2;
				if ((CountP > 6) && (CountP <= 10)) CountT = 3;
				if ((CountP > 10) && (CountP <= 12)) CountT = 4;
				CountSV = 2 * (CountT + 1) - W;
				break;
			default:
				return false;
				break;
			}
			size_t c_in(0), c_out(0), c_sv(0), c_t(0);
			for (int i = 0; i < v.size(); i++){
				if (v[i] % 100 == 44)
					++c_in;
				if (v[i] % 100 == 55)
					++c_out;
				if (v[i] % 100 == 66)
					++c_t;
			}
			c_sv = v.size() - 2 - c_in - c_out - c_t;
			this->label15->Text = "(" + c_t.ToString() + ")";
			this->label16->Text = "(" + c_sv.ToString() + ")";
			if ((c_in == 1) && (c_out == 1) && (c_t == CountT) && (c_sv == CountSV))
				return true;
			else
				return false;
}

template <class T>
void AddToListBox(System::Windows::Forms::ListBox^  LB, System::String^ str1, System::String^ HEAD, std::vector<T> VECT){
	LB->Items->Add(str1 + ":");
	LB->Items->Add(HEAD);
	System::String^ str = "";
	for (size_t j = 0; j < VECT.size(); j++)
		str += (int(VECT[j] * 100) / 100.0).ToString() + "	";
	LB->Items->Add(str);
	LB->Items->Add("");
}

template <class T>
void AddToListBox(System::Windows::Forms::ListBox^  LB, System::String^ str1, System::String^ HEAD, std::vector<std::vector<T>> VECT){
	LB->Items->Add(str1 + ":");
	LB->Items->Add(HEAD);
	for (size_t i = 0; i < VECT.size(); i++){
		System::String^ str = (i + 1).ToString() + ":	";
		for (size_t j = 0; j < VECT[i].size(); j++)
			str += (int(VECT[i][j] * 100) / 100.0).ToString() + "	";
		LB->Items->Add(str);
	}
	LB->Items->Add("");
}

char * StringToChar(System::String^ string)
{
	return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
}

System::String^ CharToString(char* ch)
{
	char * chr = ch;
	System::String^ str;
	for (int i = 0; chr[i] != '\0'; i++)
	{
		str += wchar_t(ch[i]);
	}
	return str;
}

void AddToListBox(System::Windows::Forms::ListBox^  LB, System::String^ str1, System::String^ HEAD, std::vector<std::vector<char>> VECT){
	LB->Items->Add(str1 + ":");
	LB->Items->Add(HEAD);
	for (size_t i = 0; i < VECT.size(); i++){
		System::String^ str = (i + 1).ToString() + ":	";
		for (size_t j = 0; j < VECT[i].size(); j++){
			if (VECT[i][j] == '+')
				str += "+	";
			if (VECT[i][j] == '-')
				str += "-	";
			if (VECT[i][j] == '0')
				str += "0	";
		}
		LB->Items->Add(str);
	}
	LB->Items->Add("");
}

private: System::Void maskedTextBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Enter){
				 double d = Convert::ToDouble(this->maskedTextBox1->Text);
				 if (d != 0){
					 VectI.push_back(d);
					 this->listBox1->Items->Add(VectI[countP].ToString());
					 countP += 1;
					 this->maskedTextBox1->Text = "+0";
					 GetParam(countP + 1, countS);
					 this->button1->Enabled = true;
					 if (ToolStripMenuItem3->Checked == true){
						 TMake Make;
						 TPlanRyad PlanRyad;
						 this->listBox2->Items->Clear();
						 std::vector<size_t>Input;
						 //Input.clear();
						 Input.resize(4);
						 Input[0] = VectI.size();
						 Vect.clear();
						 Vect.push_back(Input[0]);
						 Vect.push_back(0);
						 Input[1] = 0;
						 Input[2] = 1144;
						 Input[3] = 2155;
						 Make.Run(Input);
						 DisplayEptry(Make, V);
						 this->button1->Enabled = false;
					 }
				 }
				 else
				 if (this->button1->Enabled == true)
					 button1_Click(sender, e);				
			 }
			 
		 }

private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				countS = (int)this->numericUpDown1->Value;
				GetParam(countP+1, countS);
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 TGenerate Gen(countP + 1, countS, VectI);
			 System::String^ s;
			 int in, out;
			 int count = 1;
			 Schemes.clear();
			 double E = Convert::ToDouble(this->maskedTextBox4->Text);
			 double k = Convert::ToDouble(this->maskedTextBox5->Text);
			 double beg1 = Convert::ToDouble(this->maskedTextBox6->Text);
			 double end1 = Convert::ToDouble(this->maskedTextBox7->Text);
			 double beg2 = Convert::ToDouble(this->maskedTextBox9->Text);
			 double end2 = Convert::ToDouble(this->maskedTextBox8->Text);
			 if (beg1 > end1)
				 std::swap(beg1, end1);
			 if (beg2 > end2)
				 std::swap(beg2, end2);
			if (ToolStripMenuItem2->Checked == true){
				in = Convert(Convert::ToInt32(this->maskedTextBox2->Text));
				out = Convert(Convert::ToInt32(this->maskedTextBox3->Text));
				Gen.Run(in, out, E, k, beg1, end1, beg2, end2);
			} 
			if (ToolStripMenuItem1->Checked == true) {
				Gen.Run(E, k, beg1, end1, beg2, end2);
			}
			if (ToolStripMenuItem3->Checked == true) {
				TPKP pkp(Vect, VectI, E, k, beg1, end1, beg2, end2);
				if (pkp.Finded){
					System::String ^S;
					S = "";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "k" + (i + 1).ToString() + "	";
					AddToListBox(this->listBox3, "Внутренне передаточное отношение ПМ - k", S, pkp.k);
					S = "";
					for (size_t i = 0; i < pkp.i.size(); i++)
						S = S + "i" + (i + 1).ToString() + "	";
					AddToListBox(this->listBox3, "Фактические передаточные отношения КП - I", S, pkp.i);
					AddToListBox(this->listBox3, "Числа зубьев на шестернях - z", "	z1	z2	z4", pkp.z);
					S = "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "w1" + (i + 1).ToString() + "	w2" + (i + 1).ToString() + "	w3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "w4" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "wT" + (i + 1).ToString() + "	";
					S += "wF1	wF2	wIn	wOut\n";
					AddToListBox(this->listBox3, "Угловая скорость основных звеньев ПКП - w, 1/с", S, pkp.w_Ext);
					S = "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "M1" + (i + 1).ToString() + "	M2" + (i + 1).ToString() + "	M3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "MT" + (i + 1).ToString() + "	";
					S += "MF1	MF2	MIn	MOut\n";
					AddToListBox(this->listBox3, "Моменты, действующие на центральные звенья, тормоза, фрикционы - M, Нм", S, pkp.M);
					S = "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "N1" + (i + 1).ToString() + "	N2" + (i + 1).ToString() + "	N3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "N4" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "N" + (i + 1).ToString() + "	";
					S += "NF1	NF2	NIn	NOut\n";
					AddToListBox(this->listBox3, "Знак мощьности, проходящей через основные звенья, тормоза, фрикционы - N", S, pkp.N);
					S = "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "M1" + (i + 1).ToString() + "	M2" + (i + 1).ToString() + "	M3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < pkp.k.size(); i++)
						S = S + "MT" + (i + 1).ToString() + "	";
					S += "MF1	MF2	MIn	MOut\n";
					AddToListBox(this->listBox3, "Моменты, действующие на центральные звенья, тормоза, фрикционы, с учетом КПД - M, Нм", S, pkp.Mn);
					AddToListBox(this->listBox3, "Критерии качества", "K1	K2	K3	K4	K5_1	K5_2	K6	Kint", pkp.K);
					Schemes.push_back(pkp);
				}else{
					MessageBox::Show("Решение не найдено", "Решение не найдено", MessageBoxButtons::OK, MessageBoxIcon::Asterisk); 
					//this->listBox3->Items->Add("Решение не найдено");
				}
				return;
			}
			if (Gen.MasPKP_all.size() == 0){
				MessageBox::Show("Решение не найдено", "Решение не найдено", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				//this->listBox3->Items->Add("Решение не найдено");
				return;
			}
			for (size_t l = 0; l < Gen.MasPKP_all.size(); l++){
				s = "";
				s += count.ToString();
				s += ":	 ";
				count++;
				Schemes.push_back(Gen.MasPKP_all[l]);
				for (unsigned k = 0; k < Gen.MasPKP_all[l].Code.size(); k++)
					s += Gen.MasPKP_all[l].Code[k].ToString() + " ";
				this->listBox2->Items->Add(s);
			}
			this->button1->Enabled = false;
		 }

private: System::Void ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			ToolStripMenuItem2->Checked = false;
			ToolStripMenuItem3->Checked = false;
			if (ToolStripMenuItem1->Checked == false)
				ToolStripMenuItem1->Checked = true;
			this->повторитьToolStripMenuItem_Click(sender, e);
			this->maskedTextBox2->Visible = false;
			this->maskedTextBox3->Visible = false;
			this->label7->Visible = false;
			this->label8->Visible = false;
			this->label1->Text = "Choose W";
		 }

private: System::Void ToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
			ToolStripMenuItem1->Checked = false;
			ToolStripMenuItem3->Checked = false;
			if (ToolStripMenuItem2->Checked == false)
				ToolStripMenuItem2->Checked = true;
			this->повторитьToolStripMenuItem_Click(sender, e);
			this->maskedTextBox2->Visible = true;
			this->maskedTextBox3->Visible = true;
			this->label7->Visible = true;
			this->label8->Visible = true;
			this->label1->Text = "Choose W";
		 }

private: System::Void ToolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e) {
			ToolStripMenuItem1->Checked = false;
			ToolStripMenuItem2->Checked = false;
			if (ToolStripMenuItem3->Checked == false)
				ToolStripMenuItem3->Checked = true;
			this->повторитьToolStripMenuItem_Click(sender, e);
			this->maskedTextBox2->Visible = false;
			this->maskedTextBox3->Visible = false;
			this->label7->Visible = false;
			this->label8->Visible = false;
			this->label1->Text = "Choose CountPlanRyad";
			this->button1->Enabled = false;
		 }

private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
			countS = (int)this->numericUpDown1->Value;
			ToolStripMenuItem1->Checked = true;
			this->maskedTextBox2->Visible = false;
			this->maskedTextBox3->Visible = false;
			this->label7->Visible = false;
			this->label8->Visible = false;
			this->comboBox1->Items->Add("K1");
			this->comboBox1->Items->Add("K2");
			this->comboBox1->Items->Add("K3");
			this->comboBox1->Items->Add("K4");
			this->comboBox1->Items->Add("K5_1");
			this->comboBox1->Items->Add("K5_2");
			this->comboBox1->Items->Add("K6");
			this->comboBox1->Items->Add("Kint");
			this->comboBox1->SelectedIndex = 0;
			Form1::maskedTextBox1->Focus();
		 }

private: System::Void повторитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			countP = 0;
			countS = (int)this->numericUpDown1->Value;
			VectI.clear();
			Schemes.clear();
			this->listBox1->Items->Clear();
			this->listBox2->Items->Clear();
			this->listBox3->Items->Clear();
			this->maskedTextBox1->Text = "+0";
			this->maskedTextBox2->Text = "";
			this->maskedTextBox3->Text = "";
			this->label3->Text = "";
			this->label4->Text = "";
			this->label5->Text = "";
			this->label6->Text = "";
			this->label15->Text = "";
			this->label16->Text = "";
			Graphics^ g = Graphics::FromHwnd(this->panel2->Handle);
			g->Clear(Color::White);
			Vect.clear();
			V.clear();
		 }

private: System::Void закрытьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void listBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if ((ToolStripMenuItem3->Checked == false) && (this->listBox2->SelectedIndex <= Schemes.size())) {
					TMake Make;
					Make.Run(Schemes[this->listBox2->SelectedIndex].Code);
					Display(Make);
					this->listBox3->Items->Clear();
					System::String ^S;
					S = "";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S =  S + "k" + (i+1).ToString() + "	";
					AddToListBox(this->listBox3, "Внутренне передаточное отношение ПМ - k", S, Schemes[this->listBox2->SelectedIndex].k);
					S = "";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].i.size(); i++)
						S = S + "i" + (i + 1).ToString() + "	";
					AddToListBox(this->listBox3, "Фактические передаточные отношения КП - I", S, Schemes[this->listBox2->SelectedIndex].i);
					AddToListBox(this->listBox3, "Числа зубьев на шестернях - z", "	z1	z2	z4", Schemes[this->listBox2->SelectedIndex].z);
					S = "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "w1" + (i + 1).ToString() + "	w2" + (i + 1).ToString() + "	w3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "w4" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "wT" + (i + 1).ToString() + "	";
					S += "wF1	wF2	wIn	wOut\n";
					AddToListBox(this->listBox3, "Угловая скорость основных звеньев ПКП - w, 1/с", S, Schemes[this->listBox2->SelectedIndex].w_Ext);
					S = "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "M1" + (i + 1).ToString() + "	M2" + (i + 1).ToString() + "	M3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "MT" + (i + 1).ToString() + "	";
					S += "MF1	MF2	MIn	MOut\n";
					AddToListBox(this->listBox3, "Моменты, действующие на центральные звенья, тормоза, фрикционы - M, Нм", S, Schemes[this->listBox2->SelectedIndex].M);
					S = "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "N1" + (i + 1).ToString() + "	N2" + (i + 1).ToString() + "	N3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "N4" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "NT" + (i + 1).ToString() + "	";
					S += "NF1	NF2	NIn	NOut\n";
					AddToListBox(this->listBox3, "Знак мощьности, проходящей через основные звенья, тормоза, фрикционы - N", S, Schemes[this->listBox2->SelectedIndex].N);
					S = "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "M1" + (i + 1).ToString() + "	M2" + (i + 1).ToString() + "	M3" + (i + 1).ToString() + "	";
					for (size_t i = 0; i < Schemes[this->listBox2->SelectedIndex].k.size(); i++)
						S = S + "MT" + (i + 1).ToString() + "	";
					S += "MF1	MF2	MIn	MOut\n";
					AddToListBox(this->listBox3, "Моменты, действующие на центральные звенья, тормоза, фрикционы, с учетом КПД - M, Нм", S, Schemes[this->listBox2->SelectedIndex].Mn);
					AddToListBox(this->listBox3, "Критерии качества", "K1	K2	K3	K4	K5_1	K5_2	K6	Kint", Schemes[this->listBox2->SelectedIndex].K);
				}
		 }

private: System::Void panel2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (ToolStripMenuItem3->Checked == true){
				 TMake Make;
				 int link;
				 if (SecondClick == false){
					 for (unsigned int i = 0; i < V.size(); i = i + 3){
						 if ((V[i + 1] < e->X + 4) &&
							 (V[i + 1] > e->X - 4) &&
							 (V[i + 2] < e->Y + 4) &&
							 (V[i + 2] > e->Y - 4)){
							 L = V[i];
							 SecondClick = true;
						 }
					 }
				 }
				 else{
					 for (unsigned int i = 0; i < V.size(); i = i + 3)
					 if ((V[i + 1] < e->X + 4) &&
						 (V[i + 1] > e->X - 4) &&
						 (V[i + 2] < e->Y + 4) &&
						 (V[i + 2] > e->Y - 4)){
						 if ((L == 4400) || (L == 5500) || (L == 6600))
							 L = L / 100 + V[i];
						 else
							 L = L + V[i] / 100;
						 SecondClick = false;
						 link = L;
						 if (link % 100 == 66)
							 ++Vect[1];
						 if (link % 100 == 44)
							 Vect.insert(Vect.begin() + 2, link);
						 else
							 Vect.push_back(link);
						 Make.Run(Vect);
						 this->Display(Make);
						 this->listBox2->Items->Clear();
						 for (unsigned int i = 0; i < Vect.size(); i++)
							 this->listBox2->Items->Add(Vect[i].ToString());
					 }
				 }
				 if (GetParam(Vect[0]+1, 2, Vect))
					 this->button1->Enabled = true;
				 else
					 this->button1->Enabled = false;
			 }
		 }

private: System::Void panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (ToolStripMenuItem3->Checked == true) {
				if (!SecondClick)
					this->Cursor = System::Windows::Forms::Cursors::Arrow;
				 else
					 this->Cursor = System::Windows::Forms::Cursors::Cross;
				 Graphics^ g = Graphics::FromHwnd(this->panel2->Handle);
				 Pen^ MyPen = gcnew Pen(Brushes::Red);
				 MyPen->Width = 4;
				 for (unsigned int i = 0; i < V.size(); i = i+3)
					if ((V[i+1] < e->X+4) &&
						(V[i+1] > e->X-4) &&
						(V[i+2] < e->Y+4) &&
						(V[i+2] > e->Y-4)){
							MyPen->Color = Color::Red;
							g->DrawRectangle(MyPen, V[i+1]-2, V[i+2]-2, 4, 4);
							this->Cursor = System::Windows::Forms::Cursors::Hand;
					}
					else{
							MyPen->Color = Color::Black;
							g->DrawRectangle(MyPen, V[i+1]-2, V[i+2]-2, 4, 4);
					}
			 }
		 }
private: System::Void сохранитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && folderBrowserDialog1->SelectedPath->Length > 0){
				 System::String^ Folder = folderBrowserDialog1->SelectedPath;
				 char buffer[80];
				 time_t seconds = time(NULL);
				 tm* timeinfo = localtime(&seconds);
				 char* format = "%d_%B_%Y_%H_%M_%S";
				 strftime(buffer, 80, format, timeinfo);
				 System::String^ File = CharToString(buffer);
				 File = Folder + "\\" + File + ".pkp";
				 double E = Convert::ToDouble(this->maskedTextBox4->Text);
				 double k = Convert::ToDouble(this->maskedTextBox5->Text);
				 double beg1 = Convert::ToDouble(this->maskedTextBox6->Text);
				 double end1 = Convert::ToDouble(this->maskedTextBox7->Text);
				 double beg2 = Convert::ToDouble(this->maskedTextBox9->Text);
				 double end2 = Convert::ToDouble(this->maskedTextBox8->Text);
				 if (beg1 > end1)
					 std::swap(beg1, end1);
				 if (beg2 > end2)
					 std::swap(beg2, end2);
				 char* file_name = StringToChar(File);
				 std::ofstream file(file_name, std::ios::binary | std::ios::out);
				 if (file.fail()) {
					 this->listBox2->Items->Add("Error");
					 return;
				 }
				 size_t size = VectI.size();
				 file << E << ' ' << k << ' ' << beg1 << ' ' << end1 << ' ' << beg2 << ' ' << end2 << '\n' << size << ' ';
				 for (size_t j = 0; j < VectI.size(); j++)
					 file << VectI[j] << ' ';
				 file << '\n';
				 file << Schemes[0].Code.size() << '\n';
				 for (size_t j = 0; j < Schemes.size(); j++){
					 for (size_t k = 0; k < Schemes[0].Code.size(); k++)
						 file << Schemes[j].Code[k] << ' ';
					 file << '\n';
				 }
				 file.close();
			 }
}
private: System::Void загрузитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ToolStripMenuItem1->Checked = true;
			 ToolStripMenuItem3->Checked = false;
			 this->повторитьToolStripMenuItem_Click(sender, e);
			 // Create an OpenFileDialog to request a file to open.
			 std::fstream f;
			 // Initialize the OpenFileDialog to look for RTF files.
			 openFileDialog1->DefaultExt = "*.pkp";
			 openFileDialog1->Filter = "TXT Files|*.pkp";
			 // Determine whether the user selected a file from the OpenFileDialog.
			 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
			 {
				 char *file_name = StringToChar(openFileDialog1->FileName);
				 double E, dK, K1, K2, K3, K4;
				 std::fstream file;
				 file.open(file_name, std::ios::binary | std::ios::in);
				 if (file.fail()) {
					 this->listBox2->Items->Add("Error");
					 return;
				 }
				 size_t size;
				 file >> E >> dK >> K1 >> K2 >> K3 >> K4 >> size;
				 VectI.clear();
				 VectI.resize(size);
				 for (size_t j = 0; j < size; j++){
					 file >> VectI[j];
					 listBox1->Items->Add(Convert::ToString(VectI[j]));
				 }
				 file >> size;
				 std::vector<size_t> temp;
				 temp.resize(size);
				 Schemes.clear();
				 while (!file.eof()){
					 for (size_t k = 0; k < size; k++)
						 file >> temp[k];
					 TPKP pkp(temp, VectI, E, dK, K1, K2, K3, K4);
					 Schemes.push_back(pkp);
				 }
				 file.close();
				 this->maskedTextBox4->Text = E.ToString();
				 this->maskedTextBox5->Text = dK.ToString();
				 this->maskedTextBox6->Text = K1.ToString();
				 this->maskedTextBox7->Text = K2.ToString();
				 this->maskedTextBox9->Text = K3.ToString();
				 this->maskedTextBox8->Text = K4.ToString();
				 System::String^ s;
				 int count = 1;
				 for (size_t l = 0; l < Schemes.size(); l++){
					 s = "";
					 s += count.ToString();
					 s += ":	 ";
					 count++;
					 Schemes[l].krit = this->comboBox1->SelectedIndex;
					 for (unsigned k = 0; k < Schemes[l].Code.size(); k++)
						 s += Schemes[l].Code[k].ToString() + " ";
					 this->listBox2->Items->Add(s);
				 }
				 return;
			 }
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 for (size_t l = 0; l < Schemes.size(); l++){
				 Schemes[l].krit = this->comboBox1->SelectedIndex;
			 }
			 std::sort(Schemes.begin(), Schemes.end());
			 this->listBox2->Items->Clear();
			 System::String^ s;
			 int count = 1;
			 for (size_t l = 0; l < Schemes.size(); l++){
				 s = "";
				 s += count.ToString();
				 s += ":	 ";
				 count++;
				 Schemes[l].krit = this->comboBox1->SelectedIndex;
				 for (unsigned k = 0; k < Schemes[l].Code.size(); k++)
					 s += Schemes[l].Code[k].ToString() + " ";
				 this->listBox2->Items->Add(s);
			 }

}
private: System::Void сохранитьXLSToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && folderBrowserDialog1->SelectedPath->Length > 0){
				 System::String^ Folder = folderBrowserDialog1->SelectedPath;
				 char buffer[80];
				 time_t seconds = time(NULL);
				 tm* timeinfo = localtime(&seconds);
				 char* format = "%d_%B_%Y_%H_%M_%S";
				 strftime(buffer, 80, format, timeinfo);
				 System::String^ File = CharToString(buffer);
				 File = Folder + "\\" + File + ".xls";
				 char* file_name = StringToChar(File);
				 std::fstream file(file_name, std::ios::out);
				 if (file.fail()) {
					 this->listBox2->Items->Add("Error");
					 return;
				 }
				 for (size_t i = 0; i < Schemes.size(); i++){
					 Schemes[i].WriteToFile(file);
				 }
				 file.close();
			 }
}
};
}

