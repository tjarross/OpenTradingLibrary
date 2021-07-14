#include "TL.h"

#include <math.h>

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern unsigned int *g_chart_data_length;

TL_STATUS TL_obv(TL_CHART chart, TL_OHLC ohlc_type, double *output)
{
    if (!output)
        return (TL_E_NULL_POINTER);
    if (chart < 0 || chart >= g_total_charts_allocated || g_chart[chart] == -1)
        return (TL_E_BAD_CHART);
    if (ohlc_type <= TL_NO_OHLC || ohlc_type >= TL_OHLC_MAX)
        return (TL_E_BAD_OHLC_TYPE);
    double *ohlc_ptr = get_ptr_from_ohlc(chart, ohlc_type);
    double *volume = get_ptr_from_ohlc(chart, TL_VOLUME);

    output[0] = 0;
    for (unsigned int i = 1; i < g_chart_data_length[chart]; ++i)
    {
        if (ohlc_ptr[i] > ohlc_ptr[i - 1])
            output[i] = output[i - 1] + volume[i];
        else if (ohlc_ptr[i] < ohlc_ptr[i - 1])
            output[i] = output[i - 1] - volume[i];
    }
    output[0] = NAN;
    return (TL_SUCCESS);
}