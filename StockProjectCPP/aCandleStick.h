#pragma once
    using namespace System;
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

    public ref class aCandlestick
    {

    public:
        property DateTime date;
        property double open;
        property double close;
        property double high;
        property double low;
        property unsigned long volume;

        /// <summary>
        /// Default candlestick constructor, sets default values of 0
        /// </summary>
        aCandlestick()
        {
            this->date = DateTime::MinValue;
            this->open = 0.0;
            this->close = 0.0;
            this->high = 0.0;
            this->low = 0.0;
            this->volume = 0;
        }

        /// <summary>
        /// Candlestick constructor that takes in values
        /// </summary>
        /// <param name="date"></param>
        /// <param name="open"></param>
        /// <param name="high"></param>
        /// <param name="low"></param>
        /// <param name="close"></param>
        /// <param name="volume"></param>
        aCandlestick(DateTime d, double o, double h, double l, double c, unsigned long long v)
        {
            this->date = d;
            this->open = o;
            this->close = c;
            this->high = h;
            this->low = l;
            this->volume = v;
        }

        /// <summary>
        /// Candlestick constructor that takes in a single line from a CSV file represented as a string
        /// expects pattern of "Ticker","Period","Date","Open","High","Low","Close","Volume"
        /// </summary>
        /// <param name="csv line string"></param>
        aCandlestick(String^ csv)
        {
            aCandlestick^ cs = createCandlestick(csv);
            this->date = cs->date;
            this->open = cs->open;
            this->high = cs->high;
            this->low = cs->low;
            this->close = cs->close;
            this->volume = cs->volume;
        }

        /// <summary>
        /// Candlestick constructor that takes in an existing candlestick and makes a copy
        /// </summary>
        /// <param name="cs aCandlestick"></param>
        aCandlestick(aCandlestick^ cs)
        {
            this->date = cs->date;
            this->open = cs->open;
            this->high = cs->high;
            this->low = cs->low;
            this->close = cs->close;
            this->volume = cs->volume;
        }
        /// <summary>
        /// Takes in a csv line string and returns a new candlestick object
        /// </summary>
        /// <param name="csvLine"></param>
        /// <returns></returns>
        static aCandlestick^ createCandlestick(String^ csvLine)
        {
            try
            {
                // Split the line using delimiters
                array<String^>^ delimiters = gcnew array<String^> { "\",\"", ",", "\"", " " };
                array<String^>^ fields = csvLine->Split(delimiters, StringSplitOptions::RemoveEmptyEntries);

                // Ensure the correct number of fields were found
                if (fields->Length >= 9)
                {
                    // Parse the date, which is split into three parts
                    String^ dateField = fields[3] + "/" + fields[2] + "/" + fields[4];

                    DateTime csvDate;
                    if (DateTime::TryParseExact(dateField, "d/MMM/yyyy", CultureInfo::InvariantCulture, DateTimeStyles::None, csvDate))
                    {
                        // Parse the remaining stock data into the candlestick
                        double open = Double::Parse(fields[5], CultureInfo::InvariantCulture);
                        double high = Double::Parse(fields[6], CultureInfo::InvariantCulture);
                        double low = Double::Parse(fields[7], CultureInfo::InvariantCulture);
                        double close = Double::Parse(fields[8], CultureInfo::InvariantCulture);
                        UInt64 volume = UInt64::Parse(fields[9], CultureInfo::InvariantCulture);

                        // Use the constructor with parameters to create a new instance of aCandlestick
                        aCandlestick^ candlestick = gcnew aCandlestick(csvDate, open, high, low, close, volume);

                        return candlestick;
                    }
                    else
                    {
                        Console::WriteLine("Date format is not correct");
                        return nullptr;
                    }
                }
                else
                {
                    Console::WriteLine("Incorrect number of fields in CSV line");
                    return nullptr;
                }
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("Error parsing CSV line: " + ex->Message);
                return nullptr;
            }
        }

    };
    public ref class smartCandlestick : public aCandlestick
        {
        private:
            double _range;
            double _bodySize;
            double _upperShadowSize;
            double _lowerShadowSize;
            double _topPrice;
            double _bottomPrice;
            bool _isBullish;
            bool _isBearish;
            bool _isNeutral;
            bool _isMarubozu;
            bool _isDoji;
            bool _isLongLeggedDoji;
            bool _isDragonflyDoji;
            bool _isGravestoneDoji;
            bool _isFourPriceDoji;
            bool _isHammer;
            bool _isInvertedHammer;

        public:
            property double range { double get() { return _range; } }
            property double bodySize { double get() { return _bodySize; } }
            property double upperShadowSize { double get() { return _upperShadowSize; } }
            property double lowerShadowSize { double get() { return _lowerShadowSize; } }
            property double topPrice { double get() { return _topPrice; } }
            property double bottomPrice { double get() { return _bottomPrice; } }
            bool isBullish() { return _isBullish; }
            bool isBearish() { return _isBearish; }
            bool isNeutral() { return _isNeutral; }
            bool isMarubozu() { return _isMarubozu; }
            bool isDoji() { return _isDoji; }
            bool isLongLeggedDoji() { return _isLongLeggedDoji; }
            bool isDragonflyDoji() { return _isDragonflyDoji; }
            bool isGravestoneDoji() { return _isGravestoneDoji; }
            bool isFourPriceDoji() { return _isFourPriceDoji; }
            bool isHammer() { return _isHammer; }
            bool isInvertedHammer() { return _isInvertedHammer; }

            //leeway variables for different kinds of patterns
            static double leeway = 0.05;
            static double bullishLeeway = 1.1;
            static double bearishLeeway = 1.1;
            static double dojiLeeway = 0.03;
            static double hammerLeeway = 0.15;
            static double longLegLeeway = 0.8;

            /// <summary>
            /// smartCandlestick constructor that takes in a normal candlestick and creates a smartCandlestick
            /// </summary>
            /// <param name="cs aCandlestick"></param>
            smartCandlestick(aCandlestick^ cs) : aCandlestick(cs->date, cs->open, cs->high, cs->low, cs->close, cs->volume) {
                this->calculateProperties();
                this->calculatePatterns();
            }
            /// <summary>
            /// smartCandlestick constructor that takes in a single line from a CSV file represented as a string and creates a new smartCandlestick
            /// expects pattern of "Ticker","Period","Date","Open","High","Low","Close","Volume"
            /// </summary>
            /// <param name="csv"></param>
            smartCandlestick(String^ csv) : aCandlestick(createCandlestick(csv)) {
                this->calculateProperties();
                this->calculatePatterns();
            }
            /// <summary>
            /// smartCandlestick function that calculates the different physicaly properties of the candlestick
            /// </summary>
            void calculateProperties()
            {
                _range = high - low;
                _bodySize = Math::Abs(open - close);
                _upperShadowSize = Math::Abs(high - Math::Max(open, close));
                _lowerShadowSize = Math::Abs(Math::Min(open, close) - low);
                _topPrice = Math::Max(open, close);
                _bottomPrice = Math::Min(open, close);
            }
            /// <summary>
            /// smartCandlestick function that determines what patterns the candlestick matches
            /// </summary>
            void calculatePatterns()
            {
                _isBullish = (open * bullishLeeway) < close;
                _isBearish = (close * bearishLeeway) < open;
                _isNeutral = !_isBearish && !_isBullish;
                _isMarubozu = _bodySize == _range;
                _isDoji = _bodySize / _topPrice <= dojiLeeway;
                _isLongLeggedDoji = _isDoji && low <= _bottomPrice * 0.5 && high >= _topPrice * 1.5;
                _isDragonflyDoji = _isDoji && high <= (_topPrice * 1.01) && low <= (_bottomPrice * 0.50);
                _isGravestoneDoji = _isDoji && high >= (_topPrice * 1.50) && low >= (_bottomPrice * 0.01);
                _isFourPriceDoji = high == low && high == close && high == open;
                _isHammer = _bodySize <= (_range * hammerLeeway) && !_isDoji && high <= (_topPrice * 1.02) && _upperShadowSize != 0 && low <= (_bottomPrice * 0.50);
                if (_isHammer) _isBullish = true;
                _isInvertedHammer = _bodySize >= (_range * hammerLeeway) && !_isDoji && high >= (_topPrice * 1.50) && low >= (_bottomPrice * 0.02) && _lowerShadowSize != 0;
                if (_isInvertedHammer) _isBearish = true;
            }

     };
   