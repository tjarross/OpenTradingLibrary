#ifndef TL_H
#define TL_H

#include "chart_storage.h"

#define BATCH_CHART 128

typedef enum e_TL_STATUS
{
    TL_SUCCESS = 0,
    TL_E_NULL_POINTER = 1,
    TL_E_BAD_CHART_LENGTH = 2,
    TL_E_BAD_CHART = 3,
    TL_E_MALLOC_FAIL = 4,
    TL_W_LIB_ALREADY_INIT = 5,
    TL_E_BAD_OHLC_TYPE = 6,
    TL_E_BAD_DATA_TYPE = 7,
    TL_E_LIB_NOT_INITIALIZED = 8,
    TL_E_BAD_MA_PERIOD = 9,
    TL_E_BAD_OFFSET = 10,
} TL_STATUS;

typedef int TL_CHART;

TL_STATUS TL_init(void);
TL_CHART TL_create_chart(unsigned int length, TL_STATUS *status);
void *get_ptr_from_ohlc(TL_CHART chart, TL_OHLC ohlc_type);
TL_STATUS TL_chart_add_data(TL_CHART chart, const void *data, TL_DATA_TYPE data_type, TL_OHLC ohlc_type);
TL_STATUS TL_release_chart(TL_CHART chart);
void TL_terminate(void);

TL_STATUS TL_ma(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, double *output);
TL_STATUS TL_average(const double *array, unsigned int length, double *output);
TL_STATUS TL_ema(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, unsigned int smoothing, double *output);

#endif
