#pragma once
#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Exception.h"
#include <string>
#include "Compute.h"
#include <map>

namespace Project1EM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	
	std::map<std::string, MyVector> vectors;
	std::map<std::string, MyMatrix> matrices;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		
	private: System::Windows::Forms::ListBox^  listBox1;
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				22.08092F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				77.91908F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				15)));
			this->tableLayoutPanel1->Controls->Add(this->button1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->button2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->listBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->textBox1, 1, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 91.14173F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.858268F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(874, 508);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 465);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 40);
			this->button1->TabIndex = 0;
			this->button1->Text = L"read";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(192, 465);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 40);
			this->button2->TabIndex = 1;
			this->button2->Text = L"compute";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 15;
			this->listBox1->Location = System::Drawing::Point(3, 3);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(183, 454);
			this->listBox1->TabIndex = 4;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->InitialDirectory = L"D:\\Downloads\\Project1_EM\\Project1_EM\\test";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(192, 3);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(663, 456);
			this->textBox1->TabIndex = 5;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(874, 508);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->ShowDialog();
}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	try
	{
		StreamReader^ file = gcnew StreamReader(openFileDialog1->FileName);
		String^ str = file->ReadToEnd();
		array<String^>^ temp = str->Split(gcnew array<System::String ^>{" ", "\n", "\t"}, System::StringSplitOptions::RemoveEmptyEntries);;
		int index = 1;
		matrices.clear();
		vectors.clear();
		listBox1->Items->Clear();
		while (index < temp->Length)
		{
			//Vector reading
			if (temp[index] == "V")
			{
				index++;
				MyVector v;
				int dimension = int::Parse(temp[index++]);

				for (int i = 0; i < dimension; i++)
				{
					//std::cout << double::Parse(temp[index]) << " ";
					v.data.push_back(double::Parse(temp[index++]));
				}
				std::string s = "V";
				s += std::to_string(vectors.size() + 1);
				vectors[s] = v;

				String ^str = gcnew String("");
				str = "V" + vectors.size() + " size:" + v.dimension();
				//std::cout << std::endl;
				listBox1->Items->Add(str);
			}
			//Matrix reading
			else if (temp[index] == "M")
			{
				index++;
				MyMatrix m;
				int row = int::Parse(temp[index++]);
				int col = int::Parse(temp[index++]);
				for (int i = 0; i < row; i++)
				{
					MyVector v;
					for (int j = 0; j < col; j++)
					{
						v.data.push_back(double::Parse(temp[index++]));
					}
					m.data.push_back(v);
				}
				String ^str = gcnew String("");
				str = "M" + matrices.size() + " size:" + m.row() + "*" + m.col();
				listBox1->Items->Add(str);

				std::string s = "M";
				s += std::to_string(matrices.size() + 1);
				matrices[s] = m;
			}
		}
	}
	catch (Exceptions e)
	{
		if (e.getType() == error::readError)
		{
			std::cout << "File can NOT read!" << std::endl;
		}
		else
		{
			std::cout << "error" << std::endl;
		}
	}
	catch (...)
	{

	}
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	try
	{
		//convert C# String to c++ std::string.
		using System::Runtime::InteropServices::Marshal;
		System::IntPtr pointer = Marshal::StringToHGlobalAnsi(textBox1->Text);
		char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
		std::string returnString(charPointer, textBox1->Text->Length);
		Marshal::FreeHGlobal(pointer);
		
		std::cout << Compute(returnString, vectors, matrices) << std::endl;
	}
	catch (Exceptions e)
	{
		switch (e.getType())
		{
		case error::dimension:
			std::cout << "Dimension not equal!" << std::endl; 
			break;
		case error::divideZero:
			std::cout << "Divide 0!" << std::endl;
			break;
		case error::rowNotEqualCol:
			std::cout << "Row is not equal col." << std::endl;
			break;
		case error::noInverse:
			std::cout << "No inverse." << std::endl;
			break;
		case error::done:
			break;
		case error::computeError:
			std::cout << "Compute error." << std::endl;
			break;
		default:
			std::cout << "wrong";
			break;
		}
	}
	catch (...)
	{

	}
}
};
}
