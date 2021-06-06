#ifndef CHART_STORAGE_H
#define CHART_STORAGE_H

typedef enum e_TL_OHLC
{
    TL_NO_OHLC = 0,

    TL_OPEN = 1,
    TL_HIGH = 2,
    TL_LOW = 3,
    TL_CLOSE = 4,
    TL_VOLUME = 5,

    TL_OHLC_MAX,
} TL_OHLC;

typedef enum e_TL_DATA_TYPE
{
    TL_NO_DATA_TYPE = 0,

    TL_BYTE = 1,
    TL_UNSIGNED_BYTE = 2,

    TL_SHORT = 3,
    TL_UNSIGNED_SHORT = 4,

    TL_INT = 5,
    TL_UNSIGNED_INT = 6,

    TL_LONG = 7,
    TL_UNSIGNED_LONG = 8,

    TL_FLOAT = 9,
    TL_DOUBLE = 10,

    TL_DATA_TYPE_MAX,
} TL_DATA_TYPE;

typedef struct s_TL_CHART_DATA
{
    double open;
    double high;
    double low;
    double close;
    double volume;
} TL_CHART_DATA;

#endif