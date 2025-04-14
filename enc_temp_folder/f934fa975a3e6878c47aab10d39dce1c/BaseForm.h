#pragma once
#include <thread>
#include <shlobj.h>
#include "Crypto.h"
#include <msclr\marshal_cppstd.h>
#pragma comment(lib, "shell32.lib")

namespace TaskManager {

	LPCSTR mutexName = "TaskManager";
	HANDLE hMutex;
	public delegate void MyDel();

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ BaseForm
	/// </summary>
	public ref class BaseForm : public System::Windows::Forms::Form
	{
	public:
		String^ sPID="";
		String^ sNameDll="";
		void gridRefreshThread();
		void gridRefresh();
		void getDataFromNum(std::string s, std::string s1);
		void sendDataFromNum(std::string s, std::string s1);
		void endFromNum(std::string s);
		std::string postData(std::string postData);
		//BOOL IsUserAdmin();
		BaseForm(void)
		{
			InitializeComponent();
			gridAdd();
			thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &BaseForm::gridRefreshThread));
			thread->Start();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~BaseForm()
		{
			thread->Abort();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	protected:
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ buttonGet;

	private: System::Windows::Forms::Button^ buttonSend;

	private: System::Windows::Forms::Button^ buttonEnd;
	private: System::Windows::Forms::Button^ buttonRestart;
	private: System::Threading::Thread^ thread;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->buttonGet = (gcnew System::Windows::Forms::Button());
			this->buttonSend = (gcnew System::Windows::Forms::Button());
			this->buttonEnd = (gcnew System::Windows::Forms::Button());
			this->buttonRestart = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->dataGridView1, 2, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(696, 437);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 4;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel2->Controls->Add(this->buttonGet, 3, 0);
			this->tableLayoutPanel2->Controls->Add(this->buttonSend, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->buttonEnd, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->buttonRestart, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 396);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(690, 38);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// buttonGet
			// 
			this->buttonGet->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonGet->Location = System::Drawing::Point(519, 3);
			this->buttonGet->Name = L"buttonGet";
			this->buttonGet->Size = System::Drawing::Size(168, 32);
			this->buttonGet->TabIndex = 3;
			this->buttonGet->Text = L"Get data";
			this->buttonGet->UseVisualStyleBackColor = true;
			this->buttonGet->Click += gcnew System::EventHandler(this, &BaseForm::buttonGet_Click);
			// 
			// buttonSend
			// 
			this->buttonSend->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonSend->Location = System::Drawing::Point(347, 3);
			this->buttonSend->Name = L"buttonSend";
			this->buttonSend->Size = System::Drawing::Size(166, 32);
			this->buttonSend->TabIndex = 2;
			this->buttonSend->Text = L"Send data";
			this->buttonSend->UseVisualStyleBackColor = true;
			this->buttonSend->Click += gcnew System::EventHandler(this, &BaseForm::buttonSend_Click);
			// 
			// buttonEnd
			// 
			this->buttonEnd->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonEnd->Location = System::Drawing::Point(175, 3);
			this->buttonEnd->Name = L"buttonEnd";
			this->buttonEnd->Size = System::Drawing::Size(166, 32);
			this->buttonEnd->TabIndex = 1;
			this->buttonEnd->Text = L"End task";
			this->buttonEnd->UseVisualStyleBackColor = true;
			this->buttonEnd->Click += gcnew System::EventHandler(this, &BaseForm::buttonEnd_Click);
			// 
			// buttonRestart
			// 
			this->buttonRestart->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonRestart->Location = System::Drawing::Point(3, 3);
			this->buttonRestart->Name = L"buttonRestart";
			this->buttonRestart->Size = System::Drawing::Size(166, 32);
			this->buttonRestart->TabIndex = 0;
			this->buttonRestart->Text = L"Restart with Admin";
			this->buttonRestart->UseVisualStyleBackColor = true;
			this->buttonRestart->Click += gcnew System::EventHandler(this, &BaseForm::buttonRestart_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->Location = System::Drawing::Point(3, 3);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(690, 387);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &BaseForm::dataGridView1_CellClick);
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->MinimumWidth = 6;
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			// 
			// BaseForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(696, 437);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MinimumSize = System::Drawing::Size(714, 484);
			this->Name = L"BaseForm";
			this->Text = L"TaskManager";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
		void gridAdd()
		{
			if (IsUserAnAdmin()) { this->buttonRestart->Enabled = false; };
			this->dataGridView1->Columns[0]->Name = "PID";
			this->dataGridView1->Columns[1]->Name = "Name";
			this->dataGridView1->Columns[0]->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridView1->Columns[1]->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
		}
		void rowsaddDel(int pos)
		{
			this->dataGridView1->Rows->Insert(pos, 1);
		}
		void rowsdelDel(int pos)
		{
			this->dataGridView1->Rows->RemoveAt(pos);
		}
		void rowsadd(String^ s1, String^ s2, int pos) {
			this->dataGridView1->Invoke(gcnew Action<int>(this, &BaseForm::rowsaddDel), pos);
			this->dataGridView1->Rows[pos]->Cells[0]->Value = s1;
			this->dataGridView1->Rows[pos]->Cells[1]->Value = s2;
		}
		void rowschange(String^ s1, String^ s2,int pos) {
			this->dataGridView1->Rows[pos]->Cells[0]->Value = s1;
			this->dataGridView1->Rows[pos]->Cells[1]->Value = s2;
		}		
		void rowsdel(int pos) {
			this->dataGridView1->Invoke(gcnew Action<int>(this, &BaseForm::rowsdelDel), pos);
		}
		void messageBox(String^ s1)
		{
			MessageBox::Show(s1, "ѕолученные данные", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
#pragma endregion
private: System::Void buttonRestart_Click(System::Object^ sender, System::EventArgs^ e) {
	HANDLE hMutexO = OpenMutexA(MUTEX_ALL_ACCESS, 0, mutexName);
	if (hMutexO) { CloseHandle(hMutexO); CloseHandle(hMutex);}
	hMutex = OpenMutexA(MUTEX_ALL_ACCESS, 0, mutexName);
	wchar_t szPath[MAX_PATH];
	if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
	{
		SHELLEXECUTEINFO sei = { sizeof(sei) };
		sei.lpVerb = L"runas";
		sei.lpFile = szPath;
		sei.hwnd = NULL;
		sei.nShow = SW_NORMAL;
		if (!ShellExecuteEx(&sei))
		{
			hMutex = CreateMutexA(0, 0, mutexName);
		}
		else
		{
			_exit(1); 
		}
	}
}
private: System::Void buttonEnd_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ s1 = sPID;
	endFromNum(msclr::interop::marshal_as<std::string>(s1));
}
private: System::Void buttonSend_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ s1 = sPID; String^ s2 = sNameDll;
	if (s1 != "")
	{
		sendDataFromNum(msclr::interop::marshal_as<std::string>(s1), msclr::interop::marshal_as<std::string>(s2));
	}
}
private: System::Void buttonGet_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ s1 = sPID; String^ s2 = sNameDll;
	if (s1 != "")
	{
		getDataFromNum(msclr::interop::marshal_as<std::string>(s1), msclr::interop::marshal_as<std::string>(s2));
	}
}
private: System::Void dataGridView1_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) 
{
	if (this->dataGridView1->RowCount >= 2 && e->RowIndex!= this->dataGridView1->RowCount-1)
	{sPID = this->dataGridView1->Rows[e->RowIndex]->Cells[0]->Value->ToString();
	 sNameDll = this->dataGridView1->Rows[e->RowIndex]->Cells[1]->Value->ToString();}
}
};
}
