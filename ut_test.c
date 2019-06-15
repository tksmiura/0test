#include "0test.h"

/*
 * test codes
 */
bool test001(void)
{
    return true;
}

bool test002(void)
{
    TEST_ASSERT("check1", false);

    return true;
}

bool test003(void)
{
    TEST_ASSERT("check2", true);

    return true;
}
