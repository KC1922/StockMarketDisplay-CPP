#pragma once
#include "aCandleStick.h"
using namespace System;
using namespace System::Collections::Generic;

namespace StockProjectCPP {

    public ref class patternRecognizer abstract
    {
    public:
        int patternSize;
        String^ patternName;
        Color patternColor;
        // Constructor
        patternRecognizer(int size, String^ name, Color color)
        {
            this->patternSize = size;
            this->patternName = name;
            this->patternColor = color;
        }

        /// <summary>
        /// Method to find indices where the candlestick pattern is found
        /// </summary>
        /// <param name="listSmartcs"></param>
        /// <returns></returns>
        List<int>^ recognizePatterns(List<smartCandlestick^>^ listSmartcs)
        {
            int listSize = listSmartcs->Count;
            List<int>^ foundIndices = gcnew List<int>();
            for (int index = 0; index <= listSize - patternSize; ++index)
            {
                //create a sublist of candlesticks based on the pattern size
                List<smartCandlestick^>^ subList = listSmartcs->GetRange(index, patternSize);
                if (recognizePattern(subList))
                {
                    foundIndices->Add(index);
                }
            }
            return foundIndices;
        }

        /// <summary>
        /// abstract method to be implemented by derived classes for pattern recognition logic
        /// </summary>
        /// <param name="cs"></param>
        /// <returns></returns>
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) = 0;
    };

    public ref class BullishRecognizer : public patternRecognizer
    {
    public:
        BullishRecognizer() : patternRecognizer(1, "Bullish", Color::SpringGreen){}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override { return cs[0]->isBullish(); }
    };
    public ref class BearishRecognizer : public patternRecognizer
    {
    public:
        BearishRecognizer() : patternRecognizer(1, "Bearish", Color::DarkRed) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isBearish();}
    };

    public ref class NeutralRecognizer : public patternRecognizer
    {
    public:
        NeutralRecognizer() : patternRecognizer(1, "Neutral", Color::DarkSlateGray) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isNeutral(); }
    };

    public ref class MarubozuRecognizer : public patternRecognizer
    {
    public:
        MarubozuRecognizer() : patternRecognizer(1, "Marubozu", Color::MediumPurple) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isMarubozu(); }
    };

    public ref class DojiRecognizer : public patternRecognizer
    {
    public:
        DojiRecognizer() : patternRecognizer(1, "Doji", Color::RoyalBlue) {}

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override { return cs[0]->isDoji();}
    };

    public ref class LongLeggedDojiRecognizer : public patternRecognizer
    {
    public:
        LongLeggedDojiRecognizer() : patternRecognizer(1, "Long-Legged Doji", Color::ForestGreen) {}

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isLongLeggedDoji();}
    };

    public ref class DragonflyDojiRecognizer : public patternRecognizer
    {
    public:
        DragonflyDojiRecognizer() : patternRecognizer(1, "Dragonfly Doji", Color::LimeGreen) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isDragonflyDoji(); }
    };

    public ref class GravestoneDojiRecognizer : public patternRecognizer
    {
    public:
        GravestoneDojiRecognizer() : patternRecognizer(1, "Gravestone Doji", Color::IndianRed) {}

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isGravestoneDoji();}
    };

    public ref class FourPriceDojiRecognizer : public patternRecognizer
    {
    public:
        FourPriceDojiRecognizer() : patternRecognizer(1, "Four-Price Doji", Color::Gold) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override { return cs[0]->isFourPriceDoji(); }
    };

    public ref class HammerRecognizer : public patternRecognizer
    {
    public:
        HammerRecognizer() : patternRecognizer(1, "Hammer", Color::Orange) {}
 
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override { return cs[0]->isHammer();}
    };

    public ref class InvertedHammerRecognizer : public patternRecognizer
    {
    public:
        InvertedHammerRecognizer() : patternRecognizer(1, "Inverted Hammer", Color::Blue) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isInvertedHammer();}
    };

    public ref class MorningStarRecognizer : public patternRecognizer
    {
    public:
        MorningStarRecognizer() : patternRecognizer(3, "Morning Star", Color::Green) {}

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            
            return cs[0]->isBearish() && (cs[1]->isDoji() || cs[1]->isNeutral()) && cs[2]->isBullish();
        }
    };

    public ref class EveningStarRecognizer : public patternRecognizer
    {
    public:
        EveningStarRecognizer() : patternRecognizer(3, "Evening Star", Color::Red) {}

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->isBullish() && (cs[1]->isDoji() || cs[1]->isNeutral()) && cs[2]->isBearish();}
    };

    public ref class EngulfingRecognizer : public patternRecognizer
    {
    public:
        EngulfingRecognizer() : patternRecognizer(2, "Engulfing", Color::LightGoldenrodYellow) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->high < Math::Max(cs[1]->open, cs[1]->close) && cs[0]->low > Math::Min(cs[1]->open, cs[1]->close);}
    };

    public ref class BullishEngulfingRecognizer : public patternRecognizer
    {
    public:
        BullishEngulfingRecognizer() : patternRecognizer(2, "Bullish Engulfing", Color::LightGreen) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->high < cs[1]->topPrice && cs[0]->isBearish() && cs[0]->low > cs[1]->bottomPrice && cs[1]->isBullish(); }
    };

    public ref class BearishEngulfingRecognizer : public patternRecognizer
    {
    public:
        BearishEngulfingRecognizer() : patternRecognizer(2, "Bearish Engulfing", Color::OrangeRed) {}
        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override {return cs[0]->high < cs[1]->topPrice && cs[0]->isBullish() && cs[0]->low > cs[1]->bottomPrice && cs[1]->isBearish(); }
    };

    public ref class HarmaniRecognizer : public patternRecognizer
    {
    public:
        HarmaniRecognizer() : patternRecognizer(2, "Harmani", Color::LightYellow) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ rcs = cs[1];
            return (lcs->high > rcs->topPrice && lcs->low < rcs->bottomPrice);
        }
    };

    public ref class BullishHarmaniRecognizer : public patternRecognizer
    {
    public:
        BullishHarmaniRecognizer() : patternRecognizer(2, "Bullish Harmani", Color::SpringGreen) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ rcs = cs[1];
            return (lcs->high > rcs->topPrice && lcs->isBearish() && lcs->low < rcs->bottomPrice && rcs->isBullish());
        }
    };

    public ref class BearishHarmaniRecognizer : public patternRecognizer
    {
    public:
        BearishHarmaniRecognizer() : patternRecognizer(2, "Bearish Harmani", Color::PaleVioletRed) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ rcs = cs[1];
            return (lcs->high > rcs->topPrice && lcs->isBullish() && lcs->low < rcs->bottomPrice && rcs->isBearish());
        }
    };

    public ref class PeakRecognizer : public patternRecognizer
    {
    public:
        PeakRecognizer() : patternRecognizer(3, "Peak", Color::LightGreen) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ mcs = cs[1];
            smartCandlestick^ rcs = cs[2];
            return (lcs->high < mcs->high && rcs->high < mcs->high);
        }
    };

    public ref class ValleyRecognizer : public patternRecognizer
    {
    public:
        ValleyRecognizer() : patternRecognizer(3, "Valley", Color::DarkRed) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ mcs = cs[1];
            smartCandlestick^ rcs = cs[2];
            return (lcs->low > mcs->low && rcs->low > mcs->low);
        }
    };

    public ref class ThreeSolidersRecognizer : public patternRecognizer
    {
    public:
        ThreeSolidersRecognizer() : patternRecognizer(3, "Three Wise Soldiers", Color::LightGreen) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ mcs = cs[1];
            smartCandlestick^ rcs = cs[2];
            return (lcs->isBullish() && mcs->isBullish() && mcs->close > lcs->close && rcs->isBullish() && rcs->close > mcs->close);
        }
    };

    public ref class ThreeCrowsRecognizer : public patternRecognizer
    {
    public:
        ThreeCrowsRecognizer() : patternRecognizer(3, "Three Black Crows", Color::DarkRed) { }

        virtual bool recognizePattern(List<smartCandlestick^>^ cs) override
        {
            smartCandlestick^ lcs = cs[0];
            smartCandlestick^ mcs = cs[1];
            smartCandlestick^ rcs = cs[2];
            return (lcs->isBearish() && mcs->isBearish() && mcs->close < lcs->close && rcs->isBearish() && rcs->close < mcs->close);
        }
    };


    public ref class createListOfRecognizers {
    public:
        /// <summary>
        /// Creates an array of all recognizers in PatternRecognizer.h
        /// </summary>
        /// <returns></returns>
        static array<patternRecognizer^>^ CreateRecognizers() {
            array<patternRecognizer^>^ recognizers = gcnew array<patternRecognizer^> {
                //create instance of each recognizer
                gcnew BullishRecognizer(),
                gcnew BearishRecognizer(),
                gcnew NeutralRecognizer(),
                gcnew MarubozuRecognizer(),
                gcnew DojiRecognizer(),
                gcnew LongLeggedDojiRecognizer(),
                gcnew DragonflyDojiRecognizer(),
                gcnew GravestoneDojiRecognizer(),
                gcnew FourPriceDojiRecognizer(),
                gcnew HammerRecognizer(),
                gcnew InvertedHammerRecognizer(),
                gcnew MorningStarRecognizer(),
                gcnew EveningStarRecognizer(),
                gcnew EngulfingRecognizer(),
                gcnew BullishEngulfingRecognizer(),
                gcnew BearishEngulfingRecognizer(),
                gcnew HarmaniRecognizer(),
                gcnew BullishHarmaniRecognizer(),
                gcnew BearishHarmaniRecognizer(),
                gcnew PeakRecognizer(),
                gcnew ValleyRecognizer(),
                gcnew ThreeSolidersRecognizer(),
                gcnew ThreeCrowsRecognizer()
            };

            return recognizers;
        }
    };
}

