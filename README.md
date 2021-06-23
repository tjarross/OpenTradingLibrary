# OpenTradingLibrary

A C library for your trading analysis

## Features

* Moving Averages (SMA, MA, EMA)

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

### Sample code

```
#include <stdio.h>
#include <stdlib.h>

#include "TL.h"

int main(void)
{
    TL_STATUS status;
    TL_CHART chart;

    int data[] = {45, 12, 36, 75, 89, 0, 4, 8, 9, 50};
    size_t data_length = 10;
    unsigned int ma_period = 4;

    double *output = (double *)malloc(sizeof(double) * data_length);

    // Instantiate the library
    status = TL_init();
    if (status != TL_SUCCESS)
        return (EXIT_FAILURE);

    // Allocate a new chart
    chart = TL_create_chart(data_length, &status);
    if (status == TL_SUCCESS)
    {
        // Add data to the new allocated chart
        status = TL_chart_add_data(chart, data, TL_INT, TL_CLOSE);
        if (status == TL_SUCCESS)
        {
            // Compute the Moving Average
            TL_ma(chart, TL_CLOSE, ma_period, output);

            // Release chart
            TL_release_chart(chart);
        }
    }

    printf("Moving Average of \'data\' is:");
    for (int i = 0; i < data_length; ++i)
        printf(" %.2lf", output[i]);
    printf("\n");

    // Close the library instance
    TL_terminate();
    return (EXIT_SUCCESS);
}
```

The code above computes the moving average of a chart.
Output should be:

`Moving Average of 'data' is: nan nan nan 42.00 53.00 50.00 42.00 25.25 5.25 17.75`

## What's Next ?

* Add other indicators (Exponential moving averages, MACD, Ichimoku...)
* Ability to get charts from exchanges such as Binance, Kucoin and more
* Ability to send trades in exchanges such as Binance, Kucoin and more
