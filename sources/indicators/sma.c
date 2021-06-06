#include "ta_lib.h"

TL_STATUS TL_sma(const double *array, unsigned int length, double *output)
{
    if (!array || !output)
        return (TL_E_NULL_POINTER);
    if (!length)
        return (TL_E_BAD_CHART_LENGTH);

    double total = 0.;
    for (unsigned int i = 0; i < length; ++i)
        total += array[i];
    *output = total / (double)length;

    return (TL_SUCCESS);
}
