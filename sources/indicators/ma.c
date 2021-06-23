#include <stdlib.h>
#include <math.h>

#include "TL.h"
#include "chart_storage.h"

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern unsigned int *g_chart_data_length;

TL_STATUS TL_ma(TL_CHART chart, TL_OHLC ohlc_type, unsigned int period, double *output)
{
    if (!output)
        return (TL_E_NULL_POINTER);
    if (!period)
        return (TL_E_BAD_MA_PERIOD);
    if (chart < 0 || chart >= g_total_charts_allocated || g_chart[chart] == -1)
        return (TL_E_BAD_CHART);

    unsigned int i = 0;
    double *ohlc_ptr = get_ptr_from_ohlc(chart, ohlc_type);

    for (; i < period - 1 && i < g_chart_data_length[chart]; ++i)
        output[i] = NAN;

    for (; i < g_chart_data_length[chart]; ++i)
    {
        output[i] = 0.0;
        for (int j = i; j >= (int)(i - (period - 1)); --j)
        {
            output[i] += ohlc_ptr[j];
        }
        output[i] /= (double)period;
    }
    return (TL_SUCCESS);
}