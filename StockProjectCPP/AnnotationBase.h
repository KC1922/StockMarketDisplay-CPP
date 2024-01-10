#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;
using namespace System::Collections::Generic;

namespace StockProjectCPP {

    public ref class annotationBase abstract {
    protected:
        Chart^ chart;
        int countCandlesticks;
        double MinWidth = 1.0;

    public:
        annotationBase(Chart^ chart, int countCandlesticks) {
            if (chart == nullptr) throw gcnew ArgumentNullException("chart");
            this->chart = chart;
            this->countCandlesticks = countCandlesticks;
        }

        //abstract method to get the color of the line
        virtual Color GetLineColor();

        //abstract method to get the indices where annotations should be placed
        virtual List<int>^ GetAnnotationIndices();

        //method to create an annotation
    protected: RectangleAnnotation^ CreateAnnotation(Color lineColor, double high, double low, DataPoint^ anchorDataPoint) {
            int numberOfCandlesticks = countCandlesticks;
            double highPosition = chart->ChartAreas[0]->AxisY->ValueToPixelPosition(high);
            double lowPosition = chart->ChartAreas[0]->AxisY->ValueToPixelPosition(low);
            double height = (Math::Max(highPosition, lowPosition) - Math::Min(highPosition, lowPosition)) / 5;
            double width = 60.0 / numberOfCandlesticks;
            if (width < MinWidth) width = MinWidth;

            RectangleAnnotation^ annotation = gcnew RectangleAnnotation();
            annotation->Visible = true;
            annotation->BackColor = Color::Transparent;
            annotation->LineColor = lineColor;
            annotation->LineWidth = 2;
            annotation->Height = height;
            annotation->Width = width;
            annotation->AxisX = chart->ChartAreas["ChartArea_candlesticks"]->AxisX;
            annotation->AxisY = chart->ChartAreas["ChartArea_candlesticks"]->AxisY;
            annotation->AnchorDataPoint = anchorDataPoint;
            annotation->Y = high;
            annotation->AnchorAlignment = ContentAlignment::BottomCenter;
            annotation->ClipToChartArea = "ChartArea_candlesticks";

            return annotation;
        }

    public: void AddAnnotations() {
            List<int>^ indices = GetAnnotationIndices();
            for each (int index in indices) {
                DataPoint^ dataPoint = chart->Series[0]->Points[index];
                RectangleAnnotation^ annotation = CreateAnnotation(GetLineColor(), dataPoint->YValues[0], dataPoint->YValues[1], dataPoint);
                chart->Annotations->Add(annotation);
            }
        }
    };
    public ref class BullishAnnotation : annotationBase {
    private:
        List<int>^ patternIndex;

    public:
        BullishAnnotation() : annotationBase(nullptr, 0){}

        BullishAnnotation(Chart^ chart, int count, List<int>^ indices)
            : annotationBase(chart, count) {
            patternIndex = indices;
        }

        virtual List<int>^ GetAnnotationIndices() override {
            return patternIndex;
        }

        virtual Color GetLineColor() override {
            return Color::SpringGreen;
        }
    };
    public ref class createListOfAnnotations {
    public:
        static List<annotationBase^>^ CreateAnnotations() {
            List<annotationBase^>^ annotations = gcnew List<annotationBase^>();

            // Create an instance of each recognizer and add it to the list
            annotations->Add(gcnew BullishAnnotation());
            /*annotations->Add(gcnew BearishRecognizer());
            annotations->Add(gcnew NeutralRecognizer());
            annotations->Add(gcnew MarubozuRecognizer());
            annotations->Add(gcnew DojiRecognizer());
            annotations->Add(gcnew LongLeggedDojiRecognizer());
            annotations->Add(gcnew DragonflyDojiRecognizer());
            annotations->Add(gcnew GravestoneDojiRecognizer());
            annotations->Add(gcnew FourPriceDojiRecognizer());
            recognizers->Add(gcnew HammerRecognizer());
            recognizers->Add(gcnew InvertedHammerRecognizer());
            recognizers->Add(gcnew MorningStarRecognizer());
            recognizers->Add(gcnew EveningStarRecognizer());
            recognizers->Add(gcnew EngulfingRecognizer());
            recognizers->Add(gcnew BullishEngulfingRecognizer());
            recognizers->Add(gcnew BearishEngulfingRecognizer());*/

            return annotations;
        }
    };
}
