#include "ta_lib.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    TL_STATUS status;
    TL_CHART cchart;
    int chart[] =
        {
            0,
            1,
            2,
            3,
            4,
            5,
            6,
            7,
            8,
            9,
        };
    double *out = malloc(sizeof(double) * 10);

    if (TL_SUCCESS != TL_init())
        return (EXIT_FAILURE);

    cchart = TL_create_chart(10, TL_INT, &status);
    if (status)
        return (EXIT_FAILURE);
    status = TL_chart_add_data(cchart, chart, TL_CLOSE);
    if (status)
        return (EXIT_FAILURE);

    status = TL_ma(cchart, TL_CLOSE, 3, out);
    if (status)
        return (EXIT_FAILURE);

    for (int i = 0; i < 10; ++i)
    {
        printf("%lf, ", out[i]);
    }
    printf("\n");

    TL_terminate();
    return (EXIT_SUCCESS);
}