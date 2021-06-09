#include "TL.h"
#include "chart_storage.h"

#include <assert.h>
#include <stdlib.h>

static int g_init = 0;
static int g_last_chart_nb = 0;
int g_total_charts_allocated = 0;
TL_CHART *g_chart = NULL;
TL_CHART_DATA **g_chart_data = NULL;
size_t *g_chart_data_length = NULL;

static void realloc_charts(int new_length)
{
    assert(new_length);
    // Realloc charts
    assert((g_chart = realloc(g_chart, sizeof(*g_chart) * new_length)));
    assert((g_chart_data = realloc(g_chart_data, sizeof(*g_chart_data) * new_length)));
    assert((g_chart_data_length = realloc(g_chart_data_length, sizeof(*g_chart_data_length) * new_length)));

    // Init to default values if new allocations
    if (new_length > g_total_charts_allocated)
    {
        for (int i = g_total_charts_allocated; i < new_length; ++i)
        {
            g_chart[i] = -1;
            g_chart_data[i] = NULL;
            g_chart_data_length[i] = 0;
        }
    }

    g_total_charts_allocated = new_length;
}

void TL_terminate(void)
{
    if (g_init == 0)
        return;

    // Charts indexes
    free(g_chart);
    g_chart = NULL;

    // Charts lengths
    free(g_chart_data_length);
    g_chart_data_length = NULL;

    // Charts data
    for (int i = 0; i < g_total_charts_allocated; ++i)
        free(g_chart_data[i]);
    free(g_chart_data);
    g_chart_data = NULL;

    g_total_charts_allocated = 0;

    g_init = 0;
}

TL_STATUS TL_init(void)
{
    if (g_init)
        return (TL_W_LIB_ALREADY_INIT);

    g_last_chart_nb = 0;
    g_total_charts_allocated = BATCH_CHART;

    // Charts indexes
    if (NULL == (g_chart = (TL_CHART *)malloc(sizeof(*g_chart) * g_total_charts_allocated)))
        return (TL_E_MALLOC_FAIL);

    // Charts lengths
    if (NULL == (g_chart_data_length = (size_t *)malloc(sizeof(*g_chart_data_length) * g_total_charts_allocated)))
    {
        free(g_chart);
        g_chart = NULL;
        return (TL_E_MALLOC_FAIL);
    }

    // Charts data
    if (NULL == (g_chart_data = (TL_CHART_DATA **)malloc(sizeof(*g_chart_data) * g_total_charts_allocated)))
    {
        free(g_chart);
        g_chart = NULL;
        free(g_chart_data_length);
        g_chart_data_length = NULL;
        return (TL_E_MALLOC_FAIL);
    }

    // Init default values
    for (int i = 0; i < g_total_charts_allocated; ++i)
    {
        g_chart[i] = -1;
        g_chart_data[i] = NULL;
        g_chart_data_length[i] = 0;
    }

    g_init = 1;
    return (TL_SUCCESS);
}

static double extract_value(const void *data, unsigned int index, TL_DATA_TYPE data_type)
{
    if (data_type == TL_BYTE)
        return (((char *)data)[index]);
    if (data_type == TL_UNSIGNED_BYTE)
        return (((unsigned char *)data)[index]);
    if (data_type == TL_SHORT)
        return (((short *)data)[index]);
    if (data_type == TL_UNSIGNED_SHORT)
        return (((unsigned short *)data)[index]);
    if (data_type == TL_INT)
        return (((int *)data)[index]);
    if (data_type == TL_UNSIGNED_INT)
        return (((unsigned int *)data)[index]);
    if (data_type == TL_LONG)
        return (((long *)data)[index]);
    if (data_type == TL_UNSIGNED_LONG)
        return (((unsigned long *)data)[index]);
    if (data_type == TL_FLOAT)
        return (((float *)data)[index]);
    if (data_type == TL_DOUBLE)
        return (((double *)data)[index]);

    assert(0);
}

// TODO: handling chart offset parameter
TL_STATUS TL_chart_add_data(TL_CHART chart, const void *data, TL_DATA_TYPE data_type, TL_OHLC ohlc_type)
{
    if (g_init == 0)
        return (TL_E_LIB_NOT_INITIALIZED);

    TL_STATUS status = TL_SUCCESS;

    if (chart < 0 || chart >= g_total_charts_allocated)
        status = TL_E_BAD_CHART;
    if (g_chart[chart] == -1)
        status = TL_E_BAD_CHART;
    if (!data)
        status = TL_E_NULL_POINTER;
    if (ohlc_type <= TL_NO_OHLC || ohlc_type >= TL_OHLC_MAX)
        status = TL_E_BAD_OHLC_TYPE;
    if (data_type <= TL_NO_DATA_TYPE || data_type >= TL_DATA_TYPE_MAX)
        status = TL_E_BAD_DATA_TYPE;

    if (status != TL_SUCCESS)
        return (status);

    if (NULL == (g_chart_data[chart] = (TL_CHART_DATA *)malloc(sizeof(**g_chart_data) * g_chart_data_length[chart])))
        return (TL_E_MALLOC_FAIL);

    for (unsigned int i = 0; i < g_chart_data_length[chart]; ++i)
    {
        if (ohlc_type == TL_OPEN)
            g_chart_data[chart][i].open = extract_value(data, i, data_type);
        if (ohlc_type == TL_HIGH)
            g_chart_data[chart][i].high = extract_value(data, i, data_type);
        if (ohlc_type == TL_LOW)
            g_chart_data[chart][i].low = extract_value(data, i, data_type);
        if (ohlc_type == TL_CLOSE)
            g_chart_data[chart][i].close = extract_value(data, i, data_type);
        if (ohlc_type == TL_VOLUME)
            g_chart_data[chart][i].volume = extract_value(data, i, data_type);
    }
    return (TL_SUCCESS);
}

TL_CHART TL_create_chart(size_t length, TL_STATUS *status)
{
    if (g_init == 0)
    {
        if (status)
            *status = TL_E_LIB_NOT_INITIALIZED;
        return (-1);
    }

    TL_STATUS err = TL_SUCCESS;

    // Checks
    if (!length)
        err = TL_E_BAD_CHART_LENGTH;

    if (err != TL_SUCCESS)
    {
        if (status)
            *status = err;
        return (-1);
    }

    // Getting the first free slot
    int free_index = 0;
    while (g_chart[free_index] != -1 && free_index < g_total_charts_allocated)
        ++free_index;

    // If no free slot realloc internal chart slots
    if (free_index == g_total_charts_allocated)
        realloc_charts(g_total_charts_allocated + BATCH_CHART);

    // Creating new chart and allocating if necessary
    if (length > g_chart_data_length[free_index])
        assert((g_chart_data[free_index] = realloc(g_chart_data[free_index], sizeof(**g_chart_data) * length)));
    g_chart_data_length[free_index] = length;
    g_chart[free_index] = ++g_last_chart_nb;

    if (status)
        *status = TL_SUCCESS;
    return (free_index);
}

TL_STATUS TL_release_chart(TL_CHART chart)
{
    if (g_init == 0)
        return (TL_E_LIB_NOT_INITIALIZED);
    if (chart < 0 && chart < g_total_charts_allocated)
        return (TL_E_BAD_CHART);

    g_chart[chart] = -1;

    return (TL_SUCCESS);
}