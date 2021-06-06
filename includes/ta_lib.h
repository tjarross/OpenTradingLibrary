#ifndef TA_LIB_H
#define TA_LIB_H

#include <stdlib.h>

#include "chart_storage.h"

typedef enum e_TL_STATUS
{
    TL_SUCCESS = 0,
    TL_E_NULL_BUFFER = 1,
    TL_E_BAD_ELEM_SIZE = 2,
    TL_E_BAD_CHART_LENGTH = 3,
    TL_E_BAD_CHART = 4,
    TL_E_MALLOC_FAIL = 5,
    TL_W_LIB_ALREADY_INIT = 6,
    TL_E_BAD_OHLC_TYPE = 7,
    TL_E_BAD_DATA_TYPE = 8,
    TL_E_LIB_NOT_INITIALIZED = 9,
    TL_E_BAD_MA_PERIOD = 10,
} TL_STATUS;

typedef int TL_CHART;

TL_STATUS TL_init(void);
TL_CHART TL_create_chart(size_t length, TL_DATA_TYPE data_type, TL_STATUS *err);
TL_STATUS TL_chart_add_data(TL_CHART chart, const void *data, TL_OHLC ohlc_type);
TL_STATUS TL_release_chart(TL_CHART chart);
void TL_terminate(void);

TL_STATUS TL_ma(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, double *output);

#endif