#include "tests.h"

#include "TL.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;
    TL_STATUS status;

    result = test_TL_init();
    printf("test_TL_init(): %s (%d)\n", (result == 0 ? "OK" : "NOK"), result);
    TL_terminate();

    result = test_TL_terminate();
    printf("test_TL_terminate(): %s (%d)\n", (result == 0 ? "OK" : "NOK"), result);
    TL_terminate();

    result = test_TL_create_chart(&status);
    printf("test_TL_create_chart(): %s (%d)\n", (result == 0 ? "OK" : "NOK"), result);
    TL_terminate();

    result = test_TL_chart_add_data(&status);
    printf("test_TL_chart_add_data(): %s (%d)\n", (result == 0 ? "OK" : "NOK"), result);
    TL_terminate();

    result = test_TL_release_chart(&status);
    printf("test_TL_release_chart(): %s (%d)\n", (result == 0 ? "OK" : "NOK"), result);
    TL_terminate();
    return (EXIT_SUCCESS);
}