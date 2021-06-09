#include <stdlib.h>
#include <math.h>

#include "TL.h"
#include "chart_storage.h"

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern TL_CHART_DATA **g_chart_data;
extern size_t *g_chart_data_length;

TL_STATUS TL_ma(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, double *output)
{
    if (!output)
        return (TL_E_NULL_POINTER);
    if (!period)
        return (TL_E_BAD_MA_PERIOD);
    if (chart < 0 || chart >= g_total_charts_allocated || g_chart[chart] == -1)
        return (TL_E_BAD_CHART);

    unsigned int i = 0;

    for (; i < period - 1 && i < g_chart_data_length[chart]; ++i)
        output[i] = NAN;

    for (; i < g_chart_data_length[chart]; ++i)
    {
        output[i] = 0.0;
        for (int j = i; j >= (int)(i - (period - 1)); --j)
        {
            if (ohlc_type == TL_OPEN)
                output[i] += g_chart_data[chart][j].open;
            if (ohlc_type == TL_HIGH)
                output[i] += g_chart_data[chart][j].high;
            if (ohlc_type == TL_LOW)
                output[i] += g_chart_data[chart][j].low;
            if (ohlc_type == TL_CLOSE)
                output[i] += g_chart_data[chart][j].close;
            if (ohlc_type == TL_VOLUME)
                output[i] += g_chart_data[chart][j].volume;
        }
        output[i] /= (double)period;
    }
    return (TL_SUCCESS);
}