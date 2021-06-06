#include "ta_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    TL_STATUS status;
    TL_CHART chart;
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t data_length = sizeof(data) / sizeof(*data);
    double *out = malloc(sizeof(double) * data_length);

    if (TL_SUCCESS != TL_init())
        return (EXIT_FAILURE);

    chart = TL_create_chart(data_length, TL_DOUBLE, &status);
    status = TL_chart_add_data(chart, data, TL_CLOSE);
    status = TL_ma(chart, TL_CLOSE, data_length, out);

    for (int i = 0; i < data_length; ++i)
        printf("%lf, ", out[i]);
    printf("\n");

    TL_release_chart(chart);
    TL_terminate();
    return (EXIT_SUCCESS);
}