# TradingAnalysis

A C library for your trading analysis

## Features

* Moving Average

## Usage

### Compile and link library

Go to the cloned folder and compile the library:

`$ make`

This creates a static library called `TL.a`.
Include the file `TL.h` to your source code.
Link it with the static library generated before.

Enjoy all the functionalities !

### Test the library

To test the library, type:

`$ make tests`

This will compile the library and the tests and will launch it.
If everything isn't `OK`, please report any bug to `https://github.com/tjarross/OpenTradingLibrary/issues`

## What's Next ?

* Add other indicators (Exponential moving averages, MACD, Ichimoku...)
* Ability to get charts from exchanges such as Binance, Kucoin and more
* Ability to send trades in exchanges such as Binance, Kucoin and more
