#include "TL.h"

#include <math.h>

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern unsigned int *g_chart_data_length;

TL_STATUS TL_ema(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, unsigned int smoothing, double *output)
{
    if (!output)
        return (TL_E_NULL_POINTER);
    if (!period)
        return (TL_E_BAD_MA_PERIOD);
    if (chart < 0 || chart >= g_total_charts_allocated || g_chart[chart] == -1)
        return (TL_E_BAD_CHART);

    unsigned int length = g_chart_data_length[chart];
    double *ohlc_ptr = get_ptr_from_ohlc(chart, ohlc_type);

    if (period == 0)
        return (TL_E_BAD_MA_PERIOD);

    if (length < period)
    {
        for (unsigned int i = 0; i < length; ++i)
            output[i] = NAN;
        return (TL_SUCCESS);
    }

    for (unsigned int i = 0; i < period - 1; ++i)
        output[i] = NAN;

    double weight = smoothing / (double)(1 + period);
    TL_sma(ohlc_ptr, period, output + period - 1);
    for (unsigned int i = period; i < length; ++i)
        output[i] = (ohlc_ptr[i] * weight) + (output[i - 1] * (1 - weight));
    return (TL_SUCCESS);
}