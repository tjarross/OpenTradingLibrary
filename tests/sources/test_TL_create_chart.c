#include "TL.h"

#include <limits.h>

extern int g_total_charts_allocated;
extern TL_CHART *g_chart;
extern TL_CHART_DATA *g_chart_data;
extern unsigned int *g_chart_data_length;

static int is_valid_data(TL_CHART_DATA data)
{
    return (data.open != NULL && data.high != NULL && data.low != NULL && data.close != NULL && data.volume != NULL);
}

int test_TL_create_chart(TL_STATUS *status)
{
    TL_CHART chart;
    *status = TL_SUCCESS;

    // Lib not init + no status returned
    chart = TL_create_chart(10, NULL);
    if (chart != -1)
        return (1);

    // Lib not init + status returned
    chart = TL_create_chart(10, status);
    if (chart != -1 || *status != TL_E_LIB_NOT_INITIALIZED)
        return (2);

    // Lib not init + no size
    chart = TL_create_chart(0, status);
    if (chart != -1 || *status != TL_E_LIB_NOT_INITIALIZED)
        return (3);

    TL_init();

    // no size
    chart = TL_create_chart(0, status);
    if (chart != -1 || *status != TL_E_BAD_CHART_LENGTH)
        return (4);

    // Normal use
    chart = TL_create_chart(10, status);
    if (chart != 0 || *status != TL_SUCCESS)
        return (5);
    if (g_chart[0] == -1 || is_valid_data(g_chart_data[0]) != 1 || g_chart_data_length[0] != 10)
        return (6);

    // Normal use 2nd chart
    chart = TL_create_chart(15, status);
    if (chart != 1 || *status != TL_SUCCESS)
        return (7);
    if (g_chart[0] != 1 || is_valid_data(g_chart_data[0]) != 1 || g_chart_data_length[0] != 10)
        return (8);
    if (g_chart[1] != 2 || is_valid_data(g_chart_data[1]) != 1 || g_chart_data_length[1] != 15)
        return (9);

    TL_release_chart(1);

    // Normal use 2nd chart after release
    chart = TL_create_chart(5, status);
    if (chart != 1 || *status != TL_SUCCESS)
        return (10);
    if (g_chart[0] != 1 || is_valid_data(g_chart_data[0]) != 1 || g_chart_data_length[0] != 10)
        return (11);
    if (g_chart[1] != 3 || is_valid_data(g_chart_data[1]) != 1 || g_chart_data_length[1] != 5)
        return (12);

    TL_release_chart(0);

    // Normal use 2nd chart after release
    chart = TL_create_chart(7, status);
    if (chart != 0 || *status != TL_SUCCESS)
        return (13);
    if (g_chart[0] != 4 || is_valid_data(g_chart_data[0]) != 1 || g_chart_data_length[0] != 7)
        return (14);
    if (g_chart[1] != 3 || is_valid_data(g_chart_data[1]) != 1 || g_chart_data_length[1] != 5)
        return (15);

    TL_release_chart(1);
    TL_release_chart(0);

    // Charge tests
    for (int i = 0; i < BATCH_CHART; ++i)
        TL_create_chart(1, NULL);
    if (g_total_charts_allocated != BATCH_CHART)
        return (16);
    TL_create_chart(1, NULL);
    if (g_total_charts_allocated != 2 * BATCH_CHART)
        return (17);

    // Test indexes after re-init
    TL_terminate();
    TL_init();
    chart = TL_create_chart(1, NULL);
    if (chart != 1 && g_chart[0] != 1)
        return (18);

    TL_terminate();
    return (0);
}