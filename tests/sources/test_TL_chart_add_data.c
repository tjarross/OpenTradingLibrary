#include "TL.h"

#include <limits.h>
#include <string.h>

#define NB_ELEM(x) (sizeof((x)) / sizeof(*(x)))

extern TL_CHART_DATA **g_chart_data;

int test_TL_chart_add_data(TL_STATUS *status)
{
    TL_CHART chart = 0;
    TL_CHART double_chart = 0;
    int odata[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int hdata[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int ldata[] = {9, 8, 6, 5, 3, 2, 1, 4, 7, 0};
    int cdata[] = {7, 6, 1, 9, 4, 3, 2, 5, 8, 0};
    int vdata[] = {0, 1, 4, 7, 2, 5, 8, 9, 6, 3};
    double double_data[] = {15.5, 16.17, 8.63, 4.7};

    *status = TL_chart_add_data(0, 0, 0, 0);
    if (*status != TL_E_LIB_NOT_INITIALIZED)
        return (1);
    *status = TL_chart_add_data(chart, cdata, TL_INT, TL_CLOSE);
    if (*status != TL_E_LIB_NOT_INITIALIZED)
        return (2);

    TL_init();

    // Chart not created
    *status = TL_chart_add_data(chart, cdata, TL_INT, TL_CLOSE);
    if (*status != TL_E_BAD_CHART)
        return (3);

    // Bad parameters
    chart = TL_create_chart(10, NULL);
    *status = TL_chart_add_data(chart, NULL, TL_INT, TL_CLOSE);
    if (*status != TL_E_NULL_POINTER)
        return (4);
    *status = TL_chart_add_data(chart, cdata, -1, TL_CLOSE);
    if (*status != TL_E_BAD_DATA_TYPE)
        return (5);
    *status = TL_chart_add_data(chart, cdata, INT_MAX, TL_CLOSE);
    if (*status != TL_E_BAD_DATA_TYPE)
        return (6);
    *status = TL_chart_add_data(chart, cdata, TL_INT, -1);
    if (*status != TL_E_BAD_OHLC_TYPE)
        return (7);
    *status = TL_chart_add_data(chart, cdata, TL_INT, INT_MAX);
    if (*status != TL_E_BAD_OHLC_TYPE)
        return (8);

    // Integer test OHLC
    chart = TL_create_chart(NB_ELEM(odata), NULL);
    *status = TL_chart_add_data(chart, odata, TL_INT, TL_OPEN);
    if (*status != TL_SUCCESS)
        return (9);
    for (size_t i = 0; i < NB_ELEM(odata); ++i)
        if (g_chart_data[chart][i].open != odata[i])
            return (10);
    *status = TL_chart_add_data(chart, hdata, TL_INT, TL_HIGH);
    if (*status != TL_SUCCESS)
        return (11);
    for (size_t i = 0; i < NB_ELEM(hdata); ++i)
        if (g_chart_data[chart][i].high != hdata[i])
            return (12);
    *status = TL_chart_add_data(chart, ldata, TL_INT, TL_LOW);
    if (*status != TL_SUCCESS)
        return (13);
    for (size_t i = 0; i < NB_ELEM(ldata); ++i)
        if (g_chart_data[chart][i].low != ldata[i])
            return (14);
    *status = TL_chart_add_data(chart, cdata, TL_INT, TL_CLOSE);
    if (*status != TL_SUCCESS)
        return (15);
    for (size_t i = 0; i < NB_ELEM(cdata); ++i)
        if (g_chart_data[chart][i].close != cdata[i])
            return (16);
    *status = TL_chart_add_data(chart, vdata, TL_INT, TL_VOLUME);
    if (*status != TL_SUCCESS)
        return (15);
    for (size_t i = 0; i < NB_ELEM(vdata); ++i)
        if (g_chart_data[chart][i].volume != vdata[i])
            return (17);

    // Decimal test
    double_chart = TL_create_chart(NB_ELEM(double_data), NULL);
    *status = TL_chart_add_data(double_chart, double_data, TL_DOUBLE, TL_CLOSE);
    if (*status != TL_SUCCESS)
        return (18);
    for (size_t i = 0; i < NB_ELEM(double_data); ++i)
        if (g_chart_data[double_chart][i].close != double_data[i])
            return (19);

    // Replacing data in chart
    int new_data[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    TL_CHART_DATA *p = g_chart_data[chart];
    *status = TL_chart_add_data(chart, new_data, TL_INT, TL_CLOSE);
    if (*status != TL_SUCCESS)
        return (20);
    if (p != g_chart_data[chart])
        return (21);
    for (size_t i = 0; i < NB_ELEM(cdata); ++i)
        if (g_chart_data[chart][i].close != new_data[i])
            return (22);

    TL_terminate();
    return (0);
}