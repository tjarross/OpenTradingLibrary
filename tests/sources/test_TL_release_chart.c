#include "TL.h"

#include <stdlib.h>

extern TL_CHART *g_chart;

int test_TL_release_chart(TL_STATUS *status)
{
    // Lib not init
    *status = TL_release_chart(0);
    if (*status != TL_E_LIB_NOT_INITIALIZED)
        return (1);

    TL_init();

    *status = TL_release_chart(1);
    if (*status != TL_SUCCESS)
        return (2);
    if (g_chart[1] != -1)
        return (3);

    TL_create_chart(10, NULL);

    *status = TL_release_chart(1);
    if (*status != TL_SUCCESS)
        return (4);
    if (g_chart[1] != -1)
        return (5);

    *status = TL_release_chart(0);
    if (*status != TL_SUCCESS)
        return (6);
    if (g_chart[0] != -1)
        return (7);

    TL_create_chart(10, NULL);
    TL_create_chart(10, NULL);
    TL_create_chart(10, NULL);
    TL_create_chart(10, NULL);

    *status = TL_release_chart(2);
    if (*status != TL_SUCCESS)
        return (8);
    if (g_chart[0] != 2 && g_chart[1] != 3 && g_chart[2] != -1 && g_chart[3] != 5)
        return (9);

    TL_terminate();
    return (0);
}