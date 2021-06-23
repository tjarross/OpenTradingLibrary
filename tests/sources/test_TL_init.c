#include "TL.h"

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern TL_CHART_DATA *g_chart_data;
extern unsigned int *g_chart_data_length;

int test_TL_init(void)
{
    if (TL_SUCCESS != TL_init())
        return (1);
    if (g_total_charts_allocated != BATCH_CHART)
        return (2);
    if (g_chart == NULL || g_chart_data == NULL || g_chart_data_length == NULL)
        return (3);

    if (TL_W_LIB_ALREADY_INIT != TL_init())
        return (4);
    if (g_total_charts_allocated != BATCH_CHART)
        return (5);
    if (g_chart == NULL || g_chart_data == NULL || g_chart_data_length == NULL)
        return (6);

    TL_terminate();

    if (TL_SUCCESS != TL_init())
        return (7);
    if (g_total_charts_allocated != BATCH_CHART)
        return (8);
    if (g_chart == NULL || g_chart_data == NULL || g_chart_data_length == NULL)
        return (9);

    if (TL_W_LIB_ALREADY_INIT != TL_init())
        return (10);
    if (g_total_charts_allocated != BATCH_CHART)
        return (11);
    if (g_chart == NULL || g_chart_data == NULL || g_chart_data_length == NULL)
        return (12);

    TL_terminate();
    return (0);
}