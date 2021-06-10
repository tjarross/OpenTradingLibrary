#ifndef TEST_H
#define TEST_H

#include "TL.h"

int test_TL_init(void);
int test_TL_terminate(void);
int test_TL_create_chart(TL_STATUS *status);
int test_TL_release_chart(TL_STATUS *status);

#endif