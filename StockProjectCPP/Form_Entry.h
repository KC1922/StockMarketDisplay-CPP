#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "aCandleStick.h"
#include "Form_CandlestickChart.h"
#using <System.Core.dll>

namespace fs = std::filesystem;


namespace StockProjectCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	using namespace System::Collections::Generic;
	using namespace System::IO;
	using namespace System::Text;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form_Entry : public System::Windows::Forms::Form
	{
	private:
		List<List<smartCandlestick^>^>^ listOfListOfScs;
	public:
		Form_Entry(void)
		{
			InitializeComponent();
			dateTimePicker_Start->Value = DateTime::Parse("1/1/2021");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_Entry()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_loadStock;
	private: System::Windows::Forms::Button^ button_showOutlook;
	protected:

	protected:


	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_Start;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_End;
	private: System::Windows::Forms::Label^ label_Start;
	private: System::Windows::Forms::Label^ label_End;
	private: System::Windows::Forms::Label^ label_otherOptions;
	private: System::Windows::Forms::ComboBox^ comboBox_otherOptions;
	private: System::Windows::Forms::TextBox^ textBox_loadedStocks;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_stockFolder;
	private: System::Windows::Forms::ToolTip^ toolTip_formEntry;
	private: System::ComponentModel::IContainer^ components;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button_loadStock = (gcnew System::Windows::Forms::Button());
			this->button_showOutlook = (gcnew System::Windows::Forms::Button());
			this->dateTimePicker_Start = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_End = (gcnew System::Windows::Forms::DateTimePicker());
			this->label_Start = (gcnew System::Windows::Forms::Label());
			this->label_End = (gcnew System::Windows::Forms::Label());
			this->label_otherOptions = (gcnew System::Windows::Forms::Label());
			this->comboBox_otherOptions = (gcnew System::Windows::Forms::ComboBox());
			this->textBox_loadedStocks = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog_stockFolder = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolTip_formEntry = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->SuspendLayout();
			// 
			// button_loadStock
			// 
			this->button_loadStock->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_loadStock->Location = System::Drawing::Point(16, 17);
			this->button_loadStock->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button_loadStock->Name = L"button_loadStock";
			this->button_loadStock->Size = System::Drawing::Size(88, 55);
			this->button_loadStock->TabIndex = 0;
			this->button_loadStock->Text = L"Load Stock";
			this->button_loadStock->UseVisualStyleBackColor = true;
			this->button_loadStock->Click += gcnew System::EventHandler(this, &Form_Entry::button_loadStock_Click);
			// 
			// button_showOutlook
			// 
			this->button_showOutlook->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_showOutlook->Location = System::Drawing::Point(334, 16);
			this->button_showOutlook->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button_showOutlook->Name = L"button_showOutlook";
			this->button_showOutlook->Size = System::Drawing::Size(88, 57);
			this->button_showOutlook->TabIndex = 1;
			this->button_showOutlook->Text = L"Show Outlook";
			this->button_showOutlook->UseVisualStyleBackColor = true;
			this->button_showOutlook->Click += gcnew System::EventHandler(this, &Form_Entry::button_showOutlook_Click);
			// 
			// dateTimePicker_Start
			// 
			this->dateTimePicker_Start->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker_Start->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker_Start->Location = System::Drawing::Point(209, 17);
			this->dateTimePicker_Start->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->dateTimePicker_Start->Name = L"dateTimePicker_Start";
			this->dateTimePicker_Start->Size = System::Drawing::Size(112, 27);
			this->dateTimePicker_Start->TabIndex = 3;
			// 
			// dateTimePicker_End
			// 
			this->dateTimePicker_End->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker_End->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker_End->Location = System::Drawing::Point(209, 48);
			this->dateTimePicker_End->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->dateTimePicker_End->Name = L"dateTimePicker_End";
			this->dateTimePicker_End->Size = System::Drawing::Size(112, 27);
			this->dateTimePicker_End->TabIndex = 4;
			// 
			// label_Start
			// 
			this->label_Start->AutoSize = true;
			this->label_Start->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_Start->Location = System::Drawing::Point(109, 23);
			this->label_Start->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_Start->Name = L"label_Start";
			this->label_Start->Size = System::Drawing::Size(96, 21);
			this->label_Start->TabIndex = 5;
			this->label_Start->Text = L"Start Date:";
			// 
			// label_End
			// 
			this->label_End->AutoSize = true;
			this->label_End->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_End->Location = System::Drawing::Point(114, 54);
			this->label_End->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_End->Name = L"label_End";
			this->label_End->Size = System::Drawing::Size(88, 21);
			this->label_End->TabIndex = 6;
			this->label_End->Text = L"End Date:";
			// 
			// label_otherOptions
			// 
			this->label_otherOptions->AutoSize = true;
			this->label_otherOptions->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_otherOptions->Location = System::Drawing::Point(154, 82);
			this->label_otherOptions->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_otherOptions->Name = L"label_otherOptions";
			this->label_otherOptions->Size = System::Drawing::Size(48, 17);
			this->label_otherOptions->TabIndex = 7;
			this->label_otherOptions->Text = L"Other:";
			// 
			// comboBox_otherOptions
			// 
			this->comboBox_otherOptions->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox_otherOptions->FormattingEnabled = true;
			this->comboBox_otherOptions->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"None", L"Past Week", L"Past Month",
					L"Past Three Months", L"Year to Date", L"Past Year", L"Past Five Years", L"All"
			});
			this->comboBox_otherOptions->Location = System::Drawing::Point(209, 78);
			this->comboBox_otherOptions->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBox_otherOptions->Name = L"comboBox_otherOptions";
			this->comboBox_otherOptions->Size = System::Drawing::Size(112, 25);
			this->comboBox_otherOptions->TabIndex = 8;
			this->comboBox_otherOptions->Text = L"None";
			// 
			// textBox_loadedStocks
			// 
			this->textBox_loadedStocks->Location = System::Drawing::Point(16, 77);
			this->textBox_loadedStocks->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox_loadedStocks->Multiline = true;
			this->textBox_loadedStocks->Name = L"textBox_loadedStocks";
			this->textBox_loadedStocks->ReadOnly = true;
			this->textBox_loadedStocks->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_loadedStocks->Size = System::Drawing::Size(89, 25);
			this->textBox_loadedStocks->TabIndex = 9;
			// 
			// openFileDialog_stockFolder
			// 
			this->openFileDialog_stockFolder->FileName = L"none";
			// 
			// Form_Entry
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(443, 137);
			this->Controls->Add(this->textBox_loadedStocks);
			this->Controls->Add(this->comboBox_otherOptions);
			this->Controls->Add(this->label_otherOptions);
			this->Controls->Add(this->label_End);
			this->Controls->Add(this->label_Start);
			this->Controls->Add(this->dateTimePicker_End);
			this->Controls->Add(this->dateTimePicker_Start);
			this->Controls->Add(this->button_showOutlook);
			this->Controls->Add(this->button_loadStock);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Form_Entry";
			this->Text = L"Form_Entry";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/// <summary>
		/// Uses the opneFileDialog object to grab user selected files 
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		/// <returns></returns>
	private: System::Void button_loadStock_Click(System::Object^ sender, System::EventArgs^ e) {
		//expects stock folder to be right outside the project solution
		String^ targetFolder = "Stock Data";
		String^ currentDirectory = System::IO::Directory::GetCurrentDirectory();
		String^ parentDirectory = System::IO::Directory::GetParent(currentDirectory)->FullName;
		String^ parent2Directory = System::IO::Directory::GetParent(parentDirectory)->FullName;
		String^ filePath = System::IO::Path::Combine(parent2Directory, targetFolder);

		openFileDialog_stockFolder->InitialDirectory = filePath;
		openFileDialog_stockFolder->Multiselect = true;
		List<System::String^>^ selectedFileNames = gcnew List<System::String^>;

		//either get one stock or multiple
		if (openFileDialog_stockFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			array<System::String^>^ fileNames = openFileDialog_stockFolder->FileNames;
			for each (System::String ^ fileName in fileNames) {
				selectedFileNames->Add(System::IO::Path::GetFileName(fileName));
			}

			//convert the list of file names to a single string for display
			System::String^ displayText = String::Join(", ", selectedFileNames);
			textBox_loadedStocks->Text = displayText;
		}
	}
		   /// <summary>
		   /// Calculates the range of dates the user has selected
		   /// </summary>
		   /// <param name="startDate"></param>
		   /// <param name="endDate"></param>
	public: void determineDateRange(DateTime% startDate, DateTime% endDate)
	{
		startDate = DateTime(1753, 1, 1);
		endDate = DateTime::Today;

		if (comboBox_otherOptions->SelectedIndex == 0)
		{
			//use the selected start and end dates
			startDate = dateTimePicker_Start->Value;
			endDate = dateTimePicker_End->Value;
		}
		else if (comboBox_otherOptions->SelectedIndex == 1)
		{
			//show data for the last week
			startDate = DateTime::Now.AddDays(-7);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else if (comboBox_otherOptions->SelectedIndex == 2)
		{
			//last month
			startDate = DateTime::Now.AddMonths(-1);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else if (comboBox_otherOptions->SelectedIndex == 3)
		{
			//last three months
			startDate = DateTime::Now.AddMonths(-3);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else if (comboBox_otherOptions->SelectedIndex == 4)
		{
			//get the date for the entire current year
			startDate = DateTime(endDate.Year, 1, 1);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else if (comboBox_otherOptions->SelectedIndex == 5)
		{
			//show data from today to last year
			startDate = DateTime::Now.AddYears(-1);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else if (comboBox_otherOptions->SelectedIndex == 6)
		{
			//show data from today to five years ago
			startDate = DateTime::Now.AddYears(-5);
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;
		}
		else
		{
			//should never get here, so nothing happens if it does
		}
	}


	private: System::Void button_showOutlook_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ targetFolder = "Stock Data";
		String^ currentDirectory = System::IO::Directory::GetCurrentDirectory();
		String^ parentDirectory = System::IO::Directory::GetParent(currentDirectory)->FullName;
		String^ parent2Directory = System::IO::Directory::GetParent(parentDirectory)->FullName;
		String^ filePath = System::IO::Path::Combine(parent2Directory, targetFolder);
		String^ tickerName;

		array<String^>^ fileNamesArray = openFileDialog_stockFolder->FileNames;
		List<String^>^ filesToCheck = gcnew System::Collections::Generic::List<String^>(fileNamesArray);
		if (filesToCheck->Contains("none")) {
			MessageBox::Show("Please select a stock.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		DateTime startDate, endDate;
		determineDateRange(startDate, endDate);

		List<Form_CandlestickChart^>^ candlestickCharts = gcnew List<Form_CandlestickChart^>(16);
		int fileCount = filesToCheck->Capacity;
		List<List<smartCandlestick^>^>^ LoLoScs = gcnew List<List<smartCandlestick^>^>(fileCount);

		for each (String ^ stock in filesToCheck)
		{
			String^ tempPath = Path::GetFullPath(stock);

			if (File::Exists(tempPath))
			{
				try
				{
					tickerName = System::IO::Path::GetFileName(stock);
					tickerName = System::IO::Path::GetFileNameWithoutExtension(tickerName);
					String^ path = tempPath->ToString();
					List<smartCandlestick^>^ smartCandlestickData = gcnew List<smartCandlestick^>(1024);
					readCSV(tempPath, smartCandlestickData);

					if (smartCandlestickData->Count <= 0)
					{
						// If returned list is empty, throw error.
						// Happens when the CSV file is either empty or does not have data for the given date range
						MessageBox::Show("Error reading stock data for " + System::IO::Path::GetFileName(stock) + ". No data found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
					else if (smartCandlestickData[0]->date < startDate)
					{
						MessageBox::Show("Error reading stock data for " + System::IO::Path::GetFileName(stock) + ". Start date provided is outside stock date range. Choose an earlier start date.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
					else
					{
						LoLoScs->Add(smartCandlestickData);
						candlestickCharts->Add(gcnew Form_CandlestickChart(smartCandlestickData, tickerName, startDate, endDate));
					}
				}
				catch (Exception^ ex)
				{
					MessageBox::Show("Error reading stock data: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

				}
			}
			else
			{
				MessageBox::Show("File " + stock + " not found");
			}
		}

		for each (Form_CandlestickChart ^ form in candlestickCharts)
		{
			form->Show();
		}
	}
	/// <summary>
	/// Takes in a file path to a stock data csv file, splits its contents into lines, then passes each line to a candlestick constructor
	/// to create new candlesticks
	/// Also takes in a reference to a list of smartCandlesticks to be populated
	/// </summary>
	/// <param name="filePath the path to the stock data CSV file"></param>
	/// <param name="smartCandlesticks a list of smartCandlesticks"></param>
	public: void readCSV(String^ filePath, List<smartCandlestick^>^% smartCandlesticks) {
		//read the contents of the file
		String^ fileContents = File::ReadAllText(filePath);
		//define the header so it can be ignored when processing an entire file
		String^ header = R"("Ticker","Period","Date","Open","High","Low","Close","Volume")";
		//split the file contents into lines
		array<String^>^ lines = File::ReadAllLines(filePath);
		//for each line, create a smartCandlestick 
		for each (String ^ line in lines){
			if (String::Compare(line, header) == 0) { continue; }
			smartCandlestick^ tempCandle = gcnew smartCandlestick(line);
			if(tempCandle != nullptr) { smartCandlesticks->Add(tempCandle); }	
		}
	}
	
};
}
