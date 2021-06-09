#include "ta_lib.h"

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern TL_CHART_DATA **g_chart_data;
extern size_t *g_chart_data_length;

int test_TL_terminate(void)
{
    TL_terminate();
    if (g_chart != NULL || g_chart_data != NULL || g_chart_data_length != NULL)
        return (1);
    if (g_total_charts_allocated != 0)
        return (2);

    TL_init();
    TL_terminate();
    if (g_chart != NULL || g_chart_data != NULL || g_chart_data_length != NULL)
        return (1);
    if (g_total_charts_allocated != 0)
        return (2);

    TL_terminate();
    if (g_chart != NULL || g_chart_data != NULL || g_chart_data_length != NULL)
        return (3);
    if (g_total_charts_allocated != 0)
        return (4);
    return (0);
}