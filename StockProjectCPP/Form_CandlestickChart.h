#pragma once
#include <set>
#include <math.h>
#include "aCandleStick.h"
#include "PatternRecognizer.h"

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
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Form displays stock data on a chart, and gives options to change date range.
	/// </summary>
	public ref class Form_CandlestickChart : public System::Windows::Forms::Form
	{
	private:
		List<smartCandlestick^>^ originalCandlesticks;
		List<smartCandlestick^>^ filteredSticks;
	private: System::Windows::Forms::ComboBox^ comboBox_patternSelect;
	private: System::Windows::Forms::Button^ button_clear;
	private: array<patternRecognizer^>^ allRecognizers = createListOfRecognizers::CreateRecognizers();
	public:
		Form_CandlestickChart(List<smartCandlestick^>^ candlestickData, String^ tickerName, DateTime startDate, DateTime endDate)
		{
			InitializeComponent();
			this->Text = tickerName + " Candlestick Chart";
			this->originalCandlesticks = gcnew List<smartCandlestick^>(1028);
			this->filteredSticks = gcnew List<smartCandlestick^>(1028);
			originalCandlesticks->AddRange(candlestickData);
			originalCandlesticks->Reverse();
			dateTimePicker_Start->Value = startDate;
			dateTimePicker_End->Value = endDate;

			for each (auto r in allRecognizers) { comboBox_patternSelect->Items->Add(r->patternName); }

			updateChartDisplay();
		}
		void updateChartDisplay() {
			//empty filteredSticks
			filteredSticks->Clear();

			DateTime start = dateTimePicker_Start->Value;
			DateTime end = dateTimePicker_End->Value;

			//populate filtered sticks based on date range provided
			for each (smartCandlestick^ candle in originalCandlesticks)
			{
				if (candle->date >= start && candle->date <= end)
				{
					filteredSticks->Add(candle);
				}
				if (candle->date > end) { break; }
			}

			if (!(filteredSticks->Count <= 0)) {
				//databind filtersticks
				chart_candlesticks->DataSource = filteredSticks;
				chart_candlesticks->DataBind();
				ChartArea^ area = chart_candlesticks->ChartAreas["ChartArea_holc"];
				//manually enabled zooming insce it wasn't working with the designer
				area->AxisX->ScrollBar->Enabled = true;
				area->AxisX->ScaleView->Zoomable = true;
				area->CursorX->IsUserSelectionEnabled = true;
				area->AxisX->ScrollBar->Enabled = true;
				area->AxisX->ScaleView->Zoomable = true;
				area->CursorX->IsUserSelectionEnabled = true;

				//formatt the x axis of the candlesticks labels to be in 0.00 format
				area->AxisY->LabelStyle->Format = "{0:0.00}";

				//create the upper and lower bounds
				double minValue = getMinLow(filteredSticks);
				double maxValue = getMaxHigh(filteredSticks);
				//set the percentage from the high and low displayed, in this case 5%
				double percentage = 0.05;
				double adjustmentMin = minValue * percentage;
				double adjustmentMax = maxValue * percentage;
				//mind the range
				double adjustedMinValue = minValue - adjustmentMin;
				double adjustedMaxValue = maxValue + adjustmentMax;

				//set the new limits
				area->AxisY->Minimum = adjustedMinValue;
				area->AxisY->Maximum = adjustedMaxValue;


				//change the color of the candlesticks depending on if price goes up or down
				chart_candlesticks->Series[L"Series_holc"]->CustomProperties = L"PriceUpColor=Green,PriceDownColor=Red";
				//Similar code from my C# project for coloring the volume sticks to be green/red depending on if the volume went up or down
				chart_candlesticks->Series["Series_volume"]->Points[0]->Color = Color::Green;
				for (int i = 1; i < chart_candlesticks->Series["Series_volume"]->Points->Count; i++)
				{
					//compare current volume to previous volume
					if (chart_candlesticks->Series["Series_volume"]->Points[i]->YValues[0] > chart_candlesticks->Series["Series_volume"]->Points[i - 1]->YValues[0])
					{
						//color green if volume went up
						chart_candlesticks->Series["Series_volume"]->Points[i]->Color = Color::Green;
					}
					else
					{
						//red if it went down
						chart_candlesticks->Series["Series_volume"]->Points[i]->Color = Color::Red;
					}
				}
				chart_candlesticks->Refresh();

			}
			else {
				MessageBox::Show("Error filtering stock data to chart view. Data either does not exist for the given interval or the date range is invalid/has no data.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				chart_candlesticks->DataSource = nullptr;
				chart_candlesticks->Refresh();
			}

		}
		/// <summary>
		/// Takes in a list of candlesticks and returns the lowest value found in the data.
		/// </summary>
		/// <param name="candlestickData"></param>
		/// <returns></returns>
		double getMinLow(List<smartCandlestick^>^ candlestickData) {
			double minLow = double::MaxValue;

			for each (smartCandlestick ^ candle in candlestickData) {
				if (candle->low < minLow) {
					minLow = candle->low;
				}
			}

			return minLow;
		}
		/// <summary>
		/// Takes in a list of candlesticks and returns the highest value found in the data.
		/// </summary>
		/// <param name="candlestickData"></param>
		/// <returns></returns>
		double getMaxHigh(List<smartCandlestick^>^ candlestickData) {
			double maxHigh = double::MinValue;

			for each (smartCandlestick ^ candle in candlestickData) {
				if (candle->high > maxHigh) {
					maxHigh = candle->high;
				}
			}

			return maxHigh;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_CandlestickChart()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_candlesticks;
	protected:

	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_Start;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_End;
	private: System::Windows::Forms::Button^ button_Update;



	private: System::Windows::Forms::Label^ label_To;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart_candlesticks = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->dateTimePicker_Start = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_End = (gcnew System::Windows::Forms::DateTimePicker());
			this->button_Update = (gcnew System::Windows::Forms::Button());
			this->label_To = (gcnew System::Windows::Forms::Label());
			this->comboBox_patternSelect = (gcnew System::Windows::Forms::ComboBox());
			this->button_clear = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->BeginInit();
			this->SuspendLayout();
			// 
			// chart_candlesticks
			// 
			this->chart_candlesticks->BackColor = System::Drawing::Color::CadetBlue;
			chartArea1->BackColor = System::Drawing::Color::Gainsboro;
			chartArea1->Name = L"ChartArea_holc";
			chartArea2->BackColor = System::Drawing::Color::Gainsboro;
			chartArea2->Name = L"ChartArea_volume";
			this->chart_candlesticks->ChartAreas->Add(chartArea1);
			this->chart_candlesticks->ChartAreas->Add(chartArea2);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->chart_candlesticks->Legends->Add(legend1);
			this->chart_candlesticks->Location = System::Drawing::Point(9, 10);
			this->chart_candlesticks->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->chart_candlesticks->Name = L"chart_candlesticks";
			this->chart_candlesticks->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Grayscale;
			series1->ChartArea = L"ChartArea_holc";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->IsVisibleInLegend = false;
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->Name = L"Series_holc";
			series1->ToolTip = L"Date: #VALX\\nopen: #VALY3\\nhigh: #VALY1\\nlow: #VALY2\\nclose: #VALY4";
			series1->XValueMember = L"date";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series1->YValueMembers = L"high, low, open, close";
			series1->YValuesPerPoint = 4;
			series2->ChartArea = L"ChartArea_volume";
			series2->IsXValueIndexed = true;
			series2->Legend = L"Legend1";
			series2->Name = L"Series_volume";
			series2->ToolTip = L"Date: #VALX\\nVolume: #VALY";
			series2->XValueMember = L"date";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series2->YValueMembers = L"volume";
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Int64;
			this->chart_candlesticks->Series->Add(series1);
			this->chart_candlesticks->Series->Add(series2);
			this->chart_candlesticks->Size = System::Drawing::Size(694, 373);
			this->chart_candlesticks->TabIndex = 0;
			this->chart_candlesticks->Text = L"chart1";
			// 
			// dateTimePicker_Start
			// 
			this->dateTimePicker_Start->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker_Start->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker_Start->Location = System::Drawing::Point(9, 405);
			this->dateTimePicker_Start->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->dateTimePicker_Start->Name = L"dateTimePicker_Start";
			this->dateTimePicker_Start->Size = System::Drawing::Size(107, 24);
			this->dateTimePicker_Start->TabIndex = 1;
			// 
			// dateTimePicker_End
			// 
			this->dateTimePicker_End->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker_End->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker_End->Location = System::Drawing::Point(146, 405);
			this->dateTimePicker_End->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->dateTimePicker_End->Name = L"dateTimePicker_End";
			this->dateTimePicker_End->Size = System::Drawing::Size(107, 24);
			this->dateTimePicker_End->TabIndex = 2;
			// 
			// button_Update
			// 
			this->button_Update->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Update->Location = System::Drawing::Point(256, 405);
			this->button_Update->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button_Update->Name = L"button_Update";
			this->button_Update->Size = System::Drawing::Size(82, 24);
			this->button_Update->TabIndex = 3;
			this->button_Update->Text = L"Update";
			this->button_Update->UseVisualStyleBackColor = true;
			this->button_Update->Click += gcnew System::EventHandler(this, &Form_CandlestickChart::button_Update_Click);
			// 
			// label_To
			// 
			this->label_To->AutoSize = true;
			this->label_To->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_To->Location = System::Drawing::Point(119, 408);
			this->label_To->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_To->Name = L"label_To";
			this->label_To->Size = System::Drawing::Size(23, 19);
			this->label_To->TabIndex = 4;
			this->label_To->Text = L"To";
			this->label_To->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// comboBox_patternSelect
			// 
			this->comboBox_patternSelect->Font = (gcnew System::Drawing::Font(L"Century Gothic", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox_patternSelect->FormattingEnabled = true;
			this->comboBox_patternSelect->Location = System::Drawing::Point(392, 407);
			this->comboBox_patternSelect->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBox_patternSelect->Name = L"comboBox_patternSelect";
			this->comboBox_patternSelect->Size = System::Drawing::Size(107, 23);
			this->comboBox_patternSelect->TabIndex = 5;
			this->comboBox_patternSelect->Text = L"None";
			this->comboBox_patternSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_CandlestickChart::comboBox_patternSelect_SelectedIndexChanged);
			// 
			// button_clear
			// 
			this->button_clear->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_clear->Location = System::Drawing::Point(502, 405);
			this->button_clear->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(82, 24);
			this->button_clear->TabIndex = 6;
			this->button_clear->Text = L"Clear";
			this->button_clear->UseVisualStyleBackColor = true;
			this->button_clear->Click += gcnew System::EventHandler(this, &Form_CandlestickChart::button_clear_Click);
			// 
			// Form_CandlestickChart
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(722, 440);
			this->Controls->Add(this->button_clear);
			this->Controls->Add(this->comboBox_patternSelect);
			this->Controls->Add(this->label_To);
			this->Controls->Add(this->button_Update);
			this->Controls->Add(this->dateTimePicker_End);
			this->Controls->Add(this->dateTimePicker_Start);
			this->Controls->Add(this->chart_candlesticks);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Form_CandlestickChart";
			this->Text = L"Form_CandlestickChart";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_Update_Click(System::Object^ sender, System::EventArgs^ e) {
		updateChartDisplay();
	}
	private: System::Void button_clear_Click(System::Object^ sender, System::EventArgs^ e) {
		chart_candlesticks->Annotations->Clear();
	}
private: System::Void comboBox_patternSelect_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	int selectedIndex = comboBox_patternSelect->SelectedIndex;
	int count = filteredSticks->Count;
	int index = 0;
	List<int>^ indices = gcnew List<int>(128);
	
	//get recognizer information and found indices
	patternRecognizer^ pattern = allRecognizers[selectedIndex];
	Color patternColor = pattern->patternColor;
	String^ patternName = pattern->patternName;
	indices = pattern->recognizePatterns(filteredSticks);

	//check if any indices were found, then set lastIndex to the end of the list
	int lastIndex = 0;
	if (indices->Count > 0) { lastIndex = indices[indices->Count - 1]; }

	//loop through current chart candlesticks and add an annotation for each of the matching indices
	for each (DataPoint ^ candle in chart_candlesticks->Series[0]->Points) {
		//if the indecies list is empty, break from the loop as there are no annotations to add 
		if (lastIndex == 0) { break; }
		if (indices->Contains(index)) {
			double high = candle->YValues[0];
			double low = candle->YValues[1];
			RectangleAnnotation^ annotation = createAnnotation(patternColor, high, low, candle, count, patternName);
			chart_candlesticks->Annotations->Add(annotation);
		}
		//if we've passed the last index where the pattern was found, break from the loop to save time
		if (index > lastIndex) { break; }
		index++;
	}

	chart_candlesticks->Invalidate();
	
}
private:
	RectangleAnnotation^ createAnnotation(Color lineColor, double high, double low, DataPoint^ anchorDataPoint, int count, String^ patternName) {
		int numberOfCandlesticks = count;
		double highPosition = chart_candlesticks->ChartAreas[0]->AxisY->ValueToPixelPosition(high);
		double lowPosition = chart_candlesticks->ChartAreas[0]->AxisY->ValueToPixelPosition(low);
		double height = (Math::Max(highPosition, lowPosition) - Math::Min(highPosition, lowPosition)) / 5;
		double width = 60.0 / numberOfCandlesticks;
		if (width < 1.0) width = 1.0;

		RectangleAnnotation^ annotation = gcnew RectangleAnnotation();
		annotation->Visible = true;
		annotation->BackColor = Color::Transparent;
		annotation->LineColor = lineColor;
		annotation->LineWidth = 2;
		annotation->Height = height;
		annotation->Width = width;
		annotation->AxisX = chart_candlesticks->ChartAreas["ChartArea_holc"]->AxisX;
		annotation->AxisY = chart_candlesticks->ChartAreas["ChartArea_holc"]->AxisY;
		annotation->AnchorDataPoint = anchorDataPoint;
		annotation->Y = high;
		annotation->AnchorAlignment = ContentAlignment::BottomCenter;
		annotation->ClipToChartArea = "ChartArea_holc";
		annotation->ToolTip = patternName;

		return annotation;
	}
};
}