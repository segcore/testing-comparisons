#include "testing.h"

int main(int argc, const char **argv)
{
    tests_arg_parse(&argc, &argv);

    TEST_EQI(1, 1);

    return tests_end();
}
