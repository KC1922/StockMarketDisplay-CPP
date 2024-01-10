# Stock-Market-Project-CPP
Stock Market Analysis Application in C++ by: Kyle Cwik
---
## Project Overview
Similar project as my StockMarketDisplay project, but coded in c++ instead of c#. The c# code (which has some minor extra features) can be found here: https://github.com/KC1922/StockMarketDisplay

This stock market program is designed to provide a comprehensive and interactive platform for analyzing stock market data, tailored to user-defined parameters. At the heart of this application is the objective to demonstrate and represent object-oriented programming, user-data interaction, and technical analysis in a thorough, accessible, and informative manner. The program allows users to engage with stock market data through a series of user-driven selections, facilitating a deeper understanding of market dynamics.

## Table of Contents
- [Installation](#installation)
- [Documentation](#documentation)
- [Features](#features)

## Installation
1. **Clone repository to desired directory**
   ```bash
   git clone https://github.com/dskroskznik/Stock-Market-Chart-Program.githttps://github.com/dskroskznik/Stock-Market-Chart-Program.git](https://github.com/KC1922/StockMarketDisplay.git```
2. **Select and Open project solution folder in Visual Studio**
   ```StockProjectCS```
3. **Restore required NuGet packages necessary for project**
4. **Clean solution, Build and Run**

## Documentation
Navigate through the Microsoft .NET documentation for resources and guidance on Microsoft Visual Studio.
  - [learn.microsoft.com/dotnet](https://learn.microsoft.com/en-us/dotnet/)

## Program Features
1. **Easy to understand UI for Stock and Date Selection**
   - Uses OpenFileDialog features to allow the user to select one or more stock csv files which allows for trend comparisons.
   - Date range selection uses DateTimePickers, which gives user greater control over data displayed.
2. **CSVHelper Class Integration**
   - CSVHelper is used to improve the csv data parsing process, and creates a cleaner code structure that is easy to modify.
3. **Candlestick Chart for Displaying Data**
   - A seperate form containing a chart is created to display the stock data.
   - Hovering over each candlestick gives more details about it, and they are color coded to denote upward or downward price changes.
   - Volume is also displayed.
4. **Extra Features for Chart**
   - The date range of the data can be modified within the chart form, allowing greater control of displayed data.
   - A ComboBox allows the user to select different types of candlestick patterns (i.e. bullish, doji, hammer, e.t.c), including multi-stick patterns (i.e. valley, peak, engulfing, e.t.c).
   - A RichTextBox gives more information on what patterns are being annotated and where they are located.
5. **Modular Pattern Recognizer**
   - The structure that identifies patterns, ```patternRecognizer.cs```, uses class inheritence and polymorphism to allow the easy creation of new pattern finders.
   - ComboBox on chart form is dynamically populated with pattern names and options based on the patterns that exist in the recognizer.
